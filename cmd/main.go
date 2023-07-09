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
	"uint8":      "uint8_t",
	"uint16":     "uint16_t",
	"uint32":     "uint32_t",
	"uint64":     "uint64_t",
	"complex128": "gocpp::complex128",
	"float":      "double",
	"float32":    "float",
	"float64":    "double",
	"uint":       "unsigned int",
}

var nameSpaces = map[string]struct{}{
	"cmplx":   {},
	"fmt":     {},
	"math":    {},
	"pic":     {},
	"rand":    {},
	"runtime": {},
	"time":    {},
	"strings": {},
	"wc":      {},
}

var stdFuncMapping = map[string]string{
	// Temporary mappings while 'import' isn't implemented
	"fmt::Print":      "mocklib::Print",
	"fmt::Printf":     "mocklib::Printf",
	"fmt::Println":    "mocklib::Println",
	"fmt::Sprint":     "mocklib::Sprint",
	"fmt::Sprintf":    "mocklib::Sprintf",
	"rand::Intn":      "mocklib::Intn",
	"runtime::GOOS":   "mocklib::GOOS",
	"cmplx::Sqrt":     "std::sqrt",
	"math::Pow":       "mocklib::Pow",
	"math::Sqrt":      "std::sqrt",
	"math::Sqrt2":     "mocklib::Sqrt2",
	"math::Pi":        "M_PI",
	"pic::Show":       "mocklib::picShow",
	"time::Now":       "mocklib::Date::Now",
	"time::Saturday":  "mocklib::Date::Saturday",
	"strings::Join":   "mocklib::StringsJoin",
	"strings::Fields": "mocklib::StringsFields",
	"wc::Test":        "mocklib::wcTest",
	// Predefined functions
	"delete": "remove",
	"make":   "gocpp::make",
	"panic":  "gocpp::panic",
	"nil":    "nullptr",
	// type conversions
	"float":   "double",
	"float32": "float",
	"float64": "double",
	"uint":    "(unsigned int)",
	"uint8":   "uint8_t",
	"uint16":  "uint16_t",
	"uint32":  "uint32_t",
	"uint64":  "uint64_t",
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
	names []string
	Type  cppType
}

type typeNames []typeName

func (tn typeName) ParamDecl() []string {
	var strs []string

	if len(tn.names) != 0 {
		for _, name := range tn.names {
			strs = append(strs, fmt.Sprintf("%v %v", GetCppType(tn.Type.str), name))
		}
	} else {
		strs = append(strs, fmt.Sprintf("%v", GetCppType(tn.Type.str)))
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
	baseName      string
	inputName     string
	supportHeader string

	// Parsing and codegen parameters
	currentSwitchId *list.List
	idCount         int
	nodes           *list.List
	scopes          *list.List

	// Logs and makefile parameters
	genMakeFile bool
	makeOutFile *os.File
	makeOut     *bufio.Writer
	binOutDir   string
	astIndent   int

	// Cpp files parameters
	cppOutDir  string
	cppOutFile *os.File
	cppOut     *bufio.Writer
	cppIndent  int

	// Hpp files parameters
	hppOutFile *os.File
	hppOut     *bufio.Writer
	hppIndent  int
}

func (cv *cppVisitor) Indent() string {
	return strings.Repeat("  ", cv.astIndent)
}

func (cv *cppVisitor) CppIndent() string {
	return strings.Repeat("    ", cv.cppIndent)
}

func (cv *cppVisitor) HppIndent() string {
	return strings.Repeat("    ", cv.hppIndent)
}

func (cv *cppVisitor) GenerateId() (id string) {
	id = fmt.Sprintf("gocpp_id_%d", cv.idCount)
	cv.idCount++
	return id
}

const dbgPrefix string = "         "
const rawPrefix string = "//RAW_AST"

func printCppIntro(cv *cppVisitor) {
	//temporarily blindly add "includes" and "using"
	fmt.Fprintf(cv.cppOut, "#include <complex>\n")
	fmt.Fprintf(cv.cppOut, "#include <functional>\n")
	fmt.Fprintf(cv.cppOut, "#include <iostream>\n")
	fmt.Fprintf(cv.cppOut, "#include <iomanip>\n")
	fmt.Fprintf(cv.cppOut, "#include <map>\n")
	fmt.Fprintf(cv.cppOut, "#include <string>\n")
	fmt.Fprintf(cv.cppOut, "#include <tuple>\n")
	fmt.Fprintf(cv.cppOut, "#include <vector>\n")
	fmt.Fprintf(cv.cppOut, "\n")
	fmt.Fprintf(cv.cppOut, "#include \"%s.h\"\n", cv.baseName)
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
	fmt.Fprintf(cv.cppOut, "int main()\n")
	fmt.Fprintf(cv.cppOut, "{\n")
	fmt.Fprintf(cv.cppOut, "    try\n")
	fmt.Fprintf(cv.cppOut, "    {\n")
	fmt.Fprintf(cv.cppOut, "        std::cout << std::boolalpha << std::fixed << std::setprecision(5);\n")
	fmt.Fprintf(cv.cppOut, "        golang::main();\n")
	fmt.Fprintf(cv.cppOut, "        return 0;\n")
	fmt.Fprintf(cv.cppOut, "    }\n")
	fmt.Fprintf(cv.cppOut, "    catch(const gocpp::GoPanic& ex)\n")
	fmt.Fprintf(cv.cppOut, "    {\n")
	fmt.Fprintf(cv.cppOut, "        std::cout << \"Panic: \" << ex.what() << std::endl;\n")
	fmt.Fprintf(cv.cppOut, "        return -1;\n")
	fmt.Fprintf(cv.cppOut, "    }\n")
	fmt.Fprintf(cv.cppOut, "}\n")
}

func printHppIntro(cv *cppVisitor) {
	//temporarily blindly add "includes" and "using"
	fmt.Fprintf(cv.hppOut, "#pragma once\n")
	fmt.Fprintf(cv.hppOut, "\n")
	fmt.Fprintf(cv.hppOut, "#include <functional>\n")
	fmt.Fprintf(cv.hppOut, "#include <string>\n")
	fmt.Fprintf(cv.hppOut, "#include <tuple>\n")
	fmt.Fprintf(cv.hppOut, "#include <vector>\n")
	fmt.Fprintf(cv.hppOut, "\n")
	// TODO : make forward declaration header
	fmt.Fprintf(cv.hppOut, "#include \"%s\"\n", cv.supportHeader)
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
	cv.scopes = new(list.List)

	if cv.genMakeFile {
		cv.makeOutFile = createOutput(cv.cppOutDir, "Makefile")
		cv.makeOut = bufio.NewWriter(cv.makeOutFile)

		fmt.Fprintf(cv.makeOut, "all:\n")
	}
}

type variables map[string]bool

func (cv *cppVisitor) startScope() {
	cv.scopes.PushBack(variables{})
}

func (cv *cppVisitor) endScope() {
	cv.scopes.Remove(cv.scopes.Back())
}

func (cv *cppVisitor) DeclareVar(name string, isPtr bool) {
	vars := cv.scopes.Back().Value.(variables)
	vars[name] = isPtr
}

func (cv *cppVisitor) DeclareVars(params typeNames) {
	for _, param := range params {
		for _, name := range param.names {
			cv.DeclareVar(name, param.Type.isPtr)
		}
	}
}

// FIXME : manage composed names like A.B.C
func (cv *cppVisitor) IsPtr(name string) bool {
	for elt := cv.scopes.Back(); elt != nil; elt = elt.Prev() {
		vars := elt.Value.(variables)
		value, ok := vars[name]
		if ok {
			return value
		}
	}
	return false
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
		cv.startScope()
		fmt.Printf("%s %s %v\n", dbgPrefix, cv.Indent(), reflect.TypeOf(n))

		cv.cppOutFile = createOutputExt(cv.cppOutDir, cv.baseName, "cpp")
		cv.cppOut = bufio.NewWriter(cv.cppOutFile)

		cv.hppOutFile = createOutputExt(cv.cppOutDir, cv.baseName, "h")
		cv.hppOut = bufio.NewWriter(cv.hppOutFile)

		printCppIntro(cv)
		printHppIntro(cv)

		for _, decl := range n.Decls {
			cv.convertDecls(decl)
		}

		if cv.genMakeFile {
			fmt.Fprintf(cv.makeOut, "\t g++ -I. -I../includes %s.cpp -o ../%s/%s.exe\n", cv.baseName, cv.binOutDir, cv.baseName)
		}

		//fmt.Printf("%s Name: %v\n", v.Indent(), n.Name)
		//fmt.Printf("%s Scope: %v\n", v.Indent(), n.Scope)

		cv.endScope()

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

func (cv *cppVisitor) readFields(fields *ast.FieldList) (params typeNames) {
	if fields == nil {
		return
	}

	for _, field := range fields.List {
		var param typeName
		for _, name := range field.Names {
			param.names = append(param.names, name.Name)
		}
		param.Type = cv.convertTypeExpr(field.Type)
		params = append(params, param)
	}
	return
}

type method struct {
	name   string
	result string
	params string
}

func (cv *cppVisitor) readMethods(fields *ast.FieldList) (methods []method) {
	if fields == nil {
		return
	}

	for _, field := range fields.List {
		for _, name := range field.Names {
			outPrm, inPrm := cv.convertMethodExpr(field.Type)
			methods = append(methods, method{name.Name, outPrm, inPrm})
		}
	}
	return
}

func convertToken(t token.Token) string {
	switch t {
	// TODO: implement specific conversion need here if needed
	default:
		return fmt.Sprintf("%v", t)
	}
}

type stmtEnv struct {
	outNames []string
	outTypes []string
}

type blockEnv struct {
	stmtEnv
	isFunc bool
}

func (cv *cppVisitor) convertDecls(decl ast.Decl) {
	switch d := decl.(type) {
	case *ast.GenDecl:
		for _, declItem := range cv.convertSpecs(d.Specs, ";\n") {
			cv.cppPrintf("%s", declItem)
		}

	case *ast.FuncDecl:
		fmt.Printf("%s %s %v\n", dbgPrefix, cv.Indent(), reflect.TypeOf(d))
		fmt.Printf("%s %s  -> Name: %v\n", dbgPrefix, cv.Indent(), d.Name)
		fmt.Printf("%s %s  -> Body: %v\n", dbgPrefix, cv.Indent(), d.Body)

		params := cv.readFields(d.Recv)
		params = append(params, cv.readFields(d.Type.Params)...)
		outNames, outTypes := cv.getResultInfos(d.Type)
		resultType := buildOutType(outTypes)

		cv.DeclareVars(params)

		fmt.Fprintf(cv.cppOut, "%s%s %s(%s)\n", cv.CppIndent(), resultType, d.Name.Name, params)
		fmt.Fprintf(cv.hppOut, "%s%s %s(%s);\n", cv.CppIndent(), resultType, d.Name.Name, params)

		cv.convertBlockStmt(d.Body, blockEnv{stmtEnv{outNames, outTypes}, true})
		fmt.Fprintf(cv.cppOut, "\n")

	case *ast.BadDecl:
		panic("convertDecls[BadDecl] Not implemented")

	default:
		panic("convertDecls, unmanaged subtype")
	}
}

func (cv *cppVisitor) convertBlockStmt(block *ast.BlockStmt, env blockEnv) {
	cv.startScope()
	fmt.Fprintf(cv.cppOut, "%s{\n", cv.CppIndent())
	cv.cppIndent++

	if env.isFunc {
		fmt.Fprintf(cv.cppOut, "%sgocpp::Defer defer;\n", cv.CppIndent())
	}

	for i := range env.outNames {
		fmt.Fprintf(cv.cppOut, "%s%s %s;\n", cv.CppIndent(), GetCppType(env.outTypes[i]), env.outNames[i])
	}

	for _, stmt := range block.List {
		cv.convertStmt(stmt, env.stmtEnv)
	}

	cv.cppIndent--
	fmt.Fprintf(cv.cppOut, "%s}\n", cv.CppIndent())
	cv.endScope()
}

func (cv *cppVisitor) convertReturnExprs(exprs []ast.Expr, outNames []string) string {
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
		return fmt.Sprintf("return %s", cv.convertExprs(exprs))
	default:
		return fmt.Sprintf("return {%s}", cv.convertExprs(exprs))
	}
}

func (cv *cppVisitor) convertAssignRightExprs(exprs []ast.Expr) string {
	switch len(exprs) {
	case 0:
		return ""
	case 1:
		return cv.convertExprs(exprs)
	default:
		return fmt.Sprintf("std::tuple{%s}", cv.convertExprs(exprs))
	}
}

func (cv *cppVisitor) convertAssignExprs(stmt *ast.AssignStmt) string {
	switch stmt.Tok {
	case token.DEFINE:
		switch len(stmt.Lhs) {
		case 0:
			panic("convertAssignExprs, len(exprs) == 0")
		case 1:
			return fmt.Sprintf("auto %s = %s", cv.convertExprs(stmt.Lhs), cv.convertAssignRightExprs(stmt.Rhs))
		default:
			return fmt.Sprintf("auto [%s] = %s", cv.convertExprs(stmt.Lhs), cv.convertAssignRightExprs(stmt.Rhs))
		}
	case token.ASSIGN:
		switch len(stmt.Lhs) {
		case 0:
			panic("convertAssignExprs, len(exprs) == 0")
		case 1:
			return fmt.Sprintf("%s = %s", cv.convertExprs(stmt.Lhs), cv.convertAssignRightExprs(stmt.Rhs))
		default:
			return fmt.Sprintf("std::tie(%s) = %s", cv.convertExprs(stmt.Lhs), cv.convertAssignRightExprs(stmt.Rhs))
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
				return fmt.Sprintf("%s %s %s", cv.convertExprs(stmt.Lhs), stmt.Tok, cv.convertAssignRightExprs(stmt.Rhs))
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

func (cv *cppVisitor) convertStmt(stmt ast.Stmt, env stmtEnv) {
	switch s := stmt.(type) {
	case *ast.BlockStmt:
		cv.convertBlockStmt(s, blockEnv{env, false})

	case *ast.DeclStmt:
		cv.convertDecls(s.Decl)

	case *ast.ExprStmt:
		fmt.Fprintf(cv.cppOut, "%s%s;\n", cv.CppIndent(), cv.convertExpr(s.X))

	case *ast.IncDecStmt:
		fmt.Fprintf(cv.cppOut, "%s%s%s;\n", cv.CppIndent(), cv.convertExpr(s.X), s.Tok)

	case *ast.ReturnStmt:
		fmt.Fprintf(cv.cppOut, "%s%s;\n", cv.CppIndent(), cv.convertReturnExprs(s.Results, env.outNames))

	case *ast.AssignStmt:
		fmt.Fprintf(cv.cppOut, "%s%s;\n", cv.CppIndent(), cv.convertAssignExprs(s))

	case *ast.DeferStmt:
		fmt.Fprintf(cv.cppOut, "%sdefer.push_back([=]{ %s; });\n", cv.CppIndent(), cv.convertExpr(s.Call))

	case *ast.ForStmt:
		fmt.Fprintf(cv.cppOut, "%sfor(%s; %s; %s)\n", cv.CppIndent(), cv.inlineStmt(s.Init), cv.convertExpr(s.Cond), cv.inlineStmt(s.Post))
		cv.convertBlockStmt(s.Body, blockEnv{env, false})

	case *ast.RangeStmt:
		if s.Key != nil && s.Value != nil && s.Tok == token.DEFINE {
			fmt.Fprintf(cv.cppOut, "%sfor(auto [%s, %s] : %s)\n", cv.CppIndent(), cv.convertExpr(s.Key), cv.convertExpr(s.Value), cv.convertExpr(s.X))
		} else if s.Key != nil && s.Value == nil && s.Tok == token.DEFINE {
			fmt.Fprintf(cv.cppOut, "%sfor(auto [%s, gocpp_ignored] : %s)\n", cv.CppIndent(), cv.convertExpr(s.Key), cv.convertExpr(s.X))
		} else {
			panic("Unmanaged case of '*ast.RangeStmt'")
		}
		cv.convertBlockStmt(s.Body, blockEnv{env, false})

	case *ast.IfStmt:
		fmt.Fprintf(cv.cppOut, "%sif(%s; %s)\n", cv.CppIndent(), cv.inlineStmt(s.Init), cv.convertExpr(s.Cond))
		cv.convertBlockStmt(s.Body, blockEnv{env, false})
		if s.Else != nil {
			fmt.Fprintf(cv.cppOut, "%selse\n", cv.CppIndent())
			cv.convertStmt(s.Else, env)
		}

	case *ast.SwitchStmt:
		fmt.Fprintf(cv.cppOut, "%s//Go switch emulation\n", cv.CppIndent())
		fmt.Fprintf(cv.cppOut, "%s{\n", cv.CppIndent())
		cv.cppIndent++

		if s.Init != nil {
			fmt.Fprintf(cv.cppOut, "%s%s;\n", cv.CppIndent(), cv.inlineStmt(s.Init))
		}

		conditionVarName := "conditionId"
		inputVarName := ""
		if s.Tag != nil {
			inputVarName = "condition"
			fmt.Fprintf(cv.cppOut, "%sauto %s = %s;\n", cv.CppIndent(), inputVarName, cv.convertExpr(s.Tag))
		}

		fmt.Fprintf(cv.cppOut, "%sint %s = -1;\n", cv.CppIndent(), conditionVarName)
		se := switchEnvName{inputVarName, conditionVarName, "", inputVarName != ""}
		cv.extractCaseExpr(s.Body, &se)
		fmt.Fprintf(cv.cppOut, "%sswitch(%s)\n", cv.CppIndent(), conditionVarName)

		cv.currentSwitchId.PushBack(0)
		cv.convertBlockStmt(s.Body, blockEnv{env, false})
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
			cv.convertStmt(stmt, env)
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
				fmt.Fprintf(cv.cppOut, "%s%sif(%s == %s) { %s = %d; }\n", cv.CppIndent(), se.prefix, se.inputVarName, cv.convertExpr(expr), se.conditionVarName, id)
			} else {
				fmt.Fprintf(cv.cppOut, "%s%sif(%s) { %s = %d; }\n", cv.CppIndent(), se.prefix, cv.convertExpr(expr), se.conditionVarName, id)
			}
			cv.currentSwitchId.Back().Value = id + 1
		}
		se.prefix = "else "

	default:
		Panicf("convertStmt, unmanaged type [%v]", reflect.TypeOf(s))
	}
}

func (cv *cppVisitor) inlineStmt(stmt ast.Stmt) (result string) {
	switch s := stmt.(type) {
	case nil:
		return

	case *ast.DeclStmt:
		switch d := s.Decl.(type) {
		case *ast.GenDecl:
			for _, declItem := range cv.convertSpecs(d.Specs, "") {
				result += fmt.Sprintf("%s,", declItem)
			}
		default:
			panic("convertDecls, unmanaged subtype")
		}

	case *ast.ExprStmt:
		return cv.convertExpr(s.X)

	case *ast.IncDecStmt:
		switch s.Tok {
		case token.INC:
			return fmt.Sprintf("%s++", cv.convertExpr(s.X))
		case token.DEC:
			return fmt.Sprintf("%s--", cv.convertExpr(s.X))
		default:
			Panicf("inlineStmt, unmanaged type [%v]", reflect.TypeOf(s.Tok))
		}

	case *ast.AssignStmt:
		return cv.convertAssignExprs(s)

	default:
		Panicf("inlineStmt, unmanaged token [%v]", reflect.TypeOf(s))
	}

	// should be unreacheable
	panic("convertStmt, unmanaged case")
}

func (cv *cppVisitor) getResultInfos(funcType *ast.FuncType) (outNames, outTypes []string) {
	goResults := cv.readFields(funcType.Results)

	var useNamedResults = true
	for _, result := range goResults {
		if result.names == nil {
			useNamedResults = false
			outTypes = append(outTypes, result.Type.str)
		}
		for _, name := range result.names {
			outNames = append(outNames, name)
			outTypes = append(outTypes, result.Type.str)
		}
	}

	if !useNamedResults {
		outNames = nil
	}

	return
}

func buildOutType(outTypes []string) string {
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
	return resultType
}

func (cv *cppVisitor) convertSpecs(specs []ast.Spec, end string) []string {
	var result []string

	for _, spec := range specs {
		switch s := spec.(type) {
		case *ast.TypeSpec:
			t := cv.convertTypeSpec(s, end)
			result = append(result, t.defs...)
			result = append(result, t.str)

		case *ast.ValueSpec:
			if s.Type == nil {
				for i := range s.Names {
					if len(s.Values) == 0 {
						result = append(result, fmt.Sprintf("auto %s%s", s.Names[i].Name, end))
					} else {
						result = append(result, fmt.Sprintf("auto %s = %s%s", s.Names[i].Name, cv.convertExpr(s.Values[i]), end))
					}
				}
			} else {
				for i := range s.Names {
					t := cv.convertTypeExpr(s.Type)
					result = append(result, t.defs...)

					if len(s.Values) == 0 {
						result = append(result, fmt.Sprintf("%s %s%s", t.str, s.Names[i].Name, end))
					} else {
						result = append(result, fmt.Sprintf("%s %s = %s%s", t.str, s.Names[i].Name, cv.convertExpr(s.Values[i]), end))
					}
				}
			}

		case *ast.ImportSpec:
			result = append(result, fmt.Sprintf("// convertSpecs[ImportSpec] Not implemented => %s%s", s.Path.Value, end))

		default:
			Panicf("convertSpecs, unmanaged type [%v]", reflect.TypeOf(s))
		}
	}

	return result
}

type cppType struct {
	str   string   // cpp type as a string
	defs  []string // inline def used by type
	isPtr bool     // is type a pointer ?
}

func (cv *cppVisitor) convertTypeSpec(node *ast.TypeSpec, end string) cppType {
	if node == nil {
		panic("node is nil")
	}

	switch n := node.Type.(type) {
	case *ast.Ident:
		usingDec := fmt.Sprintf("using %s = %s", node.Name.Name, GetCppType(n.Name))
		// TODO: return type value instead of wtiting in header directly
		fmt.Fprintf(cv.hppOut, "%s%s%s", cv.HppIndent(), usingDec, end)
		// Commented output in cpp as we only need one declaration
		// TODO : manage go private/public rule to chose where to put definition
		return cppType{fmt.Sprintf("// %s%s", usingDec, end), nil, false}

	case *ast.ArrayType:
		t := cv.convertArrayTypeExpr(n)
		return cppType{fmt.Sprintf("%s %s%s", t.str, node.Name.Name, end), t.defs, false}

	case *ast.FuncType:
		return cppType{fmt.Sprintf("%s %s%s", cv.convertFuncTypeExpr(n), node.Name.Name, end), nil, false}

	case *ast.StructType:
		// TODO: return type value instead of wtiting in header directly
		fmt.Fprintf(cv.hppOut, "%sstruct %s%s", cv.HppIndent(), node.Name.Name, end)
		return cppType{cv.convertStructTypeExpr(n, node.Name.Name, true), nil, false}

	case *ast.InterfaceType:
		// TODO: return type value instead of wtiting in header directly
		fmt.Fprintf(cv.hppOut, "%sstruct %s%s", cv.HppIndent(), node.Name.Name, end)
		return cppType{cv.convertInterfaceTypeExpr(n, node.Name.Name, true), nil, false}

	default:
		return cppType{fmt.Sprintf("!!TYPE_SPEC_ERROR!! [%v];\n", reflect.TypeOf(n)), nil, false}
	}
}

func isMapType(node ast.Expr) bool {
	switch n := node.(type) {
	case *ast.MapType:
		_ = n
		return true

	default:
		return false
	}
}

func (cv *cppVisitor) convertTypeExpr(node ast.Expr) cppType {
	if node == nil {
		panic("node is nil")
	}

	switch n := node.(type) {
	case *ast.Ident:
		return cppType{GetCppType(n.Name), nil, false}

	case *ast.ArrayType:
		return cv.convertArrayTypeExpr(n)

	case *ast.FuncType:
		return cppType{cv.convertFuncTypeExpr(n), nil, false}

	// TODO
	//case *ast.InterfaceType:
	//	return "std::any", nil

	case *ast.MapType:
		return cv.convertMapTypeExpr(n)

	case *ast.StarExpr:
		t := cv.convertTypeExpr(n.X)
		return cppType{t.str + "*", t.defs, true}

	case *ast.StructType:
		name := cv.GenerateId()
		t := cv.convertStructTypeExpr(n, name, false)
		return cppType{name, []string{t}, false}

	default:
		return cppType{fmt.Sprintf("!!TYPE_EXPR_ERROR!! [%v]", reflect.TypeOf(node)), nil, false}
	}
}

func (cv *cppVisitor) convertMethodExpr(node ast.Expr) (string, string) {
	if node == nil {
		panic("node is nil")
	}

	switch n := node.(type) {
	case *ast.FuncType:
		params := cv.readFields(n.Params)
		_, outTypes := cv.getResultInfos(n)
		resultType := buildOutType(outTypes)
		return resultType, params.String()

	default:
		panic(fmt.Sprintf("Not a function type %v", n))
	}
}

func (cv *cppVisitor) convertArrayTypeExpr(node *ast.ArrayType) cppType {
	elt := cv.convertTypeExpr(node.Elt)

	if node.Len == nil {
		return cppType{fmt.Sprintf("gocpp::slice<%s>", elt.str), elt.defs, false}
	} else {
		return cppType{fmt.Sprintf("gocpp::array<%s, %s>", elt.str, cv.convertExpr(node.Len)), elt.defs, false}
	}
}

func (cv *cppVisitor) convertFuncTypeExpr(node *ast.FuncType) string {
	params := cv.readFields(node.Params)
	_, outTypes := cv.getResultInfos(node)
	resultType := buildOutType(outTypes)
	return fmt.Sprintf("std::function<%s (%s)>", resultType, params)
}

func (cv *cppVisitor) convertMapTypeExpr(node *ast.MapType) cppType {
	key := cv.convertTypeExpr(node.Key)
	value := cv.convertTypeExpr(node.Value)
	return cppType{fmt.Sprintf("gocpp::map<%s,%s>", key.str, value.str), append(key.defs, value.defs...), false}
}

func (cv *cppVisitor) convertStructTypeExpr(node *ast.StructType, structName string, withStreamOperator bool) string {
	buf := new(bytes.Buffer)

	fmt.Fprintf(buf, "struct %[1]s\n", structName)
	fmt.Fprintf(buf, "%s{\n", cv.CppIndent())

	cv.cppIndent++
	fields := cv.readFields(node.Fields)
	for _, field := range fields {
		for _, name := range field.names {
			fmt.Fprintf(buf, "%s%s %s;\n", cv.CppIndent(), field.Type.str, name)
		}
	}

	fmt.Fprintf(buf, "\n")
	fmt.Fprintf(buf, "%susing isGoStruct = void;\n", cv.CppIndent())
	fmt.Fprintf(buf, "\n")
	fmt.Fprintf(buf, "%sstatic %[2]s Init(void (init)(%[2]s&))\n", cv.CppIndent(), structName)
	fmt.Fprintf(buf, "%s{\n", cv.CppIndent())
	fmt.Fprintf(buf, "%s    %s value;\n", cv.CppIndent(), structName)
	fmt.Fprintf(buf, "%s    init(value);\n", cv.CppIndent())
	fmt.Fprintf(buf, "%s    return value;\n", cv.CppIndent())
	fmt.Fprintf(buf, "%s}\n", cv.CppIndent())
	fmt.Fprintf(buf, "\n")
	fmt.Fprintf(buf, "%sstd::ostream& PrintTo(std::ostream& os) const\n", cv.CppIndent())
	fmt.Fprintf(buf, "%s{\n", cv.CppIndent())
	fmt.Fprintf(buf, "%s    os << '{';\n", cv.CppIndent())
	sep := ""
	for _, field := range fields {
		for _, name := range field.names {
			fmt.Fprintf(buf, "%s    os << \"%s\" << %s;\n", cv.CppIndent(), sep, name)
			sep = " "
		}
	}
	fmt.Fprintf(buf, "%s    os << '}';\n", cv.CppIndent())
	fmt.Fprintf(buf, "%s    return os;\n", cv.CppIndent())
	fmt.Fprintf(buf, "%s}\n", cv.CppIndent())

	cv.cppIndent--
	fmt.Fprintf(buf, "%s};\n", cv.CppIndent())
	if withStreamOperator {
		fmt.Fprintf(buf, "\n")
		fmt.Fprintf(buf, "%sstd::ostream& operator<<(std::ostream& os, const %s& value)\n", cv.CppIndent(), structName)
		fmt.Fprintf(buf, "%s{\n", cv.CppIndent())
		fmt.Fprintf(buf, "%s    return value.PrintTo(os);\n", cv.CppIndent())
		fmt.Fprintf(buf, "%s}\n", cv.CppIndent())
		fmt.Fprintf(buf, "\n")
	}
	return buf.String()
}

func (cv *cppVisitor) convertInterfaceTypeExpr(node *ast.InterfaceType, structName string, withStreamOperator bool) string {
	buf := new(bytes.Buffer)
	methods := cv.readMethods(node.Methods)

	fmt.Fprintf(buf, "struct %s\n", structName)
	fmt.Fprintf(buf, "%s{\n", cv.CppIndent())
	fmt.Fprintf(buf, "%s    %s(){}\n", cv.CppIndent(), structName)
	fmt.Fprintf(buf, "%s    %[2]s(%[2]s& i) = default;\n", cv.CppIndent(), structName)
	fmt.Fprintf(buf, "%s    %[2]s(const %[2]s& i) = default;\n", cv.CppIndent(), structName)
	fmt.Fprintf(buf, "%s    %[2]s& operator=(%[2]s& i) = default;\n", cv.CppIndent(), structName)
	fmt.Fprintf(buf, "%s    %[2]s& operator=(const %[2]s& i) = default;\n", cv.CppIndent(), structName)
	fmt.Fprintf(buf, "\n")
	fmt.Fprintf(buf, "%s    template<typename T>\n", cv.CppIndent())
	fmt.Fprintf(buf, "%s    %s(T& ref)\n", cv.CppIndent(), structName)
	fmt.Fprintf(buf, "%s    {\n", cv.CppIndent())
	fmt.Fprintf(buf, "%s        value.reset(new %sImpl<T, std::unique_ptr<T>>(new T(ref)));\n", cv.CppIndent(), structName)
	fmt.Fprintf(buf, "%s    }\n", cv.CppIndent())
	fmt.Fprintf(buf, "\n")
	fmt.Fprintf(buf, "%s    template<typename T>\n", cv.CppIndent())
	fmt.Fprintf(buf, "%s    %s(const T& ref)\n", cv.CppIndent(), structName)
	fmt.Fprintf(buf, "%s    {\n", cv.CppIndent())
	fmt.Fprintf(buf, "%s        value.reset(new %sImpl<T, std::unique_ptr<T>>(new T(ref)));\n", cv.CppIndent(), structName)
	fmt.Fprintf(buf, "%s    }\n", cv.CppIndent())
	fmt.Fprintf(buf, "\n")
	fmt.Fprintf(buf, "%s    template<typename T>\n", cv.CppIndent())
	fmt.Fprintf(buf, "%s    %s(T* ptr)\n", cv.CppIndent(), structName)
	fmt.Fprintf(buf, "%s    {\n", cv.CppIndent())
	fmt.Fprintf(buf, "%s        value.reset(new %sImpl<T, gocpp::ptr<T>>(ptr));\n", cv.CppIndent(), structName)
	fmt.Fprintf(buf, "%s    }\n", cv.CppIndent())
	fmt.Fprintf(buf, "\n")
	fmt.Fprintf(buf, "%s    using isGoStruct = void;\n", cv.CppIndent())
	fmt.Fprintf(buf, "\n")
	fmt.Fprintf(buf, "%s    std::ostream& PrintTo(std::ostream& os) const\n", cv.CppIndent())
	fmt.Fprintf(buf, "%s    {\n", cv.CppIndent())
	fmt.Fprintf(buf, "%s        return os;\n", cv.CppIndent())
	fmt.Fprintf(buf, "%s    }\n", cv.CppIndent())
	fmt.Fprintf(buf, "\n")
	fmt.Fprintf(buf, "%s    struct I%s\n", cv.CppIndent(), structName)
	fmt.Fprintf(buf, "%s    {\n", cv.CppIndent())
	cv.cppIndent++
	for _, method := range methods {
		fmt.Fprintf(buf, "%s    virtual %s v%s(%s) = 0;\n", cv.CppIndent(), method.result, method.name, method.params)
	}
	cv.cppIndent--
	fmt.Fprintf(buf, "%s    };\n", cv.CppIndent())
	fmt.Fprintf(buf, "\n")
	fmt.Fprintf(buf, "%s    template<typename T, typename StoreT>\n", cv.CppIndent())
	fmt.Fprintf(buf, "%s    struct %[2]sImpl : I%[2]s\n", cv.CppIndent(), structName)
	fmt.Fprintf(buf, "%s    {\n", cv.CppIndent())
	// ** Maybe be needed if we decide to store values insstead of pointer at some point **
	// fmt.Fprintf(buf, "%s        //%sImpl(T& ref)\n", cv.CppIndent(), structName)
	// fmt.Fprintf(buf, "%s        //{\n", cv.CppIndent())
	// fmt.Fprintf(buf, "%s        //    value = &ref;\n", cv.CppIndent())
	// fmt.Fprintf(buf, "%s        //}\n", cv.CppIndent())
	// fmt.Fprintf(buf, "\n")
	fmt.Fprintf(buf, "%s        explicit %sImpl(T* ptr)\n", cv.CppIndent(), structName)
	fmt.Fprintf(buf, "%s        {\n", cv.CppIndent())
	fmt.Fprintf(buf, "%s            value.reset(ptr);\n", cv.CppIndent())
	fmt.Fprintf(buf, "%s        }\n", cv.CppIndent())
	cv.cppIndent++
	for _, method := range methods {
		fmt.Fprintf(buf, "\n")
		fmt.Fprintf(buf, "%s    %s v%s(%s) override\n", cv.CppIndent(), method.result, method.name, method.params)
		fmt.Fprintf(buf, "%s    {\n", cv.CppIndent())
		fmt.Fprintf(buf, "%s        return %s(gocpp::PtrRecv<T, true>(value.get()));\n", cv.CppIndent(), method.name)
		fmt.Fprintf(buf, "%s    }\n", cv.CppIndent())
	}
	cv.cppIndent--
	fmt.Fprintf(buf, "\n")
	fmt.Fprintf(buf, "%s        StoreT value;\n", cv.CppIndent())
	fmt.Fprintf(buf, "%s    };\n", cv.CppIndent())
	fmt.Fprintf(buf, "\n")
	fmt.Fprintf(buf, "%s    std::shared_ptr<I%s> value;\n", cv.CppIndent(), structName)
	fmt.Fprintf(buf, "%s};\n", cv.CppIndent())

	for _, method := range methods {
		endParams := ""
		if method.params != "" {
			endParams = fmt.Sprintf(", %s", method.params)
		}
		fmt.Fprintf(buf, "\n")
		fmt.Fprintf(buf, "%s%s %s(const gocpp::PtrRecv<%s, false>& self%s)\n", cv.CppIndent(), method.result, method.name, structName, endParams)
		fmt.Fprintf(buf, "%s{\n", cv.CppIndent())
		fmt.Fprintf(buf, "%s    return self.ptr->value->v%s(%s);\n", cv.CppIndent(), method.name, method.params)
		fmt.Fprintf(buf, "%s}\n", cv.CppIndent())
		fmt.Fprintf(buf, "\n")
		fmt.Fprintf(buf, "%s%s %s(const gocpp::ObjRecv<%s>& self%s)\n", cv.CppIndent(), method.result, method.name, structName, endParams)
		fmt.Fprintf(buf, "%s{\n", cv.CppIndent())
		fmt.Fprintf(buf, "%s    return self.obj.value->v%s(%s);\n", cv.CppIndent(), method.name, method.params)
		fmt.Fprintf(buf, "%s}\n", cv.CppIndent())
	}

	if withStreamOperator {
		fmt.Fprintf(buf, "\n")
		fmt.Fprintf(buf, "%sstd::ostream& operator<<(std::ostream& os, const %s& value)\n", cv.CppIndent(), structName)
		fmt.Fprintf(buf, "%s{\n", cv.CppIndent())
		fmt.Fprintf(buf, "%s    return value.PrintTo(os);\n", cv.CppIndent())
		fmt.Fprintf(buf, "%s}\n", cv.CppIndent())
		fmt.Fprintf(buf, "\n")
	}
	return buf.String()
}

// TODO: return typeDefs
func (cv *cppVisitor) convertExpr(node ast.Expr) string {
	if node == nil {
		return ""
	}

	switch n := node.(type) {
	case *ast.ArrayType:
		array := cv.convertArrayTypeExpr(n)
		// TODO: typeDefs should be and output of convertExpr
		// HACK: cv.cppOut shouldn't be used here
		for _, def := range array.defs {
			fmt.Fprintf(cv.cppOut, "%s%s\n", cv.CppIndent(), def)
		}

		// Type used as parameter, we use a dummy tag value that is used only for its type
		return fmt.Sprintf("gocpp::Tag<%s>()", array.str)

	case *ast.MapType:
		mapType := cv.convertMapTypeExpr(n)
		// TODO: mapDefs should be and output of convertExpr
		// HACK: cv.cppOut shouldn't be used here
		for _, def := range mapType.defs {
			fmt.Fprintf(cv.cppOut, "%s%s\n", cv.CppIndent(), def)
		}

		// Type used as parameter, we use a dummy tag value that is used only for its type
		return fmt.Sprintf("gocpp::Tag<%s>()", mapType.str)

	case *ast.BasicLit:
		if n.Kind == token.IMAG {
			return "gocpp::complex128(0, " + strings.Replace(n.Value, "i", "", -1) + ")"
		} else {
			return n.Value
		}

	case *ast.CompositeLit:
		// ignore 'n.Incomplete' at the moment
		buf := new(bytes.Buffer)
		var litType string
		if n.Type != nil {

			array := cv.convertTypeExpr(n.Type)
			// TODO: typeDefs should be and output of convertExpr
			// HACK: cv.cppOut shouldn't be used here
			for _, def := range array.defs {
				fmt.Fprintf(cv.cppOut, "%s%s\n", cv.CppIndent(), def)
			}

			litType = array.str
		}

		var isKvInit bool
		if len(n.Elts) != 0 {
			_, isKvInit = n.Elts[0].(*ast.KeyValueExpr)
		}

		if isKvInit && !isMapType(n.Type) {
			fmt.Fprintf(buf, "%s::Init([](%s& x) { ", litType, litType)
			for _, elt := range n.Elts {
				kv := elt.(*ast.KeyValueExpr)
				fmt.Fprintf(buf, "x.%s = %s; ", kv.Key, cv.convertExpr(kv.Value))
			}
			fmt.Fprintf(buf, "})")
		} else {
			fmt.Fprintf(buf, "%s {", litType)
			var sep = ""
			for _, elt := range n.Elts {
				fmt.Fprintf(buf, "%s%s", sep, cv.convertExpr(elt))
				sep = ", "
			}
			fmt.Fprintf(buf, "}")
		}
		return buf.String()

	case *ast.FuncLit:
		buf := new(bytes.Buffer)
		bufio := bufio.NewWriter(buf)
		previousOut := cv.cppOut
		defer func() { cv.cppOut = previousOut }()
		cv.cppOut = bufio

		params := cv.readFields(n.Type.Params)
		outNames, outTypes := cv.getResultInfos(n.Type)
		resultType := buildOutType(outTypes)

		cv.DeclareVars(params)

		fmt.Fprintf(bufio, "[=](%s) mutable -> %s\n", params, resultType)

		cv.astIndent++
		cv.convertBlockStmt(n.Body, blockEnv{stmtEnv{outNames, outTypes}, true})
		cv.astIndent--

		bufio.Flush()
		return buf.String()

	case *ast.UnaryExpr:
		_, isCompositeLit := n.X.(*ast.CompositeLit)

		switch {
		case n.Op == token.AND && isCompositeLit:
			// FIME : create a kind a smart pointer instead of this.
			return "new " + cv.convertExpr(n.X)
		default:
			return convertToken(n.Op) + " " + cv.convertExpr(n.X)
		}

	case *ast.ParenExpr:
		return "(" + cv.convertExpr(n.X) + ")"

	case *ast.KeyValueExpr:
		return fmt.Sprintf("{ %s, %s }", cv.convertExpr(n.Key), cv.convertExpr(n.Value))

	case *ast.BinaryExpr:
		return cv.convertExpr(n.X) + " " + convertToken(n.Op) + " " + cv.convertExpr(n.Y)
		// import "go/type"
		//xType := types.ExprString(n.X)
		//yType := types.ExprString(n.Y)
		//if xType == yType {
		//	return cv.convertExpr(n.X) + " " + convertToken(n.Op) + " " + cv.convertExpr(n.Y)
		//} else {
		//	return ...
		//}

	case *ast.CallExpr:
		buf := new(bytes.Buffer)

		var sep = ""
		switch fun := n.Fun.(type) {
		case *ast.SelectorExpr:
			if isNameSpace(fun.X) {
				fmt.Fprintf(buf, "%v(", GetCppFunc(cv.convertExpr(fun.X)+"::"+cv.convertExpr(fun.Sel)))
			} else {
				fmt.Fprintf(buf, "%v(gocpp::recv(%v)", cv.convertExpr(fun.Sel), cv.convertExpr(fun.X))
				sep = ", "
			}
		default:
			fmt.Fprintf(buf, "%v(", cv.convertExpr(n.Fun))
		}

		for _, arg := range n.Args {
			fmt.Fprintf(buf, "%s%s", sep, cv.convertExpr(arg))
			sep = ", "
		}
		fmt.Fprintf(buf, ")")
		return buf.String()

	case *ast.Ident:
		return GetCppFunc(n.Name)

	case *ast.IndexExpr:
		return fmt.Sprintf("%s[%s]", cv.convertExpr(n.X), cv.convertExpr(n.Index))

	case *ast.SelectorExpr:
		name := cv.convertExpr(n.X)

		if isNameSpace(n.X) {
			return GetCppFunc(name + "::" + cv.convertExpr(n.Sel))
		} else {
			if cv.IsPtr(name) {
				return GetCppFunc(name + "->" + cv.convertExpr(n.Sel))
			} else {
				return GetCppFunc(name + "." + cv.convertExpr(n.Sel))
			}
		}

	case *ast.SliceExpr:
		if n.Slice3 {
			panic("TODO: 3 value slice not implemented")
		} else if n.Low == nil {
			return fmt.Sprintf("%s.make_slice(0, %s)", cv.convertExpr(n.X), cv.convertExpr(n.High))
		} else if n.High == nil {
			return fmt.Sprintf("%s.make_slice(%s)", cv.convertExpr(n.X), cv.convertExpr(n.Low))
		} else {
			return fmt.Sprintf("%s.make_slice(%s, %s)", cv.convertExpr(n.X), cv.convertExpr(n.Low), cv.convertExpr(n.High))
		}

	case *ast.StarExpr:
		return fmt.Sprintf("*%s", cv.convertExpr(n.X))

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

func (cv *cppVisitor) convertExprs(exprs []ast.Expr) string {
	var strs []string
	for _, expr := range exprs {
		strs = append(strs, cv.convertExpr(expr))
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
		if cv.genMakeFile {
			cv.makeOut.Flush()
		}

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
	genMakeFile := flag.Bool("genMakeFile", false, "generate Makefile")
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
	cv.genMakeFile = *genMakeFile
	cv.binOutDir = *binOutDir
	cv.cppOutDir = *cppOutDir
	cv.supportHeader = "gocpp/support.h"
	cv.inputName = *inputName
	cv.baseName = strings.TrimSuffix(cv.inputName, ".go")
	cv.Init()

	fmt.Printf("\n=====\n")
	ast.Walk(cv, f)
}
