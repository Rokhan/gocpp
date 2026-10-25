//go:build OMIT
// +build OMIT

package main

import (
	"fmt"
	"math/cmplx"
)

var (
	ToBe   bool       = false
	MaxInt uint64     = 1<<64 - 1
	z      complex128 = cmplx.Sqrt(-5 + 12i)
)

// --- Defined types on top of basic types (gocpp::defined<T, Tag>) ---

type Meters int
type Feet int
type Celsius float64
type Level uint8

type Kind int

const (
	Cold Kind = iota
	Warm
	Hot
)

const Size Kind = 3

// Same method name on two types with the same underlying type:
// they must not collide once Meters and Feet are distinct C++ types.
func (m Meters) Describe() string { return "meters" }
func (f Feet) Describe() string   { return "feet" }

func (k Kind) IsHot() bool { return k == Hot }

func classify(v any) string {
	switch v.(type) {
	case Meters:
		return "Meters"
	case Feet:
		return "Feet"
	case int:
		return "int"
	default:
		return "other"
	}
}

func testDistinctTypes() {
	m := Meters(7)
	f := Feet(m) // conversion between two defined types
	fmt.Println(m.Describe(), f.Describe(), m, f)

	fmt.Println(classify(m), classify(f), classify(7), classify(7.5))
}

func testArithmetic() {
	m := Meters(7)
	fmt.Println(m+1, 2*m, m/2, m%4, -m)

	m += 3
	m <<= 1
	m |= 1
	m++
	fmt.Println(m)

	fmt.Println(m > 20, m == 22, Meters(3) < m)
}

func testWraparound() {
	l := Level(250)
	l += 10
	fmt.Println(l)
	fmt.Println(l - 5) // 4 - 5 wraps around to 255
}

func testFloat() {
	c := Celsius(100)
	fmt.Println(c/4, c+Celsius(0.5), float64(c)*2)

	var half Celsius = 0.5
	fmt.Println(half, half+Celsius(0.25))
}

func testIotaKinds() {
	fmt.Println(Cold, Warm, Hot)
	fmt.Println(Hot > Warm, Kind(2) == Hot, Warm.IsHot(), Hot.IsHot())

	names := [3]string{"cold", "warm", "hot"}
	fmt.Println(names[Warm], names[Hot])

	temps := map[Kind]string{Cold: "brr", Hot: "ouch"}
	fmt.Println(temps[Hot], temps[Warm] == "", len(temps))
}

// Needs the constant to be usable in a constant expression (constexpr).
func testConstLength() {
	var grid [Size]int
	grid[Size-1] = 5
	fmt.Println(len(grid), grid)
}

func main() {
	fmt.Printf("Type: %T Value: %v\n", ToBe, ToBe)
	fmt.Printf("Type: %T Value: %v\n", MaxInt, MaxInt)
	fmt.Printf("Type: %T Value: %v\n", z, z)

	testDistinctTypes()
	testArithmetic()
	testWraparound()
	testFloat()
	testIotaKinds()
	testConstLength()
}
