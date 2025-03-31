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
	"runtime/debug"
	"slices"
	"strings"
	"time"

	"golang.org/x/exp/maps"
	"golang.org/x/tools/go/packages"
)

func GetCppName(name string) string {
	val, ok := cppKeyWordsMapping[name]
	if ok {
		return val
	} else {
		return name
	}
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
	switch t := goType.(type) {
	case *types.Tuple:
		if t.Len() == 0 {
			return "void"
		}

		var strs []string
		for i := 0; i < t.Len(); i++ {
			strs = append(strs, GetCppGoType(t.At(i).Type()))
		}
		return strings.Join(strs, ", ")

	default:
		return GetCppType(goType.String())
	}
}

// func GetCppFunc[T string | cppExpr](funcName T) T
func GetCppFunc(funcName string) string {
	funcName = GetCppName(funcName)
	val, ok := stdFuncMapping[funcName]
	if ok {
		return val
	} else {
		return funcName
	}
}

func GetCppExprFunc(funcName cppExpr) cppExpr {
	funcName.str = GetCppName(funcName.str)
	val, ok := stdFuncMapping[funcName.str]
	if ok {
		return cppExpr{val, funcName.defs}
	} else {
		return funcName
	}
}

type typeName struct {
	names  []string
	Type   cppType
	isRecv bool
}

type typeNames []typeName

func (receivers *typeNames) setIsRecv() {
	for i := range *receivers {
		(*receivers)[i].isRecv = true
	}
}

func (tns typeNames) getDefs() (defs []place) {
	for _, tn := range tns {
		defs = append(defs, tn.Type.defs...)
	}
	return
}

func (tn typeName) ParamDecl() []string {
	var strs []string

	if len(tn.names) != 0 {
		for _, name := range tn.names {
			if tn.isRecv && tn.Type.isSimple {
				// Need to add 'struct' to avoid conflicts when function have the same name than the struct
				//   => exemple "RGBA" in "image\color\color.go"
				strs = append(strs, fmt.Sprintf("struct %v %v", GetCppType(tn.Type.str), name))
			} else {
				strs = append(strs, fmt.Sprintf("%v %v", GetCppType(tn.Type.str), name))
			}
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

func (pkgInfo *pkgInfo) basePath() string {
	if pkgInfo != nil {
		return fmt.Sprintf("%v/%v", pkgInfo.pkgPath, pkgInfo.baseName())
	}
	return "### UNDEFINED PATH ###"
}

func includeDependencies(out io.Writer, globalSubDir string, pkgInfos []*pkgInfo, tag tagType, suffix string) {
	if pkgInfos == nil {
		return
	}

	var alreadyIncluded map[string]bool = make(map[string]bool)

	slices.SortFunc(pkgInfos, func(p1 *pkgInfo, p2 *pkgInfo) int {
		return strings.Compare(p1.basePath(), p2.basePath())
	})

	for _, pkgInfo := range pkgInfos {
		if (pkgInfo.tag & tag) != tag {
			continue
		}
		if _, done := alreadyIncluded[pkgInfo.filePath]; done {
			continue
		}
		alreadyIncluded[pkgInfo.filePath] = true

		//fmt.Fprintf(out, "// globalSubDir: %v -- pkgInfo.pkgPath: %v -- pkgInfo.filePath: %v \n", globalSubDir, pkgInfo.pkgPath, pkgInfo.filePath)

		switch pkgInfo.fileType {
		case GoFiles, CompiledGoFiles:
			fmt.Fprintf(out, "#include \"%v%v%v\"\n", globalSubDir, pkgInfo.basePath(), suffix)
		case Ignored:
			fmt.Fprintf(out, "// #include \"%v%v%v\"  [Ignored, known errors]\n", globalSubDir, pkgInfo.basePath(), suffix)
		}
	}
	fmt.Fprintf(out, "\n")
}

func Ptr[T any](value T) *T {
	return &value
}

func (cv *cppConverter) includeFwdHeaderDependencies(pkgInfos []*pkgInfo, suffix string, order int) (result []*place) {
	globalSubDir := cv.shared.globalSubDir
	if pkgInfos == nil {
		return nil
	}

	var alreadyIncluded map[string]bool = make(map[string]bool)

	slices.SortFunc(pkgInfos, func(p1 *pkgInfo, p2 *pkgInfo) int {
		return strings.Compare(p1.basePath(), p2.basePath())
	})

	for _, pkgInfo := range pkgInfos {
		if _, done := alreadyIncluded[pkgInfo.filePath]; done {
			continue
		}
		alreadyIncluded[pkgInfo.filePath] = true

		order++
		di := depInfo{nil, map[types.Type]bool{}, "", map[string]bool{}, pkgInfo.basePath(), map[string]bool{}, order, 0}

		switch pkgInfo.fileType {
		case GoFiles, CompiledGoFiles:
			str := fmt.Sprintf("#include \"%v%v%v\"\n", globalSubDir, pkgInfo.basePath(), suffix)
			result = append(result, Ptr(includeStr(str, di)))
		case Ignored:
			str := fmt.Sprintf("// #include \"%v%v%v\" [Ignored, known errors]\n", globalSubDir, pkgInfo.basePath(), suffix)
			result = append(result, Ptr(includeStr(str, di)))
		}
	}
	return
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
	fmt.Fprintf(out, "#include \"%s.h\"\n", cv.shared.supportHeader)
	fmt.Fprintf(out, "\n")

	includeDependencies(out, cv.shared.globalSubDir, pkgInfos, UsesTag, ".h")

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
	fmt.Fprintf(out, "#include \"%s.h\"\n", cv.shared.supportHeader)
	fmt.Fprintf(out, "\n")

	// Can we do something with ".fwd.h" in some situations ?
	includeDependencies(out, cv.shared.globalSubDir, pkgInfos, DefsTag, ".h")

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

func printFwdIntro(cv *cppConverter /*, pkgInfos []*pkgInfo*/) {
	out := cv.fwd.out
	generatedMessage(out, cv)
	fmt.Fprintf(out, "#pragma once\n")
	fmt.Fprintf(out, "\n")
	fmt.Fprintf(out, "#include \"%s.fwd.h\"\n", cv.shared.supportHeader)
	fmt.Fprintf(out, "\n")

	cv.fwd.indent++
}

func printFwdOutro(cv *cppConverter) {
	// Close golang namespace
	cv.fwd.indent--
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

func GetFileTimeStamp(filename string, defaultInFuture bool, ignoreEmpty bool) time.Time {
	fileInfo, error := os.Stat(filename)
	if error != nil || (ignoreEmpty && fileInfo.Size() == 0) {
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
				cv.Logf("PANIC when converting file %s, %s, %s\n", cv.inputName, r, string(debug.Stack()))
			}
		}()
	}

	if !shared.alwaysRegenerate {
		cppFileName := shared.cppOutDir + "/" + cv.baseName + ".cpp"
		// Consider empty files as non-existant in strict Mode
		goFileDate := GetFileTimeStamp(cv.inputName, true, shared.strictMode)
		cppFileDate := GetFileTimeStamp(cppFileName, false, shared.strictMode)

		if shared.verbose {
			cv.Logf(" ExeDate: %v\n", shared.exeDate)
			cv.Logf(" goFileDate: %v\n", goFileDate)
			cv.Logf(" cppFileDate: %v\n", cppFileDate)
		}
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
	var allOutPlaces [][]place
	var pkgInfos []*pkgInfo
	var allCppOut, allHppOut, allFwdOut []string
	for _, decl := range cv.astFile.Decls {
		var outPlaces []place
		var cppOut, hppOut, fwdOut string

		fwdOut = cv.withFwdBuffer(func() {
			hppOut = cv.withHppBuffer(func() {
				cppOut = cv.withCppBuffer(func() {
					declOutPlaces, declPkgInfos := cv.convertDecls(decl, true)
					outPlaces = append(outPlaces, declOutPlaces...)
					pkgInfos = append(pkgInfos, declPkgInfos...)
				})
			})
		})

		allOutPlaces = append(allOutPlaces, outPlaces)
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

	var fwdHeaderElts []*place
	initialOrder := 0
	for i := 0; i < len(allOutPlaces); i++ {
		for _, place := range allOutPlaces[i] {
			if place.outline != nil {
				fmt.Fprintf(cv.cpp.out, "%s%s\n", cv.cpp.Indent(), *place.outline)
			}
			if place.fwdHeader != nil {
				initialOrder++
				place.depInfo.initialOrder = initialOrder
				fwdHeaderElts = append(fwdHeaderElts, &place)
			}
			if place.header != nil || place.inline != nil {
				panic("BUG: place.header and place.inline should always be nil at this point.")
			}
		}
		fmt.Fprintf(cv.fwd.out, "%s", allFwdOut[i])
		fmt.Fprintf(cv.hpp.out, "%s", allHppOut[i])
		fmt.Fprintf(cv.cpp.out, "%s", allCppOut[i])
	}

	fwdHeaderElts = append(fwdHeaderElts, cv.includeFwdHeaderDependencies(usedPkgInfos, ".fwd.h", initialOrder)...)
	inNamespace := false
	indent := ""

	if len(fwdHeaderElts) != 0 {
		for _, place := range fwdHeaderElts {
			di := &place.depInfo
			di.ComputeDeps()
			cv.Logf("Fwd header decl info[%v, %v]: type='%v', deps=%v, pkg='%v', depPkgs=%v, name='%v', depNames=%v\n", di.rank, di.initialOrder, di.decType, di.dependencies, di.decPkg, di.depPkgs, di.decIdent, di.depIdents)
		}

		cv.Logf("Fwd header decl: Sorting.\n")
		cv.topoSort(fwdHeaderElts)

		maxDecIndex := -1
		for i, place := range fwdHeaderElts {
			if !place.isInclude {
				maxDecIndex = i
			}
		}

		for i, place := range fwdHeaderElts {

			// Skip includes not needed by any definitions
			if i > maxDecIndex {
				break
			}

			// Close namespace for includes
			if place.isInclude && inNamespace {
				fmt.Fprintf(cv.fwd.out, "}\n")
				inNamespace = false
				indent = ""
			}

			// Open namespace for declarartions
			if !place.isInclude && !inNamespace {
				fmt.Fprintf(cv.fwd.out, "\nnamespace golang::%v\n{\n", cv.namespace)
				inNamespace = true
				indent = cv.fwd.Indent()
			}

			fmt.Fprintf(cv.fwd.out, "%s%s", indent, *place.fwdHeader)

			di := &place.depInfo
			cv.Logf("Fwd header decl info[%v, %v]: type='%v', deps=%v, pkg='%v', depPkgs=%v, name='%v', depNames=%v\n", di.rank, di.initialOrder, di.decType, di.dependencies, di.decPkg, di.depPkgs, di.decIdent, di.depIdents)
		}

		//ensure namespace is closed at end
		if inNamespace {
			fmt.Fprintf(cv.fwd.out, "}\n")
		}
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

func (cv *cppConverter) ComparePlace(x *place, y *place) int {
	_, ok := x.depInfo.dependencies[y.depInfo.decType]
	xstr := strings.TrimSpace(*x.fwdHeader)
	ystr := strings.TrimSpace(*y.fwdHeader)
	if ok {
		cv.Logf("Fwd header sort type: '%v' use type '%v' .\n", xstr, y.depInfo.decType)
		return 1
	}
	_, ok = y.depInfo.dependencies[x.depInfo.decType]
	if ok {
		cv.Logf("Fwd header sort type: '%v' use type '%v' .\n", ystr, x.depInfo.decType)
		return -1
	}

	_, ok = x.depInfo.depIdents[y.depInfo.decIdent]
	if ok {
		cv.Logf("Fwd header sort ident: '%v' use ident '%v'.\n", xstr, y.depInfo.decIdent)
		return 1
	}
	_, ok = y.depInfo.depIdents[x.depInfo.decIdent]
	if ok {
		cv.Logf("Fwd header sort ident: '%v' use ident '%v'.\n", ystr, x.depInfo.decIdent)
		return -1
	}

	_, ok = x.depInfo.depPkgs[y.depInfo.decPkg]
	if ok {
		cv.Logf("Fwd header sort pkg: '%v' used by pkg '%v'.\n", xstr, y.depInfo.decPkg)
		return 1
	}
	_, ok = y.depInfo.depPkgs[x.depInfo.decPkg]
	if ok {
		cv.Logf("Fwd header sort pkg: '%v' used by pkg '%v'.\n", ystr, x.depInfo.decPkg)
		return -1
	}

	// TODO: find a way to do include/imports as late as possible

	return 0
	//return cmp.Compare(x.depInfo.initialOrder, y.depInfo.initialOrder)
}

// Probably not an efficient toposort algorithm
// Custom toposort with additional constraints
//
//	-> that preserve initial order if possible
//	-> push import as late as possible
//	-> push declaration as soon as possible
func (cv *cppConverter) topoSort(fwdHeaderElts []*place) {
	var maxIndex int = 0
	elts := map[int]map[*place]bool{}
	elts[maxIndex] = map[*place]bool{}
	for _, elt := range fwdHeaderElts {
		elts[0][elt] = true
	}

	for len(elts[maxIndex]) > 0 {
		curentIndex := maxIndex
		maxIndex++
		elts[maxIndex] = map[*place]bool{}

		for elt1 := range elts[curentIndex] {

			for elt2 := range elts[maxIndex] {
				if elt1 == elt2 {
					continue
				}

				switch cv.ComparePlace(elt1, elt2) {
				case 1:
					delete(elts[curentIndex], elt1)
					elts[maxIndex][elt1] = true
					elt1.depInfo.rank = maxIndex
				}
			}

			for elt2 := range elts[curentIndex] {
				if elt1 == elt2 {
					continue
				}

				switch cv.ComparePlace(elt1, elt2) {
				case -1:
					delete(elts[curentIndex], elt2)
					elts[maxIndex][elt2] = true
					elt2.depInfo.rank = maxIndex
				case 1:
					delete(elts[curentIndex], elt1)
					elts[maxIndex][elt1] = true
					elt1.depInfo.rank = maxIndex
				}
			}
		}
	}

	// Add intermedite space netween existing ranks
	splitElts := map[int]map[*place]bool{}
	for i, rankElts := range elts {
		for elt := range rankElts {
			elt.depInfo.rank = 2*i + 0
		}
		splitElts[2*i+0] = rankElts
		splitElts[2*i+1] = map[*place]bool{}
	}
	elts = splitElts
	maxIndex = 2 * maxIndex

	// Push imports as late as possible
	for i := 0; i < maxIndex-1; i++ {
		for elt1 := range elts[i] {
			if elt1.depInfo.decPkg == "" {
				continue
			}
			pushLater := true
			for elt2 := range elts[i+1] {
				if cv.ComparePlace(elt1, elt2) != 0 {
					pushLater = false
					break
				}
			}

			if pushLater {
				delete(elts[i], elt1)
				elts[i+1][elt1] = true
				elt1.depInfo.rank = i + 1
			}
		}
	}

	// Push defintion as soon as possible
	for i := maxIndex; i > 0; i-- {
		for elt1 := range elts[i] {
			if elt1.depInfo.decPkg != "" {
				continue
			}
			pushSooner := true
			for elt2 := range elts[i-1] {
				if cv.ComparePlace(elt1, elt2) != 0 {
					pushSooner = false
					break
				}
			}

			if pushSooner {
				delete(elts[i], elt1)
				elts[i-1][elt1] = true
				elt1.depInfo.rank = i - 1
			}
		}
	}

	slices.SortFunc(fwdHeaderElts, func(x *place, y *place) int {
		if x.depInfo.rank < y.depInfo.rank {
			return -1
		} else if x.depInfo.rank > y.depInfo.rank {
			return +1
		}

		if x.depInfo.initialOrder < y.depInfo.initialOrder {
			return -1
		} else if x.depInfo.initialOrder > y.depInfo.initialOrder {
			return +1
		}
		return 0
	})
}

func ToString(obj fmt.Stringer) string {
	if obj != nil {
		return obj.String()
	}
	return ""
}

func (cv *cppConverter) Logf(format string, a ...any) (n int, err error) {
	fmt.Printf("%s", cv.logPrefix)
	return fmt.Printf(format, a...)
}

func (cv *cppConverter) getUsedDependency() (pkgInfos []*pkgInfo) {

	usedTypes := cv.getReferencedTypesFor(cv.inputName)
	cv.logReferencedTypesFrom(usedTypes, "Used")

	cv.shared.usedFiles[cv.inputName] = true

	for usedType, tag := range usedTypes {
		result := cv.getPackageFromType(usedType, tag)
		if result != nil {
			pkgInfos = append(pkgInfos, result)
		}
	}
	return
}

func (cv *cppConverter) getPackageFromType(usedType types.Object, tag tagType) *pkgInfo {
	if usedType == nil {
		return nil
	}

	var file = cv.shared.fileSet.Position(usedType.Pos()).Filename

	// Hack for "unsafe.Pointer" in "unsafe" package
	// Maybe we should load it manually somewhere in cv.fileset ?
	if file == "" {
		for pkgFile, path := range cv.shared.packagePaths {
			if path == "unsafe" {
				file = pkgFile
			}
		}
	}

	if file == "" || file == cv.inputName {
		pkgName := "<pkgName>"
		pkgPath := "<pkgPath>"
		if usedType.Pkg() != nil {
			pkgName = usedType.Pkg().Name()
			pkgPath = usedType.Pkg().Path()
		}
		cv.Logf("SKIPPED, pkgName: %v, pkgPath: %v, file: %v, usedTypeName: %v, tag: %v ---\n", pkgName, pkgPath, file, usedType.Name(), tag)
		return nil
	}

	cv.shared.usedFiles[file] = true
	pkg := usedType.Pkg()
	if pkg != nil {
		cv.Logf("pkginfo, pkgName: %v, pkgPath: %v, file: %v, usedTypeName: %v, tag: %v ---\n", pkg.Name(), pkg.Path(), file, usedType.Name(), tag)

		// usedType.Pkg().Path() doesn't return the full path, using value stored when loading packages
		pkgPath, ok := cv.shared.packagePaths[file]
		if ok {
			return &pkgInfo{pkg.Name(), pkgPath, file, tag, GoFiles}
		} else {
			cv.Logf("  -> pkgPath is null, file: %v\n", file)
			return &pkgInfo{pkg.Name(), pkg.Path(), file, tag, GoFiles}
		}
	} else {
		cv.Logf("pkginfo, nil pkg, file: %v, usedTypeName: %v, tag:%v ---\n", file, usedType.Name(), tag)
	}
	return nil
}

func (cv *cppConverter) getReferencedTypesFor(file string) (usedTypes map[types.Object]tagType) {
	usedTypes = make(map[types.Object]tagType)

	/*
	 * We need to manage dependecies in header and cpp like we do in forward header.
	 * Once it will be done, all "tags" used to know if we need include in header or source file will be useless.
	 */
	uses := cv.typeInfo.Uses
	cv.filtereUsedObjects(uses, file, usedTypes, UsesTag)
	defs := cv.typeInfo.Defs
	cv.filtereUsedObjects(defs, file, usedTypes, DefsTag)
	return
}

func (cv *cppConverter) filtereUsedObjects(objs map[*ast.Ident]types.Object, file string, usedTypes map[types.Object]tagType, tag tagType) {
	for id, obj := range objs {
		var filePos = cv.Position(id)
		if file != filePos.Filename {
			continue
		}

		switch t := obj.(type) {
		case *types.TypeName, *types.Const:
			usedTypes[t] |= tag
			for _, o := range GetObjectsOfType(t.Type()) {
				usedTypes[o] |= tag
			}

		case *types.Func:
			usedTypes[t] |= tag
			for _, o := range GetObjectsOfType(t.Type()) {
				usedTypes[o] |= tag
			}

		case *types.Var:
			switch tag {
			case DefsTag:
				scopeCount := getScopeCounts(obj)
				// len(scopeCount) == 0  --> member of structs
				// len(scopeCount) == 1  --> ? ? ?
				// len(scopeCount) == 2  --> global variable
				if len(scopeCount) <= 2 {
					for _, o := range GetObjectsOfType(t.Type()) {
						usedTypes[o] |= tag
					}
				}
			default:
				// We will probably need need at some point.
				// usedTypes[t] |= tag
			}
		}
	}
}

func internalGetObjectsOfType(t types.Type, seen map[types.Object]bool) {
	switch typ := t.(type) {
	case *types.Basic:
		// Basic types do not have associated objects
	case *types.Named:
		obj := typ.Obj()
		if !seen[obj] {
			seen[obj] = true
			internalGetObjectsOfType(typ.Underlying(), seen)
		}
	case *types.Pointer:
		internalGetObjectsOfType(typ.Elem(), seen)
	case *types.Array:
		internalGetObjectsOfType(typ.Elem(), seen)
	case *types.Slice:
		internalGetObjectsOfType(typ.Elem(), seen)
	case *types.Map:
		internalGetObjectsOfType(typ.Key(), seen)
		internalGetObjectsOfType(typ.Elem(), seen)
	case *types.Chan:
		internalGetObjectsOfType(typ.Elem(), seen)
	case *types.Struct:
		for i := 0; i < typ.NumFields(); i++ {
			field := typ.Field(i)
			if !seen[field] {
				seen[field] = true
				internalGetObjectsOfType(field.Type(), seen)
			}
		}
	case *types.Interface:
		for i := 0; i < typ.NumMethods(); i++ {
			method := typ.Method(i)
			if !seen[method] {
				seen[method] = true
				internalGetObjectsOfType(method.Type(), seen)
			}
		}
	case *types.Signature:
		if recv := typ.Recv(); recv != nil {
			internalGetObjectsOfType(recv.Type(), seen)
		}
		for i := 0; i < typ.Params().Len(); i++ {
			internalGetObjectsOfType(typ.Params().At(i).Type(), seen)
		}
		for i := 0; i < typ.Results().Len(); i++ {
			internalGetObjectsOfType(typ.Results().At(i).Type(), seen)
		}
	case *types.Tuple:
		for i := 0; i < typ.Len(); i++ {
			internalGetObjectsOfType(typ.At(i).Type(), seen)
		}
	}
}

// GetObjectsOfType returns a list of types.Object used to define the given type.
func GetObjectsOfType(t types.Type) []types.Object {
	seen := make(map[types.Object]bool)
	internalGetObjectsOfType(t, seen)
	return maps.Keys(seen)
}

func (cv *cppConverter) logReferencedTypesFrom(usedTypes map[types.Object]tagType, name string) {
	cv.Logf("\n")
	cv.Logf(" --- %s types by %s ---\n", name, cv.inputName)

	for usedType, tag := range usedTypes {
		pkg := usedType.Pkg()
		pkgName := "<nill pkg>"
		if pkg != nil {
			pkgName = pkg.Name()
		}
		var file = cv.shared.fileSet.Position(usedType.Pos())
		cv.Logf("path: %s.%s, objType:%T, id: %s, exported: %v, tag: %v, file: %v\n", pkgName, usedType.Name(), usedType, usedType.Id(), usedType.Exported(), tag, file)
	}

	cv.Logf("\n")
	cv.Logf(" --- ---\n")
}

type errorFilter struct {
	target string
	file   string
}

func (cv *cppConverter) ignoreKnownErrors(pkgInfos []*pkgInfo) {

	for _, pkg := range pkgInfos {

		// Potentially slow but funtion 'ignoreKnownErrors' should be removed completly in future
		for _, bad := range knownCompilationErrors {
			pkgFilePath := strings.ReplaceAll(pkg.filePath, "\\", "/")
			pkgName := strings.ReplaceAll(pkg.name, "\\", "/")
			if cv.shared.verbose {
				cv.Logf("ignoreKnownErrors, pkg.name: '%v', bad.pkg: '%v', pkgFilePath: '%v', bad.file: '%v'\n", pkg.name, bad.target, pkgFilePath, bad.file)
			}
			if pkgName == bad.target && strings.HasSuffix(pkgFilePath, bad.file) {
				pkg.fileType = Ignored
				continue
			}
		}
	}
}

func (cv *cppConverter) ignoreKnownError(funcName string, knownErrors []*errorFilter) bool {
	// Potentially slow but funtion 'ignoreKnownErrors' should be removed completly in future
	for _, bad := range knownErrors {
		pkgFilePath := strings.ReplaceAll(cv.srcBaseName, "\\", "/")
		if funcName == bad.target && strings.HasSuffix(pkgFilePath, bad.file) {
			return true
		}
	}
	return false
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

func convertUnaryToken(t token.Token) string {
	switch t {
	case token.XOR:
		return "~"
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

// print inline and header, keep outline and fwdHeader for later
func (cv *cppConverter) printOrKeepPlace(place place, outPlaces *[]place, pkgInfos *[]*pkgInfo) {
	// Print immediatly inline && header in buffer
	if place.inline != nil {
		fmt.Fprintf(cv.cpp.out, "%s%s", cv.cpp.Indent(), *place.inline)
	}
	if place.header != nil {
		fmt.Fprintf(cv.hpp.out, "%s%s", cv.hpp.Indent(), *place.header)
	}

	//outline, fwdHeader and pkgInfo will be managed by caller
	if place.outline != nil {
		*outPlaces = append(*outPlaces, place)
	}
	if place.fwdHeader != nil {
		*outPlaces = append(*outPlaces, place)
	}
	if place.pkgInfo != nil {
		*pkgInfos = append(*pkgInfos, place.pkgInfo)
	}
}

// func (cv *cppConverter) printOrKeepPlaces(places []place, outPlaces *[]place, pkgInfos *[]*pkgInfo) {
// 	for _, place := range places {
// 		cv.printOrKeepPlace(place, outPlaces, pkgInfos)
// 	}
// }

func Last[EltType any](elts []EltType) (EltType, bool) {
	if len(elts) == 0 {
		var zero EltType
		return zero, false
	}
	return elts[len(elts)-1], true
}

func (cv *cppConverter) convertDecls(decl ast.Decl, isNameSpace bool) (outPlaces []place, pkgInfos []*pkgInfo) {
	cv.Logf("decl: %v at %v\n", reflect.TypeOf(decl), cv.Position(decl))

	switch d := decl.(type) {
	case *ast.GenDecl:
		for _, place := range cv.convertSpecs(d.Specs, d.Tok, isNameSpace, ";\n") {
			cv.printOrKeepPlace(place, &outPlaces, &pkgInfos)
		}

	case *ast.FuncDecl:
		params := cv.readFields(d.Recv)
		params.setIsRecv()
		params = append(params, cv.readFields(d.Type.Params)...)
		outNames, outTypes := cv.getResultInfos(d.Type)
		resultType := buildOutType(outTypes)

		cv.DeclareVars(params)
		typenames := map[string]bool{}
		for _, param := range params {
			for _, place := range param.Type.defs {
				cv.printOrKeepPlace(place, &outPlaces, nil)
			}
			for _, tn := range param.Type.typenames {
				typenames[tn] = true
			}
		}

		name := GetCppName(d.Name.Name)

		if cv.ignoreKnownError(name, knownNameConflicts) {
			fmt.Fprintf(cv.hpp.out, "%s/* %s %s(%s); [Ignored, known name conflict] */ \n", cv.cpp.Indent(), resultType, name, params)
		} else {
			if len(typenames) != 0 {
				fmt.Fprintf(cv.hpp.out, "\n%s%s\n", cv.cpp.Indent(), mkTemplateDec(maps.Keys(typenames)))
			}
			fmt.Fprintf(cv.hpp.out, "%s%s %s(%s);\n", cv.cpp.Indent(), resultType, name, params)
		}

		last, ok := Last(params)
		if ok && last.Type.isEllipsis {

			if len(last.names) != 1 {
				Panicf("convertDecls, multiple ellipsis parameters not managed, declararation: [%v], input: %v", d, cv.Position(d))
			}

			varidicParams := params[:len(params)-1]
			varidicParams = append(make([]typeName, 0, len(varidicParams)), varidicParams...)
			var strs []string
			for _, params := range varidicParams {
				strs = append(strs, params.names...)
			}
			strs = append(strs, fmt.Sprintf("gocpp::ToSlice<%s>(%s...)", last.Type.eltType, last.names[0]))
			callParams := strings.Join(strs, ", ")
			varidicParams = append(varidicParams, typeName{last.names, mkCppType("Args...", nil), false})

			fmt.Fprintf(cv.hpp.out, "\n%stemplate<typename... Args>\n", cv.cpp.Indent())
			fmt.Fprintf(cv.hpp.out, "%s%s %s(%s)\n", cv.cpp.Indent(), resultType, name, varidicParams)
			fmt.Fprintf(cv.hpp.out, "%s{\n", cv.cpp.Indent())
			fmt.Fprintf(cv.hpp.out, "%s    return %s(%s);\n", cv.cpp.Indent(), name, callParams)
			fmt.Fprintf(cv.hpp.out, "%s}\n\n", cv.cpp.Indent())
		}

		if len(typenames) != 0 {
			fmt.Fprintf(cv.cpp.out, "\n%s%s\n", cv.cpp.Indent(), mkTemplateDec(maps.Keys(typenames)))
		}
		fmt.Fprintf(cv.cpp.out, "%s%s %s(%s)\n", cv.cpp.Indent(), resultType, name, params)
		if name == "main" {
			cv.hasMain = true
		}

		blockOutlines := cv.convertBlockStmt(d.Body, makeBlockEnv(makeStmtEnv(outNames, outTypes), true))
		outPlaces = append(outPlaces, blockOutlines...)
		fmt.Fprintf(cv.cpp.out, "\n")

	case *ast.BadDecl:
		panic("convertDecls[BadDecl] Not implemented")

	default:
		panic("convertDecls, unmanaged subtype")
	}
	return
}

func (cv *cppConverter) convertBlockStmt(block *ast.BlockStmt, env blockEnv) (outPlaces []place) {
	return cv.convertBlockStmtImpl(block, env, "\n", nil)
}

func (cv *cppConverter) convertInlinedBlockStmt(block *ast.BlockStmt, env blockEnv) (outPlaces []place) {
	return cv.convertBlockStmtImpl(block, env, "", nil)
}

func (cv *cppConverter) convertBlockStmtWithLabel(block *ast.BlockStmt, env blockEnv, label *ast.Ident) (outPlaces []place) {
	return cv.convertBlockStmtImpl(block, env, "\n", label)
}

func (cv *cppConverter) convertBlockStmtImpl(block *ast.BlockStmt, env blockEnv, end string, label *ast.Ident) (outPlaces []place) {

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
			stmtOutiles, _ := cv.convertStmt(stmt, env)
			outPlaces = append(outPlaces, stmtOutiles...)
		}

		if label != nil {
			fmt.Fprintf(cv.cpp.out, "%sif(false) {\n", cv.cpp.Indent())
			fmt.Fprintf(cv.cpp.out, "%s%s_continue:\n", cv.cpp.Indent(), label.Name)
			fmt.Fprintf(cv.cpp.out, "%s    continue;\n", cv.cpp.Indent())
			fmt.Fprintf(cv.cpp.out, "%s%s_break:\n", cv.cpp.Indent(), label.Name)
			fmt.Fprintf(cv.cpp.out, "%s    break;\n", cv.cpp.Indent())
			fmt.Fprintf(cv.cpp.out, "%s}\n", cv.cpp.Indent())
		}
	})

	if env.isFunc && *env.useDefer {
		fmt.Fprintf(cv.cpp.out, "%sgocpp::Defer defer;\n", cv.cpp.Indent())
	}

	fmt.Fprintf(cv.cpp.out, "%s", cppOut)

	cv.cpp.indent--
	fmt.Fprintf(cv.cpp.out, "%s}%s", cv.cpp.Indent(), end)
	cv.endScope()
	return
}

func (cv *cppConverter) convertReturnExprs(exprs []ast.Expr, outNames []string) cppExpr {
	switch len(exprs) {
	case 0:
		if outNames != nil {
			switch len(outNames) {
			case 0:
				panic("convertReturnExprs, len(outNames) == 0")
			case 1:
				return ExprPrintf("return %s", outNames[0])
			default:
				return ExprPrintf("return {%s}", strings.Join(outNames, ", "))
			}
		} else {
			return mkCppExpr("return")
		}
	case 1:
		return ExprPrintf("return %s", cv.convertExprs(exprs))
	default:
		return ExprPrintf("return {%s}", cv.convertExprs(exprs))
	}
}

func (cv *cppConverter) convertAssignRightExprs(exprs []ast.Expr) cppExpr {
	switch len(exprs) {
	case 0:
		return mkCppExpr("")
	case 1:
		return cv.convertExprs(exprs)
	default:
		return ExprPrintf("std::tuple{%s}", cv.convertExprs(exprs))
	}
}

func (cv *cppConverter) convertAssignStmt(stmt *ast.AssignStmt, env blockEnv) []cppExpr {
	switch stmt.Tok {
	case token.DEFINE:
		switch len(stmt.Lhs) {
		case 0:
			panic("convertAssignStmt, len(exprs) == 0")
		case 1:
			varName := cv.convertExpr(stmt.Lhs[0])
			*env.varNames = append(*env.varNames, varName.str)
			return []cppExpr{ExprPrintf("auto %s = %s", varName, cv.convertAssignRightExprs(stmt.Rhs))}
		default:
			var decl []cppExpr
			var allNew = true
			var exprList = cv.convertExprList(stmt.Lhs)
			var toDeclare []string
			// first step, just check if there is already declared names
			for _, varName := range exprList {
				if varName.str == "_" {
					varName.str = cv.GenerateId()
				}
				if !slices.Contains(*env.varNames, varName.str) {
					toDeclare = append(toDeclare, varName.str)
					*env.varNames = append(*env.varNames, varName.str)
				} else {
					allNew = false
				}
			}

			if allNew {
				// Not necessary, the default case would work, but output looks better
				return []cppExpr{ExprPrintf("auto [%s] = %s", cv.convertExprs(stmt.Lhs), cv.convertAssignRightExprs(stmt.Rhs))}
			}

			// The 2-step loop on exprList is done to not call "cv.convertExprCppType"
			// when not strictly necessary as not all types are implemented at the moment.
			for i, varName := range exprList {
				//decl = append(decl, fmt.Sprintf("// DBG, declared names : (%s)", strings.Join(*env.varNames, ", ")))
				if slices.Contains(toDeclare, varName.str) {
					if stmt.Lhs[i] != nil {
						decl = append(decl, ExprPrintf("%s %s", cv.convertExprCppType(stmt.Lhs[i]), varName))
					} else {
						decl = append(decl, ExprPrintf("%s %s", "### NIL EXPRESSION: 'stmt.Lhs[i]'", varName))
					}
					*env.varNames = append(*env.varNames, varName.str)
				}
			}
			return append(decl, ExprPrintf("std::tie(%s) = %s", cv.convertExprs(stmt.Lhs), cv.convertAssignRightExprs(stmt.Rhs)))
		}
	case token.ASSIGN:
		switch len(stmt.Lhs) {
		case 0:
			panic("convertAssignStmt, len(exprs) == 0")
		case 1:
			return []cppExpr{ExprPrintf("%s = %s", cv.convertExpr(stmt.Lhs[0]), cv.convertAssignRightExprs(stmt.Rhs))}
		default:
			return []cppExpr{ExprPrintf("std::tie(%s) = %s", cv.convertExprs(stmt.Lhs), cv.convertAssignRightExprs(stmt.Rhs))}
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
				return []cppExpr{ExprPrintf("%s %s %s", cv.convertExprs(stmt.Lhs), stmt.Tok, cv.convertAssignRightExprs(stmt.Rhs))}
			default:
				panic("convertAssignStmt, len(exprs) != 1")
			}
		}

	default:
		Panicf("convertAssignStmt, unmanaged token: %s, input: %v", stmt.Tok, cv.Position(stmt))
	}

	panic("convertAssignStmt, bug, unreacheable code reached !")
}

func (cv *cppConverter) convertStmt(stmt ast.Stmt, env blockEnv) (outPlaces []place, isFallThrough bool) {
	return cv.convertLabelledStmt(stmt, env, nil)
}

func (cv *cppConverter) convertLabelledStmt(stmt ast.Stmt, env blockEnv, label *ast.Ident) (outPlaces []place, isFallThrough bool) {

	if label != nil {
		switch s := stmt.(type) {
		case *ast.ForStmt, *ast.RangeStmt:
			/* Nothing to do */
		case *ast.SwitchStmt, *ast.SelectStmt, *ast.TypeSwitchStmt:
			Panicf("convertStmt, label not implemented. statement type: %v, input: %v", reflect.TypeOf(s), cv.Position(s))
		default:
			/* Nothing to do */
		}
	}

	cppOut := &cppExprWritter[*bufio.Writer]{cv.cpp.out, &[]place{}}

	switch s := stmt.(type) {
	case *ast.BlockStmt:
		outPlaces = cv.convertBlockStmt(s, makeSubBlockEnv(env, false))

	case *ast.DeclStmt:
		var pkgInfos []*pkgInfo
		outPlaces, pkgInfos = cv.convertDecls(s.Decl, false)
		if len(pkgInfos) != 0 {
			Panicf("convertStmt, can't manage pkgInfos here, declaration: [%v], input: %v", s.Decl, cv.Position(s))
		}

	case *ast.ExprStmt:
		cv.WritterExprPrintf(cppOut, "%s%s;\n", cv.cpp.Indent(), cv.convertExpr(s.X))

	case *ast.IncDecStmt:
		cv.WritterExprPrintf(cppOut, "%s%s%s;\n", cv.cpp.Indent(), cv.convertExpr(s.X), s.Tok)

	case *ast.ReturnStmt:
		cv.WritterExprPrintf(cppOut, "%s%s;\n", cv.cpp.Indent(), cv.convertReturnExprs(s.Results, env.outNames))

	case *ast.AssignStmt:
		stmts := cv.convertAssignStmt(s, env)
		for _, stmt := range stmts {
			cv.WritterExprPrintf(cppOut, "%s%s;\n", cv.cpp.Indent(), stmt)
		}

	case *ast.DeferStmt:
		*env.useDefer = true
		cv.WritterExprPrintf(cppOut, "%sdefer.push_back([=]{ %s; });\n", cv.cpp.Indent(), cv.convertExpr(s.Call))

	case *ast.GoStmt:
		cv.WritterExprPrintf(cppOut, "%sgocpp::go([&]{ %s; });\n", cv.cpp.Indent(), cv.convertExpr(s.Call))

	case *ast.SendStmt:
		cv.WritterExprPrintf(cppOut, "%s%s.send(%s);\n", cv.cpp.Indent(), cv.convertExpr(s.Chan), cv.convertExpr(s.Value))

	case *ast.ForStmt:
		env.startVarScope()
		cv.WritterExprPrintf(cppOut, "%sfor(%s; %s; %s)\n", cv.cpp.Indent(), cv.inlineStmt(s.Init, env), cv.convertExpr(s.Cond), cv.inlineStmt(s.Post, env))
		outPlaces = cv.convertBlockStmtWithLabel(s.Body, makeSubBlockEnv(env, false), label)

	case *ast.BranchStmt:
		if s.Label == nil {
			switch s.Tok {
			case token.BREAK:
				cv.WritterExprPrintf(cppOut, "%sbreak;\n", cv.cpp.Indent())
			case token.CONTINUE:
				cv.WritterExprPrintf(cppOut, "%scontinue;\n", cv.cpp.Indent())
			case token.FALLTHROUGH:
				isFallThrough = true
			default:
				Panicf("convertStmt, unmanaged BranchStmt [%v], input: %v", s.Tok, cv.Position(s))
			}
		} else {
			switch s.Tok {
			case token.BREAK:
				cv.WritterExprPrintf(cppOut, "%sgoto %s_break;\n", cv.cpp.Indent(), s.Label)
			case token.CONTINUE:
				cv.WritterExprPrintf(cppOut, "%sgoto %s_continue;\n", cv.cpp.Indent(), s.Label)
			case token.GOTO:
				cv.WritterExprPrintf(cppOut, "%sgoto %s;\n", cv.cpp.Indent(), s.Label)
			case token.FALLTHROUGH:
				fallthrough // Not implemented
			default:
				Panicf("convertStmt, unmanaged labelled BranchStmt, label: %v, token: %v, input: %v", s.Label, s.Tok, cv.Position(s))
			}
		}

	case *ast.LabeledStmt:
		cv.WritterExprPrintf(cppOut, "%s%s:\n", cv.cpp.Indent(), s.Label.Name)
		outPlaces, isFallThrough = cv.convertLabelledStmt(s.Stmt, env, s.Label)

	case *ast.RangeStmt:
		if s.Key != nil && s.Value != nil && s.Tok == token.DEFINE {
			cv.WritterExprPrintf(cppOut, "%sfor(auto [%s, %s] : %s)\n", cv.cpp.Indent(), cv.convertExpr(s.Key), cv.convertExpr(s.Value), cv.convertExpr(s.X))
		} else if s.Key != nil && s.Value == nil && s.Tok == token.DEFINE {
			cv.WritterExprPrintf(cppOut, "%sfor(auto [%s, gocpp_ignored] : %s)\n", cv.cpp.Indent(), cv.convertExpr(s.Key), cv.convertExpr(s.X))
		} else if s.Key == nil && s.Value == nil {
			cv.WritterExprPrintf(cppOut, "%sfor(const auto& _ : %s)\n", cv.cpp.Indent(), cv.convertExpr(s.X))
		} else {
			Panicf("Unmanaged case of '*ast.RangeStmt', token: %v, input: %v", s.Tok, cv.Position(s))
		}
		outPlaces = cv.convertBlockStmtWithLabel(s.Body, makeSubBlockEnv(env, false), label)

	case *ast.IfStmt:
		if s.Init != nil {
			env.startVarScope()
			cv.WritterExprPrintf(cppOut, "%sif(%s; %s)\n", cv.cpp.Indent(), cv.inlineStmt(s.Init, env), cv.convertExpr(s.Cond))
		} else {
			cv.WritterExprPrintf(cppOut, "%sif(%s)\n", cv.cpp.Indent(), cv.convertExpr(s.Cond))
		}

		blockOutline := cv.convertBlockStmt(s.Body, makeSubBlockEnv(env, false))
		outPlaces = append(outPlaces, blockOutline...)
		if s.Else != nil {
			cv.WritterExprPrintf(cppOut, "%selse\n", cv.cpp.Indent())
			elseOutPlace, isFallthrough := cv.convertStmt(s.Else, env)
			outPlaces = append(outPlaces, elseOutPlace...)
			if isFallthrough {
				// Shouldn't happen correctly go file
				Panicf("convertStmt, fallthrough not managed in ast.IfStmt, input: %v", cv.Position(s.Else))
			}
		}

	case *ast.SwitchStmt:
		cv.WritterExprPrintf(cppOut, "%s//Go switch emulation\n", cv.cpp.Indent())
		cv.WritterExprPrintf(cppOut, "%s{\n", cv.cpp.Indent())
		cv.cpp.indent++

		if s.Init != nil {
			env.startVarScope()
			cv.WritterExprPrintf(cppOut, "%s%s;\n", cv.cpp.Indent(), cv.inlineStmt(s.Init, env))
		}

		inputVarName := ""
		if s.Tag != nil {
			inputVarName = "condition"
			cv.WritterExprPrintf(cppOut, "%sauto %s = %s;\n", cv.cpp.Indent(), inputVarName, cv.convertExpr(s.Tag))
		}

		outPlaces = cv.convertSwitchBody(env, s.Body, "conditionId", inputVarName)

	case *ast.TypeSwitchStmt:
		cv.WritterExprPrintf(cppOut, "%s//Go type switch emulation\n", cv.cpp.Indent())
		cv.WritterExprPrintf(cppOut, "%s{\n", cv.cpp.Indent())
		cv.cpp.indent++

		if s.Init != nil {
			env.startVarScope()
			cv.WritterExprPrintf(cppOut, "%s%s;\n", cv.cpp.Indent(), cv.inlineStmt(s.Init, env))
		}

		var switchExpr cppExpr
		var inputVarName cppExpr
		switchVarName := cv.GenerateId()
		if s.Assign != nil {
			inputVarName, switchExpr = cv.convertTypeSwitchAssign(s.Assign)
			cv.WritterExprPrintf(cppOut, "%sconst auto& %s = gocpp::type_info(%s);\n", cv.cpp.Indent(), switchVarName, switchExpr)
		}

		env.isTypeSwitch = true
		env.typeSwitchVarName = inputVarName.str
		env.switchVarName = switchExpr.str
		outPlaces = cv.convertSwitchBody(env, s.Body, "conditionId", switchVarName)

	case *ast.SelectStmt:
		cv.WritterExprPrintf(cppOut, "%s//Go select emulation\n", cv.cpp.Indent())
		cv.WritterExprPrintf(cppOut, "%s{\n", cv.cpp.Indent())
		cv.cpp.indent++

		outPlaces = cv.convertSwitchBody(env, s.Body, "conditionId", "")
		cv.WritterExprPrintf(cppOut, "%sstd::this_thread::yield();\n", cv.cpp.Indent())

	case *ast.CaseClause:
		var caseType cppExpr
		if s.List == nil {
			cv.WritterExprPrintf(cppOut, "%sdefault:\n", cv.cpp.Indent())
		} else {
			for range s.List {
				id := cv.currentSwitchId.Back().Value.(int)
				cv.WritterExprPrintf(cppOut, "%scase %d:\n", cv.cpp.Indent(), id)
				cv.currentSwitchId.Back().Value = id + 1
			}

			if env.isTypeSwitch {
				caseType = cv.convertExprCppType(s.List[0]).cppExpr
			}
		}

		if env.isTypeSwitch {
			cv.WritterExprPrintf(cppOut, "%s{\n", cv.cpp.Indent())
		}

		cv.cpp.indent++

		if env.isTypeSwitch {
			if caseType.str != "" {
				cv.WritterExprPrintf(cppOut, "%s%s %s = gocpp::any_cast<%s>(%s);\n", cv.cpp.Indent(), caseType, env.switchVarName, caseType, env.typeSwitchVarName)
			} else {
				cv.WritterExprPrintf(cppOut, "%sauto %s = %s;\n", cv.cpp.Indent(), env.switchVarName, env.typeSwitchVarName)
			}
		}

		var isStmtFallthrough bool
		var stmtOutPlace []place
		for _, stmt := range s.Body {
			if isStmtFallthrough {
				// Shouldn't happen correctly go file
				Panicf("convertStmt, fallthrough not managed if not the last statement")
			}
			stmtOutPlace, isStmtFallthrough = cv.convertStmt(stmt, env)
			outPlaces = append(outPlaces, stmtOutPlace...)
		}
		if !isStmtFallthrough {
			cv.WritterExprPrintf(cppOut, "%sbreak;\n", cv.cpp.Indent())
		}
		cv.cpp.indent--

		if env.isTypeSwitch {
			cv.WritterExprPrintf(cppOut, "%s}\n", cv.cpp.Indent())
		}

	case *ast.CommClause:

		if s.Comm == nil {
			cv.WritterExprPrintf(cppOut, "%sdefault:\n", cv.cpp.Indent())
		} else {
			id := cv.currentSwitchId.Back().Value.(int)
			cv.WritterExprPrintf(cppOut, "%scase %d:\n", cv.cpp.Indent(), id)
			cv.currentSwitchId.Back().Value = id + 1
		}

		cv.cpp.indent++
		var isStmtFallthrough bool
		var stmtOutPlace []place
		for _, stmt := range s.Body {
			stmtOutPlace, isStmtFallthrough = cv.convertStmt(stmt, env)
			outPlaces = append(outPlaces, stmtOutPlace...)
		}
		if !isStmtFallthrough {
			cv.WritterExprPrintf(cppOut, "%sbreak;\n", cv.cpp.Indent())
		}
		cv.cpp.indent--

	default:
		Panicf("convertStmt, unmanaged type [%v], input: %v", reflect.TypeOf(s), cv.Position(s))
	}

	// use defer for this ?
	outPlaces = append(outPlaces, *cppOut.defs...)

	return
}

type switchEnvName struct {
	inputVarName     string
	conditionVarName string
	prefix           string
	withCondition    bool
	isTypeSwitch     bool
}

func (cv *cppConverter) convertTypeSwitchAssign(stmt ast.Stmt) (varName cppExpr, exprString cppExpr) {

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

func (cv *cppConverter) convertSwitchBody(env blockEnv, body *ast.BlockStmt, conditionVarName string, inputVarName string) (outPlaces []place) {
	cppOut := mkCppWritter(cv.cpp.out)

	cv.WritterExprPrintf(cppOut, "%sint %s = -1;\n", cv.cpp.Indent(), conditionVarName)
	se := switchEnvName{inputVarName, conditionVarName, "", inputVarName != "", env.isTypeSwitch}
	caseDefs := cv.extractCaseExpr(body, &se)
	outPlaces = append(outPlaces, caseDefs...)
	cv.WritterExprPrintf(cppOut, "%sswitch(%s)\n", cv.cpp.Indent(), conditionVarName)

	cv.currentSwitchId.PushBack(0)
	blockDefs := cv.convertBlockStmt(body, makeSubBlockEnv(env, false))
	outPlaces = append(outPlaces, blockDefs...)
	cv.currentSwitchId.Remove(cv.currentSwitchId.Back())

	cv.cpp.indent--
	cv.WritterExprPrintf(cppOut, "%s}\n", cv.cpp.Indent())

	if len(*cppOut.defs) != 0 {
		Panicf("convertSwitchBody, not Implemented, manage cppOut.defs, type [%v], %s", reflect.TypeOf(body), cv.Position(body))
	}

	return
}

func (cv *cppConverter) extractCaseExpr(stmt ast.Stmt, se *switchEnvName) (outPlaces []place) {
	cppOut := mkCppWritter(cv.cpp.out)

	switch s := stmt.(type) {
	case *ast.BlockStmt:
		cv.currentSwitchId.PushBack(0)
		for _, stmt := range s.List {
			elts := cv.extractCaseExpr(stmt, se)
			outPlaces = append(outPlaces, elts...)
		}
		cv.currentSwitchId.Remove(cv.currentSwitchId.Back())

	case *ast.CaseClause:
		for _, expr := range s.List {
			id := cv.currentSwitchId.Back().Value.(int)
			if se.withCondition {
				if se.isTypeSwitch {
					cv.WritterExprPrintf(cppOut, "%s%sif(%s == typeid(%s)) { %s = %d; }\n", cv.cpp.Indent(), se.prefix, se.inputVarName, cv.convertExprCppType(expr), se.conditionVarName, id)
				} else {
					cv.WritterExprPrintf(cppOut, "%s%sif(%s == %s) { %s = %d; }\n", cv.cpp.Indent(), se.prefix, se.inputVarName, cv.convertExpr(expr), se.conditionVarName, id)
				}
			} else {
				cv.WritterExprPrintf(cppOut, "%s%sif(%s) { %s = %d; }\n", cv.cpp.Indent(), se.prefix, cv.convertExpr(expr), se.conditionVarName, id)
			}
			cv.currentSwitchId.Back().Value = id + 1
		}
		se.prefix = "else "

	case *ast.CommClause:
		id := cv.currentSwitchId.Back().Value.(int)
		switch comm := s.Comm.(type) {
		case *ast.SendStmt:
			cv.WritterExprPrintf(cppOut, "%s%sif(%s) { %s = %d; }\n", cv.cpp.Indent(), se.prefix, cv.convertSelectCaseNode(s.Comm), se.conditionVarName, id)
		case *ast.ExprStmt:
			cv.WritterExprPrintf(cppOut, "%s%sif(%s) { %s = %d; }\n", cv.cpp.Indent(), se.prefix, cv.convertSelectCaseNode(comm.X), se.conditionVarName, id)
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

	outPlaces = append(outPlaces, *cppOut.defs...)
	return
}

func (cv *cppConverter) convertSelectCaseNode(node ast.Node) (result cppExpr) {
	switch n := node.(type) {
	case nil:
		return

	case *ast.SendStmt:
		return ExprPrintf("%s.trySend(%s)", cv.convertExpr(n.Chan), cv.convertExpr(n.Value))

	case *ast.ExprStmt:
		return cv.convertSelectCaseNode(n.X)

	case *ast.UnaryExpr:
		switch {
		case n.Op == token.ARROW:
			return ExprPrintf("auto [gocpp_ignored , ok] = %s.tryRecv(); ok", cv.convertExpr(n.X))
		default:
			Panicf("convertSelectCaseStmt,unmanaged token: [%v], inout: %v", reflect.TypeOf(n.Op), cv.Position(n))
		}

	default:
		Panicf("convertSelectCaseStmt, unmanaged node: [%v], inout: %v", reflect.TypeOf(n), cv.Position(n))
	}

	panic("convertSelectCaseStmt, bug, unreacheable code reached !")
}

func (cv *cppConverter) inlineStmt(stmt ast.Stmt, env blockEnv) (result cppExpr) {
	switch s := stmt.(type) {
	case nil:
		return

	case *ast.SendStmt:
		return ExprPrintf("%s.send(%s)", cv.convertExpr(s.Chan), cv.convertExpr(s.Value))

	case *ast.DeclStmt:
		switch d := s.Decl.(type) {
		case *ast.GenDecl:
			for _, declItem := range cv.convertSpecs(d.Specs, d.Tok, false, "") {
				if declItem.inline != nil {
					result = ExprPrintf("%s%s,", result, *declItem.inline)
				}
				// TODO
				if declItem.outline != nil {
					Panicf("inlineStmt, not implemented, can't declare outline from here. subtype [%v], input: %v", reflect.TypeOf(d), cv.Position(s))
				}
				if declItem.header != nil {
					Panicf("inlineStmt, not implemented, can't declare header from here. subtype [%v], input: %v", reflect.TypeOf(d), cv.Position(s))
				}
				if declItem.fwdHeader != nil {
					Panicf("inlineStmt, not implemented, can't declare forward header from here. subtype [%v], input: %v", reflect.TypeOf(d), cv.Position(s))
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
			return ExprPrintf("%s++", cv.convertExpr(s.X))
		case token.DEC:
			return ExprPrintf("%s--", cv.convertExpr(s.X))
		default:
			Panicf("inlineStmt, unmanaged type [%v]", reflect.TypeOf(s.Tok))
		}

	case *ast.AssignStmt:
		assignStmts := cv.convertAssignStmt(s, env)
		switch nbStmts := len(assignStmts); nbStmts {
		case 0:
			Panicf("inlineStmt, unmanaged multiple assignements: %v, input: %v", reflect.TypeOf(s), cv.Position(s))
		case 1:
			return assignStmts[0]
		default:
			result = assignStmts[nbStmts-1]
			for i := 0; i < nbStmts-1; i++ {
				result.defs = append(result.defs, assignStmts[i].defs...)
				result.defs = append(result.defs, inlineStr(assignStmts[i].str))
			}
			return
		}

	default:
		Panicf("inlineStmt, unmanaged token: [%v], input: %v", reflect.TypeOf(s), cv.Position(s))
	}

	panic("inlineStmt, bug, unreacheable code reached !")
}

func (cv *cppConverter) getResultInfos(funcType *ast.FuncType) (outNames, outTypes []string) {
	goResults := cv.readFields(funcType.Results)
	defs := []place{}

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
		defs = append(defs, result.Type.defs...)
	}

	if !useNamedResults {
		outNames = nil
	}

	if len(defs) != 0 {
		Panicf("getResultInfos, not Implemented, manage defs")
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

type CanForward struct {
	cv    *cppConverter
	value bool
}

func (visitor *CanForward) Visit(node ast.Node) ast.Visitor {
	switch n := node.(type) {
	case ast.Expr:
		exprType := visitor.cv.typeInfo.Types[n].Type
		switch t := exprType.(type) {
		case *types.Basic:
			switch t.Kind() {
			case types.String, types.Complex64, types.Complex128:
				visitor.value = false
				return nil
			}
		}
	case nil:
		return nil
	}
	return visitor
}

func (cv *cppConverter) canForward(expr ast.Expr) bool {
	cf := &CanForward{cv: cv, value: true}
	ast.Walk(cf, expr)
	return cf.value
}

func (cv *cppConverter) convertSpecs(specs []ast.Spec, tok token.Token, isNamespace bool, end string) []place {
	var result []place

	cv.ResetIota()
	var values []ast.Expr

	for _, spec := range specs {
		switch s := spec.(type) {
		case *ast.TypeSpec:
			if s.Comment != nil {
				for _, comment := range s.Comment.List {
					result = append(result, inlineStrf("// %s\n", comment.Text)...)
				}
			}

			t := cv.convertTypeSpec(s, end, isNamespace)
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
						canFwd := exprType.canFwd && cv.canForward(values[i])
						if name == "_" {
							result = append(result, inlineStrf("%s %s = %s%s", exprType, cv.GenerateId(), expr, end)...)
						} else if tok == token.CONST && canFwd {
							if cv.ignoreKnownError(name, knownMissingDeps) {
								result = append(result, fwdHeaderStrf(cv.getValueDepInfo(s, i), "/*const %s %s = %s [known mising deps] */%s", exprType, name, expr, end)...)
							} else {
								result = append(result, fwdHeaderStrf(cv.getValueDepInfo(s, i), "const %s %s = %s%s", exprType, name, expr, end)...)
							}
						} else {
							if cv.ignoreKnownError(name, knownMissingDeps) {
								result = append(result, headerStrf("/* extern %s %s [known mising deps] */%s", exprType.str /* don't duplicate defs */, name, end)...)
								result = append(result, inlineStrf("/* %s %s = %s [known mising deps] */%s", exprType, name, expr, end)...)
							} else {
								result = append(result, headerStrf("extern %s %s%s", exprType.str /* don't duplicate defs */, name, end)...)
								result = append(result, inlineStrf("%s %s = %s%s", exprType, name, expr, end)...)
							}
						}
					}
				} else {
					for i := range s.Names {
						exprType := cv.convertTypeExpr(s.Type)
						name := GetCppName(s.Names[i].Name)

						if len(values) == 0 {
							result = append(result, inlineStrf("%s %s%s", exprType, name, end)...)
						} else if tok == token.CONST && exprType.canFwd {
							if cv.ignoreKnownError(name, knownMissingDeps) {
								result = append(result, fwdHeaderStrf(cv.getValueDepInfo(s, i), "/*const %s %s = %s [known mising deps] */%s", exprType, name, cv.convertExpr(values[i]), end)...)
							} else {
								result = append(result, fwdHeaderStrf(cv.getValueDepInfo(s, i), "const %s %s = %s%s", exprType, name, cv.convertExpr(values[i]), end)...)
							}
						} else {
							if cv.ignoreKnownError(name, knownMissingDeps) {
								result = append(result, headerStrf("/* extern %s %s [known mising deps] */%s", exprType.str /* don't duplicate defs */, name, end)...)
								result = append(result, inlineStrf("/* %s %s = %s [known mising deps] */%s", exprType, name, cv.convertExpr(values[i]), end)...)
							} else {
								result = append(result, headerStrf("extern %s %s%s", exprType.str /* don't duplicate defs */, name, end)...)
								result = append(result, inlineStrf("%s %s = %s%s", exprType, name, cv.convertExpr(values[i]), end)...)
							}
						}
					}
				}

			} else {
				if s.Type == nil {
					for i := range s.Names {
						name := GetCppName(s.Names[i].Name)
						if len(values) == 0 {
							result = append(result, inlineStrf("auto %s%s", name, end)...)
						} else {
							result = append(result, inlineStrf("auto %s = %s%s", name, cv.convertExpr(values[i]), end)...)
						}
					}
				} else {
					for i := range s.Names {
						name := GetCppName(s.Names[i].Name)
						t := cv.convertTypeExpr(s.Type)
						if len(values) == 0 {
							result = append(result, inlineStrf("%s %s = {}%s", t, name, end)...)
						} else {
							result = append(result, inlineStrf("%s %s = %s%s", t, name, cv.convertExpr(values[i]), end)...)
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

/*
 * We need to manage dependecies in header and cpp like we do in forward header.
 * Once it will be done, all "tags" used to know if we need include in header or source file will be useless.
 */

type tagType int

const (
	UnknwonTag tagType = 0
	UsesTag    tagType = 1
	DefsTag    tagType = 2
)

type pkgInfo struct {
	name     string
	pkgPath  string
	filePath string
	tag      tagType
	fileType pkgType
}

type depInfo struct {
	decType      types.Type
	dependencies map[types.Type]bool

	decIdent  string
	depIdents map[string]bool

	decPkg  string
	depPkgs map[string]bool

	initialOrder int
	rank         int
}

func (depInfo *depInfo) ComputeDeps() {
	depInfo.dependencies = ComputeDeps(depInfo.dependencies)
}

func ComputeDeps(toDo map[types.Type]bool) map[types.Type]bool {
	done := map[types.Type]bool{}
	for len(toDo) != 0 {
		for elt := range toDo {
			if _, skip := done[elt]; skip {
				delete(toDo, elt)
				continue
			}

			switch t := elt.(type) {
			case *types.Array:
				toDo[t.Elem()] = true

			case *types.Chan:
				toDo[t.Elem()] = true

			case *types.Slice:
				toDo[t.Elem()] = true

			case *types.Map:
				toDo[t.Elem()] = true
				toDo[t.Key()] = true

			case *types.Pointer:
				toDo[t.Elem()] = true

			case nil, *types.Alias, *types.Basic, *types.Interface, *types.Named, *types.Struct:
				// Nothing to do

			default:
				Panicf("ComputeDeps, unmanaged type %T", t)
			}

			done[elt] = true
			delete(toDo, elt)
		}
	}

	return done
}

type place struct {
	// when type/declaration can be used inlined
	inline *string
	// when type/declaration need to be used outside function
	outline *string
	// when type/declaration need to be in header
	header *string
	// when type/declaration need to be in forward declarations header
	fwdHeader *string
	isInclude bool

	// -> Currently it's a fixed value chosen at creation but ultimately
	// this should be computed by looking at dependency graph.
	// -> used only for forward declaration order at the moment
	depInfo depInfo

	//packages
	pkgInfo *pkgInfo
}

func inlineStr(str string) place {
	return place{&str, nil, nil, nil, false, depInfo{}, nil}
}

func outlineStr(str string) place {
	return place{nil, &str, nil, nil, false, depInfo{}, nil}
}

func headerStr(str string) place {
	return place{nil, nil, &str, nil, false, depInfo{}, nil}
}

func fwdHeaderStr(str string, depInfo depInfo) place {
	return place{nil, nil, nil, &str, false, depInfo, nil}
}

func includeStr(str string, depInfo depInfo) place {
	return place{nil, nil, nil, &str, true, depInfo, nil}
}

func importPackage(name string, pkgPath string, filePath string, pkgType pkgType) place {
	return place{nil, nil, nil, nil, false, depInfo{}, &pkgInfo{name, pkgPath, filePath, UnknwonTag, pkgType}}
}

func inlineStrf(format string, params ...any) []place {
	expr := ExprPrintf(format, params...)
	expr.defs = append(expr.defs, inlineStr(expr.str))
	return expr.defs
}

// func outlineStrf(format string, params ...any) []place {
// 	expr := ExprPrintf(format, params...)
// 	expr.defs = append(expr.defs, outlineStr(expr.str))
// 	return expr.defs
// }

func headerStrf(format string, params ...any) []place {
	expr := ExprPrintf(format, params...)
	expr.defs = append(expr.defs, headerStr(expr.str))
	return expr.defs
}

func fwdHeaderStrf(di depInfo, format string, params ...any) []place {
	expr := ExprPrintf(format, params...)
	expr.defs = append(expr.defs, fwdHeaderStr(expr.str, di))
	return expr.defs
}

type cppExpr struct {
	str  string  // cpp type as a string
	defs []place // inline def used by type
}

func (expr cppExpr) toCppType() cppType {
	return cppType{expr, false, false, false, "", nil, true}
}

func mkCppExpr(str string) cppExpr {
	return cppExpr{str, nil}
}

type cppType struct {
	cppExpr
	isPtr      bool // is type a pointer ?
	isSimple   bool // is the name of a stuct or an interface
	isEllipsis bool // is type created by an ellipsis
	eltType    string
	typenames  []string

	canFwd bool // Can go in forward header
}

func mkCppType(str string, defs []place) cppType {
	return cppType{cppExpr{str, defs}, false, false, false, "", nil, true}
}

func mkCppPtrType(expr cppExpr) cppType {
	return cppType{expr, true, false, false, "", nil, true}
}

func mkCppEllipsis(expr cppExpr, eltType string) cppType {
	return cppType{expr, false, false, true, eltType, nil, true}
}

type cppExprWritter[TWritter io.Writer] struct {
	buff TWritter // cpp type as a string
	defs *[]place // inline def used by type
}

type cppExprBuffer cppExprWritter[*bytes.Buffer]

func mkCppWritter[TWritter io.Writer](w TWritter) *cppExprWritter[TWritter] {
	return &cppExprWritter[TWritter]{w, &[]place{}}
}

func mkCppBuffer() *cppExprBuffer {
	return &cppExprBuffer{new(bytes.Buffer), &[]place{}}
}

// func (buff *cppExprBuffer) UpCast() *cppExprWritter[io.Writer] {
// 	// maybe there is a better way to do this
// 	// I can't manage to do directly a type cast
// 	return &cppExprWritter[io.Writer]{buff.buff, buff.defs}
// }

func (buff *cppExprBuffer) Expr() cppExpr {
	return cppExpr{buff.buff.String(), *buff.defs}
}

func mkTemplateDec(templatePrms []string) string {
	return fmt.Sprintf("template<typename %s>", strings.Join(templatePrms, ", typename "))
}

func (cv *cppConverter) convertTypeSpec(node *ast.TypeSpec, end string, isNamespace bool) cppType {
	if node == nil {
		panic("node is nil")
	}

	templateDec := ""
	templatePrms := []string{}
	if node.TypeParams != nil {
		for _, field := range node.TypeParams.List {
			for _, name := range field.Names {
				templatePrms = append(templatePrms, name.Name)
			}
		}

		templateDec = mkTemplateDec(templatePrms) + " "
	}

	switch n := node.Type.(type) {

	// Check if it possible to simplify other case and delegates
	// more things to "convertTypeExpr".
	case *ast.ArrayType, *ast.ChanType, *ast.FuncType, *ast.Ident, *ast.MapType, *ast.SelectorExpr, *ast.StarExpr:
		t := cv.convertTypeExpr(n)
		name := GetCppName(node.Name.Name)
		var usingDec string

		if cv.ignoreKnownError(name, knownMissingDeps) {
			usingDec = fmt.Sprintf("/* %susing %s = %s */%s", templateDec, name, t.str, end)
		} else {
			usingDec = fmt.Sprintf("%susing %s = %s%s", templateDec, name, t.str, end)
		}

		if isNamespace {
			return mkCppType("", append(t.defs, fwdHeaderStr(usingDec, cv.getTypeDepInfo(node))))
		} else {
			return mkCppType("", append(t.defs, inlineStr(usingDec)))
		}

	case *ast.StructType:
		name := GetCppName(node.Name.Name)
		defs := []place{}

		if isNamespace {
			structFwdDecl := fmt.Sprintf("%sstruct %s;\n", templateDec, name)
			defs = append(defs, fwdHeaderStr(structFwdDecl, cv.getTypeDepInfo(node)))

			structDecl := cv.convertStructTypeExpr(n, templatePrms, genStructParam{name, decl, with})
			if templateDec != "" {
				structDecl = fmt.Sprintf("%s\n%s%s", templateDec, cv.hpp.Indent(), structDecl)
			}
			defs = append(defs, headerStr(structDecl))
		}

		return mkCppType(cv.convertStructTypeExpr(n, templatePrms, genStructParam{name, implem, with}), defs)

	case *ast.InterfaceType:
		name := GetCppName(node.Name.Name)
		defs := []place{}

		if isNamespace {
			structFwdDecl := fmt.Sprintf("%sstruct %s;\n", templateDec, name)
			defs = append(defs, fwdHeaderStr(structFwdDecl, cv.getTypeDepInfo(node)))

			structDecl := cv.convertInterfaceTypeExpr(n, templatePrms, genStructParam{name, decl, with})
			if templateDec != "" {
				structDecl = fmt.Sprintf("%s\n%s%s", templateDec, cv.hpp.Indent(), structDecl)
			}
			defs = append(defs, headerStr(structDecl))
		}

		return mkCppType(cv.convertInterfaceTypeExpr(n, templatePrms, genStructParam{name, implem, with}), defs)

	default:
		Panicf("convertTypeSpec, type %v, expr '%v', position %v", reflect.TypeOf(n), types.ExprString(n), cv.Position(n))
	}

	panic("convertTypeSpec, bug, unreacheable code reached !")
}

type GetIdentfiers struct {
	idents map[*ast.Ident]bool
}

func (visitor *GetIdentfiers) Visit(node ast.Node) ast.Visitor {
	switch n := node.(type) {
	case *ast.Ident:
		visitor.idents[n] = true
	case nil:
		return nil
	}
	return visitor
}

func getAllIdentifiers(expr ast.Expr) map[*ast.Ident]bool {
	gi := &GetIdentfiers{map[*ast.Ident]bool{}}
	ast.Walk(gi, expr)
	return gi.idents
}

func (cv *cppConverter) getAllUsedPackages(expr ast.Expr) map[string]bool {
	result := map[string]bool{}
	for ident := range getAllIdentifiers(expr) {
		defObj := cv.typeInfo.Uses[ident]
		if defObj != nil {
			pkg := cv.getPackageFromType(defObj, UnknwonTag)
			if pkg != nil {
				result[pkg.basePath()] = true
			}
		}
	}
	return result
}

func (cv *cppConverter) getAllUsedNames(expr ast.Expr) map[string]bool {
	result := map[string]bool{}
	for ident := range getAllIdentifiers(expr) {
		result[ident.Name] = true
	}
	return result
}

func (cv *cppConverter) getTypeDepInfo(n *ast.TypeSpec) depInfo {
	pkgs := cv.getAllUsedPackages(n.Type)
	definedName := cv.typeInfo.Defs[n.Name].Type()
	usedType := cv.typeInfo.Types[n.Type].Type
	return depInfo{definedName, map[types.Type]bool{usedType: true}, n.Name.Name, map[string]bool{}, "", pkgs, 0, 0}
}

func (cv *cppConverter) getValueDepInfo(n *ast.ValueSpec, i int) depInfo {
	// // Probably wrong, should be managed differently than types
	// // We need to manage dependecies on variable names declaration and not on types.
	// defName := cv.typeInfo.Defs[n.Names[i]].Type()
	// defType := cv.typeInfo.Types[n.Type].Type
	// return depInfo{defName, map[types.Type]bool{defType: true}, 0}

	var pkgs map[string]bool
	var names map[string]bool
	if n.Values != nil {
		pkgs = cv.getAllUsedPackages(n.Values[i])
		names = cv.getAllUsedNames(n.Values[i])
	} else {
		pkgs = map[string]bool{}
		names = map[string]bool{}
	}
	defType := cv.typeInfo.Defs[n.Names[i]].Type()
	return depInfo{nil, map[types.Type]bool{defType: true}, n.Names[i].Name, names, "", pkgs, 0, 0}
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

func (cv *cppConverter) checkSimpleType(expr ast.Expr, cppType *cppType) {
	tv := cv.typeInfo.Types[expr].Type

	switch tv.(type) {
	case *types.Named:
		switch tv.Underlying().(type) {
		case *types.Interface:
			cppType.isSimple = true
		case *types.Struct:
			cppType.isSimple = true
		}
	}

	if cv.shared.verbose {
		cv.Logf("checkSimpleType, %v => %v, %T, %T\n", types.ExprString(expr), cppType.isSimple, tv, tv.Underlying())
	}
}

func (cv *cppConverter) checkCanFwd(cppType *cppType) {
	switch cppType.str {
	case "std::string":
		cppType.canFwd = false
	case "gocpp::complex128":
		cppType.isSimple = true
	}
}

// put this in cppConverter ?
var exprToId map[ast.Expr]string = map[ast.Expr]string{}

func (cv *cppConverter) GenerateExprId(expr ast.Expr) (string, bool) {
	id, ok := exprToId[expr]
	if ok {
		return id, false
	}

	id = cv.GenerateId()
	exprToId[expr] = id
	return id, true
}

// Maybe merge this function with "convertExprType" in future ?
// Maybe merge this function with "convertExprCppType" in future ?
func (cv *cppConverter) convertTypeExpr(node ast.Expr) cppType {
	if node == nil {
		panic("node is nil")
	}

	switch n := node.(type) {
	case *ast.Ident:
		identType := mkCppType(GetCppType(n.Name), nil)
		cv.checkSimpleType(n, &identType)
		cv.checkCanFwd(&identType)
		cv.checkIsParam(n, &identType)
		return identType

	case *ast.ArrayType:
		return cv.convertArrayTypeExpr(n)

	case *ast.ChanType:
		return cv.convertChanTypeExpr(n)

	case *ast.FuncType:
		return cv.convertFuncTypeExpr(n)

	case *ast.IndexExpr:
		// TODO: CppTypePrintf ?
		typeName := cv.convertTypeExpr(n.Index)
		cppType := ExprPrintf("%s<%s>", cv.convertTypeExpr(n.X), typeName).toCppType()
		cppType.typenames = append(cppType.typenames, typeName.str)
		return cppType

	case *ast.MapType:
		return cv.convertMapTypeExpr(n)

	case *ast.ParenExpr:
		return cv.convertTypeExpr(n.X)

	case *ast.SelectorExpr:
		typeName := GetCppExprFunc(ExprPrintf("%s::%s", cv.convertExpr(n.X), cv.convertExpr(n.Sel)))
		// TODO: Check this. Why mkCppPtrType and not mkCppType ?
		return mkCppPtrType(typeName)

	case *ast.StarExpr:
		typeExpr := cv.convertTypeExpr(n.X)
		identType := mkCppPtrType(ExprPrintf("%s*", typeExpr))
		cv.checkSimpleType(n.X, &identType)
		identType.typenames = append(identType.typenames, typeExpr.typenames...)
		return identType

	case *ast.StructType:
		name, first := cv.GenerateExprId(node)
		if first {
			structFwdDecl := fmt.Sprintf("struct %s;\n", name)

			// if we want to use "inlineStr" we have to know if we are inside function or not to disable
			// stream operator generation.
			structDef := cv.convertStructTypeExpr(n, nil, genStructParam{name, all, with})
			//return mkCppType(name, []place{inlineStr(structDef), fwdHeaderStr(structFwdDecl, depInfo{})})
			return mkCppType(name, []place{outlineStr(structDef), fwdHeaderStr(structFwdDecl, depInfo{})})
		}
		return mkCppType(name, nil)

	case *ast.InterfaceType:
		if n.Methods == nil || len(n.Methods.List) == 0 {
			return mkCppType("std::any", nil)
		} else {
			name, first := cv.GenerateExprId(node)

			defs := []place{}

			if first {
				structDecl := cv.convertInterfaceTypeExpr(n, nil, genStructParam{name, decl, with})
				defs = append(defs, headerStr(structDecl))

				structDef := cv.convertInterfaceTypeExpr(n, nil, genStructParam{name, implem, with})
				defs = append(defs, outlineStr(structDef))
			}

			return mkCppPtrType(cppExpr{name, defs})
		}

	case *ast.Ellipsis:
		return cv.convertEllipsisTypeExpr(n)

	default:
		Panicf("convertTypeExpr, type %v, expr '%v', position %v", reflect.TypeOf(n), types.ExprString(n), cv.Position(n))
	}

	panic("convertExprCppType, bug, unreacheable code reached !")
}

func (cv *cppConverter) checkIsParam(n *ast.Ident, identType *cppType) {
	_, isParam := cv.typeInfo.Types[n].Type.(*types.TypeParam)
	if isParam {
		identType.typenames = append(identType.typenames, n.Name)
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

	switch node.Len.(type) {
	case nil:
		return ExprPrintf("gocpp::slice<%s>", elt).toCppType()
	case *ast.Ellipsis:
		return ExprPrintf("gocpp::array_base<%s>", elt).toCppType()
	default:
		return ExprPrintf("gocpp::array<%s, %s>", elt, cv.convertExpr(node.Len)).toCppType()
	}
}

func (cv *cppConverter) convertEllipsisTypeExpr(node *ast.Ellipsis) cppType {
	elt := cv.convertTypeExpr(node.Elt)
	return mkCppEllipsis(ExprPrintf("gocpp::slice<%s>", elt), elt.str)
}

func (cv *cppConverter) convertChanTypeExpr(node *ast.ChanType) cppType {
	elt := cv.convertTypeExpr(node.Value)
	return mkCppType(fmt.Sprintf("gocpp::channel<%s>", node.Value), elt.defs)
}

func (cv *cppConverter) convertFuncTypeExpr(node *ast.FuncType) cppType {
	params := cv.readFields(node.Params)
	_, outTypes := cv.getResultInfos(node)
	resultType := buildOutType(outTypes)
	return mkCppType(fmt.Sprintf("std::function<%s (%s)>", resultType, params), params.getDefs())
}

func (cv *cppConverter) convertMapTypeExpr(node *ast.MapType) cppType {
	key := cv.convertTypeExpr(node.Key)
	value := cv.convertTypeExpr(node.Value)
	return mkCppType(fmt.Sprintf("gocpp::map<%s, %s>", key.str, value.str), append(key.defs, value.defs...))
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

func (cv *cppConverter) computeGenStructData(param genStructParam, templatePrmList string) (res genStructData) {

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
		res.namePrefix = param.name + templatePrmList + "::"
		res.out = cv.cpp
	default:
		Panicf("unmanaged GenOutputType value %v", param.output)
	}

	return res
}

func (cv *cppConverter) convertStructTypeExpr(node *ast.StructType, templatePrms []string, param genStructParam) string {
	buf := new(bytes.Buffer)
	fields := cv.readFields(node.Fields)

	templatePrmList := ""
	if len(templatePrms) != 0 {
		templatePrmList = fmt.Sprintf("<%s>", strings.Join(templatePrms, ", "))
	}

	data := cv.computeGenStructData(param, templatePrmList)

	switch param.output {
	case all, decl:
		fmt.Fprintf(buf, "struct %[1]s\n", param.name)
		fmt.Fprintf(buf, "%s{\n", data.out.Indent())

		// Not needed for now, we want to keep struct an aggregate type.
		//fmt.Fprintf(buf, "%s    %s(){}\n", data.out.Indent(), param.name)
		//fmt.Fprintf(buf, "%s    %[2]s(%[2]s& i) = default;\n", data.out.Indent(), param.name)
		//fmt.Fprintf(buf, "%s    %[2]s(const %[2]s& i) = default;\n", data.out.Indent(), param.name)
		//fmt.Fprintf(buf, "%s    %[2]s& operator=(%[2]s& i) = default;\n", data.out.Indent(), param.name)
		//fmt.Fprintf(buf, "%s    %[2]s& operator=(const %[2]s& i) = default;\n", data.out.Indent(), param.name)

		data.out.indent++
		for _, field := range fields {
			for _, name := range field.names {
				fieldAndType := fmt.Sprintf("%s::%s", param.name, name)
				if cv.ignoreKnownError(fieldAndType, knownIncomplete) {
					fmt.Fprintf(buf, "%s/* %s %s; [Known incomplete type] */\n", data.out.Indent(), field.Type.str, name)
				} else {
					fmt.Fprintf(buf, "%s%s %s;\n", data.out.Indent(), field.Type.str, name)
				}
			}
		}

		fmt.Fprintf(buf, "\n")
		fmt.Fprintf(buf, "%susing isGoStruct = void;\n", data.out.Indent())
	case implem:
		// Nothing to do
	default:
		Panicf("unmanaged GenOutputType value %v", param.output)
	}

	excludedNames := append(templatePrms, param.name)
	newTemplateParamName := getAnotherTemplateParamName(excludedNames)

	// Not needed for now, we want to keep struct an aggregate type.
	// fmt.Fprintf(buf, "\n")
	// if param.output == implem {
	// 	PrintTemplatePrefix(buf, data, templatePrms)
	// }
	//
	// fmt.Fprintf(buf, "%stemplate<typename %s>\n", data.out.Indent(), newTemplateParamName)
	// fmt.Fprintf(buf, "%s%s%s(const %s& ref)%s\n", data.out.Indent(), data.namePrefix, param.name, newTemplateParamName, data.declEnd)
	// if data.needBody {
	// 	fmt.Fprintf(buf, "%s{\n", data.out.Indent())
	// 	for _, field := range fields {
	// 		for _, name := range field.names {
	// 			fmt.Fprintf(buf, "%s    %s = ref.%s;\n", data.out.Indent(), name, name)
	// 		}
	// 	}
	// 	fmt.Fprintf(buf, "%s}\n", data.out.Indent())
	// }

	fmt.Fprintf(buf, "\n")
	if param.output == implem {
		PrintTemplatePrefix(buf, data, templatePrms)
	}

	fmt.Fprintf(buf, "%stemplate<typename %s> requires gocpp::GoStruct<%s>\n", data.out.Indent(), newTemplateParamName, newTemplateParamName)
	fmt.Fprintf(buf, "%s%soperator %s()%s\n", data.out.Indent(), data.namePrefix, newTemplateParamName, data.declEnd)
	if data.needBody {
		fmt.Fprintf(buf, "%s{\n", data.out.Indent())
		fmt.Fprintf(buf, "%s    %s result;\n", data.out.Indent(), newTemplateParamName)
		for _, field := range fields {
			for _, name := range field.names {
				fmt.Fprintf(buf, "%s    result.%s = this->%s;\n", data.out.Indent(), name, name)
			}
		}
		fmt.Fprintf(buf, "%s    return result;\n", data.out.Indent())
		fmt.Fprintf(buf, "%s}\n", data.out.Indent())
	}

	fmt.Fprintf(buf, "\n")
	if param.output == implem {
		PrintTemplatePrefix(buf, data, templatePrms)
	}

	fmt.Fprintf(buf, "%stemplate<typename %s> requires gocpp::GoStruct<%s>\n", data.out.Indent(), newTemplateParamName, newTemplateParamName)
	fmt.Fprintf(buf, "%sbool %soperator==(const %s& ref) const%s\n", data.out.Indent(), data.namePrefix, newTemplateParamName, data.declEnd)
	if data.needBody {
		fmt.Fprintf(buf, "%s{\n", data.out.Indent())
		for _, field := range fields {
			for _, name := range field.names {
				fmt.Fprintf(buf, "%s    if (%s != ref.%s) return false;\n", data.out.Indent(), name, name)
			}
		}
		fmt.Fprintf(buf, "%s    return true;\n", data.out.Indent())
		fmt.Fprintf(buf, "%s}\n", data.out.Indent())
	}

	fmt.Fprintf(buf, "\n")
	if param.output == implem {
		PrintTemplatePrefix(buf, data, templatePrms)
	}

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

		PrintTemplatePrefix(buf, data, templatePrms)

		// Need to add 'struct' to avoid conflicts when function have the same name than the struct
		//   => exemple "RGBA" in "image\color\color.go"
		fmt.Fprintf(buf, "%sstd::ostream& operator<<(std::ostream& os, const struct %s%s& value)%s\n", data.out.Indent(), param.name, templatePrmList, data.declEnd)
		if data.needBody {
			fmt.Fprintf(buf, "%s{\n", data.out.Indent())
			fmt.Fprintf(buf, "%s    return value.PrintTo(os);\n", data.out.Indent())
			fmt.Fprintf(buf, "%s}\n", data.out.Indent())
			fmt.Fprintf(buf, "\n")
		}
	}
	return buf.String()
}

func PrintTemplatePrefix(buf *bytes.Buffer, data genStructData, templatePrms []string) {
	if len(templatePrms) != 0 {
		fmt.Fprintf(buf, "%s%s\n", data.out.Indent(), mkTemplateDec(templatePrms))
	}
}

var defaultTemplateNames = []string{"T", "U", "V", "W"}

func getAnotherTemplateParamName(excludedNames []string) string {
	usedNames := make(map[string]bool)
	for _, name := range excludedNames {
		usedNames[name] = true
	}

	// Try to use one of the default template names
	for _, defaultName := range defaultTemplateNames {
		if !usedNames[defaultName] {
			return defaultName
		}
	}

	// If all default names are used, append a suffix number
	for i := 1; ; i++ {
		for _, defaultName := range defaultTemplateNames {
			candidate := fmt.Sprintf("%s%d", defaultName, i)
			if !usedNames[candidate] {
				return candidate
			}
		}
	}
}

func (cv *cppConverter) convertInterfaceTypeExpr(node *ast.InterfaceType, templatePrms []string, param genStructParam) string {
	buf := new(bytes.Buffer)
	methods := cv.readMethods(node.Methods)

	templatePrmList := ""
	if len(templatePrms) != 0 {
		templatePrmList = fmt.Sprintf("<%s>", strings.Join(templatePrms, ", "))
	}

	data := cv.computeGenStructData(param, templatePrmList)
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
		fmt.Fprintf(buf, "%s    using isGoInterface = void;\n", data.out.Indent())
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
		// Need to add 'struct' to avoid conflicts when function have the same name than the struct
		//   => exemple "RGBA" in "image\color\color.go"
		if len(templatePrms) != 0 {
			fmt.Fprintf(buf, "%s%s\n", data.out.Indent(), mkTemplateDec(templatePrms))
		}
		fmt.Fprintf(buf, "%sstd::ostream& operator<<(std::ostream& os, const struct %s%s& value)%s\n", data.out.Indent(), structName, templatePrmList, data.declEnd)
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
// Maybe merge this function with "convertExprType" in future ?
// Maybe merge this function with "convertTypeExpr" in future ?
// Return cppType ?
func (cv *cppConverter) convertExprCppType(node ast.Expr) cppType {
	if node == nil {
		return mkCppType("", nil)
	}

	switch n := node.(type) {

	// TODO: merge with default case and remove switch ?
	case *ast.BasicLit:
		canFwd := true
		var basicLit string
		switch n.Kind {
		case token.IMAG:
			basicLit = "gocpp::complex128"
			canFwd = false
		case token.INT:
			basicLit = "long"
		case token.FLOAT:
			basicLit = "double"
		case token.CHAR:
			basicLit = "char"
		case token.STRING:
			basicLit = "std::string"
			canFwd = false
		default:
			Panicf("Unmanaged token in convert type %v, token %v, position %v", reflect.TypeOf(node), n.Kind, cv.Position(n))
		}
		cppType := mkCppType(basicLit, nil)
		cppType.canFwd = canFwd
		return cppType

	case *ast.CompositeLit:
		return cv.convertCompositeLitType(n, false)

	case *ast.UnaryExpr:
		switch n.Op {
		case token.AND:
			return ExprPrintf("%s*", cv.convertExprCppType(n.X)).toCppType()
		default:
			return cv.convertExprCppType(n.X)
		}

	case *ast.CallExpr:
		switch fun := n.Fun.(type) {
		// Type conversion expression
		case *ast.ParenExpr:
			return cv.convertTypeExpr(fun.X)
		}

		// case *ast.BinaryExpr, *ast.Ident:
		// 	return convertGoToCppType(cv.convertExprType(n))

		// case *ast.IndexExpr:
		// 	objType := convertExprType(n.X)
		// 	indexType := convertExprType(n.Index)
		// 	return fmt.Sprintf("%s[%s]", cv.convertExpr(n.X), cv.convertExpr(n.Index))
	}

	// Generic fallback to guess type
	exprType := cv.convertExprType(node)
	if exprType != nil {
		typeStr := convertGoToCppType(exprType, cv.Position(node))
		// Probably this steps should only be done for named types
		// Move code to 'GetCppGoType' ?
		typeStr = strings.TrimPrefix(typeStr, cv.namespace+".")
		typeStr = strings.ReplaceAll(typeStr, ".", "::")
		typeStr, _ = Last(strings.Split(typeStr, "/"))
		cppType := mkCppType(typeStr, nil)

		switch typeStr {
		case "std::string":
			cppType.canFwd = false
		case "gocpp::complex128":
			cppType.canFwd = false
		}
		return cppType
	} else {
		Panicf("convertExprCppType, [%T, %s, %s]", node, types.ExprString(node), cv.Position(node))
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

// TODO, check if we really need all this methods/function
//
//	-> convertGoToCppType(goType types.Type, position token.Position) string
//	-> convertTypeExpr(node ast.Expr) cppType
//	-> convertTypeSpec(node *ast.TypeSpec, end string) cppType
func convertGoToCppType(goType types.Type, position token.Position) string {
	if goType == nil {
		panic("convertGoToCppType, Cannot convert nil type.")
	}

	switch subType := goType.(type) {
	case *types.Array:
		return fmt.Sprintf("gocpp::array<%s, %d>", GetCppGoType(subType.Elem()), subType.Len())

	case *types.Basic:
		return GetCppGoType(subType)

	// case *types.Chan:
	// 	return fmt.Sprintf("gocpp::channel<%s>", GetCppGoType(subType.Elem()))

	case *types.Named:
		return GetCppGoType(subType)

	case *types.Pointer:
		return fmt.Sprintf("%s*", GetCppGoType(subType.Elem()))

	case *types.Slice:
		return fmt.Sprintf("gocpp::slice<%s>", GetCppGoType(subType.Elem()))

	case *types.TypeParam:
		return fmt.Sprintf("%s", subType)

	case *types.Signature:
		if subType.Results().Len() <= 1 {
			return fmt.Sprintf("std::function<%s (%s)>", GetCppGoType(subType.Results()), GetCppGoType(subType.Params()))
		} else {
			return fmt.Sprintf("std::function<std::tuple<%s> (%s)>", GetCppGoType(subType.Results()), GetCppGoType(subType.Params()))
		}

	default:
		panic(fmt.Sprintf("Unmanaged subType in convertGoToCppType, type [%v], position[%v]", reflect.TypeOf(subType), position))
	}
}

func extractParamDefs(srcParams ...any) ([]place, []any) {
	defs := []place{}
	params := []any{}

	for _, srcParam := range srcParams {
		switch prm := srcParam.(type) {
		case cppType:
			defs = append(defs, prm.defs...)
			params = append(params, prm.str)
		case cppExpr:
			defs = append(defs, prm.defs...)
			params = append(params, prm.str)
		default:
			params = append(params, srcParam)
		}
	}
	return defs, params
}

// Sprintf formats according to a format specifier and returns the resulting string.
func ExprPrintf(format string, srcParams ...any) cppExpr {
	defs, params := extractParamDefs(srcParams...)
	return cppExpr{fmt.Sprintf(format, params...), defs}
}

// Sprintf formats according to a format specifier and returns the resulting string.
func (cv *cppConverter) BuffExprPrintf(buff *cppExprBuffer, format string, srcParams ...any) (n int, err error) {
	defs, params := extractParamDefs(srcParams...)
	*buff.defs = append(*buff.defs, defs...)
	return fmt.Fprintf(buff.buff, format, params...)
}

func (cv *cppConverter) printInline(bBuff io.Writer, bDefs *[]place, defs []place) {
	for _, def := range defs {
		if def.inline != nil {
			fmt.Fprintf(bBuff, "%s%s\n", cv.cpp.Indent(), *def.inline)
		} else {
			*bDefs = append(*bDefs, def)
		}
	}
}

// Sprintf formats according to a format specifier.
func (cv *cppConverter) WritterExprPrintf(buff *cppExprWritter[*bufio.Writer], format string, srcParams ...any) (n int, err error) {
	defs, params := extractParamDefs(srcParams...)
	cv.printInline(buff.buff, buff.defs, defs)
	return fmt.Fprintf(buff.buff, format, params...)
}

// TODO: return typeDefs
func (cv *cppConverter) convertExpr(node ast.Expr) cppExpr {
	return cv.convertExprImpl(node, false)
}

func (cv *cppConverter) convertSubExpr(node ast.Expr) cppExpr {
	return cv.convertExprImpl(node, true)
}

func (cv *cppConverter) convertExprImpl(node ast.Expr, isSubExpr bool) cppExpr {
	if node == nil {
		return mkCppExpr("")
	}

	switch n := node.(type) {

	case *ast.ArrayType, *ast.ChanType, *ast.FuncType, *ast.MapType, *ast.InterfaceType:
		typeDesc := cv.convertTypeExpr(n)
		// Type used as parameter, we use a dummy tag value that is used only for its type
		return ExprPrintf("gocpp::Tag<%s>()", typeDesc)

	case *ast.BasicLit:
		switch n.Kind {
		case token.IMAG:
			return mkCppExpr("gocpp::complex128(0, " + strings.Replace(n.Value, "i", "", -1) + ")")
		case token.INT, token.FLOAT:
			return mkCppExpr(strings.ReplaceAll(n.Value, "_", ""))
		default:
			switch n.Value[0] {
			case '`':
				// TODO: check if there is other replacements to do
				content := "\"" + strings.ReplaceAll(strings.Trim(n.Value, "`"), "\\", "\\\\") + "\""
				return mkCppExpr(content)
			default:
				return mkCppExpr(n.Value)

			}
		}

	case *ast.CompositeLit:
		return cv.convertCompositeLit(n, false)

	case *ast.FuncLit:
		expr := cppExpr{}
		expr.str = cv.withCppBuffer(func() {
			params := cv.readFields(n.Type.Params)
			outNames, outTypes := cv.getResultInfos(n.Type)
			resultType := buildOutType(outTypes)

			cv.DeclareVars(params)

			var captureExpr = "[=]"
			if cv.scopes.Len() <= 1 {
				captureExpr = "[]" // global scope
			}

			fmt.Fprintf(cv.cpp.out, "%s(%s) mutable -> %s\n", captureExpr, params, resultType)

			expr.defs = cv.convertInlinedBlockStmt(n.Body, makeBlockEnv(makeStmtEnv(outNames, outTypes), true))
		})
		return expr

	case *ast.UnaryExpr:
		compositLit, isCompositeLit := n.X.(*ast.CompositeLit)

		switch {
		case n.Op == token.AND && isCompositeLit:
			return cv.convertCompositeLit(compositLit, true)
		case n.Op == token.ARROW:
			return ExprPrintf("%s.recv()", cv.convertExpr(n.X))
		default:
			return ExprPrintf("%s %s", convertUnaryToken(n.Op), cv.convertExpr(n.X))
		}

	case *ast.ParenExpr:
		return ExprPrintf("(%s)", cv.convertExpr(n.X))

	case *ast.KeyValueExpr:
		return ExprPrintf("{ %s, %s }", cv.convertExpr(n.Key), cv.convertExpr(n.Value))

	case *ast.BinaryExpr:
		if needPriority(n.Op) && isSubExpr {
			return ExprPrintf("(%s %s %s)", cv.convertSubExpr(n.X), convertToken(n.Op), cv.convertSubExpr(n.Y))
		} else {
			return ExprPrintf("%s %s %s", cv.convertSubExpr(n.X), convertToken(n.Op), cv.convertSubExpr(n.Y))
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
		buf := mkCppBuffer()
		var sep = ""
		var isSizeOf bool = false
		switch fun := n.Fun.(type) {
		case *ast.SelectorExpr:
			if cv.isNameSpace(fun.X) {
				funcName := ExprPrintf("%s::%s", cv.convertExpr(fun.X), cv.convertExpr(fun.Sel))
				funcName = GetCppExprFunc(funcName)
				// Need a special case for unsafe::Sizeof to avoid difficulties with constexpr
				if funcName.str == "gocpp::Sizeof" {
					isSizeOf = true
					cv.BuffExprPrintf(buf, "%v<", funcName)
				} else {
					cv.BuffExprPrintf(buf, "%v(", funcName)
				}
			} else {
				cv.BuffExprPrintf(buf, "%v(gocpp::recv(%v)", cv.convertExpr(fun.Sel), cv.convertExpr(fun.X))
				sep = ", "
			}
		case *ast.ParenExpr:
			cv.BuffExprPrintf(buf, "(%v)(", cv.convertTypeExpr(fun.X))
		default:
			cv.BuffExprPrintf(buf, "%v(", cv.convertExpr(n.Fun))
		}

		for _, arg := range n.Args {
			if isSizeOf {
				cv.BuffExprPrintf(buf, "%s%s", sep, cv.convertExprCppType(arg))
			} else {
				cv.BuffExprPrintf(buf, "%s%s", sep, cv.convertExpr(arg))
			}
			sep = ", "
		}
		if isSizeOf {
			cv.BuffExprPrintf(buf, ">()")
		} else {
			cv.BuffExprPrintf(buf, ")")
		}
		return buf.Expr()

	case *ast.Ident:
		if n.Name == "iota" {
			return mkCppExpr(cv.Iota())
		} else {
			return mkCppExpr(GetCppFunc(n.Name))
		}

	case *ast.IndexExpr:
		return ExprPrintf("%s[%s]", cv.convertExpr(n.X), cv.convertExpr(n.Index))

	case *ast.SelectorExpr:
		name := cv.convertExpr(n.X)

		if cv.isNameSpace(n.X) {
			return GetCppExprFunc(ExprPrintf("%s::%s", name, cv.convertExpr(n.Sel)))
		} else {
			// TODO: use only IsExprPtr ?
			if cv.IsPtr(name.str) || cv.IsExprPtr(n.X) {
				return GetCppExprFunc(ExprPrintf("%s->%s", name, cv.convertExpr(n.Sel)))
			} else {
				return GetCppExprFunc(ExprPrintf("%s.%s", name, cv.convertExpr(n.Sel)))
			}
		}

	case *ast.SliceExpr:
		if n.Slice3 {
			return ExprPrintf("%s.make_slice(%s, %s, %s)", cv.convertExpr(n.X), cv.convertExpr(n.Low), cv.convertExpr(n.High), cv.convertExpr(n.Max))
		} else if n.Low == nil {
			return ExprPrintf("%s.make_slice(0, %s)", cv.convertExpr(n.X), cv.convertExpr(n.High))
		} else if n.High == nil {
			return ExprPrintf("%s.make_slice(%s)", cv.convertExpr(n.X), cv.convertExpr(n.Low))
		} else {
			return ExprPrintf("%s.make_slice(%s, %s)", cv.convertExpr(n.X), cv.convertExpr(n.Low), cv.convertExpr(n.High))
		}

	case *ast.StarExpr:
		return ExprPrintf("*%s", cv.convertExpr(n.X))

	case *ast.TypeAssertExpr:
		return ExprPrintf("gocpp::getValue<%s>(%s)", cv.convertExprCppType(n.Type), cv.convertExpr(n.X))

	default:
		Panicf("convertExprImpl, type %v, expr '%v', position %v", reflect.TypeOf(node), types.ExprString(n), cv.Position(n))
	}
	panic("convertExprType, bug, unreacheable code reached !")
}

func (cv *cppConverter) isNameSpace(expr ast.Expr) bool {

	switch n := expr.(type) {
	case *ast.Ident:
		exprType := cv.typeInfo.Uses[n]
		switch exprType.(type) {
		case *types.PkgName:
			return true
		}
	}
	return false
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

func (cv *cppConverter) convertCompositeLit(n *ast.CompositeLit, addPtr bool) cppExpr {
	// ignore 'n.Incomplete' at the moment
	buf := mkCppBuffer()
	var litType cppExpr
	if n.Type != nil {
		litType = cv.convertTypeExpr(n.Type).cppExpr
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
		cv.BuffExprPrintf(buf, "gocpp::Init%s<%s>([](%s& x) { ", ptrSuffix, litType, litType)

		for _, elt := range n.Elts {
			kv := elt.(*ast.KeyValueExpr)
			//goType := cv.convertExprType(expr)
			cv.BuffExprPrintf(buf, "x.%s = %s; ", cv.convertExpr(kv.Key), cv.convertExpr(kv.Value))
		}
		cv.BuffExprPrintf(buf, "})")
	} else {
		newPrefix := ""
		if addPtr {
			// FIME : create a kind a smart pointer instead of using new.
			newPrefix = "new "
		}

		cv.BuffExprPrintf(buf, "%s%s {", newPrefix, litType)
		var sep = ""
		for _, elt := range n.Elts {
			cv.BuffExprPrintf(buf, "%s%s", sep, cv.convertExpr(elt))
			sep = ", "
		}
		cv.BuffExprPrintf(buf, "}")
	}

	return buf.Expr()
}

func (cv *cppConverter) convertExprList(exprs []ast.Expr) (strs []cppExpr) {
	for _, expr := range exprs {
		strs = append(strs, cv.convertExpr(expr))
	}
	return strs
}

func (cv *cppConverter) convertExprs(exprs []ast.Expr) cppExpr {
	cppExprs := cv.convertExprList(exprs)
	defs := []place{}
	strs := []string{}
	for _, expr := range cppExprs {
		defs = append(defs, expr.defs...)
		if expr.str == "_" {
			expr.str = cv.GenerateId()
		}
		strs = append(strs, expr.str)
	}

	return cppExpr{strings.Join(strs, ", "), defs}
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
	fmt.Println()
	fmt.Println(" --  Info.Types -- ")
	for expr, obj := range cv.typeInfo.Types {
		var filePos = cv.Position(expr)
		cv.Logf("%s (%3d,%3d) => %25v has type [%15T] %v\n", filePos.Filename, filePos.Line, filePos.Column, types.ExprString(expr), obj.Type, obj.Type)
	}

	fmt.Println(" --  Info.Defs -- ")
	for id, obj := range cv.typeInfo.Defs {
		var filePos = cv.Position(id)
		// printing scopes is too big, just get number of elements
		scopeCounts := getScopeCounts(obj)
		cv.Logf("%s (%3d,%3d) => %15q defines [%15T] %v, scopes: %v\n", filePos.Filename, filePos.Line, filePos.Column, id.Name, obj, obj, scopeCounts)
	}

	fmt.Println(" --  Info.Uses -- ")
	for id, obj := range cv.typeInfo.Uses {
		var filePos = cv.Position(id)
		// printing scopes is too big, just get number of elements
		scopeCounts := getScopeCounts(obj)
		cv.Logf("%s (%3d,%3d) => %15q uses [%15T] %v, scopes: %v\n", filePos.Filename, filePos.Line, filePos.Column, id.Name, obj, obj, scopeCounts)
	}
}

func getScopeCounts(obj types.Object) []int {
	var scopeCounts []int
	if obj == nil {
		return scopeCounts
	}

	scope := obj.Parent()
	for {
		if scope == nil {
			break
		}

		scopeCounts = append(scopeCounts, len(scope.Names()))
		scope = scope.Parent()
	}
	return scopeCounts
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
		cv.srcBaseName = "$(ImportDir)/" + pkgInfo.basePath()
		cv.baseName = cv.shared.globalSubDir + pkgInfo.basePath()

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
	shared.supportHeader = "gocpp/support"
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

	if err := cv.LoadAndCheckDefs(cv.astFile.Name.Name, fset, cv.astFile); err != nil {
		log.Fatal(err) // type error
	}

	defer cv.PrintDefsUsage()

	cv.ConvertFile()
}
