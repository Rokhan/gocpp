//go:build OMIT
// +build OMIT

package main

import (
	"fmt"
	"math"
)

func toto() {
}

type III interface{ M() }

type T struct{}

func (*T) M() {
}

func main() {
	var x, y int = 3, 4
	var f float64 = math.Sqrt(float64(x*x + y*y))
	var z uint = uint(f)
	fmt.Println(x, y, z)

	//type any = interface{}

	var ifunc any = (func())(toto)
	fmt.Println(ifunc)

	// var t III = &T{}
	// eface := (any)(*(*interface{ M() })(&t))
	// fmt.Println(eface)
}
