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

func (v *Vertex) Print() {
	fmt.Println("Receiver, Vertex:", v.X, v.Y)
}

func (v *vvvv2) Print() {
	fmt.Println("Receiver, vvvv2:", v.X, v.Y)
}

func UseTypedefPtr1(t *vvvv1) {
	fmt.Println("\nUseTypedefPtr1")
	fmt.Println("vvvv1:", t.X, t.Y)
	t.Print()
}
func UseTypedefPtr2(t *vvvv2) {
	fmt.Println("\nUseTypedefPtr2")
	fmt.Println("vvvv2:", t.X, t.Y)
	t.Print()
}
func UseStructPtr(t *Vertex) {
	fmt.Println("\nUseStructPtr")
	fmt.Println("Vertex:", t.X, t.Y)
	t.Print()
}

type str1 string
type str2 string

func main() {
	vstr1 := str1("hello")
	vstr2 := str2("hello")
	fmt.Println("str1:", vstr1, ", str2:", vstr2)

	fmt.Println(Vertex{1, 2})
	UseTypedefPtr1(&Vertex{1, 2})
	UseTypedefPtr1(&vvvv1{1, 2})

	UseTypedefPtr2(&vvvv2{1, 2})
	UseStructPtr(&Vertex{1, 2})

	var v01 vvvv1 = Vertex{}
	var v02 Vertex = v01
	_ = v01
	_ = v02

	// var v11 vvvv2 = Vertex{}
	// var v12 Vertex = v11
	// _ = v11
	// _ = v12
}
