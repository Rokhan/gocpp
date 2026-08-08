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
	testSwitchWithLabel1([]int{0, 0, 0})
	testSwitchWithLabel1([]int{-5})
	testSwitchWithLabel1([]int{7})
	testSwitchWithLabel1([]int{7, -2, 0, 5, 0, 0, -9})

	testSwitchWithLabel2(`"hello"`, 1)
	testSwitchWithLabel2(`"true"`, 1)
	testSwitchWithLabel2("true", 1)
	testSwitchWithLabel2("1234567", 1)
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

func testSwitchWithLabel1(items []int) {
	result := ""

Outer:
	for i, item := range items {
	Selector:
		switch {
		case item < 0:
			for j := 0; j < 3; j++ {
				if j == 1 {
					break Selector
				}
				result += fmt.Sprint("neg-scan:", j, " ")
			}
			result += "after-loop;"

		case item == 0:
			for j := 0; j < 3; j++ {
				if j == i%3 {
					continue Outer
				}
				result += fmt.Sprint("zero-scan:", j, " ")
			}
			result += "after-loop;"

		case item > 0:
			result += "pos;"

		default:
			result += "other;"
		}

		result += fmt.Sprint("[", item, "]")
	}

	fmt.Println(result)
}

// switch loop from "encoding/json/decode.go"
func testSwitchWithLabel2(data string, offset int) {
	d, i := data, offset
Switch:
	switch d[i-1] {
	case '"': // string
		for ; i < len(d); i++ {
			switch d[i] {
			case '\\':
				i++ // escaped char
			case '"':
				i++ // tokenize the closing quote too
				break Switch
			}
		}
	case '0', '1', '2', '3', '4', '5', '6', '7', '8', '9', '-': // number
		for ; i < len(d); i++ {
			switch d[i] {
			case '0', '1', '2', '3', '4', '5', '6', '7', '8', '9',
				'.', 'e', 'E', '+', '-':
			default:
				break Switch
			}
		}
	case 't': // true
		i += len("rue")
	case 'f': // false
		i += len("alse")
	case 'n': // null
		i += len("ull")
	}
	fmt.Println(i)
}
