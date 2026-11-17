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

func testDeclarations(kind int) {
	switch kind {
	case 0:
		var hr, mm, ss int
		hr, mm, ss = 1, 2, 3
		fmt.Println("case 0:", hr, mm, ss)
	case 1:
		var total = 10
		total += kind
		fmt.Println("case 1:", total)
	case 2:
		const factor = 3
		fmt.Println("case 2:", kind*factor)
	case 3:
		var s string
		fmt.Println("case 3:", s == "")
		fallthrough
	case 4:
		hr := 40 // same name as in case 0, each clause has its own scope
		fmt.Println("case 4:", hr)
	default:
		var d int
		fmt.Println("default:", d)
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

	for i := 0; i < 6; i++ {
		testDeclarations(i)
	}
}
