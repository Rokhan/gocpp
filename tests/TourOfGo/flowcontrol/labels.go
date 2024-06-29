//go:build OMIT
// +build OMIT

package main

import "fmt"

func main() {
	testFor(0)
	testFor(1)
	testFor(2)

	testRange(0)
	testRange(1)
	testRange(2)
}

func testFor(k int) {
loop1:
	for i := 0; i < 3; i++ {
		for j := 0; j < 3; j++ {
			fmt.Println("for", i, j)
			switch k {
			case 1:
				break loop1
			case 2:
				continue loop1
			}
		}
	}
	fmt.Println("end")
	fmt.Println()
}

func testRange(k int) {
loop1:
	for i := range []int{0, 1, 2} {
		for j := range []int{0, 1, 2} {
			fmt.Println("range", i, j)
			switch k {
			case 1:
				break loop1
			case 2:
				continue loop1
			}
		}
	}
	fmt.Println("end")
	fmt.Println()
}
