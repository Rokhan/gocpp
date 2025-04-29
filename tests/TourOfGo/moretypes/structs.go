//go:build OMIT
// +build OMIT

package main

import "fmt"

type Vertex struct {
	X int
	Y int
}

type Empty struct{}
type Dummy struct{ i int }

type Person struct {
	identity *struct {
		firstName string
		lastName  string
	}
	age int
}

func inlineStructDef(dummy struct{ a int }) {}

func main() {
	fmt.Println(Vertex{1, 2})

	var i struct{}
	var j struct{}
	fmt.Println(i == j)

	e := Empty{}
	fmt.Println(e == j)

	v1 := struct{ i int }{1}
	v2 := struct{ i int }{1}
	fmt.Println(v1 == v2)

	d := Dummy{1}
	d = struct{ i int }{1}
	fmt.Println(d == v2)
	fmt.Println(d == v1)

	var p1 *Dummy = &d
	fmt.Println(p1)

	p1 = nil
	fmt.Println(p1)

	//var p2 *Dummy = &v1
	//fmt.Println(p2)
}
