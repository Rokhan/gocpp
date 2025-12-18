//go:build OMIT
// +build OMIT

package main

import (
	"fmt"
	"math"
)

type I interface {
	M()
}

type T struct {
	S string
}

type F float64

func (f F) M() {
	fmt.Println(f)
}

// This method means type T implements the interface I,
// but we don't need to explicitly declare that it does so.
func (t T) M() {
	fmt.Println(t.S)
}

func main() {
	var i I = T{"hello"}
	i.M()

	t := T{"hello"}
	var j I = t
	j.M()

	compare()
}

func compare() {
	var i I

	t1 := &T{"Hello1"}
	t2 := &T{"Hello2"}
	t3 := T{"Hello2"}
	f := F(math.Pi)

	i = t1
	fmt.Println(i == t1) // true
	fmt.Println(i == t2) // false
	fmt.Println(i == t3) // false
	// TODO: enable once interface comparison is supported for non-struct types
	//fmt.Printf("%v\n", i == f) // false

	i = t2
	fmt.Println(i == t1) // false
	fmt.Println(i == t2) // true
	fmt.Println(i == t3) // false
	// TODO: enable once interface comparison is supported for non-struct types
	//fmt.Printf("%v\n", i == f) // false

	i = t3
	fmt.Println(i == t1) // false
	fmt.Println(i == t2) // false
	// TODO: associating T value with interface creates a copy at the moment,
	// so this is false. It shouldn't be the case.
	//fmt.Println(i == t3) // true
	// TODO: enable once interface comparison is supported for non-struct types
	//fmt.Printf("%v\n", i == f) // false

	i = f
	fmt.Println(i == t1) // false
	fmt.Println(i == t2) // false
	fmt.Println(i == t3) // false
	// TODO: enable once interface comparison is supported for non-struct types
	//fmt.Printf("%v\n", i == f) // true
}
