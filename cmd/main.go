package main

import (
	"bufio"
	"bytes"
	"container/list"
	"flag"
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

var stdTypeMapping = map[string]string{
	"string": "std::string",
	"int":    "int",
}

type typeName struct {
	name    []string
	typeStr string
}
type typeNames []typeName

func (tn typeName) String() string {
	return fmt.Sprintf("%v %v", stdTypeMapping[tn.typeStr], strings.Join(tn.name, "."))
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

	astIndent int

	makeOutFile *os.File
	makeOut     *bufio.Writer

	cppOutFile *os.File
	cppOut     *bufio.Writer
	cppIndent  int

	hppOutFile *os.File
	hppOut     *bufio.Writer
	hppIndent  int

	nodes *list.List
}

func (cv *cppVisitor) Indent() string {
	return strings.Repeat("  ", cv.astIndent)
}

func (cv *cppVisitor) CppIndent() string {
	return strings.Repeat("    ", cv.cppIndent)
}

const dbgPrefix string = "         "
const rawPrefix string = "//RAW_AST"

func printCppIntro(cv *cppVisitor) {
	//temporarily blindly add "includes" and "using"
	fmt.Fprintf(cv.cppOut, "#include <string>\n")
	fmt.Fprintf(cv.cppOut, "#include <iostream>\n")
	fmt.Fprintf(cv.cppOut, "\n")
	fmt.Fprintf(cv.cppOut, "#include \"%s.h\"\n", cv.inputName)
	fmt.Fprintf(cv.cppOut, "\n")
	fmt.Fprintf(cv.cppOut, "\n")

	//temporary dummy/mock implementations
	fmt.Fprintf(cv.cppOut, "namespace fmt\n")
	fmt.Fprintf(cv.cppOut, "{\n")
	fmt.Fprintf(cv.cppOut, "    // Temporary mock implementations\n")
	fmt.Fprintf(cv.cppOut, "    template<typename T>\n")
	fmt.Fprintf(cv.cppOut, "    void Printf(const T& str)\n")
	fmt.Fprintf(cv.cppOut, "    {\n")
	fmt.Fprintf(cv.cppOut, "        std::cout << str;\n")
	fmt.Fprintf(cv.cppOut, "    }\n")
	fmt.Fprintf(cv.cppOut, "\n")
	fmt.Fprintf(cv.cppOut, "    template<typename T, typename... Args>\n")
	fmt.Fprintf(cv.cppOut, "    void Printf(const T& str, Args&&... args)\n")
	fmt.Fprintf(cv.cppOut, "    {\n")
	fmt.Fprintf(cv.cppOut, "        std::cout << str;\n")
	fmt.Fprintf(cv.cppOut, "        Printf(std::forward<Args>(args)...);\n")
	fmt.Fprintf(cv.cppOut, "    }\n")
	fmt.Fprintf(cv.cppOut, "}\n")
	fmt.Fprintf(cv.cppOut, "\n")

	// Put everything generated in "golang" namespace
	fmt.Fprintf(cv.cppOut, "namespace golang\n")
	fmt.Fprintf(cv.cppOut, "{\n")
	cv.cppIndent++
}

func printCppOutro(cv *cppVisitor) {
	// Close golang namespace
	cv.cppIndent--
	fmt.Fprintf(cv.cppOut, "}\n")
	fmt.Fprintf(cv.cppOut, "\n")

	// TODO: manage main parameters
	fmt.Fprintf(cv.cppOut, "int main()")
	fmt.Fprintf(cv.cppOut, "{\n")
	fmt.Fprintf(cv.cppOut, "    golang::main();\n")
	fmt.Fprintf(cv.cppOut, "    return 0;\n")
	fmt.Fprintf(cv.cppOut, "}\n")
}

func printHppIntro(cv *cppVisitor) {
	//temporarily blindly add "includes" and "using"
	fmt.Fprintf(cv.hppOut, "#pragma once\n")
	fmt.Fprintf(cv.hppOut, "\n")
	fmt.Fprintf(cv.hppOut, "#include <string>\n")
	fmt.Fprintf(cv.hppOut, "\n")

	// Put everything generated in "golang" namespace
	fmt.Fprintf(cv.hppOut, "namespace golang\n")
	fmt.Fprintf(cv.hppOut, "{\n")
	cv.hppIndent++
}

func printHppOutro(cv *cppVisitor) {
	// Close golang namespace
	cv.hppIndent--
	fmt.Fprintf(cv.hppOut, "}\n")
	fmt.Fprintf(cv.hppOut, "\n")
}

func createOutputExt(name string, ext string) *os.File {
	var outName = name + "." + ext
	return createOutput(outName)
}

func createOutput(name string) *os.File {
	var outName = "out/" + name
	var outDir = path.Dir(outName)

	errDir := os.MkdirAll(outDir, os.ModePerm)
	if errDir != nil {
		log.Fatal(errDir)
	}

	file, err := os.Create(outName)
	if err != nil {
		log.Fatal(err)
		panic("cannot create output file")
	}

	return file
}

func (cv *cppVisitor) Init() {
	cv.makeOutFile = createOutput("Makefile")
	cv.makeOut = bufio.NewWriter(cv.makeOutFile)

	fmt.Fprintf(cv.makeOut, "all:\n")
}

func (cv *cppVisitor) cppPrintf(format string, a ...interface{}) (n int, err error) {
	return fmt.Fprintf(cv.cppOut, "%s"+format, append([]interface{}{cv.CppIndent()}, a...)...)
}

// Start reading node
func (cv *cppVisitor) VisitStart(node ast.Node) {
	switch n := node.(type) {
	case *ast.Package:
		//TODO

	case *ast.File:
		fmt.Printf("%s %s %v\n", dbgPrefix, cv.Indent(), reflect.TypeOf(n))

		cv.cppOutFile = createOutputExt(cv.inputName, "cpp")
		cv.cppOut = bufio.NewWriter(cv.cppOutFile)

		cv.hppOutFile = createOutputExt(cv.inputName, "h")
		cv.hppOut = bufio.NewWriter(cv.hppOutFile)

		printCppIntro(cv)
		printHppIntro(cv)

		fmt.Fprintf(cv.makeOut, "\t g++ -I. %s.cpp -o %s.exe\n", cv.inputName, cv.inputName)

		//fmt.Printf("%s Name: %v\n", v.Indent(), n.Name)
		//fmt.Printf("%s Scope: %v\n", v.Indent(), n.Scope)

	case *ast.BadDecl:
		fmt.Printf("%s %s %v\n", dbgPrefix, cv.Indent(), reflect.TypeOf(n))

	case *ast.FuncDecl:
		fmt.Printf("%s %s %v\n", dbgPrefix, cv.Indent(), reflect.TypeOf(n))
		fmt.Printf("%s %s  -> Name: %v\n", dbgPrefix, cv.Indent(), n.Name)
		fmt.Printf("%s %s  -> Body: %v\n", dbgPrefix, cv.Indent(), n.Body)
		params := readFields(n.Type.Params)
		results := readFields(n.Type.Results)
		var resultType string
		switch len(results) {
		case 0:
			resultType = "void"
		case 1:
			resultType = results[0].typeStr
		default:
			panic("multiple return type not managed")
		}

		fmt.Fprintf(cv.cppOut, "%s%s %s(%s)\n", cv.CppIndent(), resultType, n.Name.Name, params)
		fmt.Fprintf(cv.hppOut, "%s%s %s(%s);\n", cv.CppIndent(), resultType, n.Name.Name, params)

	case *ast.BlockStmt:
		fmt.Fprintf(cv.cppOut, "%s{\n", cv.CppIndent())
		cv.cppIndent++

	case *ast.DeclStmt:
		cv.cppPrintf("%s", convertDecl(n.Decl))

	case *ast.ExprStmt:
		fmt.Fprintf(cv.cppOut, "%s%s", cv.CppIndent(), convertExpr(n.X))

	case *ast.ReturnStmt:
		fmt.Fprintf(cv.cppOut, "%sreturn %s;\n", cv.CppIndent(), convertExprs(n.Results))

	case *ast.CallExpr:
	case *ast.BasicLit:
		// Managed recursiveley, not by visitor

	case *ast.GenDecl:
		fmt.Printf("%s %s %v\n", dbgPrefix, cv.Indent(), reflect.TypeOf(n))
		fmt.Printf("%s %s  -> Specs: %v\n", dbgPrefix, cv.Indent(), n.Specs)
	default:
	}
}

func readFields(fields *ast.FieldList) (params typeNames) {
	if fields == nil {
		return
	}

	for _, field := range fields.List {
		var param typeName
		for _, name := range field.Names {
			param.name = append(param.name, name.Name)
		}
		param.typeStr = fmt.Sprintf("%v", field.Type)
		params = append(params, param)
	}
	return
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
		return "!!TOKEN_ERROR!!"
	}
}

func convertDecl(decl ast.Decl) string {
	switch d := decl.(type) {
	case *ast.GenDecl:
		return convertSpecs(d.Specs)

	case *ast.FuncDecl:
		panic("convertDecl[FuncDecl] Not implemented")

	case *ast.BadDecl:
		panic("convertDecl[BadDecl] Not implemented")

	default:
		panic("convertDecl, unknown subtype")
	}
}

func convertSpecs(specs []ast.Spec) string {
	var result string

	for _, spec := range specs {
		switch s := spec.(type) {
		case *ast.TypeSpec:
			result += convertExpr(s.Type) + " " + s.Name.Name + ";\n"

		case *ast.ValueSpec:
			for i := range s.Names {
				result += convertExpr(s.Type) + " " + s.Names[i].Name + " = " + convertExpr(s.Values[i]) + ";\n"
			}

		case *ast.ImportSpec:
			panic("convertSpecs[ImportSpec] Not implemented")

		default:
			panic("convertSpecs, unknown subtype")
		}
	}

	return result
}

func convertExpr(node ast.Expr) string {
	if node == nil {
		return "auto"
	}

	switch n := node.(type) {
	case *ast.BasicLit:
		return n.Value
	case *ast.BinaryExpr:
		return convertExpr(n.X) + " " + convertToken(n.Op) + " " + convertExpr(n.Y)
	case *ast.CallExpr:
		buf := new(bytes.Buffer)
		fmt.Fprintf(buf, "%v(", convertExpr(n.Fun))
		var sep = ""
		for _, arg := range n.Args {
			fmt.Fprintf(buf, "%s%s", sep, convertExpr(arg))
			sep = ", "
		}
		fmt.Fprintf(buf, ")")
		return buf.String()

	case *ast.Ident:
		return n.Name
	case *ast.SelectorExpr:
		return convertExpr(n.X) + "::" + convertExpr(n.Sel)
	default:
		//panic(fmt.Sprintf("Unmanaged type in convert %v", n))
		return fmt.Sprintf("!!EXPR_ERROR!! [%v]", reflect.TypeOf(node))
	}
}

func convertExprs(exprs []ast.Expr) string {
	var strs []string
	for _, expr := range exprs {
		strs = append(strs, convertExpr(expr))
	}
	return strings.Join(strs, ", ")
}

// End of node visit
func (cv *cppVisitor) VisitEnd(node ast.Node) {
	switch n := node.(type) {
	case *ast.File:
		printCppOutro(cv)
		printHppOutro(cv)

		//fmt.Printf("\n=====\n")
		//fmt.Printf("%v\n", cv.inputName)
		//fmt.Printf("%v\n", cv.cppOut)
		//fmt.Printf("%v\n", cv.cppOutFile)
		cv.cppOut.Flush()
		cv.hppOut.Flush()
		cv.makeOut.Flush()

	case *ast.BadDecl:
		fmt.Printf("%s %s %v\n", dbgPrefix, cv.Indent(), reflect.TypeOf(n))

	case *ast.FuncDecl:
		fmt.Fprintf(cv.cppOut, "\n")

	case *ast.BlockStmt:
		cv.cppIndent--
		fmt.Fprintf(cv.cppOut, "%s}\n", cv.CppIndent())

	case *ast.ExprStmt:
		fmt.Fprintf(cv.cppOut, ";\n")

	case *ast.CallExpr:
	case *ast.BasicLit:
		// Managed recursiveley, not by visitor

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

	inputName := flag.String("input", "tests/HelloWorld.go", "The file to parse")
	parseFmtDir := flag.Bool("parseFmt", true, "temporary test parameter")

	flag.Parse()
	fset := token.NewFileSet()

	f, err := parser.ParseFile(fset, *inputName, nil, 0)
	if err != nil {
		fmt.Println(err)
		return
	}

	if *parseFmtDir {
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
	}

	var cv *cppVisitor = new(cppVisitor)
	cv.Init()
	cv.inputName = *inputName
	cv.nodes = new(list.List)

	fmt.Printf("\n=====\n")
	ast.Walk(cv, f)
}
