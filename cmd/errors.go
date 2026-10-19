package main

import (
	"go/token"
	"strings"
)

type sharedParsingContext struct {
	fileSet *token.FileSet
	nsNamer *NsNamer
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

func (cv *parsingContext) Assertf(ok bool, format string, a ...interface{}) {
	if !ok {
		cv.Panicf(format, a...)
	}
}
