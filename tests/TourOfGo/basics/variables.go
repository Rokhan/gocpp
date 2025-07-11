//go:build OMIT
// +build OMIT

package main

import "fmt"

var c, python, java bool
var ii, jj, kk int = 3, 4, 5

type pos struct {
	x, y int
}

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
	withNamedResults()
	inlineAssign(99)
}

func withNamedResults() (i int, s string) {
	i = 3
	s = "hello"
	p := pos{x: 1, y: 2}
	{
		j := i
		i := 10 + i
		x := p.x
		p := p.y
		k := i
		s := "world"
		fmt.Println("withNamedResults:", i, s, j, k, x, p)
	}
	fmt.Println("withNamedResults:", i, s)
	return
}

func inlineAssign(i int) {
	if i, ok1 := 1, true; ok1 {
		fmt.Println("inlineAssign:", i)
	}
	fmt.Println("inlineAssign:", i)

	if i, ok2 := 2, true; ok2 {
		fmt.Println("inlineAssign:", i)
	}
	fmt.Println("inlineAssign:", i)

	if i, ok2 := 22, true; ok2 {
		fmt.Println("inlineAssign:", i)
	}

	{
		if i, ok1 := 3, true; ok1 {
			fmt.Println("inlineAssign:", i)
		}
		fmt.Println("inlineAssign:", i)
	}
	fmt.Println("inlineAssign:", i)

	{
		i := 66
		if i, ok1 := 4, true; ok1 {
			fmt.Println("inlineAssign:", i)
		}
		fmt.Println("inlineAssign:", i)
	}
	fmt.Println("inlineAssign:", i)
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
