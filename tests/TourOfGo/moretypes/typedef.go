//go:build OMIT
// +build OMIT

package main

import (
	"fmt"
)

type ArbitraryType int
type IntegerType int
type Pointer *ArbitraryType

type Vertex struct {
	X int
	Y int
}

type VertexAlias Vertex
type VertexPtr *Vertex

type vvvv1 = Vertex
type vvvv2 Vertex

func UseTypedefPtr1(t *vvvv1) {}
func UseTypedefPtr2(t *vvvv2) {}
func UseStructPtr(t *Vertex)  {}

type str1 string
type str2 string

func main() {
	vstr1 := str1("hello")
	vstr2 := str2("hello")
	fmt.Println("str1:", vstr1, ", str2:", vstr2)

	fmt.Println(Vertex{1, 2})
	UseTypedefPtr1(&Vertex{1, 2})
	UseTypedefPtr2(&vvvv2{1, 2})
	UseStructPtr(&Vertex{1, 2})
}
