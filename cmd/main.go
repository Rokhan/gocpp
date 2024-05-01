package main

import (
	"bufio"
	"bytes"
	"container/list"
	"flag"
	"fmt"
	"go/ast"
	"go/importer"
	"go/parser"
	"go/token"
	"go/types"
	"log"
	"os"
	"path"
	"reflect"
	"strings"
)

// cf following files to add missing types:
//
//	=> "go\types\basic.go"
//	=> "go\types\universe.go"
var stdTypeMapping = map[string]string{
	"byte":       "unsigned char",
	"complex128": "gocpp::complex128",
	"float":      "double",
	"float32":    "float",
	"float64":    "double",
	"int":        "int",
	"string":     "std::string",
	"uint":       "unsigned int",
	"uint8":      "uint8_t",
	"uint16":     "uint16_t",
	"uint32":     "uint32_t",
	"uint64":     "uint64_t",
	// untyped types !!!
	"untyped bool":    "bool",
	"untyped complex": "goccp::complex128",
	"untyped float":   "double",
	"untyped int":     "int",
	"untyped string":  "string",
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
	// fmt
	"fmt::Print":   "mocklib::Print",
	"fmt::Printf":  "mocklib::Printf",
	"fmt::Println": "mocklib::Println",
	"fmt::Sprint":  "mocklib::Sprint",
	"fmt::Sprintf": "mocklib::Sprintf",
	// rand
	"rand::Intn": "mocklib::Intn",
	// runtime
	"runtime::GOOS": "mocklib::GOOS",
	// cmplx
	"cmplx::Sqrt": "std::sqrt",
	// math
	"math::Pow":   "mocklib::Pow",
	"math::Sqrt":  "std::sqrt",
	"math::Sqrt2": "mocklib::Sqrt2",
	"math::Pi":    "mocklib::Pi",
	// pic
	"pic::Show": "mocklib::picShow",
	// time
	"time::After":       "mocklib::After",
	"time::Tick":        "mocklib::Tick",
	"time::Now":         "mocklib::Date::Now",
	"time::Saturday":    "mocklib::Date::Saturday",
	"time::Sleep":       "mocklib::Sleep",
	"time::Second":      "mocklib::Second",
	"time::Millisecond": "mocklib::Millisecond",
	// strings
	"strings::Join":   "mocklib::StringsJoin",
	"strings::Fields": "mocklib::StringsFields",
	// sync
	"sync::Mutex": "mocklib::Mutex",

	// wc
	"wc::Test": "mocklib::wcTest",

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

type outFile struct {
	file   *os.File
	out    *bufio.Writer
	indent int
}

type cppConverter struct {
	baseName      string
	inputName     string
	supportHeader string

	// golang tokens and types infos
	typeInfo *types.Info
	fileSet  *token.FileSet

	// Parsing and codegen parameters
	currentSwitchId *list.List
	idCount         int
	scopes          *list.List
	iota_value      int

	// Logs and makefile parameters
	genMakeFile bool
	makeOutFile *os.File
	makeOut     *bufio.Writer
	binOutDir   string
	astIndent   int

	// Cpp files parameters
	cppOutDir string
	cpp       outFile
	hpp       outFile
	fwd       outFile
}

func (cv *cppConverter) ResetIota() {
	cv.iota_value = 0
}

func (cv *cppConverter) Iota() string {
	return fmt.Sprintf("%d", cv.iota_value)
}

func (cv *cppConverter) UpdateIota() {
	cv.iota_value++
}

func (cv *cppConverter) Indent() string {
	return strings.Repeat("  ", cv.astIndent)
}

func (of *outFile) Indent() string {
	return strings.Repeat("    ", of.indent)
}

func (cv *cppConverter) GenerateId() (id string) {
	id = fmt.Sprintf("gocpp_id_%d", cv.idCount)
	cv.idCount++
	return id
}

const dbgPrefix string = "         "

func printCppIntro(cv *cppConverter) {
	//temporarily blindly add "includes" and "using"
	fmt.Fprintf(cv.cpp.out, "#include <complex>\n")
	fmt.Fprintf(cv.cpp.out, "#include <functional>\n")
	fmt.Fprintf(cv.cpp.out, "#include <iostream>\n")
	fmt.Fprintf(cv.cpp.out, "#include <iomanip>\n")
	fmt.Fprintf(cv.cpp.out, "#include <map>\n")
	fmt.Fprintf(cv.cpp.out, "#include <string>\n")
	fmt.Fprintf(cv.cpp.out, "#include <tuple>\n")
	fmt.Fprintf(cv.cpp.out, "#include <vector>\n")
	fmt.Fprintf(cv.cpp.out, "\n")
	fmt.Fprintf(cv.cpp.out, "#include \"%s.h\"\n", cv.baseName)
	fmt.Fprintf(cv.cpp.out, "#include \"%s\"\n", cv.supportHeader)
	fmt.Fprintf(cv.cpp.out, "\n")
	fmt.Fprintf(cv.cpp.out, "\n")

	// Put everything generated in "golang" namespace
	fmt.Fprintf(cv.cpp.out, "namespace golang\n")
	fmt.Fprintf(cv.cpp.out, "{\n")
	cv.cpp.indent++
}

func printCppOutro(cv *cppConverter) {
	// Close golang namespace
	cv.cpp.indent--
	fmt.Fprintf(cv.cpp.out, "}\n")
	fmt.Fprintf(cv.cpp.out, "\n")

	// TODO: manage main parameters
	fmt.Fprintf(cv.cpp.out, "int main()\n")
	fmt.Fprintf(cv.cpp.out, "{\n")
	fmt.Fprintf(cv.cpp.out, "    try\n")
	fmt.Fprintf(cv.cpp.out, "    {\n")
	fmt.Fprintf(cv.cpp.out, "        std::cout << std::boolalpha << std::fixed << std::setprecision(5);\n")
	fmt.Fprintf(cv.cpp.out, "        golang::main();\n")
	fmt.Fprintf(cv.cpp.out, "        return 0;\n")
	fmt.Fprintf(cv.cpp.out, "    }\n")
	fmt.Fprintf(cv.cpp.out, "    catch(const gocpp::GoPanic& ex)\n")
	fmt.Fprintf(cv.cpp.out, "    {\n")
	fmt.Fprintf(cv.cpp.out, "        std::cout << \"Panic: \" << ex.what() << std::endl;\n")
	fmt.Fprintf(cv.cpp.out, "        return -1;\n")
	fmt.Fprintf(cv.cpp.out, "    }\n")
	fmt.Fprintf(cv.cpp.out, "}\n")
}

func printHppIntro(cv *cppConverter) {
	//temporarily blindly add "includes" and "using"
	fmt.Fprintf(cv.hpp.out, "#pragma once\n")
	fmt.Fprintf(cv.hpp.out, "\n")
	fmt.Fprintf(cv.hpp.out, "#include <functional>\n")
	fmt.Fprintf(cv.hpp.out, "#include <string>\n")
	fmt.Fprintf(cv.hpp.out, "#include <tuple>\n")
	fmt.Fprintf(cv.hpp.out, "#include <vector>\n")
	fmt.Fprintf(cv.hpp.out, "\n")
	fmt.Fprintf(cv.hpp.out, "#include \"%s.fwd.h\"\n", cv.baseName)
	fmt.Fprintf(cv.hpp.out, "#include \"%s\"\n", cv.supportHeader)
	fmt.Fprintf(cv.hpp.out, "\n")

	// Put everything generated in "golang" namespace
	fmt.Fprintf(cv.hpp.out, "namespace golang\n")
	fmt.Fprintf(cv.hpp.out, "{\n")
	cv.hpp.indent++
}

func printHppOutro(cv *cppConverter) {
	// Close golang namespace
	cv.hpp.indent--
	fmt.Fprintf(cv.hpp.out, "}\n")
	fmt.Fprintf(cv.hpp.out, "\n")
}

func printFwdIntro(cv *cppConverter) {
	fmt.Fprintf(cv.fwd.out, "#pragma once\n")
	fmt.Fprintf(cv.fwd.out, "\n")

	// Put everything generated in "golang" namespace
	fmt.Fprintf(cv.fwd.out, "namespace golang\n")
	fmt.Fprintf(cv.fwd.out, "{\n")
	cv.fwd.indent++
}

func printFwdOutro(cv *cppConverter) {
	// Close golang namespace
	cv.fwd.indent--
	fmt.Fprintf(cv.fwd.out, "}\n")
	fmt.Fprintf(cv.fwd.out, "\n")
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

func (cv *cppConverter) Init() {
	cv.currentSwitchId = new(list.List)
	cv.scopes = new(list.List)

	if cv.genMakeFile {
		cv.makeOutFile = createOutput(cv.cppOutDir, "Makefile")
		cv.makeOut = bufio.NewWriter(cv.makeOutFile)

		fmt.Fprintf(cv.makeOut, "all:\n")
	}
}

type variables map[string]bool

func (cv *cppConverter) startScope() {
	cv.scopes.PushBack(variables{})
}

func (cv *cppConverter) endScope() {
	cv.scopes.Remove(cv.scopes.Back())
}

func (cv *cppConverter) DeclareVar(name string, isPtr bool) {
	vars := cv.scopes.Back().Value.(variables)
	vars[name] = isPtr
}

func (cv *cppConverter) DeclareVars(params typeNames) {
	for _, param := range params {
		for _, name := range param.names {
			cv.DeclareVar(name, param.Type.isPtr)
		}
	}
}

// FIXME : manage composed names like A.B.C
func (cv *cppConverter) IsPtr(name string) bool {
	for elt := cv.scopes.Back(); elt != nil; elt = elt.Prev() {
		vars := elt.Value.(variables)
		value, ok := vars[name]
		if ok {
			return value
		}
	}
	return false
}

func (cv *cppConverter) IsExprPtr(expr ast.Expr) bool {
	goType := cv.convertExprType(expr)

	switch goType.(type) {
	case *types.Pointer:
		return true

	// TODO: types.Named, types.Alias ??

	default:
		return false
	}
}

func (cv *cppConverter) IsExprMap(expr ast.Expr) bool {
	goType := cv.convertExprType(expr)
	return cv.IsTypeMap(goType)
}

func (cv *cppConverter) IsTypeMap(goType types.Type) bool {
	switch t := goType.(type) {
	case *types.Map:
		return true

	case *types.Named:
		return cv.IsTypeMap(t.Underlying())

	// case *types.Alias:
	// 	return cv.IsTypeMap(types.Unalias(t))

	default:
		return false
	}
}

// func (cv *cppConverter) cppPrintf(format string, a ...interface{}) (n int, err error) {
// 	return fmt.Fprintf(cv.cpp.out, "%s"+format, append([]interface{}{cv.cpp.Indent()}, a...)...)
// }

func (cv *cppConverter) ConvertFile(node ast.File) {

	cv.startScope()
	fmt.Printf("%s %s %v\n", dbgPrefix, cv.Indent(), reflect.TypeOf(node))

	cv.cpp.file = createOutputExt(cv.cppOutDir, cv.baseName, "cpp")
	cv.cpp.out = bufio.NewWriter(cv.cpp.file)

	cv.hpp.file = createOutputExt(cv.cppOutDir, cv.baseName, "h")
	cv.hpp.out = bufio.NewWriter(cv.hpp.file)

	cv.fwd.file = createOutputExt(cv.cppOutDir, cv.baseName, "fwd.h")
	cv.fwd.out = bufio.NewWriter(cv.fwd.file)

	printCppIntro(cv)
	printHppIntro(cv)
	printFwdIntro(cv)

	for _, decl := range node.Decls {
		var outlines []string

		cppOut := cv.withCppBuffer(func() {
			decOutline := cv.convertDecls(decl, true)
			outlines = append(outlines, decOutline...)
		})

		for _, outline := range outlines {
			fmt.Fprintf(cv.cpp.out, "%s%s\n", cv.cpp.Indent(), outline)
		}

		fmt.Fprintf(cv.cpp.out, "%s", cppOut)
	}

	if cv.genMakeFile {
		fmt.Fprintf(cv.makeOut, "\t g++ -std=c++20 -I. -I../includes -I../thirdparty/includes %s.cpp -o ../%s/%s.exe\n", cv.baseName, cv.binOutDir, cv.baseName)
	}

	//fmt.Printf("%s Name: %v\n", v.Indent(), n.Name)
	//fmt.Printf("%s Scope: %v\n", v.Indent(), n.Scope)
	cv.endScope()

	printCppOutro(cv)
	printHppOutro(cv)
	printFwdOutro(cv)

	cv.cpp.out.Flush()
	cv.hpp.out.Flush()
	cv.fwd.out.Flush()
	if cv.genMakeFile {
		cv.makeOut.Flush()
	}
}

func (cv *cppConverter) readFields(fields *ast.FieldList) (params typeNames) {
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

func (cv *cppConverter) readMethods(fields *ast.FieldList) (methods []method) {
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

func needPriority(t token.Token) bool {
	switch t {
	case token.SHL, token.SHR:
		return true
	default:
		return false
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

func (cv *cppConverter) outputsPrint(place place, outlines *[]string) {
	if place.inline != nil {
		fmt.Fprintf(cv.cpp.out, "%s%s", cv.cpp.Indent(), *place.inline)
	}
	if place.outline != nil {
		*outlines = append(*outlines, *place.outline)
	}
	if place.header != nil {
		fmt.Fprintf(cv.hpp.out, "%s%s", cv.hpp.Indent(), *place.header)
	}
}

func (cv *cppConverter) convertDecls(decl ast.Decl, isNameSpace bool) (outlines []string) {
	switch d := decl.(type) {
	case *ast.GenDecl:
		for _, place := range cv.convertSpecs(d.Specs, isNameSpace, ";\n") {
			cv.outputsPrint(place, &outlines)
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
		for _, param := range params {
			for _, place := range param.Type.defs {
				cv.outputsPrint(place, &outlines)
			}
		}

		fmt.Fprintf(cv.cpp.out, "%s%s %s(%s)\n", cv.cpp.Indent(), resultType, d.Name.Name, params)
		fmt.Fprintf(cv.hpp.out, "%s%s %s(%s);\n", cv.cpp.Indent(), resultType, d.Name.Name, params)

		blockOutlines := cv.convertBlockStmt(d.Body, blockEnv{stmtEnv{outNames, outTypes}, true})
		outlines = append(outlines, blockOutlines...)
		fmt.Fprintf(cv.cpp.out, "\n")

	case *ast.BadDecl:
		panic("convertDecls[BadDecl] Not implemented")

	default:
		panic("convertDecls, unmanaged subtype")
	}
	return
}

func (cv *cppConverter) convertBlockStmt(block *ast.BlockStmt, env blockEnv) (outlines []string) {
	cv.startScope()
	fmt.Fprintf(cv.cpp.out, "%s{\n", cv.cpp.Indent())
	cv.cpp.indent++

	if env.isFunc {
		fmt.Fprintf(cv.cpp.out, "%sgocpp::Defer defer;\n", cv.cpp.Indent())
	}

	for i := range env.outNames {
		fmt.Fprintf(cv.cpp.out, "%s%s %s;\n", cv.cpp.Indent(), GetCppType(env.outTypes[i]), env.outNames[i])
	}

	for _, stmt := range block.List {
		outlines = append(outlines, cv.convertStmt(stmt, env.stmtEnv)...)
	}

	cv.cpp.indent--
	fmt.Fprintf(cv.cpp.out, "%s}\n", cv.cpp.Indent())
	cv.endScope()
	return
}

func (cv *cppConverter) convertReturnExprs(exprs []ast.Expr, outNames []string) string {
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

func (cv *cppConverter) convertAssignRightExprs(exprs []ast.Expr) string {
	switch len(exprs) {
	case 0:
		return ""
	case 1:
		return cv.convertExprs(exprs)
	default:
		return fmt.Sprintf("std::tuple{%s}", cv.convertExprs(exprs))
	}
}

func (cv *cppConverter) convertAssignExprs(stmt *ast.AssignStmt) string {
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
		Panicf("convertAssignExprs, unmanaged token: %s, input: %v", stmt.Tok, cv.Position(stmt))
	}

	// should be unreacheable
	panic("convertAssignExprs, unmanaged case")
}

func (cv *cppConverter) convertStmt(stmt ast.Stmt, env stmtEnv) (outlines []string) {
	switch s := stmt.(type) {
	case *ast.BlockStmt:
		outlines = cv.convertBlockStmt(s, blockEnv{env, false})

	case *ast.DeclStmt:
		outlines = cv.convertDecls(s.Decl, false)

	case *ast.ExprStmt:
		fmt.Fprintf(cv.cpp.out, "%s%s;\n", cv.cpp.Indent(), cv.convertExpr(s.X))

	case *ast.IncDecStmt:
		fmt.Fprintf(cv.cpp.out, "%s%s%s;\n", cv.cpp.Indent(), cv.convertExpr(s.X), s.Tok)

	case *ast.ReturnStmt:
		fmt.Fprintf(cv.cpp.out, "%s%s;\n", cv.cpp.Indent(), cv.convertReturnExprs(s.Results, env.outNames))

	case *ast.AssignStmt:
		fmt.Fprintf(cv.cpp.out, "%s%s;\n", cv.cpp.Indent(), cv.convertAssignExprs(s))

	case *ast.DeferStmt:
		fmt.Fprintf(cv.cpp.out, "%sdefer.push_back([=]{ %s; });\n", cv.cpp.Indent(), cv.convertExpr(s.Call))

	case *ast.GoStmt:
		fmt.Fprintf(cv.cpp.out, "%sgocpp::go([&]{ %s; });\n", cv.cpp.Indent(), cv.convertExpr(s.Call))

	case *ast.SendStmt:
		fmt.Fprintf(cv.cpp.out, "%s%s.send(%s);\n", cv.cpp.Indent(), cv.convertExpr(s.Chan), cv.convertExpr(s.Value))

	case *ast.ForStmt:
		fmt.Fprintf(cv.cpp.out, "%sfor(%s; %s; %s)\n", cv.cpp.Indent(), cv.inlineStmt(s.Init), cv.convertExpr(s.Cond), cv.inlineStmt(s.Post))
		outlines = cv.convertBlockStmt(s.Body, blockEnv{env, false})

	case *ast.BranchStmt:
		switch s.Tok {
		case token.BREAK:
			fmt.Fprintf(cv.cpp.out, "%sbreak;\n", cv.cpp.Indent())
		case token.CONTINUE:
			fmt.Fprintf(cv.cpp.out, "%scontinue;\n", cv.cpp.Indent())
		default:
			Panicf("convertStmt, unmanaged BranchStmt [%v], input: %v", s.Tok, cv.Position(s))
		}

	case *ast.RangeStmt:
		if s.Key != nil && s.Value != nil && s.Tok == token.DEFINE {
			fmt.Fprintf(cv.cpp.out, "%sfor(auto [%s, %s] : %s)\n", cv.cpp.Indent(), cv.convertExpr(s.Key), cv.convertExpr(s.Value), cv.convertExpr(s.X))
		} else if s.Key != nil && s.Value == nil && s.Tok == token.DEFINE {
			fmt.Fprintf(cv.cpp.out, "%sfor(auto [%s, gocpp_ignored] : %s)\n", cv.cpp.Indent(), cv.convertExpr(s.Key), cv.convertExpr(s.X))
		} else {
			panic("Unmanaged case of '*ast.RangeStmt'")
		}
		outlines = cv.convertBlockStmt(s.Body, blockEnv{env, false})

	case *ast.IfStmt:
		if s.Init != nil {
			fmt.Fprintf(cv.cpp.out, "%sif(%s; %s)\n", cv.cpp.Indent(), cv.inlineStmt(s.Init), cv.convertExpr(s.Cond))
		} else {
			fmt.Fprintf(cv.cpp.out, "%sif(%s)\n", cv.cpp.Indent(), cv.convertExpr(s.Cond))
		}

		blockOutline := cv.convertBlockStmt(s.Body, blockEnv{env, false})
		outlines = append(outlines, blockOutline...)
		if s.Else != nil {
			fmt.Fprintf(cv.cpp.out, "%selse\n", cv.cpp.Indent())
			elseOutline := cv.convertStmt(s.Else, env)
			outlines = append(outlines, elseOutline...)
		}

	case *ast.SwitchStmt:
		fmt.Fprintf(cv.cpp.out, "%s//Go switch emulation\n", cv.cpp.Indent())
		fmt.Fprintf(cv.cpp.out, "%s{\n", cv.cpp.Indent())
		cv.cpp.indent++

		if s.Init != nil {
			fmt.Fprintf(cv.cpp.out, "%s%s;\n", cv.cpp.Indent(), cv.inlineStmt(s.Init))
		}

		inputVarName := ""
		if s.Tag != nil {
			inputVarName = "condition"
			fmt.Fprintf(cv.cpp.out, "%sauto %s = %s;\n", cv.cpp.Indent(), inputVarName, cv.convertExpr(s.Tag))
		}

		cv.convertSwitchBody(env, s.Body, "conditionId", inputVarName)

	case *ast.SelectStmt:
		fmt.Fprintf(cv.cpp.out, "%s//Go select emulation\n", cv.cpp.Indent())
		fmt.Fprintf(cv.cpp.out, "%s{\n", cv.cpp.Indent())
		cv.cpp.indent++

		cv.convertSwitchBody(env, s.Body, "conditionId", "")
		fmt.Fprintf(cv.cpp.out, "%sstd::this_thread::yield();\n", cv.cpp.Indent())

	case *ast.CaseClause:
		if s.List == nil {
			fmt.Fprintf(cv.cpp.out, "%sdefault:\n", cv.cpp.Indent())
		} else {
			for range s.List {
				id := cv.currentSwitchId.Back().Value.(int)
				fmt.Fprintf(cv.cpp.out, "%scase %d:\n", cv.cpp.Indent(), id)
				cv.currentSwitchId.Back().Value = id + 1
			}
		}

		cv.cpp.indent++
		for _, stmt := range s.Body {
			stmtOutline := cv.convertStmt(stmt, env)
			outlines = append(outlines, stmtOutline...)
		}
		fmt.Fprintf(cv.cpp.out, "%sbreak;\n", cv.cpp.Indent())
		cv.cpp.indent--

	case *ast.CommClause:

		if s.Comm == nil {
			fmt.Fprintf(cv.cpp.out, "%sdefault:\n", cv.cpp.Indent())
		} else {
			id := cv.currentSwitchId.Back().Value.(int)
			fmt.Fprintf(cv.cpp.out, "%scase %d:\n", cv.cpp.Indent(), id)
			cv.currentSwitchId.Back().Value = id + 1
		}

		cv.cpp.indent++
		for _, stmt := range s.Body {
			stmtOutline := cv.convertStmt(stmt, env)
			outlines = append(outlines, stmtOutline...)
		}
		fmt.Fprintf(cv.cpp.out, "%sbreak;\n", cv.cpp.Indent())
		cv.cpp.indent--

	default:
		Panicf("convertStmt, unmanaged type [%v], input: %v", reflect.TypeOf(s), cv.Position(s))
	}
	return
}

type switchEnvName struct {
	inputVarName     string
	conditionVarName string
	prefix           string
	withCondition    bool
}

func (cv *cppConverter) convertSwitchBody(env stmtEnv, body *ast.BlockStmt, conditionVarName string, inputVarName string) (outlines []string) {

	fmt.Fprintf(cv.cpp.out, "%sint %s = -1;\n", cv.cpp.Indent(), conditionVarName)
	se := switchEnvName{inputVarName, conditionVarName, "", inputVarName != ""}
	cv.extractCaseExpr(body, &se)
	fmt.Fprintf(cv.cpp.out, "%sswitch(%s)\n", cv.cpp.Indent(), conditionVarName)

	cv.currentSwitchId.PushBack(0)
	outlines = cv.convertBlockStmt(body, blockEnv{env, false})
	cv.currentSwitchId.Remove(cv.currentSwitchId.Back())

	cv.cpp.indent--
	fmt.Fprintf(cv.cpp.out, "%s}\n", cv.cpp.Indent())
	return
}

func (cv *cppConverter) extractCaseExpr(stmt ast.Stmt, se *switchEnvName) {
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
				fmt.Fprintf(cv.cpp.out, "%s%sif(%s == %s) { %s = %d; }\n", cv.cpp.Indent(), se.prefix, se.inputVarName, cv.convertExpr(expr), se.conditionVarName, id)
			} else {
				fmt.Fprintf(cv.cpp.out, "%s%sif(%s) { %s = %d; }\n", cv.cpp.Indent(), se.prefix, cv.convertExpr(expr), se.conditionVarName, id)
			}
			cv.currentSwitchId.Back().Value = id + 1
		}
		se.prefix = "else "

	case *ast.CommClause:
		id := cv.currentSwitchId.Back().Value.(int)
		switch comm := s.Comm.(type) {
		case *ast.SendStmt:
			fmt.Fprintf(cv.cpp.out, "%s%sif(%s) { /* SendStmt */ %s = %d; }\n", cv.cpp.Indent(), se.prefix, cv.convertSelectCaseNode(s.Comm), se.conditionVarName, id)
		case *ast.ExprStmt:
			fmt.Fprintf(cv.cpp.out, "%s%sif(%s) { /* ExprStmt */ %s = %d; }\n", cv.cpp.Indent(), se.prefix, cv.convertSelectCaseNode(comm.X), se.conditionVarName, id)
		case nil:
			/* default, nothing to do */
		default:
			Panicf("extractCaseExpr, commClause, unmanaged type [%v], input %s", reflect.TypeOf(comm), cv.Position(comm))
		}
		cv.currentSwitchId.Back().Value = id + 1
		se.prefix = "else "

	default:
		Panicf("extractCaseExpr, unmanaged type [%v], input %s", reflect.TypeOf(s), cv.Position(s))
	}
}

func (cv *cppConverter) convertSelectCaseNode(node ast.Node) (result string) {
	switch n := node.(type) {
	case nil:
		return

	case *ast.SendStmt:
		return fmt.Sprintf("%s.trySend(%s)", cv.convertExpr(n.Chan), cv.convertExpr(n.Value))

	case *ast.ExprStmt:
		return cv.convertSelectCaseNode(n.X)

	case *ast.UnaryExpr:
		switch {
		case n.Op == token.ARROW:
			return fmt.Sprintf("auto [gocpp_ignored , ok] = %s.tryRecv(); ok", cv.convertExpr(n.X))
		default:
			Panicf("convertSelectCaseStmt,unmanaged token: [%v], inout: %v", reflect.TypeOf(n.Op), cv.Position(n))
		}

	default:
		Panicf("convertSelectCaseStmt, unmanaged node: [%v], inout: %v", reflect.TypeOf(n), cv.Position(n))
	}

	// should be unreacheable
	panic("convertSelectCaseStmt, bug, unreacheable code reached !")
}

func (cv *cppConverter) inlineStmt(stmt ast.Stmt) (result string) {
	switch s := stmt.(type) {
	case nil:
		return

	case *ast.SendStmt:
		return fmt.Sprintf("%s.send(%s)", cv.convertExpr(s.Chan), cv.convertExpr(s.Value))

	case *ast.DeclStmt:
		switch d := s.Decl.(type) {
		case *ast.GenDecl:
			for _, declItem := range cv.convertSpecs(d.Specs, false, "") {
				if declItem.inline != nil {
					result += fmt.Sprintf("%s,", *declItem.inline)
				}
				if declItem.outline != nil {
					result += "### NOT IMPLEMENTED, inlineStmt, can't declare outline from here"
				}
				if declItem.header != nil {
					result += "### NOT IMPLEMENTED, inlineStmt, can't declare in header from here"
				}
			}
			return
		default:
			Panicf("inlineStmt, unmanaged subtype [%v], input: %v", reflect.TypeOf(d), cv.Position(s))
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
		Panicf("inlineStmt, unmanaged token: [%v], inout: %v", reflect.TypeOf(s), cv.Position(s))
	}

	// should be unreacheable
	panic("inlineStmt, bug, unreacheable code reached !")
}

func (cv *cppConverter) getResultInfos(funcType *ast.FuncType) (outNames, outTypes []string) {
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

func (cv *cppConverter) convertSpecs(specs []ast.Spec, isNamespace bool, end string) []place {
	var result []place

	cv.ResetIota()
	var values []ast.Expr

	for _, spec := range specs {
		switch s := spec.(type) {
		case *ast.TypeSpec:
			t := cv.convertTypeSpec(s, end)
			result = append(result, t.defs...)
			if t.str != "" {
				result = append(result, inlineStr(t.str))
			}

		case *ast.ValueSpec:
			if len(s.Values) != 0 {
				values = s.Values
			}

			if isNamespace {
				if s.Type == nil {
					for i := range s.Names {
						if len(values) == 0 {
							Panicf("convertSpecs, can't compute get variable type: %v, name:%v, input: %v", reflect.TypeOf(s), s.Names[i], cv.Position(s))
						}
						expr := cv.convertExpr(values[i])
						exprType := cv.convertExprCppType(values[i])
						name := s.Names[i].Name
						if name == "_" {
							result = append(result, inlineStr(fmt.Sprintf("%s %s = %s%s", exprType, cv.GenerateId(), expr, end)))
						} else {
							result = append(result, headerStr(fmt.Sprintf("extern %s %s%s", exprType, name, end)))
							result = append(result, inlineStr(fmt.Sprintf("%s %s = %s%s", exprType, name, expr, end)))
						}
					}
				} else {
					for i := range s.Names {
						t := cv.convertTypeExpr(s.Type)
						result = append(result, t.defs...)

						if len(values) == 0 {
							result = append(result, inlineStr(fmt.Sprintf("%s %s%s", t.str, s.Names[i].Name, end)))
						} else {
							result = append(result, inlineStr(fmt.Sprintf("%s %s = %s%s", t.str, s.Names[i].Name, cv.convertExpr(values[i]), end)))
						}
					}
				}

			} else {
				if s.Type == nil {
					for i := range s.Names {
						if len(values) == 0 {
							result = append(result, inlineStr(fmt.Sprintf("auto %s%s", s.Names[i].Name, end)))
						} else {
							result = append(result, inlineStr(fmt.Sprintf("auto %s = %s%s", s.Names[i].Name, cv.convertExpr(values[i]), end)))
						}
					}
				} else {
					for i := range s.Names {
						t := cv.convertTypeExpr(s.Type)
						result = append(result, t.defs...)
						if len(values) == 0 {
							result = append(result, inlineStr(fmt.Sprintf("%s %s%s", t.str, s.Names[i].Name, end)))
						} else {
							result = append(result, inlineStr(fmt.Sprintf("%s %s = %s%s", t.str, s.Names[i].Name, cv.convertExpr(values[i]), end)))
						}
					}
				}
			}

		case *ast.ImportSpec:
			result = append(result, inlineStr(fmt.Sprintf("// convertSpecs[ImportSpec] Not implemented => %s%s", s.Path.Value, end)))

		default:
			Panicf("convertSpecs, unmanaged type [%v], input: %v", reflect.TypeOf(s), cv.Position(s))
		}
		cv.UpdateIota()
	}

	return result
}

type place struct {
	// when type/declaration can be used inlined
	inline *string
	// when type/declaration need to be used outside function
	outline *string
	// when type/declaration need to be in header
	header *string
}

func inlineStr(str string) place {
	return place{&str, nil, nil}
}

func outlineStr(str string) place {
	return place{nil, &str, nil}
}

func headerStr(str string) place {
	return place{nil, nil, &str}
}

type cppType struct {
	str   string  // cpp type as a string
	defs  []place // inline def used by type
	isPtr bool    // is type a pointer ?
}

func (cv *cppConverter) convertTypeSpec(node *ast.TypeSpec, end string) cppType {
	if node == nil {
		panic("node is nil")
	}

	switch n := node.Type.(type) {
	case *ast.Ident:
		// TODO : manage go private/public rule to chose where to put definition
		usingDec := fmt.Sprintf("using %s = %s%s", node.Name.Name, GetCppType(n.Name), end)

		// Commented output in cpp as we only need one declaration
		return cppType{"// " + usingDec, []place{headerStr(usingDec)}, false}

	case *ast.ArrayType:
		t := cv.convertArrayTypeExpr(n)
		usingDec := fmt.Sprintf("using %s = %s%s", node.Name.Name, t.str, end)
		return cppType{"", append(t.defs, headerStr(usingDec)), false}

	case *ast.FuncType:
		// TODO: This part is probably wrong
		return cppType{fmt.Sprintf("%s %s%s", cv.convertFuncTypeExpr(n), node.Name.Name, end), nil, false}

	case *ast.MapType:
		t := cv.convertMapTypeExpr(n)
		usingDec := fmt.Sprintf("using %s = %s%s", node.Name.Name, t.str, end)
		return cppType{"", append(t.defs, headerStr(usingDec)), false}

	case *ast.StructType:
		// TODO: return type value instead of writing in forward header directly
		fmt.Fprintf(cv.fwd.out, "%sstruct %s;\n", cv.fwd.Indent(), node.Name.Name)

		// TODO: return type value instead of writing in header directly
		structDecl := cv.convertStructTypeExpr(n, genStructParam{node.Name.Name, decl, with})
		fmt.Fprintf(cv.hpp.out, "%s%s", cv.hpp.Indent(), structDecl)

		return cppType{cv.convertStructTypeExpr(n, genStructParam{node.Name.Name, implem, with}), nil, false}

	case *ast.InterfaceType:
		// TODO: return type value instead of writing in forward header directly
		fmt.Fprintf(cv.fwd.out, "%sstruct %s;\n", cv.fwd.Indent(), node.Name.Name)

		// TODO: return type value instead of writing in header directly
		structDecl := cv.convertInterfaceTypeExpr(n, genStructParam{node.Name.Name, decl, with})
		fmt.Fprintf(cv.hpp.out, "%s%s", cv.hpp.Indent(), structDecl)

		return cppType{cv.convertInterfaceTypeExpr(n, genStructParam{node.Name.Name, implem, with}), nil, false}

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

func (cv *cppConverter) convertTypeExpr(node ast.Expr) cppType {
	if node == nil {
		panic("node is nil")
	}

	switch n := node.(type) {
	case *ast.Ident:
		return cppType{GetCppType(n.Name), nil, false}

	case *ast.ArrayType:
		return cv.convertArrayTypeExpr(n)

	case *ast.ChanType:
		return cv.convertChanTypeExpr(n)

	case *ast.FuncType:
		return cppType{cv.convertFuncTypeExpr(n), nil, false}

	case *ast.MapType:
		return cv.convertMapTypeExpr(n)

	case *ast.SelectorExpr:
		typeName := GetCppFunc(cv.convertExpr(n.X) + "::" + cv.convertExpr(n.Sel))
		return cppType{typeName, nil, true}

	case *ast.StarExpr:
		t := cv.convertTypeExpr(n.X)
		return cppType{t.str + "*", t.defs, true}

	case *ast.StructType:
		name := cv.GenerateId()
		t := cv.convertStructTypeExpr(n, genStructParam{name, all, without})
		return cppType{name, []place{inlineStr(t)}, false}

	case *ast.InterfaceType:
		if n.Methods == nil || len(n.Methods.List) == 0 {
			return cppType{"std::any", nil, false}
		} else {
			name := cv.GenerateId()

			defs := []place{}

			structDecl := cv.convertInterfaceTypeExpr(n, genStructParam{name, decl, with})
			defs = append(defs, headerStr(structDecl))

			structDef := cv.convertInterfaceTypeExpr(n, genStructParam{name, implem, with})
			defs = append(defs, outlineStr(structDef))

			return cppType{name, defs, true}
		}

	default:
		return cppType{fmt.Sprintf("!!TYPE_EXPR_ERROR!! [%v]", reflect.TypeOf(node)), nil, false}
	}
}

func (cv *cppConverter) convertMethodExpr(node ast.Expr) (string, string) {
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

func (cv *cppConverter) convertArrayTypeExpr(node *ast.ArrayType) cppType {
	elt := cv.convertTypeExpr(node.Elt)

	if node.Len == nil {
		return cppType{fmt.Sprintf("gocpp::slice<%s>", elt.str), elt.defs, false}
	} else {
		return cppType{fmt.Sprintf("gocpp::array<%s, %s>", elt.str, cv.convertExpr(node.Len)), elt.defs, false}
	}
}

func (cv *cppConverter) convertChanTypeExpr(node *ast.ChanType) cppType {
	elt := cv.convertTypeExpr(node.Value)
	return cppType{fmt.Sprintf("gocpp::channel<%s>", node.Value), elt.defs, false}
}

func (cv *cppConverter) convertFuncTypeExpr(node *ast.FuncType) string {
	params := cv.readFields(node.Params)
	_, outTypes := cv.getResultInfos(node)
	resultType := buildOutType(outTypes)
	return fmt.Sprintf("std::function<%s (%s)>", resultType, params)
}

func (cv *cppConverter) convertMapTypeExpr(node *ast.MapType) cppType {
	key := cv.convertTypeExpr(node.Key)
	value := cv.convertTypeExpr(node.Value)
	return cppType{fmt.Sprintf("gocpp::map<%s, %s>", key.str, value.str), append(key.defs, value.defs...), false}
}

type GenOutputType int

const (
	decl   GenOutputType = 0
	implem GenOutputType = 1
	all    GenOutputType = 2
)

type StreamOp int

const (
	without StreamOp = 0
	with    StreamOp = 1
)

type genStructParam struct {
	name     string
	output   GenOutputType
	streamOp StreamOp
}

type genStructData struct {
	needBody     bool
	declEnd      string
	staticPrefix string
	namePrefix   string
	out          outFile
}

func (cv *cppConverter) computeGenStructData(param genStructParam) (res genStructData) {

	switch param.output {
	case all:
		res.needBody = true
		res.declEnd = ""
		res.staticPrefix = "static "
		res.namePrefix = ""
		res.out = cv.cpp
	case decl:
		res.needBody = false
		res.declEnd = ";"
		res.staticPrefix = "static "
		res.namePrefix = ""
		res.out = cv.hpp
	case implem:
		res.needBody = true
		res.declEnd = ""
		res.staticPrefix = ""
		res.namePrefix = param.name + "::"
		res.out = cv.cpp
	default:
		Panicf("unmanaged GenOutputType value %v", param.output)
	}

	return res
}

func (cv *cppConverter) convertStructTypeExpr(node *ast.StructType, param genStructParam) string {
	buf := new(bytes.Buffer)
	fields := cv.readFields(node.Fields)
	data := cv.computeGenStructData(param)

	switch param.output {
	case all, decl:
		fmt.Fprintf(buf, "struct %[1]s\n", param.name)
		fmt.Fprintf(buf, "%s{\n", data.out.Indent())

		data.out.indent++
		for _, field := range fields {
			for _, name := range field.names {
				fmt.Fprintf(buf, "%s%s %s;\n", data.out.Indent(), field.Type.str, name)
			}
		}

		fmt.Fprintf(buf, "\n")
		fmt.Fprintf(buf, "%susing isGoStruct = void;\n", data.out.Indent())
	case implem:
		// Nothing to do
	default:
		Panicf("unmanaged GenOutputType value %v", param.output)
	}

	fmt.Fprintf(buf, "\n")
	fmt.Fprintf(buf, "%sstd::ostream& %sPrintTo(std::ostream& os) const%s\n", data.out.Indent(), data.namePrefix, data.declEnd)
	if data.needBody {
		fmt.Fprintf(buf, "%s{\n", data.out.Indent())
		fmt.Fprintf(buf, "%s    os << '{';\n", data.out.Indent())
		sep := ""
		for _, field := range fields {
			for _, name := range field.names {
				fmt.Fprintf(buf, "%s    os << \"%s\" << %s;\n", data.out.Indent(), sep, name)
				sep = " "
			}
		}
		fmt.Fprintf(buf, "%s    os << '}';\n", data.out.Indent())
		fmt.Fprintf(buf, "%s    return os;\n", data.out.Indent())
		fmt.Fprintf(buf, "%s}\n", data.out.Indent())
	}

	switch param.output {
	case all, decl:
		data.out.indent--
		fmt.Fprintf(buf, "%s};\n", data.out.Indent())
	case implem:
		// Nothing to do
	default:
		Panicf("unmanaged GenOutputType value %v", param.output)
	}

	if param.streamOp == with {
		fmt.Fprintf(buf, "\n")
		fmt.Fprintf(buf, "%sstd::ostream& operator<<(std::ostream& os, const %s& value)%s\n", data.out.Indent(), param.name, data.declEnd)
		if data.needBody {
			fmt.Fprintf(buf, "%s{\n", data.out.Indent())
			fmt.Fprintf(buf, "%s    return value.PrintTo(os);\n", data.out.Indent())
			fmt.Fprintf(buf, "%s}\n", data.out.Indent())
			fmt.Fprintf(buf, "\n")
		}
	}
	return buf.String()
}

func (cv *cppConverter) convertInterfaceTypeExpr(node *ast.InterfaceType, param genStructParam) string {
	buf := new(bytes.Buffer)
	methods := cv.readMethods(node.Methods)
	data := cv.computeGenStructData(param)
	structName := param.name

	switch param.output {
	case all, decl:
		fmt.Fprintf(buf, "struct %s : gocpp::Interface\n", structName)
		fmt.Fprintf(buf, "%s{\n", data.out.Indent())
		fmt.Fprintf(buf, "%s    %s(){}\n", data.out.Indent(), structName)
		fmt.Fprintf(buf, "%s    %[2]s(%[2]s& i) = default;\n", data.out.Indent(), structName)
		fmt.Fprintf(buf, "%s    %[2]s(const %[2]s& i) = default;\n", data.out.Indent(), structName)
		fmt.Fprintf(buf, "%s    %[2]s& operator=(%[2]s& i) = default;\n", data.out.Indent(), structName)
		fmt.Fprintf(buf, "%s    %[2]s& operator=(const %[2]s& i) = default;\n", data.out.Indent(), structName)
	case implem:
		data.out.indent--
	default:
		Panicf("unmanaged GenOutputType value %v", param.output)
	}

	fmt.Fprintf(buf, "\n")
	fmt.Fprintf(buf, "%s    template<typename T>\n", data.out.Indent())
	fmt.Fprintf(buf, "%s    %s%s(T& ref)%s\n", data.out.Indent(), data.namePrefix, structName, data.declEnd)
	if data.needBody {
		fmt.Fprintf(buf, "%s    {\n", data.out.Indent())
		fmt.Fprintf(buf, "%s        value.reset(new %sImpl<T, std::unique_ptr<T>>(new T(ref)));\n", data.out.Indent(), structName)
		fmt.Fprintf(buf, "%s    }\n", data.out.Indent())
	}
	fmt.Fprintf(buf, "\n")
	fmt.Fprintf(buf, "%s    template<typename T>\n", data.out.Indent())
	fmt.Fprintf(buf, "%s    %s%s(const T& ref)%s\n", data.out.Indent(), data.namePrefix, structName, data.declEnd)
	if data.needBody {
		fmt.Fprintf(buf, "%s    {\n", data.out.Indent())
		fmt.Fprintf(buf, "%s        value.reset(new %sImpl<T, std::unique_ptr<T>>(new T(ref)));\n", data.out.Indent(), structName)
		fmt.Fprintf(buf, "%s    }\n", data.out.Indent())
	}
	fmt.Fprintf(buf, "\n")
	fmt.Fprintf(buf, "%s    template<typename T>\n", data.out.Indent())
	fmt.Fprintf(buf, "%s    %s%s(T* ptr)%s\n", data.out.Indent(), data.namePrefix, structName, data.declEnd)
	if data.needBody {
		fmt.Fprintf(buf, "%s    {\n", data.out.Indent())
		fmt.Fprintf(buf, "%s        value.reset(new %sImpl<T, gocpp::ptr<T>>(ptr));\n", data.out.Indent(), structName)
		fmt.Fprintf(buf, "%s    }\n", data.out.Indent())
	}

	switch param.output {
	case all, decl:
		fmt.Fprintf(buf, "\n")
		fmt.Fprintf(buf, "%s    using isGoStruct = void;\n", data.out.Indent())
	}

	fmt.Fprintf(buf, "\n")
	fmt.Fprintf(buf, "%s    std::ostream& %sPrintTo(std::ostream& os) const%s\n", data.out.Indent(), data.namePrefix, data.declEnd)
	if data.needBody {
		fmt.Fprintf(buf, "%s    {\n", data.out.Indent())
		fmt.Fprintf(buf, "%s        return os;\n", data.out.Indent())
		fmt.Fprintf(buf, "%s    }\n", data.out.Indent())
	}
	fmt.Fprintf(buf, "\n")

	switch param.output {
	case all, decl:
		fmt.Fprintf(buf, "%s    struct I%s\n", data.out.Indent(), structName)
		fmt.Fprintf(buf, "%s    {\n", data.out.Indent())
		data.out.indent++
		for _, method := range methods {
			fmt.Fprintf(buf, "%s    virtual %s v%s(%s) = 0;\n", data.out.Indent(), method.result, method.name, method.params)
		}
		data.out.indent--
		fmt.Fprintf(buf, "%s    };\n", data.out.Indent())

		fmt.Fprintf(buf, "\n")
		fmt.Fprintf(buf, "%s    template<typename T, typename StoreT>\n", data.out.Indent())
		fmt.Fprintf(buf, "%s    struct %[2]sImpl : I%[2]s\n", data.out.Indent(), structName)
		fmt.Fprintf(buf, "%s    {\n", data.out.Indent())
		// ** Maybe be needed if we decide to store values insstead of pointer at some point **
		// fmt.Fprintf(buf, "%s        //%sImpl(T& ref)\n", data.out.Indent(), structName)
		// fmt.Fprintf(buf, "%s        //{\n", data.out.Indent())
		// fmt.Fprintf(buf, "%s        //    value = &ref;\n", data.out.Indent())
		// fmt.Fprintf(buf, "%s        //}\n", data.out.Indent())
		// fmt.Fprintf(buf, "\n")
		fmt.Fprintf(buf, "%s        explicit %sImpl(T* ptr)\n", data.out.Indent(), structName)
		fmt.Fprintf(buf, "%s        {\n", data.out.Indent())
		fmt.Fprintf(buf, "%s            value.reset(ptr);\n", data.out.Indent())
		fmt.Fprintf(buf, "%s        }\n", data.out.Indent())

		data.out.indent++
		for _, method := range methods {
			fmt.Fprintf(buf, "\n")
			fmt.Fprintf(buf, "%s    %s v%s(%s) override%s\n", data.out.Indent(), method.result, method.name, method.params, data.declEnd)
			if data.needBody {
				fmt.Fprintf(buf, "%s    {\n", data.out.Indent())
				fmt.Fprintf(buf, "%s        return %s(gocpp::PtrRecv<T, false>(value.get()));\n", data.out.Indent(), method.name)
				fmt.Fprintf(buf, "%s    }\n", data.out.Indent())
			}
		}
		data.out.indent--
		fmt.Fprintf(buf, "\n")
		fmt.Fprintf(buf, "%s        StoreT value;\n", data.out.Indent())
		fmt.Fprintf(buf, "%s    };\n", data.out.Indent())

	case implem:
		for _, method := range methods {
			fmt.Fprintf(buf, "%[1]s    template<typename T, typename StoreT>\n", data.out.Indent())
			fmt.Fprintf(buf, "%[1]s    %[2]s %[5]s::%[5]sImpl<T, StoreT>::v%[3]s(%[4]s)\n", data.out.Indent(), method.result, method.name, method.params, structName)
			fmt.Fprintf(buf, "%[1]s    {\n", data.out.Indent())
			fmt.Fprintf(buf, "%[1]s        return %s(gocpp::PtrRecv<T, false>(value.get()));\n", data.out.Indent(), method.name)
			fmt.Fprintf(buf, "%[1]s    }\n", data.out.Indent())
		}
	}

	switch param.output {
	case all, decl:
		fmt.Fprintf(buf, "\n")
		fmt.Fprintf(buf, "%s    std::shared_ptr<I%s> value;\n", data.out.Indent(), structName)
		fmt.Fprintf(buf, "%s};\n", data.out.Indent())
	case implem:
		data.out.indent++
	default:
		Panicf("unmanaged GenOutputType value %v", param.output)
	}

	for _, method := range methods {
		endParams := ""
		if method.params != "" {
			endParams = fmt.Sprintf(", %s", method.params)
		}
		fmt.Fprintf(buf, "\n")

		fmt.Fprintf(buf, "%s%s %s(const gocpp::PtrRecv<%s, false>& self%s)%s\n", data.out.Indent(), method.result, method.name, structName, endParams, data.declEnd)
		if data.needBody {
			fmt.Fprintf(buf, "%s{\n", data.out.Indent())
			fmt.Fprintf(buf, "%s    return self.ptr->value->v%s(%s);\n", data.out.Indent(), method.name, method.params)
			fmt.Fprintf(buf, "%s}\n", data.out.Indent())
			fmt.Fprintf(buf, "\n")
		}

		fmt.Fprintf(buf, "%s%s %s(const gocpp::ObjRecv<%s>& self%s)%s\n", data.out.Indent(), method.result, method.name, structName, endParams, data.declEnd)
		if data.needBody {
			fmt.Fprintf(buf, "%s{\n", data.out.Indent())
			fmt.Fprintf(buf, "%s    return self.obj.value->v%s(%s);\n", data.out.Indent(), method.name, method.params)
			fmt.Fprintf(buf, "%s}\n", data.out.Indent())
		}
	}

	if param.streamOp == with {
		fmt.Fprintf(buf, "\n")
		fmt.Fprintf(buf, "%sstd::ostream& operator<<(std::ostream& os, const %s& value)%s\n", data.out.Indent(), structName, data.declEnd)
		if data.needBody {
			fmt.Fprintf(buf, "%s{\n", data.out.Indent())
			fmt.Fprintf(buf, "%s    return value.PrintTo(os);\n", data.out.Indent())
			fmt.Fprintf(buf, "%s}\n", data.out.Indent())
			fmt.Fprintf(buf, "\n")
		}
	}
	return buf.String()
}

type action func()

func (cv *cppConverter) withCppBuffer(action action) string {
	buf := new(bytes.Buffer)
	bufio := bufio.NewWriter(buf)
	previousOut := cv.cpp.out
	defer func() { cv.cpp.out = previousOut }()
	cv.cpp.out = bufio

	action()

	bufio.Flush()
	return buf.String()
}

// Maybe merge this function with "convertExpr" in future ?
func (cv *cppConverter) convertExprCppType(node ast.Expr) string {
	if node == nil {
		return ""
	}

	switch n := node.(type) {

	// TODO: merge with default case and remove switch ?
	case *ast.BasicLit:
		switch n.Kind {
		case token.IMAG:
			return "gocpp::complex128"
		case token.INT:
			return "int"
		case token.FLOAT:
			return "double"
		case token.CHAR:
			return "char"
		case token.STRING:
			return "string"
		default:
			panic(fmt.Sprintf("Unmanaged token in convert type %v, token %v", reflect.TypeOf(node), n.Kind))
		}

	case *ast.CompositeLit:
		return cv.convertCompositeLitType(n, false)

	case *ast.UnaryExpr:
		switch n.Op {
		case token.AND:
			return cv.convertExprCppType(n.X) + "*"
		default:
			return cv.convertExprCppType(n.X)
		}

	// case *ast.BinaryExpr, *ast.Ident:
	// 	return convertGoToCppType(cv.convertExprType(n))

	// case *ast.IndexExpr:
	// 	objType := convertExprType(n.X)
	// 	indexType := convertExprType(n.Index)
	// 	return fmt.Sprintf("%s[%s]", cv.convertExpr(n.X), cv.convertExpr(n.Index))

	// default:
	// 	panic(fmt.Sprintf("Unmanaged type in convert type %v, input: %v", reflect.TypeOf(node), cv.Position(node)))

	default:
		return convertGoToCppType(cv.convertExprType(n))

	}
}

func (cv *cppConverter) convertExprType(node ast.Expr) types.Type {
	if node == nil {
		return nil
	}

	return cv.typeInfo.Types[node].Type
}

func convertGoToCppType(goType types.Type) string {
	if goType == nil {
		panic("convertGoToCppType, Cannot convert nil type.")
	}

	switch subType := goType.(type) {
	case *types.Basic:
		return GetCppType(subType.String())

	case *types.Named:
		return GetCppType(subType.String())

	case *types.Pointer:
		return GetCppType(subType.Elem().String()) + "*"

	default:
		panic(fmt.Sprintf("Unmanaged subType in convertGoToCppType: %v", reflect.TypeOf(subType)))
	}
}

// TODO: return typeDefs
func (cv *cppConverter) convertExpr(node ast.Expr) string {
	return cv.convertExprImpl(node, false)
}

func (cv *cppConverter) convertSubExpr(node ast.Expr) string {
	return cv.convertExprImpl(node, true)
}

func (cv *cppConverter) convertExprImpl(node ast.Expr, isSubExpr bool) string {
	if node == nil {
		return ""
	}

	switch n := node.(type) {
	case *ast.ArrayType:
		array := cv.convertArrayTypeExpr(n)
		// TODO: typeDefs should be and output of convertExpr
		// HACK: cv.cpp.out shouldn't be used here
		for _, def := range array.defs {
			if def.inline != nil {
				fmt.Fprintf(cv.cpp.out, "%s%s\n", cv.cpp.Indent(), *def.inline)
			}
			if def.outline != nil {
				return "### NOT IMPLEMENTED, convertExpr, can't declare outline from here ###"
			}
			if def.header != nil {
				return "### NOT IMPLEMENTED, convertExpr, can't declare in header from here ###"
			}
		}

		// Type used as parameter, we use a dummy tag value that is used only for its type
		return fmt.Sprintf("gocpp::Tag<%s>()", array.str)

	case *ast.ChanType:
		chanType := cv.convertChanTypeExpr(n)
		// TODO: mapDefs should be and output of convertExpr
		// HACK: cv.cpp.out shouldn't be used here
		for _, def := range chanType.defs {
			if def.inline != nil {
				fmt.Fprintf(cv.cpp.out, "%s%s\n", cv.cpp.Indent(), *def.inline)
			}
			if def.outline != nil {
				return "### NOT IMPLEMENTED, convertExpr, can't declare outline from here ###"
			}
			if def.header != nil {
				return "### NOT IMPLEMENTED, convertExpr, can't declare in header from here ###"
			}
		}

		// Type used as parameter, we use a dummy tag value that is used only for its type
		return fmt.Sprintf("gocpp::Tag<%s>()", chanType.str)

	case *ast.MapType:
		mapType := cv.convertMapTypeExpr(n)
		// TODO: mapDefs should be and output of convertExpr
		// HACK: cv.cpp.out shouldn't be used here
		for _, def := range mapType.defs {
			if def.inline != nil {
				fmt.Fprintf(cv.cpp.out, "%s%s\n", cv.cpp.Indent(), *def.inline)
			}
			if def.outline != nil {
				return "### NOT IMPLEMENTED, convertExpr, can't declare outline from here ###"
			}
			if def.header != nil {
				return "### NOT IMPLEMENTED, convertExpr, can't declare in header from here ###"
			}
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
		return cv.convertCompositeLit(n, false)

	case *ast.FuncLit:
		return cv.withCppBuffer(func() {
			params := cv.readFields(n.Type.Params)
			outNames, outTypes := cv.getResultInfos(n.Type)
			resultType := buildOutType(outTypes)

			cv.DeclareVars(params)

			fmt.Fprintf(cv.cpp.out, "[=](%s) mutable -> %s\n", params, resultType)

			cv.astIndent++
			outline := cv.convertBlockStmt(n.Body, blockEnv{stmtEnv{outNames, outTypes}, true})
			if outline != nil {
				fmt.Fprintf(cv.cpp.out, "### NOT IMPLEMENTED, convertExpr, outline not managed in ast.FuncLit ###")
			}
			cv.astIndent--
		})

	case *ast.UnaryExpr:
		compositLit, isCompositeLit := n.X.(*ast.CompositeLit)

		switch {
		case n.Op == token.AND && isCompositeLit:
			return cv.convertCompositeLit(compositLit, true)
		case n.Op == token.ARROW:
			return fmt.Sprintf("%s.recv()", cv.convertExpr(n.X))
		default:
			return convertToken(n.Op) + " " + cv.convertExpr(n.X)
		}

	case *ast.ParenExpr:
		return "(" + cv.convertExpr(n.X) + ")"

	case *ast.KeyValueExpr:
		return fmt.Sprintf("{ %s, %s }", cv.convertExpr(n.Key), cv.convertExpr(n.Value))

	case *ast.BinaryExpr:
		if needPriority(n.Op) && isSubExpr {
			return fmt.Sprintf("(%s %s %s)", cv.convertSubExpr(n.X), convertToken(n.Op), cv.convertSubExpr(n.Y))
		} else {
			return fmt.Sprintf("%s %s %s", cv.convertSubExpr(n.X), convertToken(n.Op), cv.convertSubExpr(n.Y))
		}
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
		if n.Name == "iota" {
			return cv.Iota()
		} else {
			return GetCppFunc(n.Name)
		}

	case *ast.IndexExpr:
		return fmt.Sprintf("%s[%s]", cv.convertExpr(n.X), cv.convertExpr(n.Index))

	case *ast.SelectorExpr:
		name := cv.convertExpr(n.X)

		if isNameSpace(n.X) {
			return GetCppFunc(name + "::" + cv.convertExpr(n.Sel))
		} else {
			// TODO: use only IsExprPtr ?
			if cv.IsPtr(name) || cv.IsExprPtr(n.X) {
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

func (cv *cppConverter) convertCompositeLitType(n *ast.CompositeLit, addPtr bool) string {
	if n.Type != nil {
		result := cv.convertTypeExpr(n.Type).str
		if addPtr {
			result += "*"
		}
		return result
	}

	panic("Undefined type: 'n.Type == nil'")
}

func (cv *cppConverter) convertCompositeLit(n *ast.CompositeLit, addPtr bool) string {
	// ignore 'n.Incomplete' at the moment
	buf := new(bytes.Buffer)
	var litType string
	if n.Type != nil {

		exprType := cv.convertTypeExpr(n.Type)
		// TODO: typeDefs should be and output of convertExpr
		// HACK: cv.cpp.out shouldn't be used here
		for _, def := range exprType.defs {
			if def.inline != nil {
				fmt.Fprintf(cv.cpp.out, "%s%s\n", cv.cpp.Indent(), *def.inline)
			}
			if def.outline != nil {
				return "### NOT IMPLEMENTED, convertExpr, can't declare outline from here"
			}
			if def.header != nil {
				return "### NOT IMPLEMENTED, convertExpr, can't declare in header from here"
			}
		}

		litType = exprType.str
	}

	var isKvInit bool
	if len(n.Elts) != 0 {
		_, isKvInit = n.Elts[0].(*ast.KeyValueExpr)
	}

	if isKvInit && !isMapType(n.Type) && !cv.IsExprMap(n) {
		ptrSuffix := ""
		if addPtr {
			ptrSuffix = "Ptr"
		}
		fmt.Fprintf(buf, "gocpp::Init%s<%s>([](%s& x) { ", ptrSuffix, litType, litType)

		for _, elt := range n.Elts {
			kv := elt.(*ast.KeyValueExpr)
			//goType := cv.convertExprType(expr)
			fmt.Fprintf(buf, "x.%s = %s; ", cv.convertExpr(kv.Key), cv.convertExpr(kv.Value))
		}
		fmt.Fprintf(buf, "})")
	} else {
		newPrefix := ""
		if addPtr {
			// FIME : create a kind a smart pointer instead of using new.
			newPrefix = "new "
		}

		fmt.Fprintf(buf, "%s%s {", newPrefix, litType)
		var sep = ""
		for _, elt := range n.Elts {
			fmt.Fprintf(buf, "%s%s", sep, cv.convertExpr(elt))
			sep = ", "
		}
		fmt.Fprintf(buf, "}")
	}
	return buf.String()
}

func (cv *cppConverter) convertExprs(exprs []ast.Expr) string {
	var strs []string
	for _, expr := range exprs {
		strs = append(strs, cv.convertExpr(expr))
	}
	return strings.Join(strs, ", ")
}

func (cv *cppConverter) Position(expr ast.Node) token.Position {
	return cv.fileSet.Position(expr.Pos())
}

/* from example: https://github.com/golang/example/tree/master/gotypes#introduction */
func (cv *cppConverter) PrintDefsUses(path string, fset *token.FileSet, files ...*ast.File) error {
	conf := types.Config{Importer: importer.Default()}
	cv.typeInfo = &types.Info{
		Types: make(map[ast.Expr]types.TypeAndValue),
		Defs:  make(map[*ast.Ident]types.Object),
		Uses:  make(map[*ast.Ident]types.Object),
	}
	_, err := conf.Check(path, fset, files, cv.typeInfo)
	if err != nil {
		return err // type error
	}

	fmt.Println(" --  Info.Types -- ")
	for expr, obj := range cv.typeInfo.Types {
		var filePos = cv.Position(expr)
		fmt.Printf("%s (%3d,%3d) => %25v has type [%15T] %v\n", filePos.Filename, filePos.Line, filePos.Column, types.ExprString(expr), obj.Type, obj.Type)
	}

	fmt.Println(" --  Info.Defs -- ")
	for id, obj := range cv.typeInfo.Defs {
		var filePos = cv.Position(id)
		fmt.Printf("%s (%3d,%3d) => %15q defines [%15T] %v\n", filePos.Filename, filePos.Line, filePos.Column, id.Name, obj, obj)
	}

	fmt.Println(" --  Info.Uses -- ")
	for id, obj := range cv.typeInfo.Uses {
		var filePos = cv.Position(id)
		fmt.Printf("%s (%3d,%3d) => %15q uses [%15T] %v\n", filePos.Filename, filePos.Line, filePos.Column, id.Name, obj, obj)
	}
	return nil
}

func main() {

	inputName := flag.String("input", "tests/HelloWorld.go", "The file to parse")
	parseFmtDir := flag.Bool("parseFmt", false, "temporary test parameter")
	cppOutDir := flag.String("cppOutDir", "out", "generated code directory")
	binOutDir := flag.String("binOutDir", "log", "gcc output dir in Makefile")
	genMakeFile := flag.Bool("genMakeFile", false, "generate Makefile")
	flag.Parse()

	fset := token.NewFileSet()

	f, err := parser.ParseFile(fset, *inputName, nil, parser.ParseComments)
	if err != nil {
		fmt.Println(err)
		return
	}

	if *parseFmtDir {
		pkgs, errPkg := parser.ParseDir(fset, "F:/Dev/Golang/src/fmt", nil, parser.ParseComments)
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

	var cv *cppConverter = new(cppConverter)
	cv.genMakeFile = *genMakeFile
	cv.binOutDir = *binOutDir
	cv.cppOutDir = *cppOutDir
	cv.supportHeader = "gocpp/support.h"
	cv.inputName = *inputName
	cv.baseName = strings.TrimSuffix(cv.inputName, ".go")
	cv.fileSet = fset
	cv.Init()

	if err := cv.PrintDefsUses("gocpp", fset, f); err != nil {
		fmt.Println(err.Error()) // type error
		//log.Fatal(err) // type error
	}

	fmt.Printf("\n=====\n")

	cv.ConvertFile(*f)
}
