//go:build OMIT

package main

import (
	"fmt"
	"go/ast"
	"go/types"

	"golang.org/x/tools/go/packages"
)

func main() {
	cfg := &packages.Config{
		Mode: packages.NeedName | packages.NeedFiles | packages.NeedSyntax |
			packages.NeedTypes | packages.NeedTypesInfo | packages.NeedImports | packages.NeedDeps,
	}
	pkgs, err := packages.Load(cfg, "image")
	if err != nil {
		panic(err)
	}

	for _, pkg := range pkgs {
		info := pkg.TypesInfo
		for _, file := range pkg.Syntax {
			ast.Inspect(file, func(n ast.Node) bool {
				fd, ok := n.(*ast.FuncDecl)
				if !ok || fd.Body == nil || fd.Type.Results == nil {
					return true
				}
				resultTypes := flatten(info, fd.Type.Results)

				ast.Inspect(fd.Body, func(n ast.Node) bool {
					ret, ok := n.(*ast.ReturnStmt)
					if !ok {
						return true
					}
					for i, expr := range ret.Results {
						if i >= len(resultTypes) {
							break
						}
						dst := resultTypes[i]
						iface, ok := dst.Underlying().(*types.Interface)
						if !ok {
							continue // target isn't an interface, skip
						}
						src := info.TypeOf(expr)
						if src == nil || types.Identical(src, dst) {
							continue // nothing being converted
						}
						if !types.AssignableTo(src, dst) {
							continue
						}

						if have := singleParamInterface(fd, info); have != nil {
							pos := pkg.Fset.Position(expr.Pos())
							fmt.Printf("%s: %s -> %s\n", pos, src, dst)
							for _, m := range missingMethods(have, iface) {
								fmt.Printf("    requires: %s\n", m)
							}
						}
					}
					return true
				})
				return false
			})
		}
	}
}

func flatten(info *types.Info, fl *ast.FieldList) []types.Type {
	var out []types.Type
	for _, f := range fl.List {
		t := info.TypeOf(f.Type)
		n := len(f.Names)
		if n == 0 {
			n = 1
		}
		for i := 0; i < n; i++ {
			out = append(out, t)
		}
	}
	return out
}

func singleParamInterface(fd *ast.FuncDecl, info *types.Info) *types.Interface {
	if fd.Type.Params == nil || len(fd.Type.Params.List) != 1 {
		return nil
	}
	f := fd.Type.Params.List[0]
	if len(f.Names) > 1 {
		return nil
	}
	iface, _ := info.TypeOf(f.Type).Underlying().(*types.Interface)
	return iface
}

// missingMethods returns methods `want` requires that `have` doesn't already
// provide — i.e. the "gap" that must be filled for the conversion to happen.
func missingMethods(have, want *types.Interface) []string {
	var missing []string
	for i := 0; i < want.NumMethods(); i++ {
		m := want.Method(i)
		found := false
		for j := 0; j < have.NumMethods(); j++ {
			hm := have.Method(j)
			if hm.Name() == m.Name() && types.Identical(hm.Type(), m.Type()) {
				found = true
				break
			}
		}
		if !found {
			missing = append(missing, m.Name())
		}
	}
	return missing
}
