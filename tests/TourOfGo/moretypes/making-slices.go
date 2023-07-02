// +build OMIT

package main

import "fmt"

func main() {
	a := make([]int, 5)
	printSlice("a", a)

	b := make([]int, 0, 5)
	printSlice("b", b)

	bc := b[:2]
	printSlice("bc", bc)

	bd := b[2:5]
	printSlice("bd", bd)

	ac := a[:2]
	printSlice("bc", ac)

	ad := a[2:5]
	printSlice("bd", ad)
}

func printSlice(s string, x []int) {
	// fmt.Printf("%s len=%d cap=%d %v\n", s, len(x), cap(x), x)
	fmt.Printf("%v len=%v cap=%v %v\n", s, len(x), cap(x), x)
}
