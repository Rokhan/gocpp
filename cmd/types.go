package main

import (
	"fmt"
	"go/ast"
	"go/token"
	"go/types"
	"reflect"
	"strings"

	"golang.org/x/tools/go/ast/astutil"
)

type parsingInfos struct {
	parsingContext

	typeInfo   *types.Info
	astFile    *ast.File
	commentMap ast.CommentMap
}

func convertGoToCppTypes(goType []types.Type, namespace string, position token.Position) []string {
	results := []string{}
	for _, subType := range goType {
		result, _ := convertGoToCppType(subType, typeConvCtx{namespace, position})
		results = append(results, result)
	}
	return results
}

func convertCommentLines(comment *ast.CommentGroup) []string {
	if comment == nil {
		return nil
	}
	lines := []string{}
	for _, c := range strings.Split(comment.Text(), "\n") {
		line := strings.TrimSpace(c)
		if line != "" {
			lines = append(lines, line)
		}
	}
	return lines
}

func convertComment(comment *ast.CommentGroup, indent string) string {
	lines := convertCommentLines(comment)
	sep := "\n" + indent + "// "
	return fmt.Sprintf("// %s", strings.Join(lines, sep))
}

func convertInlinedComment(comment *ast.CommentGroup, indent string) string {
	lines := convertCommentLines(comment)
	sep := "\n" + indent
	return fmt.Sprintf("/* %s */", strings.Join(lines, sep))
}

func getArrayLen(goType types.Type, position token.Position) int64 {
	if goType == nil {
		panic("getArrayLen. Cannot convert nil type.")
	}

	switch subType := goType.(type) {
	case *types.Array:
		return subType.Len()
	}

	Panicf("getArrayLen. Unmanaged type, type [%v], position[%v]", reflect.TypeOf(goType), position)
	return 0
}

// Get the type parameters from an expression
func (cv *parsingInfos) GetExprTypeParameters(expr ast.Expr) []types.Type {
	goType := cv.convertExprToType(expr)
	return cv.GetTypeParameters(goType, expr)
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

	for {
		switch t := goType.(type) {
		case *types.Array:
			return true

		case *types.Named:
			goType = t.Underlying()

		// TODO: types.Named, types.Alias ??

		default:
			return false
		}
	}
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

func (cv *parsingInfos) getReferencedTypesFor(file string) (usedTypes map[types.Object]tagType) {
	usedTypes = make(map[types.Object]tagType)

	/*
	 * We need to manage dependencies in header and cpp like we do in forward header.
	 * Once it will be done, all "tags" used to know if we need include in header or source file will be useless.
	 */

	types := cv.typeInfo.Types
	cv.filterTypes(types, file, usedTypes, UsesTag)
	uses := cv.typeInfo.Uses
	cv.filterUsedObjects(uses, file, usedTypes, UsesTag)
	defs := cv.typeInfo.Defs
	cv.filterUsedObjects(defs, file, usedTypes, DefsTag)
	// selections := cv.typeInfo.Selections
	// cv.filterSelections(selections, file, usedTypes, UsesTag)
	return
}

// func (cv *cppConverter) filterSelections(srcSelections map[*ast.SelectorExpr]*types.Selection, file string, usedTypes map[types.Object]tagType, tag tagType) {
// 	for sel, selection := range srcSelections {
// 		var filePos = cv.Position(sel)
// 		if file != filePos.Filename {
// 			continue
// 		}
// 		usedTypes[selection.Obj()] |= tag
// 	}
// }

func (cv *parsingInfos) filterTypes(srcTypes map[ast.Expr]types.TypeAndValue, file string, usedTypes map[types.Object]tagType, tag tagType) {
	for expr, typeAndValue := range srcTypes {
		var filePos = cv.Position(expr)
		if file != filePos.Filename {
			continue
		}

		for _, o := range GetObjectsOfType(typeAndValue.Type) {
			usedTypes[o] |= tag
		}
	}
}

func (cv *parsingInfos) filterUsedObjects(objs map[*ast.Ident]types.Object, file string, usedTypes map[types.Object]tagType, tag tagType) {
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

// Get the return type of a function node
func getFunctionSignature(typeInfo *types.Info, funcNode ast.Node) (sig *types.Signature) {

	switch n := funcNode.(type) {
	case *ast.FuncDecl:
		// Try the ast.FuncType entry first
		if n.Type != nil {
			if tv, ok := typeInfo.Types[n.Type]; ok {
				if sig, ok = tv.Type.(*types.Signature); ok {
					break
				}
			}
		}
		// Fall back to function object (named func)
		if n.Name != nil {
			if def := typeInfo.Defs[n.Name]; def != nil {
				var ok bool
				if sig, ok = def.Type().(*types.Signature); ok {
					break
				}
			}
		}

	case *ast.FuncLit:
		if n.Type != nil {
			if tv, ok := typeInfo.Types[n.Type]; ok {
				if sig, ok = tv.Type.(*types.Signature); ok {
					break
				}
			}
		}

	case *ast.FuncType:
		if tv, ok := typeInfo.Types[n]; ok {
			if sig, ok = tv.Type.(*types.Signature); ok {
				break
			}
		}
	}
	return sig
}

func getFunctionReturnType(typeInfo *types.Info, funcNode ast.Node) *types.Tuple {
	sig := getFunctionSignature(typeInfo, funcNode)
	return sig.Results()
}

// Tell if a function is a method (has a receiver) or not
func (cv *parsingInfos) IsMethod(funcNode ast.Node) bool {
	if funcNode == nil {
		return false
	}
	sig := getFunctionSignature(cv.typeInfo, funcNode)
	return sig != nil && sig.Recv() != nil
}

type FuncKind int

const (
	FuncKindAny    FuncKind = 0
	FuncKindPlain  FuncKind = 1
	FuncKindMethod FuncKind = 2
)

func (kind FuncKind) AppliesTo(sig *types.Signature) bool {
	switch kind {
	case FuncKindAny:
		return true
	case FuncKindPlain:
		return sig.Recv() == nil
	case FuncKindMethod:
		return sig.Recv() != nil
	default:
		Panicf("Unexpected FuncKind value: %v", kind)
		return false // unreachable
	}
}

// Get the list of methods declared in the current package
func (cv *parsingInfos) GetPackageFuncs(fk FuncKind) []*types.Func {
	if cv.typeInfo == nil {
		return nil
	}
	var result []*types.Func
	for _, obj := range cv.typeInfo.Defs {
		if obj == nil {
			continue
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

func (cv *parsingInfos) GetPackageMethods() []*types.Func {
	return cv.GetPackageFuncs(FuncKindMethod)
}

func (cv *parsingInfos) GetPackageMethodsNames() []string {
	methods := cv.GetPackageMethods()
	return getFuncNames(methods)
}

func (cv *parsingInfos) GetPackageFunctionsNames() []string {
	methods := cv.GetPackageFuncs(FuncKindPlain)
	return getFuncNames(methods)
}

func getFuncNames(methods []*types.Func) []string {
	var result []string
	for _, m := range methods {
		result = append(result, m.Name())
	}
	return result
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
