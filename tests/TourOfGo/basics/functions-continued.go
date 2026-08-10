//go:build OMIT
// +build OMIT

package main

import (
	"fmt"
	"unsafe"
)

func add(x, y int) int {
	return x + y
}

// Small non-regression test for name scoping.
// Check that the "Pointer" declaration doesn't create confusion with the "Pointer" type.
func toto1(x, y int) unsafe.Pointer {
	return nil
}

var Pointer *int = nil

func toto2(x, y int) unsafe.Pointer {
	return unsafe.Pointer(Pointer)
}

func main() {
	fmt.Println(add(42, 13))
}

// Nonreg: there is an ambiguity in identifier dependency tracking code
// and declaration of this type was creating an infinite loop in topoSort
// (Formater depending on Formater).
func Formatter(ctx ...fmt.Formatter) {
}
