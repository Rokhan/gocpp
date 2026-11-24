package main

import (
	"fmt"
	"go/ast"
	"go/constant"
	"go/token"
	"go/types"
	"path/filepath"
	"reflect"
	"slices"
	"strings"

	"golang.org/x/tools/go/ast/astutil"
)

type parsingInfos struct {
	parsingContext

	typeInfo   *types.Info
	astFile    *ast.File
	pkg        *types.Package
	commentMap ast.CommentMap
}

// posFilePath return the path computed via the shared FileSet.
func (cv *parsingInfos) posFilePath(t token.Pos) string {
	tf := cv.pcShared.fileSet.File(t)
	if tf == nil {
		return "<unknown>"
	}
	return CleanPath(tf.Name())
}

// posFilePath return the base name computed via the shared FileSet.
func (cv *parsingInfos) posBaseName(t token.Pos) string {
	tf := cv.pcShared.fileSet.File(t)
	if tf == nil {
		return "<unknown>"
	}
	return strings.TrimSuffix(filepath.Base(tf.Name()), ".go")
}

// Get the type parameters from an expression
func (cv *parsingInfos) GetExprTypeParameters(expr ast.Expr) []types.Type {
	goType := cv.convertExprToType(expr)
	return cv.GetTypeParameters(goType, expr)
}

// Not used at the moment
//
// // Get the list of methods declared in the current file
// func (cv *parsingInfos) GetFileMethods() []*types.Func {
// 	if cv.astFile == nil || cv.typeInfo == nil {
// 		return nil
// 	}
// 	var result []*types.Func
// 	for _, decl := range cv.astFile.Decls {
// 		fn, ok := decl.(*ast.FuncDecl)
// 		if !ok || fn.Recv == nil || fn.Name == nil {
// 			continue
// 		}
// 		if def := cv.typeInfo.Defs[fn.Name]; def != nil {
// 			if f, ok := def.(*types.Func); ok {
// 				result = append(result, f)
// 			}
// 		}
// 	}
// 	return result
// }
//
// func (cv *parsingInfos) GetFileMethodsNames() []string {
// 	methods := cv.GetFileMethods()
// 	return getFuncNames(methods)
// }

func (cv *parsingInfos) convertExprToType(node ast.Expr) types.Type {
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

	cv.Panicf("convertExprToType, node [%s], position [%s]", types.ExprString(node), cv.Position(node))
	panic("convertExprToType, bug, unreacheable code reached !")
}

// Get the list of functions/methods declared in the current package
func (cv *parsingInfos) GetPackageFuncs(fk FuncKind) []*types.Func {
	if cv.typeInfo == nil {
		return nil
	}
	var result []*types.Func
	for _, obj := range cv.typeInfo.Defs {
		if obj == nil {
			continue
		}

		if obj.Pkg() != cv.pkg {
			continue // belongs to a different package
		}

		if fn, ok := obj.(*types.Func); ok {
			if sig, ok := fn.Type().(*types.Signature); ok {
				if fk.AppliesTo(sig) {
					result = append(result, fn)
				}
			}
		}
	}
	return result
}

// // GetPackageVars returns the list of global (package-level) variables
// // declared in the current package.
// func (cv *parsingInfos) GetPackageVars() []*types.Var {
// 	if cv.typeInfo == nil {
// 		return nil
// 	}
// 	var result []*types.Var
// 	for _, obj := range cv.typeInfo.Defs {
// 		if obj == nil {
// 			continue
// 		}
// 		v, ok := obj.(*types.Var)
// 		if !ok {
// 			continue
// 		}
// 		if v.IsField() {
// 			continue // struct field, not a package-level var
// 		}
// 		// TODO
// 		// if v.Pkg() != cv.pkg {
// 		// 	continue // belongs to a different package
// 		// }
// 		if v.Parent() != v.Pkg().Scope() {
// 			continue // local var / param, not package-level
// 		}
// 		result = append(result, v)
// 	}
// 	return result
// }

func (cv *parsingInfos) GetPackageMethods() []*types.Func {
	return cv.GetPackageFuncs(FuncKindMethod)
}

func (cv *parsingInfos) GetPackageMethodsNames() []string {
	methods := cv.GetPackageMethods()
	return getFuncNames(methods)
}

func (cv *parsingInfos) GetPackageFuncNames(fk FuncKind) []string {
	methods := cv.GetPackageFuncs(fk)
	return getFuncNames(methods)
}

func (cv *parsingInfos) getPkgFromExprType(expr ast.Expr) (pkg *types.Package) {
	typ := cv.typeInfo.Types[expr].Type
	if typ == nil {
		return nil
	}

	switch t := typ.(type) {
	case *types.Named:
		pkg = t.Obj().Pkg()
	case *types.Pointer:
		if named, ok := t.Elem().(*types.Named); ok {
			pkg = named.Obj().Pkg()
		}
	default:
	}
	return pkg
}

func (cv *parsingInfos) GetTypeParameters(goType types.Type, expr ast.Expr) []types.Type {
	if goType == nil {
		return nil
	}

	switch t := goType.(type) {
	case *types.Basic:
		return nil

	case *types.Alias:
		if t.TypeArgs() != nil && t.TypeArgs().Len() > 0 {
			var result []types.Type
			for i := 0; i < t.TypeArgs().Len(); i++ {
				result = append(result, t.TypeArgs().At(i))
			}
			return result
		}

	case *types.Named:
		if t.TypeArgs() != nil && t.TypeArgs().Len() > 0 {
			var result []types.Type
			for i := 0; i < t.TypeArgs().Len(); i++ {
				result = append(result, t.TypeArgs().At(i))
			}
			return result
		}

	case *types.Array:
		return cv.GetTypeParameters(t.Elem(), expr)

	case *types.Interface:
		return nil

	case *types.Map:
		var result []types.Type
		result = append(result, cv.GetTypeParameters(t.Key(), expr)...)
		result = append(result, cv.GetTypeParameters(t.Elem(), expr)...)
		return result

	case *types.Pointer:
		return cv.GetTypeParameters(t.Elem(), expr)

	case *types.Slice:
		return cv.GetTypeParameters(t.Elem(), expr)

	case *types.Struct:
		return nil

	case *types.TypeParam:
		return []types.Type{t}

	case *types.Union:
		// For a union, collect type parameters from all terms
		var result []types.Type
		for i := 0; i < t.Len(); i++ {
			term := t.Term(i)
			params := cv.GetTypeParameters(term.Type(), expr)
			if params != nil {
				result = append(result, params...)
			}
		}
		return result

	default:
		cv.Panicf("GetExprTypeParameters, unimplemented case: type=%v, expr=%s, position=%s", reflect.TypeOf(goType), types.ExprString(expr), cv.Position(expr))
	}

	return nil
}

func (cv *parsingInfos) IsExprInt(expr ast.Expr) bool {
	goType := cv.convertExprToType(expr)
	switch t := goType.(type) {
	case *types.Basic:
		switch t.Kind() {
		case types.Int, types.Int8, types.Int16, types.Int32, types.Int64,
			types.Uint, types.Uint8, types.Uint16, types.Uint32, types.Uint64:
			return true
		}
	}
	return false
}

func (cv *parsingInfos) IsExprPtr(expr ast.Expr) bool {
	goType := cv.convertExprToType(expr)

	switch goType.(type) {
	case *types.Pointer:
		return true

	// TODO: types.Named, types.Alias ??

	default:
		return false
	}
}

func (cv *parsingInfos) IsExprArray(expr ast.Expr) bool {
	goType := cv.convertExprToType(expr)
	return isArray(goType)
}

func isArray(goType types.Type) bool {
	switch goType.Underlying().(type) {
	case *types.Array:
		return true
	}
	return false
}

// Tell if a function is a method (has a receiver) or not
func (cv *parsingInfos) IsMethod(funcNode ast.Node) bool {
	if funcNode == nil {
		return false
	}
	sig := getFunctionSignature(cv.typeInfo, funcNode)
	return sig != nil && sig.Recv() != nil
}

func (cv *parsingInfos) isNameUsebyMethods(name string) bool {
	// TODO, maybe slow, can be optimized by caching.
	methods := cv.GetPackageMethodsNames()
	if slices.Contains(methods, name) {
		return true
	}
	return false
}

func (cv *parsingInfos) isNameUsebyFunction(name string, fk FuncKind) bool {
	// TODO, maybe slow, can be optimized by caching.
	methods := cv.GetPackageFuncNames(fk)
	if slices.Contains(methods, name) {
		return true
	}
	return false
}

func (cv *parsingInfos) getNeededNamespaceAliasesForHeaderEnd(headerEndElts []*place, usingEmitted set[string], namespaceElt map[string]namespaceAlias) []string {
	neededNs := set[string]{}
	for _, elt := range headerEndElts {
		for ns := range elt.depInfo.depNss {
			neededNs.add(ns)
		}
	}
	if len(neededNs) == 0 {
		return nil
	}

	neededNs.remove(usingEmitted)

	var result []string
	for _, ns := range namespaceElt {
		if neededNs.has(ns.ns) {
			result = append(result, ns.aliasString())
		}
	}
	slices.Sort(result)
	return result
}

func (cv *parsingInfos) ConvertDocToStrings(doc *ast.CommentGroup) (result []string) {
	if doc == nil {
		return
	}

	for _, comment := range doc.List {
		text := strings.TrimSpace(comment.Text)
		if text != "" {
			result = append(result, text+"\n")
		}
	}
	return
}

// isConstExpr reports whether go/types folded e to a constant.
func (cv *parsingInfos) isConstExpr(e ast.Expr) bool {
	tv, ok := cv.typeInfo.Types[e]
	return ok && tv.Value != nil
}

func (cv *parsingInfos) constKey(obj types.Object) string {
	p := cv.pcShared.fileSet.Position(obj.Pos())
	return fmt.Sprintf("%s:%d", CleanPath(p.Filename), p.Offset)
}
func (cv *parsingInfos) getAllUsedNameSpaces(expr ast.Expr) map[string]bool {
	result := map[string]bool{}
	for goNs, selector := range getAllNsSelectorIds(expr, cv.typeInfo) {
		// Check if the identifier is a package name
		if defObj := cv.typeInfo.Uses[goNs]; defObj != nil {
			if _, ok := defObj.(*types.PkgName); ok {
				selType := cv.typeInfo.Uses[selector]
				ns := cv.NamespaceFromTypePkg(selType.Pkg())
				result[ns] = true
			}
		}
	}
	return result
}

func (cv *parsingInfos) getAllUsedNames(expr ast.Expr) map[string]bool {
	result := map[string]bool{}
	for ident := range getAllIdentifiers(expr) {
		result[ident.Name] = true
	}
	return result
}

func (cv *parsingInfos) getAllUsedVars(expr ast.Expr) map[types.Object]bool {
	result := map[types.Object]bool{}
	for ident := range getAllIdentifiers(expr) {
		defObj := cv.typeInfo.Uses[ident]
		switch def := defObj.(type) {
		case *types.Const:
			result[def] = true
		case *types.Var:
			result[def] = true
		}
	}
	return result
}

func (cv *parsingInfos) NamespaceFromTypePkg(pkg *types.Package) string {
	return cv.pcShared.nsNamer.NamespaceFromTypePkg(pkg)
}

// Returns the type parameters referenced by the fields of an anonymous struct.
func (cv *parsingInfos) structTypeParams(st *ast.StructType) typeParams {
	tps := typeParams{}
	ast.Inspect(st, func(n ast.Node) bool {
		id, ok := n.(*ast.Ident)
		if !ok {
			return true
		}
		tn, ok := cv.typeInfo.Uses[id].(*types.TypeName)
		if !ok {
			return true
		}
		if _, isParam := tn.Type().(*types.TypeParam); isParam {
			name := GetCppName(id.Name)
			if _, dup := tps[name]; !dup {
				tps[name] = &typeParam{name: name, order: len(tps)}
			}
		}
		return true
	})
	return tps
}

func (cv *parsingInfos) isParam(n *ast.Ident) (bool, string) {
	_, isParam := cv.typeInfo.Types[n].Type.(*types.TypeParam)
	return isParam, n.Name
}

func (cv *parsingInfos) checkIsParam(n *ast.Ident, identType *cppType) {
	_, isParam := cv.typeInfo.Types[n].Type.(*types.TypeParam)
	if isParam {
		identType.typenames = append(identType.typenames, n.Name)
	}
}

// Sprintf formats according to a format specifier and returns the resulting string.
func (cv *parsingInfos) BuffExprPrintf(buff *cppExprBuffer, format string, srcParams ...any) (n int, err error) {
	defs, params /*tns*/, _, coms, dbgs := extractParamDefs(srcParams...)
	//cv.Assertf(tns == nil, "typenames should be nil here")
	for _, com := range coms {
		com = cleanCommentString(com)
		fmt.Fprintf(buff.buff, "    /* %s */\n", com)
	}
	*buff.defs = append(*buff.defs, defs...)
	buff.dbgs = append(buff.dbgs, dbgs...)
	return fmt.Fprintf(buff.buff, format, params...)
}

func (cv *parsingInfos) constExprWidth(root ast.Expr) constWidth {
	w := fitsInt32
	ast.Inspect(root, func(n ast.Node) bool {
		e, ok := n.(ast.Expr)
		if !ok {
			return true
		}
		tv, ok := cv.typeInfo.Types[e]
		if !ok || tv.Value == nil || tv.Value.Kind() != constant.Int {
			return true
		}
		if b, ok := types.Unalias(tv.Type).Underlying().(*types.Basic); ok &&
			b.Info()&types.IsInteger != 0 && b.Info()&types.IsUntyped == 0 && fitsOwnType(tv.Value, b) {
			// Typed and representable in its own type: never needs bigint, but the C++
			// literals building it are plain int, so they must be widened when the value
			// is beyond int32 (e.g. '-1 << 63' for a Duration).
			if constant.Compare(tv.Value, token.LSS, int32Min) || constant.Compare(tv.Value, token.GTR, int32Max) {
				if constant.Compare(tv.Value, token.GEQ, int64Min) && constant.Compare(tv.Value, token.LEQ, int64Max) {
					w = max(w, fitsInt64)
				}
				// beyond int64 (e.g. ^uint(0)): its typed conversion already produces the right C++ type
			}
			return true
		}
		switch {
		case constant.Compare(tv.Value, token.GEQ, int32Min) && constant.Compare(tv.Value, token.LEQ, int32Max):
		case constant.Compare(tv.Value, token.GEQ, int64Min) && constant.Compare(tv.Value, token.LEQ, int64Max):
			w = max(w, fitsInt64)
		default:
			w = max(w, needsBig)
		}
		return true
	})
	return w
}

// 5454

func (cv *parsingInfos) isConstLeaf(e ast.Expr) bool {
	tv, ok := cv.typeInfo.Types[e]
	return ok && tv.Value != nil && tv.Value.Kind() == constant.Int
}

// Handles float literals such as `1e3` that are seen as an integer by the type system.
// Returns the C++ integer literal and true/false if integer/float
func (cv *parsingInfos) floatLitAsInt(lit *ast.BasicLit) (string, bool) {
	tv, ok := cv.typeInfo.Types[lit]
	if !ok || tv.Value == nil {
		return "", false
	}
	b, ok := types.Unalias(tv.Type).Underlying().(*types.Basic)
	if !ok || b.Info()&types.IsInteger == 0 || b.Info()&types.IsUntyped != 0 {
		return "", false
	}
	v := constant.ToInt(tv.Value)
	if v.Kind() != constant.Int {
		return "", false
	}

	str := groupDigits(v.ExactString())
	switch {
	case constant.Compare(v, token.GEQ, int32Min) && constant.Compare(v, token.LEQ, int32Max):
		return str, true
	case constant.Compare(v, token.GEQ, int64Min) && constant.Compare(v, token.LEQ, int64Max):
		return str + "LL", true
	case constant.Compare(v, token.GTR, int64Max) && constant.Compare(v, token.LEQ, uint64Max):
		return str + "ULL", true
	}
	return "", false
}

func (cv *parsingInfos) buildPkgDepInfo(obj *types.PkgName, selector *ast.Ident) depInfo {
	use := cv.typeInfo.Uses[selector]
	pkgId := obj.Imported().Path() + "/" + cv.posBaseName(use.Pos())
	di := depInfo{depPkgs: map[string]includeType{pkgId: FwdInclude}}
	return di
}

func (cv *parsingInfos) nsFromPkg(obj *types.PkgName) string {
	return cv.pcShared.nsNamer.NamespaceFromTypePkg(obj.Imported())
}

func (cv *parsingInfos) isCurrentPkgTopLevel(obj types.Object) bool {
	return obj != nil && obj.Pkg() != nil && obj.Pkg() == cv.pkg && isTopLevel(obj)
}

func (cv *parsingInfos) isArrayOrArrayPtr(e ast.Expr) bool {
	t := cv.typeInfo.TypeOf(e)
	if t == nil {
		return false
	}
	if p, ok := t.Underlying().(*types.Pointer); ok {
		t = p.Elem()
	}
	_, ok := t.Underlying().(*types.Array)
	return ok
}

func (cv *parsingInfos) isNameSpace(expr ast.Expr) bool {

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

func (cv *parsingInfos) IsExprInterface(expr ast.Expr) bool {
	goType := cv.convertExprToType(expr)

	for {
		switch t := goType.(type) {
		case *types.Interface:
			return true

		case *types.Named:
			goType = t.Underlying()

		default:
			return false
		}
	}
}

func (cv *parsingInfos) IsSelectorExprSignature(expr *ast.SelectorExpr) (isFunc bool, hasReceiv bool, nbPrams int) {
	exprGoType := cv.convertExprToType(expr)
	selectorGoType := cv.typeInfo.TypeOf(expr.Sel)

	switch exprType := exprGoType.(type) {
	case *types.Signature:
		nExpr := exprType.Params().Len()

		switch selType := selectorGoType.(type) {
		case *types.Signature:
			nSel := selType.Params().Len()
			return true, nSel != nExpr, nExpr
		}
		return true, false, nExpr

	// TODO: types.Named, types.Alias ??

	default:
		return false, false, 0
	}
}

func (cv *parsingInfos) IsFunc(expr ast.Expr) bool {
	tv := cv.typeInfo.Types[expr].Type

	switch tv.(type) {
	case *types.Signature:
		return true
	}
	return false
}

func (cv *parsingInfos) IsExprSignature(expr ast.Expr) (isFunc bool, hasReceiv bool, nbPrams int) {
	exprGoType := cv.convertExprToType(expr)

	switch exprType := exprGoType.(type) {
	case *types.Signature:
		nExpr := exprType.Params().Len()
		return true, exprType.Recv() != nil, nExpr

	default:
		return false, false, 0
	}
}

func (cv *parsingInfos) IsExprMap(expr ast.Expr) bool {
	goType := cv.convertExprToType(expr)
	return cv.IsTypeMap(goType)
}

func (cv *parsingInfos) IsTypeMap(goType types.Type) bool {
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

func (cv *parsingInfos) IsType(expr ast.Expr) bool {
	tv, ok := cv.typeInfo.Types[expr]
	return ok && tv.IsType()
}

func (cv *parsingInfos) getReferencedTypes() (usedTypes map[types.Object]tagType) {
	usedTypes = make(map[types.Object]tagType)

	/*
	 * We need to manage dependencies in header and cpp like we do in forward header.
	 * Once it will be done, all "tags" used to know if we need include in header or source file will be useless.
	 */
	ast.Inspect(cv.astFile, func(n ast.Node) bool {
		if n == nil {
			return false
		}

		if expr, ok := n.(ast.Expr); ok {
			if tv, ok := cv.typeInfo.Types[expr]; ok {
				cv.filterType(tv, usedTypes, UsesTag)
			}
		}

		if id, ok := n.(*ast.Ident); ok {
			if use := cv.typeInfo.Uses[id]; use != nil {
				cv.filterUsedObject(use, usedTypes, UsesTag)
			}
			if def := cv.typeInfo.Defs[id]; def != nil {
				cv.filterUsedObject(def, usedTypes, DefsTag)
			}
		}

		// Maybe needed at some point.
		// if sel, ok := n.(*ast.SelectorExpr); ok {
		// 	if def := cv.typeInfo.Selections[sel]; def != nil {
		// 		cv.filterSelections(def, file, usedTypes, UsesTag)
		// 	}
		// }

		return true
	})
	return
}

// func (cv *parsingInfos) filterSelections(selection *types.Selection, usedTypes map[types.Object]tagType, tag tagType) {
// 	usedTypes[selection.Obj()] |= tag
// }

func (cv *parsingInfos) filterType(srcType types.TypeAndValue, usedTypes map[types.Object]tagType, tag tagType) {
	for _, o := range GetObjectsOfType(srcType.Type) {
		usedTypes[o] |= tag
	}
}

func (cv *parsingInfos) filterUsedObject(obj types.Object, usedTypes map[types.Object]tagType, tag tagType) {

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
			usedTypes[t] |= tag
		}
	}
}

// Take a node in the ast and return the return type of the function in which it is located
func (cv *parsingInfos) getReturnType(node ast.Node) *types.Tuple {
	funcNode := cv.getReturnFunc(node)
	if funcNode == nil {
		return nil
	}
	return getFunctionReturnType(cv.typeInfo, funcNode)
}

// Tell if node is used in a method or not
func (cv *parsingInfos) IsInMethod(node ast.Node) bool {
	funcNode := cv.getReturnFunc(node)
	if funcNode == nil {
		return false
	}
	return cv.IsMethod(funcNode)
}

// Take a node in the ast get the containing function
func (cv *parsingInfos) getReturnFunc(node ast.Node) ast.Node {
	if cv.typeInfo == nil || node == nil || cv.astFile == nil {
		return nil
	}

	// Find the innermost function-related node that encloses the given node.
	var best ast.Node
	var bestSpan token.Pos = 0
	pos := node.Pos()

	// Use AST path helper to get candidates near the position.
	if path, _ := astutil.PathEnclosingInterval(cv.astFile, pos, pos); path != nil {
		for _, n := range path {
			switch n.(type) {
			case *ast.FuncDecl, *ast.FuncLit, *ast.FuncType:
				if n.Pos() <= pos && pos <= n.End() {
					span := n.End() - n.Pos()
					if best == nil || span < bestSpan {
						best = n
						bestSpan = span
					}
				}
			}
		}
	}

	return best
}

// Tell whether obj is a package-level object whose name is also used
// by a function in the rec:: namespace.
func (cv *cppConverter) isShadowedByRec(obj types.Object) bool {
	return cv.isCurrentPkgTopLevel(obj) && cv.recNamespaceNames().has(obj.Name())
}
