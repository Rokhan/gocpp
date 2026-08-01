//go:build OMIT
// +build OMIT

package main

import "fmt"

func add(x int, y int) int {
	return x + y
}

func returnMap(x int, y int) map[int]int {
	return map[int]int{x: y}
}

func returnAny(x int, y int) interface{} {
	return x + y
}

func main() {
	fmt.Println(add(42, 13))

	// predefined functions
	fmt.Println(max(42, 13, 17))
	fmt.Println(max(42, 51.12345, 17))
	fmt.Println(min(42, 13, 17))

	fmt.Println(returnMap(1, 2))
	fmt.Println(returnAny(1, 2))
}
