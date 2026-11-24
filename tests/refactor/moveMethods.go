package main

import (
	"flag"
	"fmt"
	"go/ast"
	"go/token"
	"go/types"
	"os"
	"sort"

	"golang.org/x/tools/go/packages"
)

type cand struct {
	decl *ast.FuncDecl
	fn   *types.Func
	recv *types.Var // nil when the receiver is unnamed or "_"
	id   *ast.Ident // the `cppConverter` identifier in the receiver type
}

type edit struct {
	start, end int
	text       string
}

func main() {
	dir := flag.String("dir", ".", "module directory")
	pattern := flag.String("pkg", "./cmd", "package to rewrite")
	from := flag.String("from", "cppConverter", "current receiver type")
	to := flag.String("to", "parsingInfos", "target receiver type")
	write := flag.Bool("w", false, "write files (default: dry run)")
	flag.Parse()

	cfg := &packages.Config{
		Dir: *dir,
		Mode: packages.NeedName | packages.NeedFiles | packages.NeedSyntax |
			packages.NeedTypes | packages.NeedTypesInfo,
	}
	pkgs, err := packages.Load(cfg, *pattern)
	if err != nil || packages.PrintErrors(pkgs) > 0 || len(pkgs) != 1 {
		fmt.Fprintln(os.Stderr, "load failed", err)
		os.Exit(1)
	}
	pkg := pkgs[0]
	info := pkg.TypesInfo

	fromObj, _ := pkg.Types.Scope().Lookup(*from).(*types.TypeName)
	toObj, _ := pkg.Types.Scope().Lookup(*to).(*types.TypeName)
	if fromObj == nil || toObj == nil {
		fmt.Fprintln(os.Stderr, "type not found")
		os.Exit(1)
	}
	toPtr := types.NewPointer(toObj.Type())

	// 1. Collect candidates: `func (x *from) M(...)`.
	cands := map[*types.Func]*cand{}
	for _, f := range pkg.Syntax {
		for _, d := range f.Decls {
			fd, ok := d.(*ast.FuncDecl)
			if !ok || fd.Recv == nil || len(fd.Recv.List) != 1 || fd.Body == nil {
				continue
			}
			star, ok := fd.Recv.List[0].Type.(*ast.StarExpr)
			if !ok {
				continue
			}
			id, ok := star.X.(*ast.Ident)
			if !ok || info.Uses[id] != fromObj {
				continue
			}
			c := &cand{decl: fd, fn: info.Defs[fd.Name].(*types.Func), id: id}
			if names := fd.Recv.List[0].Names; len(names) == 1 && names[0].Name != "_" {
				c.recv, _ = info.Defs[names[0]].(*types.Var)
			}
			// Name already provided by the target (own or promoted)?
			if obj, _, _ := types.LookupFieldOrMethod(toPtr, true, pkg.Types, fd.Name.Name); obj != nil {
				fmt.Printf("skip %-40s name already exists on %s\n", fd.Name.Name, *to)
				continue
			}
			cands[c.fn] = c
		}
	}

	// 2. Does every use of the receiver resolve identically on the target?
	usable := func(c *cand) bool {
		if c.recv == nil {
			return true
		}
		ok := true
		handled := map[*ast.Ident]bool{}
		ast.Inspect(c.decl.Body, func(n ast.Node) bool {
			switch n := n.(type) {
			case *ast.SelectorExpr:
				id, isId := n.X.(*ast.Ident)
				if !isId || info.Uses[id] != c.recv {
					return true
				}
				handled[id] = true
				sel := info.Selections[n]
				if sel == nil {
					ok = false
					return false
				}
				obj := sel.Obj()
				if fn, isFn := obj.(*types.Func); isFn {
					if _, inSet := cands[fn]; inSet {
						return true // moves along with us
					}
				}
				if found, _, _ := types.LookupFieldOrMethod(toPtr, true, pkg.Types, obj.Name()); found != obj {
					ok = false
				}
			case *ast.Ident:
				if info.Uses[n] == c.recv && !handled[n] {
					ok = false // bare use of the receiver
				}
			}
			return ok
		})
		return ok
	}

	// 3. Fixed point: drop violators until stable.
	for changed := true; changed; {
		changed = false
		for fn, c := range cands {
			if !usable(c) {
				delete(cands, fn)
				changed = true
			}
		}
	}

	// 4. Edits: replace the receiver type name.
	fset := pkg.Fset
	edits := map[string][]edit{}
	var names []string
	for _, c := range cands {
		p, e := fset.Position(c.id.Pos()), fset.Position(c.id.End())
		edits[p.Filename] = append(edits[p.Filename], edit{p.Offset, e.Offset, *to})
		names = append(names, fmt.Sprintf("%s:%d %s", p.Filename, p.Line, c.fn.Name()))
	}
	sort.Strings(names)
	for _, n := range names {
		fmt.Println("move", n)
	}
	fmt.Printf("%d methods can move from *%s to *%s\n", len(cands), *from, *to)
	if !*write {
		return
	}
	for file, es := range edits {
		src, err := os.ReadFile(file)
		if err != nil {
			panic(err)
		}
		sort.Slice(es, func(i, j int) bool { return es[i].start > es[j].start })
		for _, e := range es {
			src = append(src[:e.start:e.start], append([]byte(e.text), src[e.end:]...)...)
		}
		if err := os.WriteFile(file, src, 0o644); err != nil {
			panic(err)
		}
	}
	_ = token.NoPos
}
