//go:build OMIT
// +build OMIT

package main

import "fmt"

type ArbitraryType int
type IntegerType int
type Pointer *ArbitraryType

type Vertex struct {
	X int
	Y int
}

type VertexAlias Vertex
type VertexPtr *Vertex

func main() {
	fmt.Println(Vertex{1, 2})
}
