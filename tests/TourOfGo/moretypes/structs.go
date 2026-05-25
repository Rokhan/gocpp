//go:build OMIT
// +build OMIT

package main

import (
	"fmt"
	"unsafe"
)

type Vertex struct {
	X int32
	Y int32
}

// Similar to ARM64 and X86 structs in cpu package (internal\cpu\cpu.go)
var AnonymousStruct struct {
	first  int32
	second int16
}

type Empty struct{}
type Dummy struct{ i int }

type Dummy2 struct {
	Dummy
	Vertex
	i int
}

type Person struct {
	identity *struct {
		firstName string
		lastName  string
	}
	age int
}

func inlineStructDef(dummy struct{ a int }) {
	fmt.Println("inlineStructDef", dummy.a)
}

func embededStructDef() {
	s := []byte("hello world")

	type span struct {
		start int
		end   int
	}

	spans := make([]span, 0, 32)
	spans = append(spans, span{0, 5})
	spans = append(spans, span{6, 11})

	a := make([][]byte, len(spans))
	for i, span := range spans {
		a[i] = s[span.start:span.end:span.end]
	}

	for i, part := range a {
		fmt.Println("part ", i, ":", string(part))
	}
}

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

	dd := Dummy2{d, Vertex{}, 3}
	fmt.Println(dd)

	inlineStructDef(struct{ a int }{42})
	embededStructDef()

	vv := Vertex{3, 4}
	offsetX := unsafe.Offsetof(vv.X)
	offsetY := unsafe.Offsetof(vv.Y)
	fmt.Println("Offset of X in Vertex:", offsetX)
	fmt.Println("Offset of Y in Vertex:", offsetY)
	fmt.Println("Size of Vertex:", unsafe.Sizeof(vv))

	fmt.Println("Offset of a in Anonymous struct:", unsafe.Offsetof(AnonymousStruct.first))
	fmt.Println("Offset of b in Anonymous struct:", unsafe.Offsetof(AnonymousStruct.second))
	fmt.Println("Size of Anonymous struct:", unsafe.Sizeof(AnonymousStruct))

	//var p2 *Dummy = &v1
	//fmt.Println(p2)
}
