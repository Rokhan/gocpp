//go:build ignore || OMIT
// +build ignore OMIT

package main

import (
	"fmt"
)

func Sqrt(x float64) float64 {
	if x <= 0 {
		panic("error, Sqrt(x) with x<1")
	}

	z := 1.0
	for i := 0; i < 15; i++ {
		//fmt.Printf("z: %v\n", z)
		z -= (z*z - 2) / (2 * x)
		if z > 0 && z < 0.000_000_001 {
			break
		}
	}
	return z
}

func main() {
	fmt.Println(Sqrt(2))
}
