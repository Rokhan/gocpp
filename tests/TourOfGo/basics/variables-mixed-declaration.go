//go:build OMIT
// +build OMIT

package main

import "fmt"

func f1() (string, int, []string)  { return "f1", 1001, []string{"a", "b"} }
func f2() (string, int, [3]string) { return "f2", 1002, [3]string{"c", "d", "e"} }

func main() {
	s1, i1 := "string1", 1
	fmt.Println(s1, i1)

	s1, i2 := "string2", 2
	fmt.Println(s1, i2)

	s2, i2 := "string3", 3
	fmt.Println(s2, i2)

	s2, i2 = "string4", 4
	fmt.Println(s2, i2)

	s2, i2, a1 := f1()
	fmt.Println(s2, i2, a1)

	s2, i2, a2 := f2()
	fmt.Println(s2, i2, a2)
}
