//go:build OMIT
// +build OMIT

package main

import (
	"fmt"
	"runtime"
)

func testFallThrough(n int) {
	switch n {
	case 1:
		fmt.Print("1 ")
		fallthrough
	case 2:
		fmt.Print("2 ")
		fallthrough
	case 3:
		fmt.Print("3 ")
		fallthrough
	default:
		fmt.Printf("Soleil !\n")
	}
}

func main() {
	fmt.Print("Go runs on ")
	switch os := runtime.GOOS; os {
	case "darwin":
		fmt.Println("OS X.")
	case "linux":
		fmt.Println("Linux.")
	default:
		// freebsd, openbsd,
		// plan9, windows...
		fmt.Printf("%s.\n", os)
	}

	testFallThrough(0)
	testFallThrough(1)
	testFallThrough(2)
	testFallThrough(3)
}
