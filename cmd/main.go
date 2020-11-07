package main

import (
	"bufio"
	"container/list"
	"fmt"
	"go/ast"
	"go/parser"
	"go/token"
	"log"
	"os"
	"path"
	"reflect"
	"strings"
)

type typeName struct {
	name    []string
	typeStr string
}
type typeNames []typeName

func (tn typeName) String() string {
	return fmt.Sprintf("%v %v", tn.typeStr, strings.Join(tn.name, "."))
}

func (tns typeNames) String() string {
	var strs []string
	for _, tn := range tns {
		strs = append(strs, tn.String())
	}
	return strings.Join(strs, ", ")
}

type cppVisitor struct {
	inputName string
	outFile   *os.File
	out       *bufio.Writer
	astIndent int
	outIndent int
	nodes     *list.List
}

func (cv *cppVisitor) Indent() string {
	return strings.Repeat("  ", cv.astIndent)
}

func (cv *cppVisitor) OutIndent() string {
	return strings.Repeat("    ", cv.outIndent)
}

const dbgPrefix string = "         "
const rawPrefix string = "//RAW_AST"

func buildHeader(out *bufio.Writer) {
	//temporarily blindly add "includes" and "using"
	fmt.Fprintf(out, "#include <string>\n")
	fmt.Fprintf(out, "#include <iostream>\n")
	fmt.Fprintf(out, "\n")
	fmt.Fprintf(out, "using namespace std;\n")
	fmt.Fprintf(out, "\n")

	//temporary dummy implementations
	fmt.Fprintf(out, "namespace fmt\n")
	fmt.Fprintf(out, "{\n")
	fmt.Fprintf(out, "    void Printf(const string& str)\n")
	fmt.Fprintf(out, "    {\n")
	fmt.Fprintf(out, "        cout << str;\n")
	fmt.Fprintf(out, "    }\n")
	fmt.Fprintf(out, "}\n")
	fmt.Fprintf(out, "\n")
}

// Start reading node
func (cv *cppVisitor) VisitStart(node ast.Node) {
	switch n := node.(type) {
	case *ast.File:
		fmt.Printf("%s %s %v\n", dbgPrefix, cv.Indent(), reflect.TypeOf(n))
		var outName = "out/" + cv.inputName + ".cpp"
		var outDir = path.Dir(outName)

		errDir := os.MkdirAll(outDir, os.ModePerm)
		if errDir != nil {
			log.Fatal(errDir)
		}

		file, err := os.Create(outName)
		cv.outFile = file
		if err != nil {
			log.Fatal(err)
		}

		cv.out = bufio.NewWriter(cv.outFile)

		buildHeader(cv.out)

		//fmt.Printf("%s Name: %v\n", v.Indent(), n.Name)
		//fmt.Printf("%s Scope: %v\n", v.Indent(), n.Scope)
	case *ast.BadDecl:
		fmt.Printf("%s %s %v\n", dbgPrefix, cv.Indent(), reflect.TypeOf(n))

	case *ast.FuncDecl:
		fmt.Printf("%s %s %v\n", dbgPrefix, cv.Indent(), reflect.TypeOf(n))
		fmt.Printf("%s %s  -> Name: %v\n", dbgPrefix, cv.Indent(), n.Name)
		fmt.Printf("%s %s  -> Body: %v\n", dbgPrefix, cv.Indent(), n.Body)
		params := typeNames{}
		for _, field := range n.Type.Params.List {
			var param typeName
			for _, name := range field.Names {
				param.name = append(param.name, name.Name)
			}
			param.typeStr = fmt.Sprintf("%v", field.Type)
			params = append(params, param)
		}

		fmt.Fprintf(cv.out, "void %s(%s)\n", n.Name.Name, params)

	case *ast.BlockStmt:
		fmt.Fprintf(cv.out, "{\n")
		cv.outIndent++

	case *ast.ExprStmt:
		fmt.Fprintf(cv.out, "%s", cv.OutIndent())

	case *ast.CallExpr:
		fmt.Fprintf(cv.out, "%v(", convertExpr(n.Fun))
		var sep = ""
		for _, arg := range n.Args {
			fmt.Fprintf(cv.out, "%s%s", sep, convertExpr(arg))
			sep = ", "
		}
		fmt.Fprintf(cv.out, ")")

	case *ast.BasicLit:

	case *ast.GenDecl:
		fmt.Printf("%s %s %v\n", dbgPrefix, cv.Indent(), reflect.TypeOf(n))
		fmt.Printf("%s %s  -> Specs: %v\n", dbgPrefix, cv.Indent(), n.Specs)
	default:
	}
}

func convertToken(t token.Token) string {
	switch t {
	case token.ADD:
		return "+"
	case token.SUB:
		return "-"
	case token.MUL:
		return "*"
	case token.QUO:
		return "/"
	default:
		return "!!ERROR!!"
	}
}

func convertExpr(node ast.Expr) string {
	switch n := node.(type) {
	case *ast.BasicLit:
		return n.Value
	case *ast.BinaryExpr:
		return convertExpr(n.X) + " " + convertToken(n.Op) + " " + convertExpr(n.Y)
	case *ast.Ident:
		return n.Name
	case *ast.SelectorExpr:
		return convertExpr(n.X) + "::" + convertExpr(n.Sel)
	default:
		//panic(fmt.Sprintf("Unmanaged type in convert %v", n))
		return "!!ERROR!!"
	}
}

// End of node visit
func (cv *cppVisitor) VisitEnd(node ast.Node) {
	switch n := node.(type) {
	case *ast.File:
		//fmt.Printf("\n=====\n")
		//fmt.Printf("%v\n", cv.inputName)
		//fmt.Printf("%v\n", cv.out)
		//fmt.Printf("%v\n", cv.outFile)
		cv.out.Flush()

	case *ast.BadDecl:
		fmt.Printf("%s %s %v\n", dbgPrefix, cv.Indent(), reflect.TypeOf(n))

	case *ast.FuncDecl:
		fmt.Fprintf(cv.out, "\n")

	case *ast.BlockStmt:
		fmt.Fprintf(cv.out, "}\n")
		cv.outIndent--

	case *ast.ExprStmt:
		fmt.Fprintf(cv.out, ";\n")

	case *ast.CallExpr:

	case *ast.BasicLit:

	case *ast.GenDecl:

	default:
	}
}

func (cv *cppVisitor) Visit(node ast.Node) ast.Visitor {
	if node == nil {
		last := cv.nodes.Back()
		cv.nodes.Remove(last)
		cv.astIndent--
		oldnode := last.Value.(ast.Node)
		cv.VisitEnd(oldnode)
		fmt.Printf("%s %s <<%T -> %v\n", rawPrefix, cv.Indent(), oldnode, oldnode)
		return cv
	}

	cv.nodes.PushBack(node)
	fmt.Printf("%s %s >>%T -> %v\n", rawPrefix, cv.Indent(), node, node)

	cv.VisitStart(node)

	cv.astIndent++
	return cv
}

func main() {
	fset := token.NewFileSet()
	var inputName string = "tests/HelloWorld.go"

	f, err := parser.ParseFile(fset, inputName, nil, 0)
	if err != nil {
		fmt.Println(err)
		return
	}

	pkgs, errPkg := parser.ParseDir(fset, "F:/Dev/Golang/src/fmt", nil, 0)
	if errPkg != nil {
		fmt.Println(errPkg)
		return
	}

	ast.Print(fset, f)

	for pkg, v := range pkgs {
		for file := range v.Files {
			fmt.Printf("%v -> %v\n", pkg, file)
		}
	}

	for _, u := range f.Unresolved {
		fmt.Printf("%v unresolved\n", u.Name)
	}

	var cv *cppVisitor = new(cppVisitor)
	cv.inputName = inputName
	cv.nodes = new(list.List)

	fmt.Printf("\n=====\n")
	ast.Walk(cv, f)
}
