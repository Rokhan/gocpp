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
	"io"
	"log"
	"os"
	"path"
	"path/filepath"
	"reflect"
	"slices"
	"strings"
	"time"

	"golang.org/x/tools/go/packages"
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
	"uintptr":    "uintptr_t",
	"uint":       "unsigned int",
	"uint8":      "uint8_t",
	"uint16":     "uint16_t",
	"uint32":     "uint32_t",
	"uint64":     "uint64_t",
	"int8":       "int8_t",
	"int16":      "int16_t",
	"int32":      "int32_t",
	"int64":      "int64_t",
	// untyped types !!!
	"untyped bool":    "bool",
	"untyped complex": "goccp::complex128",
	"untyped float":   "double",
	"untyped int":     "int",
	"untyped string":  "std::string",
	// predefined types
	"error": "std::string",
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

// TODO, make a dynamic mapping
var cppKeyWordsMapping = map[string]string{
	"class":    "go_class",
	"do":       "go_do",
	"new":      "go_new",
	"template": "go_template",
	"throw":    "go_throw",
	"typeid":   "go_typeid",
	"while":    "go_while",
}

func GetCppName(name string) string {
	val, ok := cppKeyWordsMapping[name]
	if ok {
		return val
	} else {
		return name
	}
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
	goType = GetCppName(goType)
	val, ok := stdTypeMapping[goType]
	if ok {
		return val
	} else {
		return goType
	}
}

func GetCppGoType(goType types.Type) string {
	return GetCppType(goType.String())
}

func GetCppFunc(funcName string) string {
	funcName = GetCppName(funcName)
	val, ok := stdFuncMapping[funcName]
	if ok {
		return val
	} else {
		return funcName
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

// Global parameters and data shared by all child coverters
type cppConverterSharedData struct {
	// global parmeters
	globalSubDir     string
	supportHeader    string
	exeDate          time.Time
	verbose          bool
	strictMode       bool
	alwaysRegenerate bool

	// shared data
	parsedFiles    map[string]*ast.File
	generatedFiles map[string]bool
	usedFiles      map[string]bool
	packagePaths   map[string]string

	// golang tokens, parsing and types infos
	fileSet *token.FileSet

	// Cpp files parameters
	cppOutDir string
}

type cppConverter struct {
	shared *cppConverterSharedData

	// Logs and error management
	logPrefix  string
	tryRecover bool
	statusMd   outFile

	// code generation data
	baseName    string
	srcBaseName string
	inputName   string

	// golang tokens, parsing and types infos
	typeInfo *types.Info
	astFile  *ast.File

	// Parsing and codegen parameters
	currentSwitchId *list.List
	idCount         int
	scopes          *list.List
	iota_value      int

	// Makefile parameters
	genMakeFile bool
	makeFile    outFile
	binOutDir   string

	// Cpp files parameters
	cpp       outFile
	hpp       outFile
	fwd       outFile
	hasMain   bool
	namespace string
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

func (of *outFile) Indent() string {
	return strings.Repeat("    ", of.indent)
}

func (cv *cppConverter) GenerateId() (id string) {
	id = fmt.Sprintf("gocpp_id_%d", cv.idCount)
	cv.idCount++
	return id
}

func (pkgInfo *pkgInfo) baseName() string {
	return strings.TrimSuffix(filepath.Base(pkgInfo.filePath), ".go")
}

func includeDependencies(out io.Writer, globalSubDir string, pkgInfos []*pkgInfo, suffix string) {
	if pkgInfos == nil {
		return
	}

	var alreadyIncluded map[string]bool = make(map[string]bool)

	slices.SortFunc(pkgInfos, func(p1 *pkgInfo, p2 *pkgInfo) int {
		bn1 := p1.baseName()
		bn2 := p2.baseName()
		return strings.Compare(p1.pkgPath+bn1, p2.pkgPath+bn2)
	})

	for _, pkgInfo := range pkgInfos {
		if _, done := alreadyIncluded[pkgInfo.filePath]; done {
			continue
		}
		alreadyIncluded[pkgInfo.filePath] = true

		//fmt.Fprintf(out, "// globalSubDir: %v -- pkgInfo.pkgPath: %v -- pkgInfo.filePath: %v \n", globalSubDir, pkgInfo.pkgPath, pkgInfo.filePath)

		baseName := pkgInfo.baseName()
		switch pkgInfo.fileType {
		case GoFiles, CompiledGoFiles:
			fmt.Fprintf(out, "#include \"%v%v/%v%v\"\n", globalSubDir, pkgInfo.pkgPath, baseName, suffix)
		case Ignored:
			fmt.Fprintf(out, "// #include \"%v%v/%v%v\"  [Ignored, known errors]\n", globalSubDir, pkgInfo.pkgPath, baseName, suffix)
		}
	}
	fmt.Fprintf(out, "\n")
}

func generatedMessage(out io.Writer, cv *cppConverter) {
	fmt.Fprintf(out, "// generated by GoCpp from file '%v.go'\n", cv.srcBaseName)
}

func printCppIntro(cv *cppConverter, pkgInfos []*pkgInfo) {
	out := cv.cpp.out
	generatedMessage(out, cv)
	//temporarily blindly add "includes" and "using"
	fmt.Fprintf(out, "#include <complex>\n")
	fmt.Fprintf(out, "#include <functional>\n")
	fmt.Fprintf(out, "#include <iostream>\n")
	fmt.Fprintf(out, "#include <iomanip>\n")
	fmt.Fprintf(out, "#include <map>\n")
	fmt.Fprintf(out, "#include <string>\n")
	fmt.Fprintf(out, "#include <tuple>\n")
	fmt.Fprintf(out, "#include <vector>\n")
	fmt.Fprintf(out, "\n")
	fmt.Fprintf(out, "#include \"%s.h\"\n", cv.baseName)
	fmt.Fprintf(out, "#include \"%s\"\n", cv.shared.supportHeader)
	fmt.Fprintf(out, "\n")

	includeDependencies(out, cv.shared.globalSubDir, pkgInfos, ".h")

	// Put everything generated in "golang" namespace
	fmt.Fprintf(out, "namespace golang::%v\n", cv.namespace)
	fmt.Fprintf(out, "{\n")
	cv.cpp.indent++
}

func printCppOutro(cv *cppConverter) {
	out := cv.cpp.out
	// Closing golang namespace
	cv.cpp.indent--
	fmt.Fprintf(out, "}\n")
	fmt.Fprintf(out, "\n")

	if cv.hasMain {
		// TODO: manage main parameters
		fmt.Fprintf(out, "int main()\n")
		fmt.Fprintf(out, "{\n")
		fmt.Fprintf(out, "    try\n")
		fmt.Fprintf(out, "    {\n")
		fmt.Fprintf(out, "        std::cout << std::boolalpha << std::fixed << std::setprecision(5);\n")
		fmt.Fprintf(out, "        golang::%v::main();\n", cv.namespace)
		fmt.Fprintf(out, "        return 0;\n")
		fmt.Fprintf(out, "    }\n")
		fmt.Fprintf(out, "    catch(const gocpp::GoPanic& ex)\n")
		fmt.Fprintf(out, "    {\n")
		fmt.Fprintf(out, "        std::cout << \"Panic: \" << ex.what() << std::endl;\n")
		fmt.Fprintf(out, "        return -1;\n")
		fmt.Fprintf(out, "    }\n")
		fmt.Fprintf(out, "}\n")
	}
}

func printHppIntro(cv *cppConverter, pkgInfos []*pkgInfo) {
	out := cv.hpp.out
	generatedMessage(out, cv)
	//temporarily blindly add "includes" and "using"
	fmt.Fprintf(out, "#pragma once\n")
	fmt.Fprintf(out, "\n")
	fmt.Fprintf(out, "#include <functional>\n")
	fmt.Fprintf(out, "#include <string>\n")
	fmt.Fprintf(out, "#include <tuple>\n")
	fmt.Fprintf(out, "#include <vector>\n")
	fmt.Fprintf(out, "\n")
	fmt.Fprintf(out, "#include \"%s.fwd.h\"\n", cv.baseName)
	fmt.Fprintf(out, "#include \"%s\"\n", cv.shared.supportHeader)
	fmt.Fprintf(out, "\n")

	// Can we do something with ".fwd.h" in some situations ?
	includeDependencies(out, cv.shared.globalSubDir, pkgInfos, ".h")

	// Put everything generated in "golang" namespace
	fmt.Fprintf(out, "namespace golang::%v\n", cv.namespace)
	fmt.Fprintf(out, "{\n")
	cv.hpp.indent++
}

func printHppOutro(cv *cppConverter) {
	out := cv.hpp.out
	// Closing golang namespace
	cv.hpp.indent--
	fmt.Fprintf(out, "}\n")
	fmt.Fprintf(out, "\n")
}

func printFwdIntro(cv *cppConverter) {
	out := cv.fwd.out
	generatedMessage(out, cv)
	fmt.Fprintf(out, "#pragma once\n")
	fmt.Fprintf(out, "\n")

	// Put everything generated in "golang" namespace
	fmt.Fprintf(out, "namespace golang::%v\n", cv.namespace)
	fmt.Fprintf(out, "{\n")
	cv.fwd.indent++
}

func printFwdOutro(cv *cppConverter) {
	out := cv.fwd.out
	// Close golang namespace
	cv.fwd.indent--
	fmt.Fprintf(out, "}\n")
	fmt.Fprintf(out, "\n")
}

func createOutputExt(outdir, name, ext string) outFile {
	var outName = name + "." + ext
	return createOutput(outdir, outName)
}

func createOutput(outdir, name string) outFile {
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

	writer := bufio.NewWriter(file)
	return outFile{file, writer, 0}
}

func buildSharedData() (shared *cppConverterSharedData) {
	shared = new(cppConverterSharedData)
	shared.generatedFiles = map[string]bool{}
	shared.parsedFiles = map[string]*ast.File{}
	shared.usedFiles = map[string]bool{}
	shared.packagePaths = map[string]string{}
	return
}

func (cv *cppConverter) InitAndParse() {

	cv.currentSwitchId = new(list.List)
	cv.scopes = new(list.List)

	if cv.genMakeFile {
		cv.makeFile = createOutput(cv.shared.cppOutDir, "Makefile")

		fmt.Fprintf(cv.makeFile.out, "all:\n")
	}

	if astFile, done := cv.shared.parsedFiles[cv.inputName]; done {
		cv.astFile = astFile
	} else {
		var parsedFile *ast.File
		parsedFile, err := parser.ParseFile(cv.shared.fileSet, cv.inputName, nil, parser.ParseComments)
		cv.astFile = parsedFile
		if err != nil {
			fmt.Println(err)
			return
		}
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

func GetFileTimeStamp(filename string, defaultInFuture bool) time.Time {
	fileInfo, error := os.Stat(filename)
	if error != nil {
		if defaultInFuture {
			return time.Now().AddDate(1000, 0, 0)
		}
		return time.Time{}
	}

	return fileInfo.ModTime()
}

func (cv *cppConverter) ConvertFile() (toBeConverted []*cppConverter) {
	shared := cv.shared
	generated := false
	if cv.tryRecover {
		defer func() {
			if r := recover(); r != nil {
				cv.Logf("PANIC when converting file %s, %s\n", cv.inputName, r)
			}
		}()
	}

	cppFileName := shared.cppOutDir + "/" + cv.baseName + ".cpp"
	goFileDate := GetFileTimeStamp(cv.inputName, true)
	cppFileDate := GetFileTimeStamp(cppFileName, false)

	if shared.verbose {
		cv.Logf(" ExeDate: %v\n", shared.exeDate)
		cv.Logf(" goFileDate: %v\n", goFileDate)
		cv.Logf(" cppFileDate: %v\n", cppFileDate)
	}
	if !shared.alwaysRegenerate {
		// Probably too aggressive, we should check dependencies
		if cppFileDate.After(shared.exeDate) && cppFileDate.After(goFileDate) {
			cv.Logf(" <<< Skipped already up to date file: %s >>>", cv.inputName)
			return
		}
	}

	defer func(bool) {
		cv.statusMd = createOutputExt(cv.binOutDir, cv.baseName, "status.md")
		if generated {
			fmt.Fprintf(cv.statusMd.out, "| %s.go | ✔️ ([cpp](%[2]s/%[3]s.cpp), [h](%[2]s/%[3]s.h))|\n", cv.srcBaseName, shared.cppOutDir, cv.baseName)
		} else {
			fmt.Fprintf(cv.statusMd.out, "| %s.go | ❌ |\n", cv.srcBaseName)
		}
		cv.statusMd.out.Flush()
	}(generated)

	cv.Logf("\n")
	cv.Logf(" !!!>> Start converting file: %v <<!!!\n", cv.inputName)
	defer cv.Logf(" !!!>> End converting file: %v <<!!!\n", cv.inputName)

	cv.startScope()

	cv.cpp = createOutputExt(shared.cppOutDir, cv.baseName, "cpp")
	cv.hpp = createOutputExt(shared.cppOutDir, cv.baseName, "h")
	cv.fwd = createOutputExt(shared.cppOutDir, cv.baseName, "fwd.h")

	cv.hpp.indent++
	cv.fwd.indent++
	cv.cpp.indent++

	cv.namespace = cv.astFile.Name.Name
	var allOutlines [][]string
	var pkgInfos []*pkgInfo
	var allCppOut, allHppOut, allFwdOut []string
	for _, decl := range cv.astFile.Decls {
		var outlines []string
		var cppOut, hppOut, fwdOut string

		fwdOut = cv.withFwdBuffer(func() {
			hppOut = cv.withHppBuffer(func() {
				cppOut = cv.withCppBuffer(func() {
					declOutline, declPkgInfos := cv.convertDecls(decl, true)
					outlines = append(outlines, declOutline...)
					pkgInfos = append(pkgInfos, declPkgInfos...)
				})
			})
		})

		allOutlines = append(allOutlines, outlines)
		allFwdOut = append(allFwdOut, fwdOut)
		allHppOut = append(allHppOut, hppOut)
		allCppOut = append(allCppOut, cppOut)
	}

	cv.fwd.indent--
	cv.hpp.indent--
	cv.cpp.indent--

	usedPkgInfos, toBeConverted := cv.convertDependency(pkgInfos)

	cv.ignoreKnownErrors(usedPkgInfos)

	printFwdIntro(cv)
	printHppIntro(cv, usedPkgInfos)
	printCppIntro(cv, usedPkgInfos)

	for i := 0; i < len(allOutlines); i++ {
		for _, outline := range allOutlines[i] {
			fmt.Fprintf(cv.cpp.out, "%s%s\n", cv.cpp.Indent(), outline)
		}
		fmt.Fprintf(cv.fwd.out, "%s", allFwdOut[i])
		fmt.Fprintf(cv.hpp.out, "%s", allHppOut[i])
		fmt.Fprintf(cv.cpp.out, "%s", allCppOut[i])
	}

	if cv.genMakeFile {
		fmt.Fprintf(cv.makeFile.out, "\t g++ -std=c++20 -I. -I../includes -I../thirdparty/includes %s.cpp -o ../%s/%s.exe\n", cv.baseName, cv.binOutDir, cv.baseName)
	}

	cv.endScope()

	printFwdOutro(cv)
	printHppOutro(cv)
	printCppOutro(cv)

	generated = true

	cv.cpp.out.Flush()
	cv.hpp.out.Flush()
	cv.fwd.out.Flush()
	if cv.genMakeFile {
		cv.makeFile.out.Flush()
	}

	return
}

func (cv *cppConverter) Logf(format string, a ...any) (n int, err error) {
	fmt.Printf("%s", cv.logPrefix)
	return fmt.Printf(format, a...)
}

func (cv *cppConverter) needFileGeneration() bool {
	// TODO
	return true
}

func (cv *cppConverter) getUsedDependency() (pkgInfos []*pkgInfo) {
	shared := cv.shared
	usedTypes := cv.getReferencedTypesFrom(cv.typeInfo.Uses, map[string]bool{cv.inputName: true})
	cv.logReferencedTypesFrom(usedTypes, "Used")

	shared.usedFiles[cv.inputName] = true

	for usedType := range usedTypes {
		var file = shared.fileSet.Position(usedType.Pos()).Filename

		// Hack for unsafe.Pointer in unsafe package
		// Maybe we should load it manually somewhere in cv.fileset ?
		if file == "" {
			for pkgFile, path := range shared.packagePaths {
				if path == "unsafe" {
					file = pkgFile
				}
			}
		}

		if file == "" || file == cv.inputName {
			continue
		}

		shared.usedFiles[file] = true
		pkg := usedType.Pkg()
		if pkg != nil {
			cv.Logf("pkginfo, pkgName: %v, pkgPath: %v, file: %v, usedTypeName: %v ---\n", usedType.Pkg().Name(), usedType.Pkg().Path(), file, usedType.Name())
			// usedType.Pkg().Path() doesn't return the full path, using value stored when loading packages
			pkgPath, ok := shared.packagePaths[file]
			if ok {
				pkgInfos = append(pkgInfos, &pkgInfo{usedType.Pkg().Name(), pkgPath, file, GoFiles})
			} else {
				pkgInfos = append(pkgInfos, &pkgInfo{usedType.Pkg().Name(), usedType.Pkg().Path(), file, GoFiles})
				cv.Logf("  -> pkgPath is null, file: %v\n", file)
			}
		} else {
			cv.Logf("pkginfo, nil pkg, file: %v, usedTypeName: %v ---\n", file, usedType.Name())
		}
	}
	return
}

func (cv *cppConverter) getReferencedTypesFrom(objects map[*ast.Ident]types.Object, files map[string]bool) (usedTypes map[types.Object]bool) {
	usedTypes = make(map[types.Object]bool)
	for id, obj := range objects {

		var filePos = cv.Position(id)
		if !files[filePos.Filename] {
			continue
		}

		switch t := obj.(type) {
		case *types.TypeName, *types.Const, *types.Func:
			usedTypes[t] = true
		}
	}
	return
}

func (cv *cppConverter) logReferencedTypesFrom(usedTypes map[types.Object]bool, name string) {
	cv.Logf("\n")
	cv.Logf(" --- %s types by %s ---\n", name, cv.inputName)
	for usedType := range usedTypes {
		pkg := usedType.Pkg()
		if pkg != nil {
			var file = cv.shared.fileSet.Position(usedType.Pos()).Filename
			cv.Logf("path: %s.%s, id: %s, exported: %v, file: %v\n", pkg.Name(), usedType.Name(), usedType.Id(), usedType.Exported(), file)
		}
	}
	cv.Logf("\n")
	cv.Logf(" --- ---\n")
}

type pkgFilter struct {
	pkg  string
	file string
}

func (cv *cppConverter) ignoreKnownErrors(pkgInfos []*pkgInfo) {
	knownErrors := []*pkgFilter{
		{"abi", "internal/abi/abi.go"},
		{"abi", "internal/abi/symtab.go"},
		{"atomic", "sync/atomic/doc.go"},
		{"goarch", "internal/goarch/goarch.go"},
		{"pic", "golang.org/x/tour@v0.1.0/pic/pic.go"},
		{"wc", "golang.org/x/tour@v0.1.0/wc/wc.go"},
		{"png", "image/png/writer.go"},
		{"race", "internal/race/norace.go"},
		{"runtime", "runtime/lockrank.go"},
		{"runtime", "runtime/stubs.go"},
		{"runtime", "runtime/sizeclasses.go"},
		{"runtime", "runtime/symtab.go"},
		{"sync", "sync/runtime.go"},
		{"sync", "sync/runtime2.go"},
		{"time", "time/tick.go"},
	}

	for _, pkg := range pkgInfos {

		// Potentially slow but funtion 'ignoreKnownErrors' should be removed completly in future
		for _, bad := range knownErrors {
			pkgFilePath := strings.ReplaceAll(pkg.filePath, "\\", "/")
			pkgName := strings.ReplaceAll(pkg.name, "\\", "/")
			if cv.shared.verbose {
				cv.Logf("ignoreKnownErrors, pkg.name: '%v', bad.pkg: '%v', pkgFilePath: '%v', bad.file: '%v'\n", pkg.name, bad.pkg, pkgFilePath, bad.file)
			}
			if pkgName == bad.pkg && strings.HasSuffix(pkgFilePath, bad.file) {
				pkg.fileType = Ignored
				continue
			}
		}
	}
}

func (cv *cppConverter) readFields(fields *ast.FieldList) (params typeNames) {
	if fields == nil {
		return
	}

	for _, field := range fields.List {
		var param typeName
		for _, name := range field.Names {
			param.names = append(param.names, GetCppName(name.Name))
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
			methods = append(methods, method{GetCppName(name.Name), outPrm, inPrm})
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
	varNames *[]string // maybe use map for perfs
}

func (env *stmtEnv) startVarScope() {
	//clear already declared var names at start of scope
	env.varNames = &[]string{}
}

func makeStmtEnv(outNames []string, outTypes []string) stmtEnv {
	varNames := outNames
	return stmtEnv{outNames, outTypes, &varNames}
}

type blockEnv struct {
	stmtEnv
	isFunc   bool
	useDefer *bool

	isTypeSwitch      bool
	switchVarName     string
	typeSwitchVarName string
}

func boolPtr(b bool) *bool {
	return &b
}

func makeBlockEnv(env stmtEnv, isFunc bool) blockEnv {
	return blockEnv{env, isFunc, boolPtr(false), false, "", ""}
}

func makeSubBlockEnv(env blockEnv, isFunc bool) blockEnv {
	return blockEnv{env.stmtEnv, isFunc, env.useDefer, env.isTypeSwitch, env.typeSwitchVarName, env.switchVarName}
}

func (cv *cppConverter) outputsPrint(place place, outlines *[]string, pkgInfos *[]*pkgInfo) {
	if place.inline != nil {
		fmt.Fprintf(cv.cpp.out, "%s%s", cv.cpp.Indent(), *place.inline)
	}
	if place.outline != nil {
		*outlines = append(*outlines, *place.outline)
	}
	if place.header != nil {
		fmt.Fprintf(cv.hpp.out, "%s%s", cv.hpp.Indent(), *place.header)
	}
	if place.pkgInfo != nil {
		*pkgInfos = append(*pkgInfos, place.pkgInfo)
	}
}

func (cv *cppConverter) convertDecls(decl ast.Decl, isNameSpace bool) (outlines []string, pkgInfos []*pkgInfo) {
	cv.Logf("decl: %v at %v\n", reflect.TypeOf(decl), cv.Position(decl))

	switch d := decl.(type) {
	case *ast.GenDecl:
		for _, place := range cv.convertSpecs(d.Specs, isNameSpace, ";\n") {
			cv.outputsPrint(place, &outlines, &pkgInfos)
		}

	case *ast.FuncDecl:
		params := cv.readFields(d.Recv)
		params = append(params, cv.readFields(d.Type.Params)...)
		outNames, outTypes := cv.getResultInfos(d.Type)
		resultType := buildOutType(outTypes)

		cv.DeclareVars(params)
		for _, param := range params {
			for _, place := range param.Type.defs {
				cv.outputsPrint(place, &outlines, nil)
			}
		}
		name := GetCppName(d.Name.Name)
		fmt.Fprintf(cv.cpp.out, "%s%s %s(%s)\n", cv.cpp.Indent(), resultType, name, params)
		fmt.Fprintf(cv.hpp.out, "%s%s %s(%s);\n", cv.cpp.Indent(), resultType, name, params)
		if name == "main" {
			cv.hasMain = true
		}

		blockOutlines := cv.convertBlockStmt(d.Body, makeBlockEnv(makeStmtEnv(outNames, outTypes), true))
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

	if block == nil {
		fmt.Fprintf(cv.cpp.out, "%v/* convertBlockStmt, nil block */;\n", cv.cpp.Indent())
		return
	}

	cv.startScope()
	env.startVarScope()
	fmt.Fprintf(cv.cpp.out, "%s{\n", cv.cpp.Indent())
	cv.cpp.indent++

	cppOut := cv.withCppBuffer(func() {
		for i := range env.outNames {
			fmt.Fprintf(cv.cpp.out, "%s%s %s;\n", cv.cpp.Indent(), GetCppType(env.outTypes[i]), env.outNames[i])
		}

		for _, stmt := range block.List {
			outlines = append(outlines, cv.convertStmt(stmt, env)...)
		}
	})

	if env.isFunc && *env.useDefer {
		fmt.Fprintf(cv.cpp.out, "%sgocpp::Defer defer;\n", cv.cpp.Indent())
	}

	fmt.Fprintf(cv.cpp.out, "%s", cppOut)

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

func (cv *cppConverter) convertAssignStmt(stmt *ast.AssignStmt, env blockEnv) []string {
	switch stmt.Tok {
	case token.DEFINE:
		switch len(stmt.Lhs) {
		case 0:
			panic("convertAssignStmt, len(exprs) == 0")
		case 1:
			varName := cv.convertExpr(stmt.Lhs[0])
			*env.varNames = append(*env.varNames, varName)
			return []string{fmt.Sprintf("auto %s = %s", varName, cv.convertAssignRightExprs(stmt.Rhs))}
		default:
			var decl []string
			var allNew = true
			var exprList = cv.convertExprList(stmt.Lhs)
			var toDeclare []string
			// first step, just check if there is already declared names
			for _, varName := range exprList {
				if !slices.Contains(*env.varNames, varName) {
					toDeclare = append(toDeclare, varName)
					*env.varNames = append(*env.varNames, varName)
				} else {
					allNew = false
				}
			}

			if allNew {
				// Not necessary, the default case would work, but output looks better
				return []string{fmt.Sprintf("auto [%s] = %s", cv.convertExprs(stmt.Lhs), cv.convertAssignRightExprs(stmt.Rhs))}
			}

			// The 2-step loop on exprList is done to not call "cv.convertExprCppType"
			// when not strictly necessary as not all types are implemented at the moment.
			for i, varName := range exprList {
				//decl = append(decl, fmt.Sprintf("// DBG, declared names : (%s)", strings.Join(*env.varNames, ", ")))
				if slices.Contains(toDeclare, varName) {
					if stmt.Lhs[i] != nil {
						decl = append(decl, fmt.Sprintf("%s %s", cv.convertExprCppType(stmt.Lhs[i]), varName))
					} else {
						decl = append(decl, fmt.Sprintf("%s %s", "### NIL EXPRESSION: 'stmt.Lhs[i]'", varName))
					}
					*env.varNames = append(*env.varNames, varName)
				}
			}
			return append(decl, fmt.Sprintf("std::tie(%s) = %s", cv.convertExprs(stmt.Lhs), cv.convertAssignRightExprs(stmt.Rhs)))
		}
	case token.ASSIGN:
		switch len(stmt.Lhs) {
		case 0:
			panic("convertAssignStmt, len(exprs) == 0")
		case 1:
			return []string{fmt.Sprintf("%s = %s", cv.convertExpr(stmt.Lhs[0]), cv.convertAssignRightExprs(stmt.Rhs))}
		default:
			return []string{fmt.Sprintf("std::tie(%s) = %s", cv.convertExprs(stmt.Lhs), cv.convertAssignRightExprs(stmt.Rhs))}
		}

	case token.ADD_ASSIGN, token.SUB_ASSIGN, token.MUL_ASSIGN,
		token.QUO_ASSIGN, token.REM_ASSIGN, token.AND_ASSIGN,
		token.OR_ASSIGN, token.XOR_ASSIGN, token.SHL_ASSIGN,
		token.SHR_ASSIGN, token.AND_NOT_ASSIGN:
		{
			switch len(stmt.Lhs) {
			case 0:
				panic("convertAssignStmt, len(exprs) == 0")
			case 1:
				return []string{fmt.Sprintf("%s %s %s", cv.convertExprs(stmt.Lhs), stmt.Tok, cv.convertAssignRightExprs(stmt.Rhs))}
			default:
				panic("convertAssignStmt, len(exprs) != 1")
			}
		}

	default:
		Panicf("convertAssignStmt, unmanaged token: %s, input: %v", stmt.Tok, cv.Position(stmt))
	}

	panic("convertAssignStmt, bug, unreacheable code reached !")
}

func (cv *cppConverter) convertStmt(stmt ast.Stmt, env blockEnv) (outlines []string) {
	switch s := stmt.(type) {
	case *ast.BlockStmt:
		outlines = cv.convertBlockStmt(s, makeSubBlockEnv(env, false))

	case *ast.DeclStmt:
		var pkgInfos []*pkgInfo
		outlines, pkgInfos = cv.convertDecls(s.Decl, false)
		if len(pkgInfos) != 0 {
			Panicf("convertStmt, can't manage pkgInfos here, declaration: [%v], input: %v", s.Decl, cv.Position(s))
		}

	case *ast.ExprStmt:
		fmt.Fprintf(cv.cpp.out, "%s%s;\n", cv.cpp.Indent(), cv.convertExpr(s.X))

	case *ast.IncDecStmt:
		fmt.Fprintf(cv.cpp.out, "%s%s%s;\n", cv.cpp.Indent(), cv.convertExpr(s.X), s.Tok)

	case *ast.ReturnStmt:
		fmt.Fprintf(cv.cpp.out, "%s%s;\n", cv.cpp.Indent(), cv.convertReturnExprs(s.Results, env.outNames))

	case *ast.AssignStmt:
		stmts := cv.convertAssignStmt(s, env)
		for _, stmt := range stmts {
			fmt.Fprintf(cv.cpp.out, "%s%s;\n", cv.cpp.Indent(), stmt)
		}

	case *ast.DeferStmt:
		*env.useDefer = true
		fmt.Fprintf(cv.cpp.out, "%sdefer.push_back([=]{ %s; });\n", cv.cpp.Indent(), cv.convertExpr(s.Call))

	case *ast.GoStmt:
		fmt.Fprintf(cv.cpp.out, "%sgocpp::go([&]{ %s; });\n", cv.cpp.Indent(), cv.convertExpr(s.Call))

	case *ast.SendStmt:
		fmt.Fprintf(cv.cpp.out, "%s%s.send(%s);\n", cv.cpp.Indent(), cv.convertExpr(s.Chan), cv.convertExpr(s.Value))

	case *ast.ForStmt:
		env.startVarScope()
		fmt.Fprintf(cv.cpp.out, "%sfor(%s; %s; %s)\n", cv.cpp.Indent(), cv.inlineStmt(s.Init, env), cv.convertExpr(s.Cond), cv.inlineStmt(s.Post, env))
		outlines = cv.convertBlockStmt(s.Body, makeSubBlockEnv(env, false))

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
		outlines = cv.convertBlockStmt(s.Body, makeSubBlockEnv(env, false))

	case *ast.IfStmt:
		if s.Init != nil {
			env.startVarScope()
			fmt.Fprintf(cv.cpp.out, "%sif(%s; %s)\n", cv.cpp.Indent(), cv.inlineStmt(s.Init, env), cv.convertExpr(s.Cond))
		} else {
			fmt.Fprintf(cv.cpp.out, "%sif(%s)\n", cv.cpp.Indent(), cv.convertExpr(s.Cond))
		}

		blockOutline := cv.convertBlockStmt(s.Body, makeSubBlockEnv(env, false))
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
			env.startVarScope()
			fmt.Fprintf(cv.cpp.out, "%s%s;\n", cv.cpp.Indent(), cv.inlineStmt(s.Init, env))
		}

		inputVarName := ""
		if s.Tag != nil {
			inputVarName = "condition"
			fmt.Fprintf(cv.cpp.out, "%sauto %s = %s;\n", cv.cpp.Indent(), inputVarName, cv.convertExpr(s.Tag))
		}

		cv.convertSwitchBody(env, s.Body, "conditionId", inputVarName)

	case *ast.TypeSwitchStmt:
		fmt.Fprintf(cv.cpp.out, "%s//Go type switch emulation\n", cv.cpp.Indent())
		fmt.Fprintf(cv.cpp.out, "%s{\n", cv.cpp.Indent())
		cv.cpp.indent++

		if s.Init != nil {
			env.startVarScope()
			fmt.Fprintf(cv.cpp.out, "%s%s;\n", cv.cpp.Indent(), cv.inlineStmt(s.Init, env))
		}

		var switchExpr string
		inputVarName := ""
		switchVarName := cv.GenerateId()
		if s.Assign != nil {
			inputVarName, switchExpr = cv.convertTypeSwitchAssign(s.Assign)
			fmt.Fprintf(cv.cpp.out, "%sconst auto& %s = gocpp::type_info(%s);\n", cv.cpp.Indent(), switchVarName, switchExpr)
		}

		env.isTypeSwitch = true
		env.typeSwitchVarName = inputVarName
		env.switchVarName = switchExpr
		cv.convertSwitchBody(env, s.Body, "conditionId", switchVarName)

	case *ast.SelectStmt:
		fmt.Fprintf(cv.cpp.out, "%s//Go select emulation\n", cv.cpp.Indent())
		fmt.Fprintf(cv.cpp.out, "%s{\n", cv.cpp.Indent())
		cv.cpp.indent++

		cv.convertSwitchBody(env, s.Body, "conditionId", "")
		fmt.Fprintf(cv.cpp.out, "%sstd::this_thread::yield();\n", cv.cpp.Indent())

	case *ast.CaseClause:
		var caseType string
		if s.List == nil {
			fmt.Fprintf(cv.cpp.out, "%sdefault:\n", cv.cpp.Indent())
		} else {
			for range s.List {
				id := cv.currentSwitchId.Back().Value.(int)
				fmt.Fprintf(cv.cpp.out, "%scase %d:\n", cv.cpp.Indent(), id)
				cv.currentSwitchId.Back().Value = id + 1
			}

			if env.isTypeSwitch {
				caseType = cv.convertExprCppType(s.List[0])
			}
		}

		if env.isTypeSwitch {
			fmt.Fprintf(cv.cpp.out, "%s{\n", cv.cpp.Indent())
		}

		cv.cpp.indent++

		if env.isTypeSwitch {
			if caseType != "" {
				fmt.Fprintf(cv.cpp.out, "%s%s %s = gocpp::any_cast<%s>(%s);\n", cv.cpp.Indent(), caseType, env.switchVarName, caseType, env.typeSwitchVarName)
			} else {
				fmt.Fprintf(cv.cpp.out, "%sauto %s = %s;\n", cv.cpp.Indent(), env.switchVarName, env.typeSwitchVarName)
			}
		}

		for _, stmt := range s.Body {
			stmtOutline := cv.convertStmt(stmt, env)
			outlines = append(outlines, stmtOutline...)
		}
		fmt.Fprintf(cv.cpp.out, "%sbreak;\n", cv.cpp.Indent())
		cv.cpp.indent--

		if env.isTypeSwitch {
			fmt.Fprintf(cv.cpp.out, "%s}\n", cv.cpp.Indent())
		}

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
	isTypeSwitch     bool
}

func (cv *cppConverter) convertTypeSwitchAssign(stmt ast.Stmt) (varName string, exprString string) {

	switch s := stmt.(type) {
	case *ast.AssignStmt:
		if len(s.Lhs) == 1 && len(s.Rhs) == 1 {
			varName = cv.convertExpr(s.Lhs[0])
			switch expr := s.Rhs[0].(type) {
			case *ast.TypeAssertExpr:
				if expr.Type != nil {
					// We managed only .(type) syntax
					Panicf("convertTypeSwitchAssign, unmanaged type switch with type [%v], input: %v", reflect.TypeOf(expr.Type), cv.Position(expr.Type))
				}
				exprString = cv.convertExpr(expr.X)
			default:
				Panicf("convertTypeSwitchAssign, unmanaged right side expression [%v], input: %v", reflect.TypeOf(expr), cv.Position(expr))
			}
		} else {
			Panicf("convertTypeSwitchAssign, unmanaged multiple assign [%v], input: %v", reflect.TypeOf(s), cv.Position(s))
		}

	default:
		Panicf("convertTypeSwitchAssign, unmanaged statemet type [%v], input: %v", reflect.TypeOf(s), cv.Position(s))
	}

	return
}

func (cv *cppConverter) convertSwitchBody(env blockEnv, body *ast.BlockStmt, conditionVarName string, inputVarName string) (outlines []string) {

	fmt.Fprintf(cv.cpp.out, "%sint %s = -1;\n", cv.cpp.Indent(), conditionVarName)
	se := switchEnvName{inputVarName, conditionVarName, "", inputVarName != "", env.isTypeSwitch}
	cv.extractCaseExpr(body, &se)
	fmt.Fprintf(cv.cpp.out, "%sswitch(%s)\n", cv.cpp.Indent(), conditionVarName)

	cv.currentSwitchId.PushBack(0)
	outlines = cv.convertBlockStmt(body, makeSubBlockEnv(env, false))
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
				if se.isTypeSwitch {
					fmt.Fprintf(cv.cpp.out, "%s%sif(%s == typeid(%s)) { %s = %d; }\n", cv.cpp.Indent(), se.prefix, se.inputVarName, cv.convertExprCppType(expr), se.conditionVarName, id)
				} else {
					fmt.Fprintf(cv.cpp.out, "%s%sif(%s == %s) { %s = %d; }\n", cv.cpp.Indent(), se.prefix, se.inputVarName, cv.convertExpr(expr), se.conditionVarName, id)
				}
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
			fmt.Fprintf(cv.cpp.out, "%s%sif(%s) { %s = %d; }\n", cv.cpp.Indent(), se.prefix, cv.convertSelectCaseNode(s.Comm), se.conditionVarName, id)
		case *ast.ExprStmt:
			fmt.Fprintf(cv.cpp.out, "%s%sif(%s) { %s = %d; }\n", cv.cpp.Indent(), se.prefix, cv.convertSelectCaseNode(comm.X), se.conditionVarName, id)
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

	panic("convertSelectCaseStmt, bug, unreacheable code reached !")
}

func (cv *cppConverter) inlineStmt(stmt ast.Stmt, env blockEnv) (result string) {
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
					Panicf("inlineStmt, not implemented, can't declare outline from here. subtype [%v], input: %v", reflect.TypeOf(d), cv.Position(s))
				}
				if declItem.header != nil {
					Panicf("inlineStmt, not implemented, can't declare header from here. subtype [%v], input: %v", reflect.TypeOf(d), cv.Position(s))
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
		assignStmts := cv.convertAssignStmt(s, env)
		switch len(assignStmts) {
		case 1:
			return assignStmts[0]
		default:
			Panicf("inlineStmt, unmanaged multiple assignements [%v], input [%v]", reflect.TypeOf(s.Tok), cv.Position(s))
		}

	default:
		Panicf("inlineStmt, unmanaged token: [%v], input: %v", reflect.TypeOf(s), cv.Position(s))
	}

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
						name := GetCppName(s.Names[i].Name)
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
						name := GetCppName(s.Names[i].Name)

						if len(values) == 0 {
							result = append(result, inlineStr(fmt.Sprintf("%s %s%s", t.str, name, end)))
						} else {
							result = append(result, inlineStr(fmt.Sprintf("%s %s = %s%s", t.str, name, cv.convertExpr(values[i]), end)))
						}
					}
				}

			} else {
				if s.Type == nil {
					for i := range s.Names {
						name := GetCppName(s.Names[i].Name)
						if len(values) == 0 {
							result = append(result, inlineStr(fmt.Sprintf("auto %s%s", name, end)))
						} else {
							result = append(result, inlineStr(fmt.Sprintf("auto %s = %s%s", name, cv.convertExpr(values[i]), end)))
						}
					}
				} else {
					for i := range s.Names {
						name := GetCppName(s.Names[i].Name)
						t := cv.convertTypeExpr(s.Type)
						result = append(result, t.defs...)
						if len(values) == 0 {
							result = append(result, inlineStr(fmt.Sprintf("%s %s = {}%s", t.str, name, end)))
						} else {
							result = append(result, inlineStr(fmt.Sprintf("%s %s = %s%s", t.str, name, cv.convertExpr(values[i]), end)))
						}
					}
				}
			}

		case *ast.ImportSpec:
			// Check doc here https://pkg.go.dev/golang.org/x/tools/go/packages
			pkg := cv.typeInfo.PkgNameOf(s).Imported()

			cfg := &packages.Config{Mode: packages.NeedFiles | packages.NeedSyntax | packages.NeedName | packages.NeedCompiledGoFiles}

			pkgs, err := packages.Load(cfg, pkg.Path())
			if err != nil {
				Panicf("load: %v\n", err)
			}
			if packages.PrintErrors(pkgs) > 0 {
				os.Exit(1)
			}

			// Print the names of the source files
			// for each package listed on the command line.
			for _, pkg := range pkgs {
				for _, file := range pkg.GoFiles {
					result = append(result, importPackage(pkg.Name, pkg.PkgPath, file, GoFiles))
				}
				for _, file := range pkg.CompiledGoFiles {
					result = append(result, importPackage(pkg.Name, pkg.PkgPath, file, CompiledGoFiles))
				}
				for _, file := range pkg.OtherFiles {
					result = append(result, importPackage(pkg.Name, pkg.PkgPath, file, OtherFiles))
				}
				// use packages.NeedEmbedFiles in config to activate
				for _, file := range pkg.EmbedFiles {
					result = append(result, importPackage(pkg.Name, pkg.PkgPath, file, EmbedFiles))
				}
			}

		default:
			Panicf("convertSpecs, unmanaged type [%v], input: %v", reflect.TypeOf(s), cv.Position(s))
		}
		cv.UpdateIota()
	}

	return result
}

type pkgType int

const (
	Ignored         pkgType = iota
	GoFiles         pkgType = iota
	CompiledGoFiles pkgType = iota
	OtherFiles      pkgType = iota
	EmbedFiles      pkgType = iota
)

type pkgInfo struct {
	name     string
	pkgPath  string
	filePath string
	fileType pkgType
}

type place struct {
	// when type/declaration can be used inlined
	inline *string
	// when type/declaration need to be used outside function
	outline *string
	// when type/declaration need to be in header
	header *string

	//packages
	pkgInfo *pkgInfo
}

func inlineStr(str string) place {
	return place{&str, nil, nil, nil}
}

func outlineStr(str string) place {
	return place{nil, &str, nil, nil}
}

func headerStr(str string) place {
	return place{nil, nil, &str, nil}
}

func importPackage(name string, pkgPath string, filePath string, pkgType pkgType) place {
	return place{nil, nil, nil, &pkgInfo{name, pkgPath, filePath, pkgType}}
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
		name := GetCppName(node.Name.Name)
		usingDec := fmt.Sprintf("using %s = %s%s", name, GetCppType(n.Name), end)

		// Commented output in cpp as we only need one declaration
		return cppType{"// " + usingDec, []place{headerStr(usingDec)}, false}

	case *ast.FuncType:
		name := GetCppName(node.Name.Name)
		// TODO: This part is probably wrong
		return cppType{fmt.Sprintf("%s %s%s", cv.convertFuncTypeExpr(n), name, end), nil, false}

	// Check if it possible to simplify other case and delegates
	// more things to "convertTypeExpr".
	case *ast.ArrayType, *ast.ChanType, *ast.MapType, *ast.StarExpr:
		t := cv.convertTypeExpr(n)
		name := GetCppName(node.Name.Name)
		usingDec := fmt.Sprintf("using %s = %s%s", name, t.str, end)
		return cppType{"", append(t.defs, headerStr(usingDec)), false}

	case *ast.StructType:
		name := GetCppName(node.Name.Name)
		// TODO: return type value instead of writing in forward header directly
		fmt.Fprintf(cv.fwd.out, "%sstruct %s;\n", cv.fwd.Indent(), name)

		// TODO: return type value instead of writing in header directly
		structDecl := cv.convertStructTypeExpr(n, genStructParam{name, decl, with})
		fmt.Fprintf(cv.hpp.out, "%s%s", cv.hpp.Indent(), structDecl)

		return cppType{cv.convertStructTypeExpr(n, genStructParam{name, implem, with}), nil, false}

	case *ast.InterfaceType:
		name := GetCppName(node.Name.Name)
		// TODO: return type value instead of writing in forward header directly
		fmt.Fprintf(cv.fwd.out, "%sstruct %s;\n", cv.fwd.Indent(), name)

		// TODO: return type value instead of writing in header directly
		structDecl := cv.convertInterfaceTypeExpr(n, genStructParam{name, decl, with})
		fmt.Fprintf(cv.hpp.out, "%s%s", cv.hpp.Indent(), structDecl)

		return cppType{cv.convertInterfaceTypeExpr(n, genStructParam{name, implem, with}), nil, false}

	default:
		Panicf("convertTypeSpec, type %v, expr '%v', position %v", reflect.TypeOf(n), types.ExprString(n), cv.Position(n))
	}

	panic("convertTypeSpec, bug, unreacheable code reached !")
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
		Panicf("convertTypeExpr, type %v, expr '%v', position %v", reflect.TypeOf(n), types.ExprString(n), cv.Position(n))
	}

	panic("convertExprCppType, bug, unreacheable code reached !")
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
	return withFileBuffer(action, &cv.cpp)
}

func (cv *cppConverter) withHppBuffer(action action) string {
	return withFileBuffer(action, &cv.hpp)
}

func (cv *cppConverter) withFwdBuffer(action action) string {
	return withFileBuffer(action, &cv.fwd)
}

func withFileBuffer(action action, file *outFile) string {
	buf := new(bytes.Buffer)
	bufio := bufio.NewWriter(buf)
	previousOut := file.out
	defer func() { file.out = previousOut }()
	file.out = bufio

	action()

	bufio.Flush()
	return buf.String()
}

// Maybe merge this function with "convertExpr" in future ?
// Return cppType ?
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
			return "std::string"
		default:
			Panicf("Unmanaged token in convert type %v, token %v, position %v", reflect.TypeOf(node), n.Kind, cv.Position(n))
		}

	case *ast.CompositeLit:
		return cv.convertCompositeLitType(n, false).str

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
		exprType := cv.convertExprType(n)
		if exprType != nil {
			return convertGoToCppType(exprType, cv.Position(node))
		} else {
			return fmt.Sprintf("[%T, %s, %s]", n, types.ExprString(n), cv.Position(n))
		}
	}

	panic("convertExprCppType, bug, unreacheable code reached !")
}

func (cv *cppConverter) convertExprType(node ast.Expr) types.Type {
	if node == nil {
		return nil
	}

	typeInfo := cv.typeInfo.Types[node].Type

	if typeInfo != nil {
		return typeInfo
	}

	ident, ok := node.(*ast.Ident)
	if ok {
		def := cv.typeInfo.Defs[ident]
		if def != nil {
			return def.Type()
		}

		use := cv.typeInfo.Uses[ident]
		if use != nil {
			return use.Type()
		}
	}

	Panicf("convertExprType, node [%s], position [%s]", types.ExprString(node), cv.Position(node))
	panic("convertExprType, bug, unreacheable code reached !")
}

func convertGoToCppType(goType types.Type, position token.Position) string {
	if goType == nil {
		panic("convertGoToCppType, Cannot convert nil type.")
	}

	switch subType := goType.(type) {
	case *types.Basic:
		return GetCppGoType(subType)

	case *types.Named:
		return GetCppGoType(subType)

	case *types.Pointer:
		return fmt.Sprintf("%s*", GetCppGoType(subType.Elem()))

	case *types.Slice:
		return fmt.Sprintf("gocpp::slice<%s>", GetCppGoType(subType.Elem()))

	case *types.Array:
		return fmt.Sprintf("gocpp::array<%s, %d>", GetCppGoType(subType.Elem()), subType.Len())

	// TODO
	// case *types.Signature:
	// 	return fmt.Sprintf("std::function<%s (%s)>", GetCppGoType(subType.Params()), GetCppGoType(subType.Results()))

	default:
		panic(fmt.Sprintf("Unmanaged subType in convertGoToCppType, type [%v], position[%v]", reflect.TypeOf(subType), position))
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
		switch n.Kind {
		case token.IMAG:
			return "gocpp::complex128(0, " + strings.Replace(n.Value, "i", "", -1) + ")"
		case token.INT, token.FLOAT:
			return strings.ReplaceAll(n.Value, "_", "")
		default:
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

			outline := cv.convertBlockStmt(n.Body, makeBlockEnv(makeStmtEnv(outNames, outTypes), true))
			if outline != nil {
				fmt.Fprintf(cv.cpp.out, "### NOT IMPLEMENTED, convertExpr, outline not managed in ast.FuncLit ###")
			}
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
			Panicf("convertExprImpl, 3 value slice not implemented: %v, input: %v", types.ExprString(n), cv.Position(n))
		} else if n.Low == nil {
			return fmt.Sprintf("%s.make_slice(0, %s)", cv.convertExpr(n.X), cv.convertExpr(n.High))
		} else if n.High == nil {
			return fmt.Sprintf("%s.make_slice(%s)", cv.convertExpr(n.X), cv.convertExpr(n.Low))
		} else {
			return fmt.Sprintf("%s.make_slice(%s, %s)", cv.convertExpr(n.X), cv.convertExpr(n.Low), cv.convertExpr(n.High))
		}

	case *ast.StarExpr:
		return fmt.Sprintf("*%s", cv.convertExpr(n.X))

	case *ast.TypeAssertExpr:
		return fmt.Sprintf("gocpp::getValue<%s>(%s)", cv.convertExprCppType(n.Type), cv.convertExpr(n.X))

	default:
		Panicf("convertExprImpl, type %v, expr '%v', position %v", reflect.TypeOf(node), types.ExprString(n), cv.Position(n))
	}
	panic("convertExprType, bug, unreacheable code reached !")
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

func (cv *cppConverter) convertCompositeLitType(n *ast.CompositeLit, addPtr bool) cppType {
	if n.Type != nil {
		result := cv.convertTypeExpr(n.Type)
		if addPtr {
			result.str += "*"
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

func (cv *cppConverter) convertExprList(exprs []ast.Expr) (strs []string) {
	for _, expr := range exprs {
		strs = append(strs, cv.convertExpr(expr))
	}
	return strs
}

func (cv *cppConverter) convertExprs(exprs []ast.Expr) string {
	return strings.Join(cv.convertExprList(exprs), ", ")
}

func (cv *cppConverter) Position(expr ast.Node) token.Position {
	return cv.shared.fileSet.Position(expr.Pos())
}

/* from example: https://github.com/golang/example/tree/master/gotypes#introduction */
func (cv *cppConverter) LoadAndCheckDefs(path string, fset *token.FileSet, files ...*ast.File) error {
	conf := types.Config{Importer: importer.ForCompiler(fset, "source", nil)}
	if cv.typeInfo == nil {
		cv.typeInfo = &types.Info{
			Defs:      make(map[*ast.Ident]types.Object),
			Implicits: make(map[ast.Node]types.Object),
			Types:     make(map[ast.Expr]types.TypeAndValue),
			Uses:      make(map[*ast.Ident]types.Object),
		}
	}

	_, err := conf.Check(path, fset, files, cv.typeInfo)
	if err != nil {
		return err // type error
	}
	return nil
}

func (cv *cppConverter) PrintDefsUsage() {
	fmt.Println(" --  Info.Types -- ")
	for expr, obj := range cv.typeInfo.Types {
		var filePos = cv.Position(expr)
		cv.Logf("%s (%3d,%3d) => %25v has type [%15T] %v\n", filePos.Filename, filePos.Line, filePos.Column, types.ExprString(expr), obj.Type, obj.Type)
	}

	fmt.Println(" --  Info.Defs -- ")
	for id, obj := range cv.typeInfo.Defs {
		var filePos = cv.Position(id)
		cv.Logf("%s (%3d,%3d) => %15q defines [%15T] %v\n", filePos.Filename, filePos.Line, filePos.Column, id.Name, obj, obj)
	}

	fmt.Println(" --  Info.Uses -- ")
	for id, obj := range cv.typeInfo.Uses {
		var filePos = cv.Position(id)
		cv.Logf("%s (%3d,%3d) => %15q uses [%15T] %v\n", filePos.Filename, filePos.Line, filePos.Column, id.Name, obj, obj)
	}
}

func (parentCv *cppConverter) convertDependency(pkgInfos []*pkgInfo) (usedPkgInfos []*pkgInfo, toBeConverted []*cppConverter) {
	var astFiles map[string][]*ast.File = make(map[string][]*ast.File)
	var files map[string]bool = map[string]bool{}
	shared := parentCv.shared
	for _, pkgInfo := range pkgInfos {
		// Ignored file are ignored only for code generation
		if !(pkgInfo.fileType == GoFiles || pkgInfo.fileType == CompiledGoFiles || pkgInfo.fileType == Ignored) {
			continue
		}

		// getUsedDependency need this to get the correct package path
		shared.packagePaths[pkgInfo.filePath] = pkgInfo.pkgPath

		// if astFile, done := parentCv.parsedFiles[pkgInfo.filePath]; done {
		// 	astFiles[pkgInfo.name] = append(astFiles[pkgInfo.name], astFile)
		// 	files[pkgInfo.filePath] = true
		// 	continue
		// }

		parentCv.Logf(" => Loading dependency: %v, %v [%v]\n", pkgInfo.pkgPath, pkgInfo.filePath, pkgInfo.fileType)

		var cv *cppConverter = new(cppConverter)
		cv.logPrefix = parentCv.logPrefix + "##> "
		cv.tryRecover = !shared.strictMode
		cv.shared = parentCv.shared
		cv.genMakeFile = parentCv.genMakeFile
		cv.binOutDir = parentCv.binOutDir
		cv.inputName = pkgInfo.filePath
		cv.srcBaseName = "$(ImportDir)/" + pkgInfo.pkgPath + "/" + pkgInfo.baseName()
		cv.baseName = cv.shared.globalSubDir + pkgInfo.pkgPath + "/" + pkgInfo.baseName()

		// We need to parse ignored file to allow type check in PrintDefsUses
		cv.InitAndParse()

		// Don't need to type check a second time already analysed files
		if _, done := shared.parsedFiles[pkgInfo.filePath]; !done {
			astFiles[pkgInfo.name] = append(astFiles[pkgInfo.name], cv.astFile)

			// Ignored file will not be converted
			if pkgInfo.fileType != Ignored {
				toBeConverted = append(toBeConverted, cv)
			}

			shared.parsedFiles[pkgInfo.filePath] = cv.astFile
			files[pkgInfo.filePath] = true
		}
	}

	for pkgName, files := range astFiles {
		if err := parentCv.LoadAndCheckDefs(pkgName, shared.fileSet, files...); err != nil {
			log.Fatal(err) // type error
		}

		parentCv.Logf("LoadAndCheckDefs, %v\n", pkgName)
		for _, file := range files {
			parentCv.Logf("    - %v\n", parentCv.Position(file.Name))
		}
	}

	usedPkgInfos = parentCv.getUsedDependency()

	newGeneratedfiles := true
	loopCount := 1
	for newGeneratedfiles {
		newGeneratedfiles = false
		ignoredFiles := map[string]*cppConverter{}
		var notConverted []*cppConverter

		for _, cv := range toBeConverted {
			cv.typeInfo = parentCv.typeInfo
			if !shared.usedFiles[cv.inputName] {
				// Not used at the moment, but can be needed by other generated files
				ignoredFiles[cv.inputName] = cv
				parentCv.Logf("[%d] Not in used file: %v \n", loopCount, cv.inputName)
				continue
			}
			if shared.generatedFiles[cv.inputName] {
				parentCv.Logf("[%d] Already generated: %v \n", loopCount, cv.inputName)
				continue
			}
			shared.generatedFiles[cv.inputName] = true
			newGeneratedfiles = true
			notConverted = append(notConverted, cv.ConvertFile()...)
		}

		loopCount++
		toBeConverted = notConverted

		// Retry all ignored files in case they were needed by new generated file
		for _, cv := range ignoredFiles {
			toBeConverted = append(toBeConverted, cv)
		}
	}

	return
}

func main() {

	inputName := flag.String("input", "tests/HelloWorld.go", "The file to parse, when converting only one file")
	parseFmtDir := flag.Bool("parseFmt", false, "temporary test parameter")
	cppOutDir := flag.String("cppOutDir", "out", "generated code directory")
	binOutDir := flag.String("binOutDir", "log", "gcc output dir in Makefile")
	genMakeFile := flag.Bool("genMakeFile", false, "generate Makefile")
	strictMode := flag.Bool("strictMode", true, "panic on every error")
	verbose := flag.Bool("verbose", false, "verbose logs")
	alwaysRegenerate := flag.Bool("alwaysRegenerate", false, "force to always generate, even if more recent")

	flag.Parse()

	fset := token.NewFileSet()

	if *parseFmtDir {
		pkgs, errPkg := parser.ParseDir(fset, "F:/Dev/Golang/src/fmt", nil, parser.ParseComments)
		if errPkg != nil {
			fmt.Println(errPkg)
			return
		}

		for pkg, v := range pkgs {
			for file := range v.Files {
				fmt.Printf("%v -> %v\n", pkg, file)
			}
		}
	}

	exePath, _ := os.Executable()
	fileInfo, _ := os.Stat(exePath)

	shared := buildSharedData()
	shared.globalSubDir = "golang/"
	shared.fileSet = fset
	shared.cppOutDir = *cppOutDir
	shared.supportHeader = "gocpp/support.h"
	shared.exeDate = fileInfo.ModTime()
	shared.verbose = *verbose
	shared.strictMode = *strictMode
	shared.alwaysRegenerate = *alwaysRegenerate

	cv := new(cppConverter)
	cv.shared = shared
	cv.genMakeFile = *genMakeFile
	cv.binOutDir = *binOutDir
	cv.inputName = *inputName
	// No global subdir for main target at the moment
	cv.baseName = strings.TrimSuffix(cv.inputName, ".go")
	cv.srcBaseName = strings.TrimSuffix(cv.inputName, ".go")
	cv.tryRecover = false

	cv.InitAndParse()

	if err := cv.LoadAndCheckDefs("gocpp", fset, cv.astFile); err != nil {
		log.Fatal(err) // type error
	}

	defer cv.PrintDefsUsage()

	cv.ConvertFile()
}
