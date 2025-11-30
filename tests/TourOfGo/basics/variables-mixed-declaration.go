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

	_, i3 := "string2A", 2
	fmt.Println("_", i3)

	s3, _ := "string3B", 3
	fmt.Println(s3, "_")

	_, i3, b1 := "string2C", 2, true
	fmt.Println("_", i3, b1)

	s3, _, b2 := "string3D", 3, true
	fmt.Println(s3, "_", b2)

	s2, i2 = "string4", 4
	fmt.Println(s2, i2)

	_, i2 = "string5", 4
	fmt.Println("_", i2)

	s2, _ = "string6", 4
	fmt.Println(s2, "_")

	s2, i2, a1 := f1()
	fmt.Println(s2, i2, a1)

	s2, i2, a2 := f2()
	fmt.Println(s2, i2, a2)
}
