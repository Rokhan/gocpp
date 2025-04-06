//go:build OMIT
// +build OMIT

package main

import (
	"fmt"
	"unsafe"
)

func main() {

	// declarartion and cast extracted from reflect/value.go, line 1230
	var eface any
	var ptr unsafe.Pointer = unsafe.Pointer(&eface)

	eface = *(*any)(ptr)

	fmt.Println(eface)

	eface = (any)(*(*interface {
		M()
	})(ptr))

	fmt.Println(eface)
}
