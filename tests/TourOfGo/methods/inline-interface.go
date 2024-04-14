//go:build OMIT
// +build OMIT

package main

import (
	"fmt"
	"math"
)

type MyInt int
type MyFloat float64

func (i MyInt) Abs() float64 {
	return math.Sqrt(float64(i * i))
}

func (f MyFloat) Abs() float64 {
	return math.Sqrt(float64(f * f))
}

type Vertex struct {
	X, Y float64
}

func (v Vertex) Abs() float64 {
	return math.Sqrt(v.X*v.X + v.Y*v.Y)
}

func main() {
	var i interface{ Abs() float64 }
	describe(i)

	i = MyInt(42)
	describe(i)

	i = MyFloat(42.0)
	describe(i)

	i = Vertex{4, 2}
	describe(i)
}

func describe(i interface{ Abs() float64 }) {
	if i != nil {
		fmt.Printf("(%v, %T) => %v\n", i, i, i.Abs())
	} else {
		fmt.Printf("(%v, %T)\n", i, i)
	}
}
