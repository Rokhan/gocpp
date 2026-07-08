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
	return GetNsCppType(goType).String()
}

func GetNsCppType(goType string) nsType {
	nsVal, ok := stdNsTypeMapping[goType]
	if ok {
		return nsVal
	}

	goType = GetCppName(goType)
	val, ok := stdTypeMapping[goType]
	if ok {
		return nsType{name: val}
	} else {
		return nsType{name: goType}
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

func GetCppGoType(goType types.Type, namespace string) string {
	switch t := goType.(type) {
	case *types.Tuple:
		if t.Len() == 0 {
			return "void"
		}

		var strs []string
		for i := 0; i < t.Len(); i++ {
			strs = append(strs, GetCppGoType(t.At(i).Type(), namespace))
		}
		return strings.Join(strs, ", ")

	case *types.Named:
		typeStr := GetCppType(goType.String())
		return convertNamespace(typeStr, namespace)

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
	// TODO: Check if useful
	// receiv, ok := mocklibReceiverElts[funcName.str]
	// if ok {
	// 	funcName.defs = append(funcName.defs, mockReceiver(receiv))
	// }
	val, ok := stdFuncMapping[funcName.str]
	if ok {
		return cppExpr{val, "", funcName.defs, funcName.typenames}
	} else {
		return funcName
	}
}

type commentInfo struct {
	doc     *ast.CommentGroup
	comment *ast.CommentGroup
}

type typeName struct {
	names []string
	commentInfo
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

// Prefix add a prefix to non-empty strings
func Prefix(str string, prefix string) string {
	if str == "" {
		return ""
	}
	return prefix + str
}

// Transform a slice of strings, applying a pattern to each element
func FormatStrings(pattern string, strs []string, params ...any) []string {
	var result []string
	for _, str := range strs {
		tmpParams := append([]any{str}, params...)
		result = append(result, fmt.Sprintf(pattern, tmpParams...))
	}
	return result
}

// JoinWithPrefix adds a separator at the start if the input slice is not empty
func JoinWithPrefix(elements []string, separator string) string {
	if len(elements) == 0 {
		return ""
	}
	return separator + strings.Join(elements, separator)
}

// JoinWithPrefix adds a separator at the end if the input slice is not empty
func JoinWithSuffix(elements []string, separator string) string {
	if len(elements) == 0 {
		return ""
	}
	return strings.Join(elements, separator) + separator
}

// clean and join path function that keeps unix style paths on all platforms
// TODO, use a specific type for clean paths
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

func Ptr[T any](value T) *T {
	return &value
}

func ArrayPtr[T any](value ...T) *[]T {
	return &value
}

func createOutputExt(outdir, name, ext string) outFile {
	var outName = name + "." + ext
	return createOutput(outdir, outName)
}

func createOutput(outdir, name string) outFile {
	outdir = CleanPath(outdir)
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
	case *types.TypeParam:
		internalGetObjectsOfType(typ.Constraint(), seen)
	case *types.Union:
		for i := 0; i < typ.Len(); i++ {
			internalGetObjectsOfType(typ.Term(i).Type(), seen)
		}
	default:
		Panicf("internalGetObjectsOfType: unhandled type %T", typ)
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

	// - maybe use map for perfs
	// - check if it can be removed: probably redundant with cv.getScopeVars()
	varNames *[]string

	toBeDeclared []string // list of variables to be declared at start of scope

	idCount *int
}

func (env *stmtEnv) startVarScope() {
	//clear already declared var names at start of scope
	env.varNames = &[]string{}
}

func (env *stmtEnv) generateId(prefix string) (id string) {
	id = fmt.Sprintf("%s%d", prefix, *env.idCount)
	*env.idCount++
	return id
}

func (env *stmtEnv) localVarScope(cv *cppConverter, todo func()) {
	//clear already declared var names at start of scope
	cv.startScope()
	outVarNames := env.varNames
	env.varNames = &[]string{}
	todo()
	env.varNames = outVarNames
	cv.endScope()
}

func makeStmtEnv(outNames []string, outTypes []outType, paramNames []string) stmtEnv {
	varNames := append(append([]string{}, outNames...), paramNames...)
	return stmtEnv{outNames, outTypes, &varNames, outNames, Ptr(0)}
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

func buildOutType(outTypes []outType, typeParams typeParams) string {
	var resultType string
	switch len(outTypes) {
	case 0:
		resultType = "void"
	case 1:
		resultType = GetCppOutType(outTypes[0])
		if deps, ok := typeParams[resultType]; ok && len(deps) != 0 {
			resultType = fmt.Sprintf("%s<%s>", resultType, strings.Join(deps, ", "))
		}
	default:
		var types []string
		for _, outType := range outTypes {
			cppOutType := GetCppOutType(outType)
			if deps, ok := typeParams[cppOutType]; ok && len(deps) != 0 {
				cppOutType = fmt.Sprintf("%s<%s>", cppOutType, strings.Join(deps, ", "))
			}
			types = append(types, cppOutType)
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
	case *ast.CallExpr:
		// special case we know they can be used in forward declaration header.
		switch fun := n.Fun.(type) {
		case *ast.Ident:
			if knownForwardableFunctions[fullName{"", fun.Name}] {
				return visitor
			}

			if obj := visitor.cv.typeInfo.Uses[fun]; obj != nil {
				//visitor.cv.Logf("CanForward::Visit, call expr with ident fun %v, obj %v, type %T\n", fun.Name, obj, obj)
				if tname, ok := obj.(*types.TypeName); ok {
					visitor.cv.Logf("CanForward::Visit, call expr with ident fun %v, obj %v, type %T, underlying type %T\n", fun.Name, obj, obj, tname.Type().Underlying())
					if _, ok := tname.Type().Underlying().(*types.Basic); ok {
						return visitor
					}
				}
			}

		case *ast.SelectorExpr:
			// known forwardable functions
			ns, ok := fun.X.(*ast.Ident)
			if ok {
				if knownForwardableFunctions[fullName{ns.Name, fun.Sel.Name}] {
					return visitor
				}
			}
		}
		// TODO: we could be more precise here by checking if the function called can be made constexpr,
		// but for now we just assume that any call makes the expression not acceptable for forward declaration.
		visitor.value = false
		return nil
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
	UnknownTag tagType = 0
	UsesTag    tagType = 1
	DefsTag    tagType = 2
	NoneTag    tagType = 9999
)

type pkgInfo struct {
	name     string
	pkgPath  string
	filePath string
	tag      tagType
	fileType pkgType
}

func (pkgInfo *pkgInfo) baseName() string {
	return strings.TrimSuffix(filepath.Base(pkgInfo.filePath), ".go")
}

func (pkgInfo *pkgInfo) pkgName() string {
	return fmt.Sprintf("%v/%v", pkgInfo.pkgPath, pkgInfo.fileName())
}

func (pkgInfo *pkgInfo) fileName() string {
	return filepath.Base(pkgInfo.baseName())
}

func (pkgInfo *pkgInfo) basePath() string {
	if pkgInfo != nil {
		return fmt.Sprintf("%v/%v", pkgInfo.pkgPath, pkgInfo.baseName())
	}
	return "### UNDEFINED PATH ###"
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

			case *types.Interface:
				if dm == DecDepend {
					for i := 0; i < t.NumEmbeddeds(); i++ {
						embeddedType := t.EmbeddedType(i)
						toDo[embeddedType.String()] = embeddedType
					}
				}

			case *types.Union:
				if dm == DecDepend {
					for i := 0; i < t.Len(); i++ {
						termType := t.Term(i).Type()
						toDo[termType.String()] = termType
					}
				}

			case nil, *types.Alias, *types.Basic, *types.Named, *types.TypeParam:
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

type receiverDesc interface {
	getFullReceiverName(cv *cppConverter) *string
}
type goReceiverDesc ast.SelectorExpr
type mockReceiverDesc string

type place struct {
	// when type/declaration need be generated inlined
	inline *string
	// when type/declaration need to be generated outline function
	outline *string
	// when type/declaration need to be in header
	header *[]string
	// when type/declaration need to be at end of header
	headerEnd *string
	// when type/declaration need to be in forward declarations header
	fwdHeader *[]string
	isInclude bool

	// -> Currently it's a fixed value chosen at creation but ultimately
	// this should be computed by looking at dependency graph.
	// -> used only for forward declaration order at the moment
	depInfo depInfo

	//packages
	pkgInfo *pkgInfo

	// source node
	//   - for debug message
	//   - for computing dependencies later on
	node ast.Node

	// used receivers
	receiver receiverDesc
}

func (place place) SetPkgInfo(pkgInfo *pkgInfo) place {
	place.pkgInfo = pkgInfo
	return place
}

func (place place) DepInfoTypeStr() string {
	if place.depInfo.decType != nil {
		return place.depInfo.decType.String()
	}
	return ""
}

func getHeader(place place) []string {
	return *place.header
}

func getFwdHeader(place place) []string {
	return *place.fwdHeader
}

func inlineStr(str string, node ast.Node) place {
	return place{&str, nil, nil, nil, nil, false, depInfo{}, nil, node, nil}
}

func goReceiver(rec ast.SelectorExpr) place {
	return place{nil, nil, nil, nil, nil, false, depInfo{}, nil, nil, goReceiverDesc(rec)}
}

func mockReceiver(rec string) place {
	return place{nil, nil, nil, nil, nil, false, depInfo{}, nil, nil, mockReceiverDesc(rec)}
}

func outlineStr(str string, node ast.Node) place {
	return place{nil, &str, nil, nil, nil, false, depInfo{}, nil, node, nil}
}

func headerStr(str string, node ast.Node) place {
	return place{nil, nil, ArrayPtr(str), nil, nil, false, depInfo{}, nil, node, nil}
}

func headerEndStr(str string) place {
	return place{nil, nil, nil, &str, nil, false, depInfo{}, nil, nil, nil}
}

func fwdHeaderStr(str string, node ast.Node, depInfo depInfo) place {
	return place{nil, nil, nil, nil, ArrayPtr(str), false, depInfo, nil, node, nil}
}

// Maybe create one version for headers and one for fwd headers.
func includeStr(str string, depInfo depInfo) place {
	return place{nil, nil, ArrayPtr(str), nil, ArrayPtr(str), true, depInfo, nil, nil, nil}
}

func importPackage(name string, pkgPath string, filePath string, pkgType pkgType, node ast.Node) place {
	return place{nil, nil, nil, nil, nil, false, depInfo{}, &pkgInfo{name, CleanPath(pkgPath), filePath, UnknownTag, pkgType}, node, nil}
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
	str       string // cpp type as a string
	dbg       string
	defs      []place // inline def used by type
	typenames []string

	// probably need some depInfo here
}

func (expr cppExpr) toCppType() cppType {
	return cppType{expr, false, false, false, nil, true}
}

func mkCppExpr(str string) cppExpr {
	return cppExpr{str: str}
}

type cppType struct {
	cppExpr
	isPtr      bool // is type a pointer ?
	isStruct   bool // is the name of a stuct or an interface
	isEllipsis bool // is type created by an ellipsis
	eltType    *cppType

	canFwd bool // Can go in forward header
}

// build a name based on type
func (ct cppType) getTypeBasedName() string {
	if ct.eltType != nil {
		return ct.eltType.getTypeBasedName()
	}
	str, _ := Last(strings.Split(ct.str, "::"))
	return str
}

func mkCppType(str string, defs []place) cppType {
	return cppType{cppExpr{str: str, defs: defs}, false, false, false, nil, true}
}

// func mkCppPtrType(expr cppExpr) cppType {
// 	return cppType{expr, true, false, false, nil, true}
// }

func mkCppEllipsis(expr cppExpr, eltType cppType) cppType {
	return cppType{expr, false, false, true, &eltType, true}
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
	return cppExpr{str: buff.buff.String(), defs: *buff.defs}
}

func mkTemplateParameter(name string, deps []string) string {
	if len(deps) == 0 {
		return fmt.Sprintf("typename %s", name)
	} else {
		// We don't really need deps names, just the number of parameters
		for i := range deps {
			deps[i] = "typename"
		}
		return fmt.Sprintf("template<%s> class  %s", strings.Join(deps, ", "), name)
	}
}

func mkTemplateParameters(templatePrms typeParams) []string {
	var templatePrmsStr []string
	for name, deps := range templatePrms {
		templatePrmsStr = append(templatePrmsStr, mkTemplateParameter(name, deps))
	}
	slices.SortFunc(templatePrmsStr, func(x, y string) int {
		return strings.Compare(x, y)
	})
	return templatePrmsStr
}

func mkTemplateDec(templatePrms typeParams) string {
	templatePrmsStr := mkTemplateParameters(templatePrms)
	return fmt.Sprintf("template<%s>", strings.Join(templatePrmsStr, ", "))
}

func mkVariadicTemplateDec(templatePrms typeParams, variadicPrm string) string {
	if len(templatePrms) == 0 {
		return fmt.Sprintf("template<typename... %s>", variadicPrm)
	} else {
		templatePrmsStr := mkTemplateParameters(templatePrms)
		return fmt.Sprintf("template<%s, typename... %s>", strings.Join(templatePrmsStr, ", "), variadicPrm)
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

type UseIdentfier struct {
	identifier string
	used       bool
}

func (visitor *UseIdentfier) Visit(node ast.Node) ast.Visitor {
	switch n := node.(type) {
	case *ast.Ident:
		if n.Name == visitor.identifier {
			visitor.used = true
			return nil
		}
	case *ast.SelectorExpr:
		// ignore field names
		ast.Walk(visitor, n.X)
		return nil

	case nil:
		return nil
	}
	return visitor
}

func isIdentifierUsed(identifier string, expr ast.Expr) bool {
	gi := &UseIdentfier{identifier, false}
	ast.Walk(gi, expr)
	return gi.used
}

// appendMap merges all entries from src into target.
// target is initialized if needed.
func appendMap[K comparable, V any](target *map[K]V, src map[K]V) {
	if src == nil {
		panic("appendMap: src map is nil")
	}
	if *target == nil {
		*target = make(map[K]V)
	}
	for k, v := range src {
		(*target)[k] = v
	}
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

func (target set[T]) toSlice() []T {
	return maps.Keys(target)
}

func makeSet[T comparable](elts ...T) set[T] {
	s := set[T]{}
	for _, elt := range elts {
		s.add(elt)
	}
	return s
}

func toSortedList(nsSet set[string]) []string {
	var nsList = maps.Keys(nsSet)
	slices.SortFunc(nsList, func(x, y string) int {
		return strings.Compare(x, y)
	})
	return nsList
}

func isDeclaration(stmt ast.Stmt) bool {
	switch s := stmt.(type) {
	case *ast.AssignStmt:
		if s.Tok == token.DEFINE {
			return true
		}
		return false
	case *ast.DeclStmt:
		switch dec := s.Decl.(type) {
		case *ast.GenDecl:
			switch dec.Tok {
			case token.VAR:
			case token.CONST:
				return true
			default:
				return false
			}
		default:
			return true
		}
	default:
		return false
	}
	return false
}

func hasDeclarations(stmts []ast.Stmt) bool {
	for _, stmt := range stmts {
		if isDeclaration(stmt) {
			return true
		}
	}
	return false
}

func canBeAliased(node ast.Expr, defType types.Type) bool {
	switch node.(type) {
	case *ast.ArrayType:
		return true
	case *ast.MapType:
		return true
	case *ast.ChanType:
		return true
	case *ast.Ident:
		switch dt := defType.(type) {
		case *types.Array:
			return true
		case *types.Map:
			return true
		case *types.Chan:
			return true
		case *types.Struct:
			return true
		case *types.Named:
			return canBeAliased(node, dt.Underlying())
		default:
			return false
		}
	default:
		return false
	}
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
