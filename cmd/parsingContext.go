package main

import (
	"fmt"
	"go/ast"
	"go/token"
	"go/types"
	"strings"
)

func (cv *parsingContext) getPosition(pos token.Pos) token.Position {
	return cv.pcShared.fileSet.Position(pos)
}

func (cv *parsingContext) Position(expr ast.Node) token.Position {
	if expr != nil {
		return cv.getPosition(expr.Pos())
	}
	return token.Position{}
}

func (cv *parsingContext) EndPosition(expr ast.Node) token.Position {
	switch e := expr.(type) {
	case *ast.CaseClause:
		if len(e.Body) > 0 {
			return cv.getPosition(e.Body[len(e.Body)-1].End())
		}
	case *ast.CommClause:
		if len(e.Body) > 0 {
			return cv.getPosition(e.Body[len(e.Body)-1].End())
		}
	default:
		return cv.getPosition(expr.End())
	}
	return token.Position{}
}

func (cv *parsingContext) TokenPosition(token token.Pos) token.Position {
	return cv.pcShared.fileSet.Position(token)
}

func (cv *parsingContext) TokenLine(token token.Pos) int {
	return cv.pcShared.fileSet.Position(token).Line
}

func (cv *parsingContext) StartLine(expr ast.Node) int {
	return cv.Position(expr).Line
}

func (cv *parsingContext) EndLine(expr ast.Node) int {
	return cv.EndPosition(expr).Line
}

// For generic functions with func-typed parameters, emit an overload taking
// any callable, since C++ can't deduce T from a lambda -> std::function<T()>.
func (cv *parsingContext) funcParamOverload(af appendFunc, name string, params typeNames, typeParams typeParams) []place {
	keep := set[string]{}
	var addKept func(n string)
	addKept = func(n string) {
		if keep.has(n) {
			return
		}
		keep.add(n)
		if tp, ok := typeParams[n]; ok {
			for _, sub := range tp.subParams {
				addKept(sub)
			}
		}
	}

	var decls, args, funcTmplParams []string
	nbF := 0

	for k, pn := range params {
		if pn.Type.isEllipsis {
			cv.Panicf("funcParamOverload, ellipsis parameter not managed, declaration: [%v]", params)
		}
		if len(pn.names) == 0 { // unnamed parameter
			pn.names = []string{fmt.Sprintf("arg%d", k)}
		}

		if !pn.Type.isFunc {
			decls = append(decls, pn.ParamDecl()...)
			args = append(args, pn.names...)
			for _, n := range pn.Type.typenames {
				addKept(n)
			}
			continue
		}

		for _, n := range pn.names {
			nbF++
			fName := fmt.Sprintf("F%d", nbF)
			funcTmplParams = append(funcTmplParams, "typename "+fName)
			decls = append(decls, fmt.Sprintf("%s&& %s", fName, n))
			args = append(args, fmt.Sprintf("std::function(std::forward<%s>(%s))", fName, n))
		}
	}

	if nbF == 0 {
		return nil
	}

	var tmplParams []string
	for _, tp := range typeParams.Ordered() {
		if keep.has(tp.name) {
			tmplParams = append(tmplParams, mkTemplateParameter(tp.name, tp.subParams))
		}
	}
	tmplParams = append(tmplParams, funcTmplParams...)

	var out []place
	af(&out, "\n")
	af(&out, "template<%s>\n", strings.Join(tmplParams, ", "))
	af(&out, "decltype(auto) %s(%s)\n", name, strings.Join(decls, ", "))
	af(&out, "{\n")
	af(&out, "    return %s(%s);\n", name, strings.Join(args, ", "))
	af(&out, "}\n")
	return out
}

func (cv *parsingInfos) isCurrentPkgTopLevel(obj types.Object) bool {
	return obj != nil && obj.Pkg() != nil && obj.Pkg() == cv.pkg && isTopLevel(obj)
}

// Tell whether obj is a package-level object whose name is also used
// by a function in the rec:: namespace.
func (cv *cppConverter) isShadowedByRec(obj types.Object) bool {
	return cv.isCurrentPkgTopLevel(obj) && cv.recNamespaceNames().has(obj.Name())
}
