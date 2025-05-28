//go:build OMIT
// +build OMIT

package main

import "fmt"

func main() {
	primes0 := [6]int{2, 3, 5, 7, 11, 13}

	var s []int = primes0[1:4]
	fmt.Println(s)

	primes1 := []int{2, 3, 5, 7, 11, 13}
	primes2 := []int{17, 19, 23}
	primes3 := []int{29, 31, 37}
	fmt.Println(primes1)
	fmt.Println(primes2)

	copy(primes2, primes1)
	fmt.Println(primes2)

	copy(primes1, primes3)
	fmt.Println(primes1)

	primes4 := primes0[:]
	fmt.Println(primes4)
}
