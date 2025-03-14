//go:build OMIT
// +build OMIT

package main

import "fmt"

var c, python, java bool
var ii, jj, kk int = 3, 4, 5

var funcVar1 = func() {
	fmt.Println("funcVar")
}

var funcVar2 = func(i int) int {
	fmt.Println("funcVar,", i)
	return 3
}

var funcVar3 = func(i int) (int, string) {
	fmt.Println("funcVar,", i)
	return 3, "zz"
}

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

	do, while, template, class := "do", "while", "template", "class"
	fmt.Println(do, while, template, class)

	dummy_vars()
	funcVar1()
	ii = funcVar2(3)

	var s string
	ii, s = funcVar3(3)
	fmt.Println(ii, s)
}

func dummy_vars() {
	var do string = "do"
	var while string = "while"
	var template string = "template"
	var class string = "class"
	fmt.Println(do, while, template, class)
}

func dummy_funcs() {
	do()
	while()
	template()
	class()
}

func do()       {}
func while()    {}
func template() {}
func class()    {}
