//go:build OMIT
// +build OMIT

package main

import "fmt"

type Vertex struct {
	X, Y, Z int
}

type Segment struct {
	Start, End Vertex
}

var (
	one = 1
	v1  = Vertex{one, 2, 3}    // has type Vertex
	v2  = Vertex{X: one}       // Y:0 is implicit
	v3  = Vertex{}             // X:0 and Y:0
	v4  = Vertex{X: one, Z: 3} //
	s1  = Segment{Start: Vertex{X: 1, Z: 3, Y: 2}, End: Vertex{1, 1, 1}}
)

func main() {
	s2 := Segment{Start: Vertex{X: one, Z: 3, Y: 2}, End: Vertex{1, one, 1}}

	fmt.Println(v1, v2, v3, v4, s1, s2)
}
