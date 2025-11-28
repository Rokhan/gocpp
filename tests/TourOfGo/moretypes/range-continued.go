//go:build OMIT
// +build OMIT

package main

import "fmt"

func main() {
	pow := make([]int, 10)
	for i := range pow {
		pow[i] = 1 << uint(i) // == 2**i
	}
	for _, value := range pow {
		//fmt.Printf("%d\n", value)
		fmt.Printf("%v\n", value)
	}

	// assignment versions
	value := 0
	for _, value = range pow {
		fmt.Printf("%v\n", value)
	}
	i := 0
	for i = range pow {
		fmt.Printf("%v\n", pow[i])
	}
	for i, _ = range pow {
		fmt.Printf("%v\n", pow[i])
	}

	// strings are range
	for _, char := range "hello" {
		fmt.Printf("%v\n", char)
	}
}
