//go:build ignore || OMIT
// +build ignore OMIT

package main

import "fmt"

func main() {
	var value interface{} = "hello"

	s := value.(string)
	fmt.Println(s)

	value = 65.4321
	f := value.(float64)
	fmt.Println(f)

	value = 65
	i := value.(int)
	fmt.Println(i)

	value = true
	b := value.(bool)
	fmt.Println(b)
}
