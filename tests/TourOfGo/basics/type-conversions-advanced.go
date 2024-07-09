package main

import (
	"fmt"
	"math"
)

func toto() {
}

func totoInt() int {
	return 0
}

type III interface{ M() }

type T struct{}

func (*T) M() {
}

type Vertex struct {
	Lat, Long float64
}

func main() {
	var x, y int = 3, 4
	var f float64 = math.Sqrt(float64(x*x + y*y))
	var z1 uint = uint(f)
	fmt.Println(x, y, z1)

	var z2 uint = (uint)(f)
	fmt.Println("z2:", z2)

	var z3 uint = (uint)(z2)
	fmt.Println("z2:", z3)

	//type any = interface{}

	var ifunc1 any = (func())(toto)
	fmt.Println(ifunc1)

	var ifunc2 any = (totoInt)()
	fmt.Println(ifunc2)

	m1 := make(map[string]Vertex)
	m2 := make((map[string]Vertex))
	m3 := make((map[(string)](Vertex)))

	var i int
	fmt.Println(m1, m2, m3, i)

	// var t III = &T{}
	// eface := (any)(*(*interface{ M() })(&t))
	// fmt.Println(eface)
}
