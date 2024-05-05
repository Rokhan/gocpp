//go:build OMIT
// +build OMIT

package main

import "fmt"

var c, python, java bool
var ii, jj, kk int = 3, 4, 5

func main() {
	var i int
	fmt.Println(i, c, python, java)
	fmt.Println(ii, jj, kk)

	ii, jj, kk = 6, 7, 8
	fmt.Println(ii, jj, kk)

	ii, zz, kk := 9, 10, 11
	fmt.Println(ii, zz, kk)

	{
		ii, zz, ll := 12, 13, 14
		fmt.Println(ii, zz, ll)
	}
	fmt.Println(ii, zz, kk)

	if true {
		ii, zz, ll := 15, 16, 17
		fmt.Println(ii, zz, ll)
	}
	fmt.Println(ii, zz, kk)
}
