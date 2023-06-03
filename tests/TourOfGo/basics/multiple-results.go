// +build OMIT

package main

import "fmt"

func swap(x, y string) (string, string) {
	return y, x
}

func main() {
	a, b := swap("hello", "world")
	s, i, f := "str", 5, 3.14159
	fmt.Println(a, b)
	fmt.Println(s, i, f)
}
