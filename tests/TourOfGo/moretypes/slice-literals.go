//go:build OMIT
// +build OMIT

package main

import "fmt"

var errors = [...]string{
	3: "argument list too long",
	5: "permission denied",
	1: "address already in use",
}

func main() {
	q := []int{2, 3, 5, 7, 11, 13}
	fmt.Println(q)

	r := []bool{true, false, true, true, false, true}
	fmt.Println(r)

	s := []struct {
		i int
		b bool
	}{
		{2, true},
		{3, false},
		{5, true},
		{7, true},
		{11, false},
		{13, true},
	}
	fmt.Println(s)

	for i, err := range errors {
		fmt.Println(i, err)
	}
}
