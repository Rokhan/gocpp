//go:build OMIT
// +build OMIT

package main

import "fmt"

func do(i interface{}) {
	switch v := i.(type) {
	case int:
		fmt.Printf("Twice %v is %v\n", v, v*2)
	case string:
		fmt.Printf("%q is %v bytes long\n", v, len(v))
	default:
		fmt.Printf("I don't know about type %T!\n", v)
	}
}

func do_withoutname(i interface{}) {
	switch i.(type) {
	case int:
		fmt.Println("int")
	case string:
		fmt.Println("string")
	default:
		fmt.Println("unknown")
	}
}

func do_WithNameReused(v interface{}) {
	switch v := v.(type) {
	case int:
		fmt.Printf("Twice %v is %v\n", v, v*2)
	case string:
		fmt.Printf("%q is %v bytes long\n", v, len(v))
	default:
		fmt.Printf("I don't know about type %T!\n", v)
	}
}

func main() {
	do(21)
	do("hello")
	do(true)

	fmt.Println("\n----")
	do_withoutname(21)
	do_withoutname("hello")
	do_withoutname(true)

	fmt.Println("\n----")
	do_WithNameReused(21)
	do_WithNameReused("hello")
	do_WithNameReused(true)
}
