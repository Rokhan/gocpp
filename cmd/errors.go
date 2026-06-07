package main

import (
	"go/ast"
	"go/token"
	"strings"
)

type sharedParsingContext struct {
	fileSet *token.FileSet
}

type parsingContext struct {
	pcShared *sharedParsingContext

	parentCv    *parsingContext
	srcBaseName string
}

func (cv *parsingContext) includeStack() []string {
	out := []string{}
	for currentCv := cv; currentCv != nil; currentCv = currentCv.parentCv {
		out = append(out, currentCv.srcBaseName)
	}
	return out
}

func (cv *parsingContext) printStack() string {
	return JoinWithPrefix(cv.includeStack(), "\n -> ")
}

func (cv *parsingContext) Panicf(format string, params ...interface{}) {
	if strings.HasSuffix(format, "\n") {
		format = format[:len(format)-1]
		format = format + ", stack: %s\n"
	} else {
		format = format + ", stack: %s"
	}

	params = append(params, cv.printStack())
	Panicf(format, params...)
}

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

func (cv *parsingContext) StartLine(expr ast.Node) int {
	return cv.Position(expr).Line
}

func (cv *parsingContext) EndLine(expr ast.Node) int {
	return cv.EndPosition(expr).Line
}
