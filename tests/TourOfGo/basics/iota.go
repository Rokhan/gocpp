//go:build OMIT
// +build OMIT

package main

import "fmt"

/* some examples from https://stackoverflow.com/a/14426447/10016 */

const ( // iota is reset to 0
	c0 = iota // c0 == 0
	c1 = iota // c1 == 1
	c2 = iota // c2 == 2
	c3        // c3 == 3
	c4        // c4 == 4
	c5        // c5 == 5
)

type Kind uint

const (
	Invalid Kind = iota
	Bool
	Int
	Int8
)

const (
	a = 1 << iota // a == 1 (iota has been reset)
	b = 1 << iota // b == 2
	c = 1 << iota // c == 4
)

const (
	z0 = 0
	za = 1 << iota // a == 1 (iota has been reset)
	zb = 1 << iota // b == 2
	zc = 1 << iota // c == 4
)

const (
	u         = iota * 42 // u == 0     (untyped integer constant)
	v float64 = iota * 42 // v == 42.0  (float64 constant)
	w         = iota * 42 // w == 84    (untyped integer constant)
)

const x = iota // x == 0 (iota has been reset)
const y = iota // y == 0 (iota has been reset)

const (
	bit0, mask0 = 1 << iota, 1<<iota - 1 // bit0 == 1, mask0 == 0
	bit1, mask1                          // bit1 == 2, mask1 == 1
	_, _                                 // skips iota == 2
	bit3, mask3                          // bit3 == 8, mask3 == 7
)

func main() {
	fmt.Printf("%v %v %v // %v %v %v\n", c0, c1, c2, c3, c4, c5)
	fmt.Printf("%v %v %v\n", a, b, c)
	fmt.Printf("%v %v %v %v\n", z0, za, zb, zc)
	fmt.Printf("%v %v %v\n", u, v, w)
	fmt.Printf("%v %v\n", x, y)
	fmt.Printf("%v %v %v\n", bit0, bit1, bit3)
	fmt.Printf("%v %v %v\n", mask0, mask1, mask3)
}
