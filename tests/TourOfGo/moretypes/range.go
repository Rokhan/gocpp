//go:build OMIT
// +build OMIT

package main

import "fmt"

var pow = []int{1, 2, 4, 8, 16, 32, 64, 128}

func main() {
	for i, v := range pow {
		//fmt.Printf("2**%d = %d\n", i, v)
		fmt.Printf("2**%v = %v\n", i, v)
	}

	for i := range pow {
		fmt.Printf("%v\n", i)
	}

	for _, v := range pow {
		fmt.Printf("%v\n", v)
	}

	var n int = 0
	for range pow {
		n++
	}

	var i, j = 0, 0 // check conflict with generated loop variable names
	for range 5 {
		fmt.Println("for range 5")
	}
	fmt.Println(i, j)
}
