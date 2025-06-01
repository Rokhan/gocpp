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
		fmt.Println(os)
	}

	// With default first
	fmt.Print("\nGo runs on ")
	switch os := runtime.GOOS; os {
	default:
		fmt.Println(os)
	case "darwin":
		fmt.Println("OS X.")
	case "linux", "gnu/linux", "debian":
		fmt.Println("Linux.")
	}

	// With multiple cases first
	fmt.Print("\nGo runs on ")
	switch os := runtime.GOOS; os {
	case "linux", "gnu/linux", "debian":
		fmt.Println("Linux.")
	default:
		fmt.Println(os)
	case "darwin":
		fmt.Println("OS X.")
	}

	testFallThrough(0)
	testFallThrough(1)
	testFallThrough(2)
	testFallThrough(3)
}
