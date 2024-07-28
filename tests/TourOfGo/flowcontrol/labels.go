//go:build OMIT

package main

import (
	"fmt"
)

func main() {
	testGoTo()

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

func testGoTo() {
	i := 0
label1:
	i++

	if i < 5 {
		fmt.Println("goto label1")
		goto label1
	}

label2:
	if i < 10 {
		i++
		fmt.Println("goto label2")
		goto label2
	}
label3:
	for j := 0; j < 10; j++ {
		i++
		if i < 15 {
			fmt.Printf("goto label3, i = %v, j = %v\n", i, j)
			goto label3
		}

		fmt.Printf("............ i = %v, j = %v\n", i, j)
	}
}
