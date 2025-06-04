package main

import (
	"bufio"
	"bytes"
	"fmt"
	"go/ast"
	"go/token"
	"go/types"
	"io"
	"os"
	"path"
	"path/filepath"
	"slices"
	"strings"
	"time"

	"golang.org/x/exp/maps"
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

func Assertf(ok bool, format string, a ...interface{}) {
	if !ok {
		Panicf(format, a...)
	}
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

// TODO: find a way to add "struct" only when needed.
// (when there is an ambiguity because of function with the same name)
func GetCppOutType(goType outType) string {
	outType := GetCppType(goType.str)
	if goType.isStruct {
		return "struct " + outType
	} else {
		return outType
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
		return cppExpr{val, funcName.defs, funcName.typenames}
	} else {
		return funcName
	}
}

type typeName struct {
	names  []string
	doc    *ast.CommentGroup
	Type   cppType
	isRecv bool
}

type outType struct {
	str       string
	isStruct  bool
	typenames []string
}

func (tn typeName) outType() outType {
	return outType{tn.Type.str, tn.Type.isStruct, tn.Type.typenames}
}

func (tn typeName) ParamDecl() []string {
	var strs []string

	if len(tn.names) != 0 {
		for _, name := range tn.names {
			if tn.Type.isStruct {
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

type typeNames []typeName

func (tns *typeNames) setIsRecv() {
	for i := range *tns {
		(*tns)[i].isRecv = true
	}
}

func (tns typeNames) getDefs() (defs []place) {
	for _, tn := range tns {
		defs = append(defs, tn.Type.defs...)
	}
	return
}

// String containing list of parameter names, with types
func (tns typeNames) String() string {
	var strs []string
	for _, tn := range tns {
		strs = append(strs, tn.ParamDecl()...)
	}
	return strings.Join(strs, ", ")
}

// String containing list of parameter names, without types
func (tns typeNames) NamesStr() string {
	return strings.Join(tns.Names(), ", ")
}

// List of parameter names
func (tns typeNames) Names() []string {
	var strs []string
	for _, tn := range tns {
		strs = append(strs, tn.names...)
	}
	return strs
}

// JoinWithPrefix adds a separator at the start if the input slice is not empty
func JoinWithPrefix(elements []string, separator string) string {
	if len(elements) == 0 {
		return ""
	}
	return separator + strings.Join(elements, separator)
}

func JoinWithSuffix(elements []string, separator string) string {
	if len(elements) == 0 {
		return ""
	}
	return strings.Join(elements, separator) + separator
}

// clean and join path function that keeps unix style paths on all platforms
func CleanPath(path string) string {
	path = filepath.Clean(path)
	path = strings.ReplaceAll(path, "\\", "/") // convert to unix path
	return path
}

func JoinPath(paths ...string) string {
	path := filepath.Join(paths...)
	path = strings.ReplaceAll(path, "\\", "/") // convert to unix path
	return path
}

type outFile struct {
	name   string
	file   *os.File
	out    *bufio.Writer
	indent int
}

func (of *outFile) Indent() string {
	return strings.Repeat(baseIndent, of.indent)
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

func Ptr[T any](value T) *T {
	return &value
}

func createOutputExt(outdir, name, ext string) outFile {
	var outName = name + "." + ext
	return createOutput(outdir, outName)
}

func createOutput(outdir, name string) outFile {
	var outName = JoinPath(outdir, name)
	var outDir = path.Dir(outName)

	errDir := os.MkdirAll(outDir, os.ModePerm)
	if errDir != nil {
		panic(errDir)
	}

	file, err := os.Create(outName)
	if err != nil {
		panic(err)
	}

	writer := bufio.NewWriter(file)
	return outFile{name, file, writer, 0}
}

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
		if typ.Params() != nil {
			for i := 0; i < typ.Params().Len(); i++ {
				internalGetObjectsOfType(typ.Params().At(i).Type(), seen)
			}
		}
		if typ.Results() != nil {
			for i := 0; i < typ.Results().Len(); i++ {
				internalGetObjectsOfType(typ.Results().At(i).Type(), seen)
			}
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

type errorFilter struct {
	target string
	file   string
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
	outTypes []outType
	varNames *[]string // maybe use map for perfs
}

func (env *stmtEnv) startVarScope() {
	//clear already declared var names at start of scope
	env.varNames = &[]string{}
}

func makeStmtEnv(outNames []string, outTypes []outType) stmtEnv {
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

func makeBlockEnv(env stmtEnv, isFunc bool) blockEnv {
	return blockEnv{env, isFunc, Ptr(false), false, "", ""}
}

func makeSubBlockEnv(env blockEnv, isFunc bool) blockEnv {
	return blockEnv{env.stmtEnv, isFunc, env.useDefer, env.isTypeSwitch, env.typeSwitchVarName, env.switchVarName}
}

func Last[EltType any](elts []EltType) (EltType, bool) {
	if len(elts) == 0 {
		var zero EltType
		return zero, false
	}
	return elts[len(elts)-1], true
}

func deduplicate[T comparable](items []T) []T {
	seen := map[T]bool{}
	var result []T
	for _, item := range items {
		if !seen[item] {
			result = append(result, item)
			seen[item] = true
		}
	}
	return result
}

// Adds a specified indentation to each non-empty line of the input string.
func addIndentation(input string, indent string) string {
	lines := strings.Split(input, "\n")
	for i, line := range lines {
		if strings.TrimSpace(line) != "" {
			lines[i] = indent + line
		}
	}
	return strings.Join(lines, "\n")
}

func buildOutType(outTypes []outType) string {
	var resultType string
	switch len(outTypes) {
	case 0:
		resultType = "void"
	case 1:
		resultType = GetCppOutType(outTypes[0])
	default:
		var types []string
		for _, outType := range outTypes {
			types = append(types, GetCppOutType(outType))
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
	dependencies map[string]types.Type

	decIdent  string
	depIdents map[string]bool

	decPkg  string
	depPkgs map[string]bool

	initialOrder int
	rank         int
}

type depMode int

const (
	UnknwonMode depMode = 0
	FwdDepend   depMode = 1
	DecDepend   depMode = 2
)

func (depInfo *depInfo) ComputeDeps(dm depMode) {
	depInfo.dependencies = ComputeDeps(depInfo.dependencies, dm)
	if depInfo.decType != nil {
		delete(depInfo.dependencies, depInfo.decType.String())
	}
}

func ComputeDeps(toDo map[string]types.Type, dm depMode) map[string]types.Type {
	done := map[string]types.Type{}
	for len(toDo) != 0 {
		for key, elt := range toDo {
			if _, skip := done[key]; skip {
				delete(toDo, key)
				continue
			}

			switch t := elt.(type) {
			case *types.Array:
				elem := t.Elem()
				toDo[elem.String()] = elem

			case *types.Chan:
				elem := t.Elem()
				toDo[elem.String()] = elem

			case *types.Slice:
				elem := t.Elem()
				toDo[elem.String()] = elem

			case *types.Map:
				elem := t.Elem()
				keyType := t.Key()
				toDo[elem.String()] = elem
				toDo[keyType.String()] = keyType

			case *types.Pointer:
				if dm == FwdDepend {
					elem := t.Elem()
					toDo[elem.String()] = elem
				}

			case *types.Signature:
				if t.Params() != nil {
					for i := 0; i < t.Params().Len(); i++ {
						paramType := t.Params().At(i).Type()
						toDo[paramType.String()] = paramType
					}
				}
				if t.Results() != nil {
					for i := 0; i < t.Results().Len(); i++ {
						resultType := t.Results().At(i).Type()
						toDo[resultType.String()] = resultType
					}
				}
				if t.Recv() != nil {
					recvType := t.Recv().Type()
					toDo[recvType.String()] = recvType
				}

			case *types.Struct:
				if dm == DecDepend {
					for i := 0; i < t.NumFields(); i++ {
						fieldType := t.Field(i).Type()
						toDo[fieldType.String()] = fieldType
					}
				}

			case nil, *types.Alias, *types.Basic, *types.Interface, *types.Named, *types.TypeParam:
				// Nothing to do

			default:
				Panicf("ComputeDeps, unmanaged type %T", t)
			}

			done[key] = elt
			delete(toDo, key)
		}
	}

	return done
}

type place struct {
	// when type/declaration need be generated inlined
	inline *string
	// when type/declaration need to be generated outline function
	outline *string
	// when type/declaration need to be in header
	header *string
	// when type/declaration need to be at end of header
	headerEnd *string
	// when type/declaration need to be in forward declarations header
	fwdHeader *string
	isInclude bool

	// -> Currently it's a fixed value chosen at creation but ultimately
	// this should be computed by looking at dependency graph.
	// -> used only for forward declaration order at the moment
	depInfo depInfo

	//packages
	pkgInfo *pkgInfo

	// source node, for debug message
	node ast.Node

	// used receivers
	receivers *ast.SelectorExpr
}

func (place place) DepInfoTypeStr() string {
	if place.depInfo.decType != nil {
		return place.depInfo.decType.String()
	}
	return ""
}

func getHeader(place place) string {
	return *place.header
}

func getFwdHeader(place place) string {
	return *place.fwdHeader
}

func inlineStr(str string, node ast.Node) place {
	return place{&str, nil, nil, nil, nil, false, depInfo{}, nil, node, nil}
}

func receiver(rec *ast.SelectorExpr) place {
	return place{nil, nil, nil, nil, nil, false, depInfo{}, nil, nil, rec}
}

func outlineStr(str string, node ast.Node) place {
	return place{nil, &str, nil, nil, nil, false, depInfo{}, nil, node, nil}
}

func headerStr(str string, node ast.Node) place {
	return place{nil, nil, &str, nil, nil, false, depInfo{}, nil, node, nil}
}

func headerEndStr(str string) place {
	return place{nil, nil, nil, &str, nil, false, depInfo{}, nil, nil, nil}
}

func fwdHeaderStr(str string, node ast.Node, depInfo depInfo) place {
	return place{nil, nil, nil, nil, &str, false, depInfo, nil, node, nil}
}

func includeStr(str string, depInfo depInfo) place {
	return place{nil, nil, nil, nil, &str, true, depInfo, nil, nil, nil}
}

func importPackage(name string, pkgPath string, filePath string, pkgType pkgType, node ast.Node) place {
	return place{nil, nil, nil, nil, nil, false, depInfo{}, &pkgInfo{name, pkgPath, filePath, UnknwonTag, pkgType}, node, nil}
}

func inlineStrf(node ast.Node, format string, params ...any) []place {
	expr := ExprPrintf(format, params...)
	expr.defs = append(expr.defs, inlineStr(expr.str, node))
	return expr.defs
}

// func outlineStrf(format string, params ...any) []place {
// 	expr := ExprPrintf(format, params...)
// 	expr.defs = append(expr.defs, outlineStr(expr.str))
// 	return expr.defs
// }

func headerStrf(node ast.Node, format string, params ...any) []place {
	expr := ExprPrintf(format, params...)
	expr.defs = append(expr.defs, headerStr(expr.str, node))
	return expr.defs
}

func headerEndStrf(format string, params ...any) []place {
	expr := ExprPrintf(format, params...)
	expr.defs = append(expr.defs, headerEndStr(expr.str))
	return expr.defs
}

func fwdHeaderStrf(di depInfo, node ast.Node, format string, params ...any) []place {
	expr := ExprPrintf(format, params...)
	expr.defs = append(expr.defs, fwdHeaderStr(expr.str, node, di))
	return expr.defs
}

// func appendInlineStrf(places *[]place, format string, params ...any) {
// 	*places = append(*places, inlineStrf(nil, format, params...)...)
// }

func appendHeaderStrf(places *[]place, format string, params ...any) {
	*places = append(*places, headerStrf(nil, format, params...)...)
}

func appendHeaderEndStrf(places *[]place, format string, params ...any) {
	*places = append(*places, headerEndStrf(format, params...)...)
}

type cppExpr struct {
	str       string  // cpp type as a string
	defs      []place // inline def used by type
	typenames []string

	// probably need some depInfo here
}

func (expr cppExpr) toCppType() cppType {
	return cppType{expr, false, false, false, "", true}
}

func mkCppExpr(str string) cppExpr {
	return cppExpr{str, nil, nil}
}

type cppType struct {
	cppExpr
	isPtr      bool // is type a pointer ?
	isStruct   bool // is the name of a stuct or an interface
	isEllipsis bool // is type created by an ellipsis
	eltType    string

	canFwd bool // Can go in forward header
}

func mkCppType(str string, defs []place) cppType {
	return cppType{cppExpr{str, defs, nil}, false, false, false, "", true}
}

func mkCppPtrType(expr cppExpr) cppType {
	return cppType{expr, true, false, false, "", true}
}

func mkCppEllipsis(expr cppExpr, eltType string) cppType {
	return cppType{expr, false, false, true, eltType, true}
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
	return cppExpr{buff.buff.String(), *buff.defs, nil}
}

func mkTemplateDec(templatePrms []string) string {
	return fmt.Sprintf("template<typename %s>", strings.Join(templatePrms, ", typename "))
}

func mkVariadicTemplateDec(templatePrms []string, variadicPrm string) string {
	if len(templatePrms) == 0 {
		return fmt.Sprintf("template<typename... %s>", variadicPrm)
	} else {
		return fmt.Sprintf("template<typename %s, typename... %s>", strings.Join(templatePrms, ", typename "), variadicPrm)
	}
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

type set[T comparable] map[T]bool

func (target set[T]) add(elt T) {
	target[elt] = true
}

func (target set[T]) addOpt(elt *T) {
	if elt == nil {
		return
	}
	target[*elt] = true
}

func (target set[T]) append(src map[T]bool) {
	for k, v := range src {
		target[k] = v
	}
}

func (target set[T]) has(value T) bool {
	v, ok := target[value]
	return ok && v
}

func toSortedList(nsSet set[string]) []string {
	var nsList = maps.Keys(nsSet)
	slices.SortFunc(nsList, func(x, y string) int {
		return strings.Compare(x, y)
	})
	return nsList
}

func isMapType(node ast.Expr) bool {
	switch node.(type) {
	case *ast.MapType:
		return true

	default:
		return false
	}
}

func isArrayType(node ast.Expr) bool {
	switch node.(type) {
	case *ast.ArrayType:
		return true

	default:
		return false
	}
}
