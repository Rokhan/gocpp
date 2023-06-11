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
	"string":     "std::string",
	"int":        "int",
	"uint64":     "uint64_t",
	"complex128": "gocpp::complex128",
	"float64":    "float",
	"uint":       "unsigned int",
}

var nameSpaces = map[string]struct{}{
	"cmplx":   {},
	"fmt":     {},
	"math":    {},
	"rand":    {},
	"runtime": {},
	"time":    {},
}

var stdFuncMapping = map[string]string{
	// Temporary mappings while 'import' isn't implemented
	"fmt::Print":     "mocklib::Print",
	"fmt::Printf":    "mocklib::Printf",
	"fmt::Println":   "mocklib::Println",
	"fmt::Sprint":    "mocklib::Sprint",
	"fmt::Sprintf":   "mocklib::Sprintf",
	"rand::Intn":     "mocklib::Intn",
	"runtime::GOOS":  "mocklib::GOOS",
	"cmplx::Sqrt":    "std::sqrt",
	"math::Pow":      "std::pow",
	"math::Sqrt":     "std::sqrt",
	"math::Pi":       "M_PI",
	"time::Now":      "mocklib::Date::Now",
	"time::Saturday": "mocklib::Date::Saturday",
	// Predefined functions
	"panic": "gocpp::GoPanic",
	// type conversions
	"float64": "float",
	"uint":    "(unsigned int)",
}

func Panicf(format string, a ...interface{}) {
	msg := fmt.Sprintf(format, a...)
	panic(msg)
}

func GetCppType(goType string) string {
	val, ok := stdTypeMapping[goType]
	if ok {
		return val
	} else {
		return goType
	}
}

func GetCppFunc(goType string) string {
	val, ok := stdFuncMapping[goType]
	if ok {
		return val
	} else {
		return goType
	}
}

type typeName struct {
	names   []string
	typeStr string
}

type typeNames []typeName

func (tn typeName) ParamDecl() []string {
	var strs []string
	for _, name := range tn.names {
		strs = append(strs, fmt.Sprintf("%v %v", stdTypeMapping[tn.typeStr], name))
	}

	return strs
}

func (tns typeNames) String() string {
	var strs []string
	for _, tn := range tns {
		strs = append(strs, tn.ParamDecl()...)
	}
	return strings.Join(strs, ", ")
}

type cppVisitor struct {
	inputName     string
	supportHeader string

	astIndent       int
	currentSwitchId *list.List

	makeOutFile *os.File
	makeOut     *bufio.Writer

	binOutDir  string
	cppOutDir  string
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
	fmt.Fprintf(cv.cppOut, "#include <complex>\n")
	fmt.Fprintf(cv.cppOut, "#include <iostream>\n")
	fmt.Fprintf(cv.cppOut, "#include <string>\n")
	fmt.Fprintf(cv.cppOut, "#include <tuple>\n")
	fmt.Fprintf(cv.cppOut, "\n")
	fmt.Fprintf(cv.cppOut, "#include \"%s.h\"\n", cv.inputName)
	fmt.Fprintf(cv.cppOut, "#include \"%s\"\n", cv.supportHeader)
	fmt.Fprintf(cv.cppOut, "\n")
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
	fmt.Fprintf(cv.hppOut, "#include <tuple>\n")
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

func createOutputExt(outdir, name, ext string) *os.File {
	var outName = name + "." + ext
	return createOutput(outdir, outName)
}

func createOutput(outdir, name string) *os.File {
	var outName = outdir + "/" + name
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
	cv.nodes = new(list.List)
	cv.currentSwitchId = new(list.List)
	cv.makeOutFile = createOutput(cv.cppOutDir, "Makefile")
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

		cv.cppOutFile = createOutputExt(cv.cppOutDir, cv.inputName, "cpp")
		cv.cppOut = bufio.NewWriter(cv.cppOutFile)

		cv.hppOutFile = createOutputExt(cv.cppOutDir, cv.inputName, "h")
		cv.hppOut = bufio.NewWriter(cv.hppOutFile)

		printCppIntro(cv)
		printHppIntro(cv)

		for _, decl := range n.Decls {
			cv.convertDecls(decl)
		}

		fmt.Fprintf(cv.makeOut, "\t g++ -I. -I../includes %s.cpp -o ../%s/%s.exe\n", cv.inputName, cv.binOutDir, cv.inputName)

		//fmt.Printf("%s Name: %v\n", v.Indent(), n.Name)
		//fmt.Printf("%s Scope: %v\n", v.Indent(), n.Scope)

	case *ast.BadDecl:
		fmt.Printf("%s %s %v\n", dbgPrefix, cv.Indent(), reflect.TypeOf(n))

	// Managed recursiveley, not by visitor
	case *ast.FuncDecl:
	case *ast.BlockStmt:
	case *ast.DeclStmt:
	case *ast.ExprStmt:
	case *ast.ReturnStmt:
	case *ast.CallExpr:
	case *ast.BasicLit:

	case *ast.GenDecl:
		// Managed recursiveley, not by visitor
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
			param.names = append(param.names, name.Name)
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
	case token.REM:
		return "%"
	case token.SHL:
		return "<<"
	case token.SHR:
		return ">>"
	case token.LSS:
		return "<"
	case token.GTR:
		return ">"
	default:
		return fmt.Sprintf("[[TOKEN_ERROR: '%v' ]]", t)
	}
}

func (cv *cppVisitor) convertDecls(decl ast.Decl) {
	switch d := decl.(type) {
	case *ast.GenDecl:
		for _, declItem := range convertSpecs(d.Specs) {
			cv.cppPrintf("%s;\n", declItem)
		}

	case *ast.FuncDecl:
		fmt.Printf("%s %s %v\n", dbgPrefix, cv.Indent(), reflect.TypeOf(d))
		fmt.Printf("%s %s  -> Name: %v\n", dbgPrefix, cv.Indent(), d.Name)
		fmt.Printf("%s %s  -> Body: %v\n", dbgPrefix, cv.Indent(), d.Body)
		params := readFields(d.Type.Params)
		goResults := readFields(d.Type.Results)

		var outNames []string
		var outTypes []string
		var useNamedResults = true
		for _, result := range goResults {
			if result.names == nil {
				useNamedResults = false
				outTypes = append(outTypes, result.typeStr)
			}
			for _, name := range result.names {
				outNames = append(outNames, name)
				outTypes = append(outTypes, result.typeStr)
			}
		}

		if !useNamedResults {
			outNames = nil
		}

		var resultType string
		switch len(outTypes) {
		case 0:
			resultType = "void"
		case 1:
			resultType = GetCppType(outTypes[0])
		default:
			var types []string
			for _, outType := range outTypes {
				types = append(types, GetCppType(outType))
			}
			resultType = fmt.Sprintf("std::tuple<%s>", strings.Join(types, ", "))
		}

		fmt.Fprintf(cv.cppOut, "%s%s %s(%s)\n", cv.CppIndent(), resultType, d.Name.Name, params)
		fmt.Fprintf(cv.hppOut, "%s%s %s(%s);\n", cv.CppIndent(), resultType, d.Name.Name, params)

		cv.convertBlockStmt(d.Body, outNames, outTypes, true)
		fmt.Fprintf(cv.cppOut, "\n")

	case *ast.BadDecl:
		panic("convertDecls[BadDecl] Not implemented")

	default:
		panic("convertDecls, unmanaged subtype")
	}
}

func (cv *cppVisitor) convertBlockStmt(block *ast.BlockStmt, outNames, outTypes []string, isFunc bool) {
	fmt.Fprintf(cv.cppOut, "%s{\n", cv.CppIndent())
	cv.cppIndent++

	if isFunc {
		fmt.Fprintf(cv.cppOut, "%sgocpp::Defer defer;\n", cv.CppIndent())
	}

	for i := range outNames {
		fmt.Fprintf(cv.cppOut, "%s%s %s;\n", cv.CppIndent(), GetCppType(outTypes[i]), outNames[i])
	}

	for _, stmt := range block.List {
		cv.convertStmt(stmt, outNames, outTypes)
	}

	cv.cppIndent--
	fmt.Fprintf(cv.cppOut, "%s}\n", cv.CppIndent())
}

func convertReturnExprs(exprs []ast.Expr, outNames []string) string {
	switch len(exprs) {
	case 0:
		if outNames != nil {
			switch len(outNames) {
			case 0:
				panic("convertReturnExprs, len(outNames) == 0")
			case 1:
				return fmt.Sprintf("return %s", outNames[0])
			default:
				return fmt.Sprintf("return {%s}", strings.Join(outNames, ", "))
			}
		} else {
			return "return"
		}
	case 1:
		return fmt.Sprintf("return %s", convertExprs(exprs))
	default:
		return fmt.Sprintf("return {%s}", convertExprs(exprs))
	}
}

func convertAssignRightExprs(exprs []ast.Expr) string {
	switch len(exprs) {
	case 0:
		return ""
	case 1:
		return convertExprs(exprs)
	default:
		return fmt.Sprintf("std::tuple{%s}", convertExprs(exprs))
	}
}

func convertAssignExprs(stmt *ast.AssignStmt) string {
	switch stmt.Tok {
	case token.DEFINE:
		switch len(stmt.Lhs) {
		case 0:
			panic("convertAssignExprs, len(exprs) == 0")
		case 1:
			return fmt.Sprintf("auto %s = %s", convertExprs(stmt.Lhs), convertAssignRightExprs(stmt.Rhs))
		default:
			return fmt.Sprintf("auto [%s] = %s", convertExprs(stmt.Lhs), convertAssignRightExprs(stmt.Rhs))
		}
	case token.ASSIGN:
		switch len(stmt.Lhs) {
		case 0:
			panic("convertAssignExprs, len(exprs) == 0")
		case 1:
			return fmt.Sprintf("%s = %s", convertExprs(stmt.Lhs), convertAssignRightExprs(stmt.Rhs))
		default:
			return fmt.Sprintf("std::tie(%s) = %s", convertExprs(stmt.Lhs), convertAssignRightExprs(stmt.Rhs))
		}

	case token.ADD_ASSIGN, token.SUB_ASSIGN, token.MUL_ASSIGN,
		token.QUO_ASSIGN, token.REM_ASSIGN, token.AND_ASSIGN,
		token.OR_ASSIGN, token.XOR_ASSIGN, token.SHL_ASSIGN,
		token.SHR_ASSIGN, token.AND_NOT_ASSIGN:
		{
			switch len(stmt.Lhs) {
			case 0:
				panic("convertAssignExprs, len(exprs) == 0")
			case 1:
				return fmt.Sprintf("%s %s %s", convertExprs(stmt.Lhs), stmt.Tok, convertAssignRightExprs(stmt.Rhs))
			default:
				panic("convertAssignExprs, len(exprs) != 1")
			}
		}

	default:
		Panicf("convertAssignExprs, unmanaged token: %s", stmt.Tok)
	}

	// should be unreacheable
	panic("convertAssignExprs, unmanaged case")
}

func (cv *cppVisitor) convertStmt(stmt ast.Stmt, outNames []string, outTypes []string) {
	switch s := stmt.(type) {
	case *ast.BlockStmt:
		cv.convertBlockStmt(s, outNames, outTypes, false)

	case *ast.DeclStmt:
		cv.convertDecls(s.Decl)

	case *ast.ExprStmt:
		fmt.Fprintf(cv.cppOut, "%s%s", cv.CppIndent(), convertExpr(s.X))
		fmt.Fprintf(cv.cppOut, ";\n")

	case *ast.ReturnStmt:
		fmt.Fprintf(cv.cppOut, "%s%s;\n", cv.CppIndent(), convertReturnExprs(s.Results, outNames))

	case *ast.AssignStmt:
		fmt.Fprintf(cv.cppOut, "%s%s;\n", cv.CppIndent(), convertAssignExprs(s))

	case *ast.DeferStmt:
		fmt.Fprintf(cv.cppOut, "%sdefer.push_back([=]{ %s; });\n", cv.CppIndent(), convertExpr(s.Call))

	case *ast.ForStmt:
		fmt.Fprintf(cv.cppOut, "%sfor(%s; %s; %s)\n", cv.CppIndent(), inlineStmt(s.Init), convertExpr(s.Cond), inlineStmt(s.Post))
		cv.convertBlockStmt(s.Body, outNames, outTypes, false)

	case *ast.IfStmt:
		fmt.Fprintf(cv.cppOut, "%sif(%s; %s)\n", cv.CppIndent(), inlineStmt(s.Init), convertExpr(s.Cond))
		cv.convertBlockStmt(s.Body, outNames, outTypes, false)
		if s.Else != nil {
			fmt.Fprintf(cv.cppOut, "%selse\n", cv.CppIndent())
			cv.convertStmt(s.Else, outNames, outTypes)
		}

	case *ast.SwitchStmt:
		fmt.Fprintf(cv.cppOut, "%s//Go switch emulation\n", cv.CppIndent())
		fmt.Fprintf(cv.cppOut, "%s{\n", cv.CppIndent())
		cv.cppIndent++

		if s.Init != nil {
			fmt.Fprintf(cv.cppOut, "%s%s;\n", cv.CppIndent(), inlineStmt(s.Init))
		}

		conditionVarName := "conditionId"
		inputVarName := ""
		if s.Tag != nil {
			inputVarName = "condition"
			fmt.Fprintf(cv.cppOut, "%sauto %s = %s;\n", cv.CppIndent(), inputVarName, convertExpr(s.Tag))
		}

		fmt.Fprintf(cv.cppOut, "%sint %s = 0;\n", cv.CppIndent(), conditionVarName)
		se := switchEnvName{inputVarName, conditionVarName, "", inputVarName != ""}
		cv.extractCaseExpr(s.Body, &se)
		fmt.Fprintf(cv.cppOut, "%sswitch(%s)\n", cv.CppIndent(), conditionVarName)

		cv.currentSwitchId.PushBack(0)
		cv.convertBlockStmt(s.Body, outNames, outTypes, false)
		cv.currentSwitchId.Remove(cv.currentSwitchId.Back())

		cv.cppIndent--
		fmt.Fprintf(cv.cppOut, "%s}\n", cv.CppIndent())

	case *ast.CaseClause:
		if s.List == nil {
			fmt.Fprintf(cv.cppOut, "%sdefault:\n", cv.CppIndent())
		} else {
			for range s.List {
				id := cv.currentSwitchId.Back().Value.(int)
				fmt.Fprintf(cv.cppOut, "%scase %d:\n", cv.CppIndent(), id)
				cv.currentSwitchId.Back().Value = id + 1
			}
		}

		cv.cppIndent++
		for _, stmt := range s.Body {
			cv.convertStmt(stmt, outNames, outTypes)
		}
		fmt.Fprintf(cv.cppOut, "%sbreak;\n", cv.CppIndent())
		cv.cppIndent--

	default:
		Panicf("convertStmt, unmanaged type [%v]", reflect.TypeOf(s))
	}
}

type switchEnvName struct {
	inputVarName     string
	conditionVarName string
	prefix           string
	withCondition    bool
}

func (cv *cppVisitor) extractCaseExpr(stmt ast.Stmt, se *switchEnvName) {
	switch s := stmt.(type) {
	case *ast.BlockStmt:
		cv.currentSwitchId.PushBack(0)
		for _, stmt := range s.List {
			cv.extractCaseExpr(stmt, se)
		}
		cv.currentSwitchId.Remove(cv.currentSwitchId.Back())

	case *ast.CaseClause:
		for _, expr := range s.List {
			id := cv.currentSwitchId.Back().Value.(int)
			if se.withCondition {
				fmt.Fprintf(cv.cppOut, "%s%sif(%s == %s) { %s = %d; }\n", cv.CppIndent(), se.prefix, se.inputVarName, convertExpr(expr), se.conditionVarName, id)
			} else {
				fmt.Fprintf(cv.cppOut, "%s%sif(%s) { %s = %d; }\n", cv.CppIndent(), se.prefix, convertExpr(expr), se.conditionVarName, id)
			}
			cv.currentSwitchId.Back().Value = id + 1
		}
		se.prefix = "else "

	default:
		Panicf("convertStmt, unmanaged type [%v]", reflect.TypeOf(s))
	}
}

func inlineStmt(stmt ast.Stmt) (result string) {
	switch s := stmt.(type) {
	case nil:
		return

	case *ast.DeclStmt:
		switch d := s.Decl.(type) {
		case *ast.GenDecl:
			for _, declItem := range convertSpecs(d.Specs) {
				result += fmt.Sprintf("%s,", declItem)
			}
		default:
			panic("convertDecls, unmanaged subtype")
		}

	case *ast.ExprStmt:
		return convertExpr(s.X)

	case *ast.IncDecStmt:
		switch s.Tok {
		case token.INC:
			return fmt.Sprintf("%s++", convertExpr(s.X))
		case token.DEC:
			return fmt.Sprintf("%s--", convertExpr(s.X))
		default:
			Panicf("inlineStmt, unmanaged type [%v]", reflect.TypeOf(s.Tok))
		}

	case *ast.AssignStmt:
		return convertAssignExprs(s)

	default:
		Panicf("inlineStmt, unmanaged token [%v]", reflect.TypeOf(s))
	}

	// should be unreacheable
	panic("convertStmt, unmanaged case")
}

func convertSpecs(specs []ast.Spec) []string {
	var result []string

	for _, spec := range specs {
		switch s := spec.(type) {
		case *ast.TypeSpec:
			result = append(result, fmt.Sprintf("%s %s", convertExpr(s.Type), s.Name.Name))

		case *ast.ValueSpec:
			for i := range s.Names {
				if len(s.Values) == 0 {
					result = append(result, fmt.Sprintf("%s %s", convertTypeExpr(s.Type), s.Names[i].Name))
				} else {
					result = append(result, fmt.Sprintf("%s %s = %s", convertTypeExpr(s.Type), s.Names[i].Name, convertExpr(s.Values[i])))
				}
			}

		case *ast.ImportSpec:
			result = append(result, "// convertSpecs[ImportSpec] Not implemented => "+s.Path.Value)

		default:
			Panicf("convertSpecs, unmanaged type [%v]", reflect.TypeOf(s))
		}
	}

	return result
}

func convertTypeExpr(node ast.Expr) string {
	if node == nil {
		return "auto"
	}

	switch n := node.(type) {
	case *ast.Ident:
		return GetCppType(n.Name)

	default:
		return fmt.Sprintf("!!TYPE_EXPR_ERROR!! [%v]", reflect.TypeOf(node))
	}
}

func convertExpr(node ast.Expr) string {
	if node == nil {
		return ""
	}

	switch n := node.(type) {
	case *ast.BasicLit:
		if n.Kind == token.IMAG {
			return "gocpp::complex128(0, " + strings.Replace(n.Value, "i", "", -1) + ")"
		} else {
			return n.Value
		}

	case *ast.UnaryExpr:
		return convertToken(n.Op) + " " + convertExpr(n.X)

	case *ast.ParenExpr:
		return "(" + convertExpr(n.X) + ")"

	case *ast.BinaryExpr:
		return convertExpr(n.X) + " " + convertToken(n.Op) + " " + convertExpr(n.Y)
		// import "go/type"
		//xType := types.ExprString(n.X)
		//yType := types.ExprString(n.Y)
		//if xType == yType {
		//	return convertExpr(n.X) + " " + convertToken(n.Op) + " " + convertExpr(n.Y)
		//} else {
		//	return ...
		//}

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
		return GetCppFunc(n.Name)

	case *ast.SelectorExpr:
		var sep string
		if isNameSpace(n.X) {
			sep = "::"
		} else {
			sep = "."
		}
		return GetCppFunc(convertExpr(n.X) + sep + convertExpr(n.Sel))

	default:
		//panic(fmt.Sprintf("Unmanaged type in convert %v", n))
		return fmt.Sprintf("!!EXPR_ERROR!! [%v]", reflect.TypeOf(node))
	}
}

func isNameSpace(expr ast.Expr) bool {

	switch n := expr.(type) {
	case *ast.Ident:
		if _, ok := nameSpaces[n.Name]; ok {
			return true
		}
		return false
	default:
		return false
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

	// Managed recursiveley, not by visitor
	case *ast.FuncDecl:
	case *ast.BlockStmt:
	case *ast.ExprStmt:
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

	inputName := flag.String("input", "tests/HelloWorld.go", "The file to parse")
	parseFmtDir := flag.Bool("parseFmt", true, "temporary test parameter")
	cppOutDir := flag.String("cppOutDir", "out", "generated code directory")
	binOutDir := flag.String("binOutDir", "log", "gcc output dir in Makefile")
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
	cv.binOutDir = *binOutDir
	cv.cppOutDir = *cppOutDir
	cv.supportHeader = "gocpp/support.h"
	cv.inputName = *inputName
	cv.Init()

	fmt.Printf("\n=====\n")
	ast.Walk(cv, f)
}
