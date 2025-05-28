//go:build OMIT
// +build OMIT

package main

import "fmt"

func add(x int, y int) int {
	return x + y
}

func main() {
	fmt.Println(add(42, 13))

	// predefined functions
	fmt.Println(max(42, 13, 17))
	fmt.Println(max(42, 51.12345, 17))
	fmt.Println(min(42, 13, 17))
}
