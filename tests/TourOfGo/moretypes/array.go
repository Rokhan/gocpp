//go:build OMIT
// +build OMIT

package main

import "fmt"

// Array of struct
type semTable1 [10]struct {
	value int
}

const ten int = 10

type semTable2 [ten]struct {
	value int
}

func main() {
	var a [2]string
	a[0] = "Hello"
	a[1] = "World"
	fmt.Println(a[0], a[1])
	fmt.Println(a)

	primes := [6]int{2, 3, 5, 7, 11, 13}
	fmt.Println(primes)

	var ints = [...]int{1, 2, 3}
	fmt.Println(ints)

	var st1 = semTable1{{1}, {1}}
	fmt.Println(st1)

	var st2 = semTable2{{1}, {1}}
	fmt.Println(st2)

	chars := [5]byte{'H', 'e', 'l', 'l', 'o'}
	fmt.Println(chars)

	var hw1 = `Hello, World!`
	var hwBytes1 = []byte(hw1)
	fmt.Println(hwBytes1)

	var hw2 = "Hello, World!"
	var hwBytes2 = []byte(hw2)
	fmt.Println(hwBytes2)
}
