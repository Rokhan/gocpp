//go:build OMIT
// +build OMIT

package main

import (
	"fmt"
	"math"
)

type Abser interface {
	Abs() float64
}

type Adder interface {
	Add(f int)
}

type Multiplier interface {
	Mul(f int)
}

type MultAdder interface {
	Adder
	Multiplier
	Print()
}

type num struct {
	value int
}

func (n *num) Add(f int) {
	n.value += f
}

func (n *num) Mul(f int) {
	n.value *= f
}

func (n *num) Print() {
	fmt.Println(n.value)
}

func testAddMul() {
	n := num{10}
	n.Add(5)
	n.Mul(2)
	n.Print()

	var iNum MultAdder
	iNum = &num{11}
	iNum.Add(6)
	iNum.Mul(3)
	iNum.Print()
}

// Check interface declaration with method with nameless parameter
type dummy interface{ As(any) bool }

func main() {
	var a Abser
	f := MyFloat(-math.Sqrt2)
	v := Vertex{3, 4}

	a = f  // a MyFloat implements Abser
	a = &v // a *Vertex implements Abser

	// In the following line, v is a Vertex (not *Vertex)
	// and does NOT implement Abser.
	//a = v

	// Interface can be compared with nil.
	if a != nil || a == nil {
		fmt.Println(a.Abs() + 0.00001)
	}

	testAddMul()
}

type MyFloat float64

func (f MyFloat) Abs() float64 {
	if f < 0 {
		return float64(-f)
	}
	return float64(f)
}

type Vertex struct {
	X, Y float64
}

func (v *Vertex) Abs() float64 {
	return math.Sqrt(v.X*v.X + v.Y*v.Y)
}
