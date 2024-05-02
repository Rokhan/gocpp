//go:build OMIT
// +build OMIT

package main

import "fmt"

func main() {
	s1, i1 := "string1", 1
	fmt.Println(s1, i1)

	s1, i2 := "string2", 2
	fmt.Println(s1, i2)

	s2, i2 := "string3", 3
	fmt.Println(s2, i2)

	s2, i2 = "string4", 4
	fmt.Println(s2, i2)
}
