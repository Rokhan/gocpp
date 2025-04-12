package main

import "fmt"

func main() {
	f()
	fmt.Println("Returned normally from f.")

	// As it's not called in a defer statement, r should always be nil.
	if r := recover(); r != nil {
		fmt.Println("R should always be nil, r =", r)
	}
}

func f() {
	defer func() {
		if r := recover(); r != nil {
			fmt.Println("Recovered in f", r)
		}
	}()

	defer func() {
		fmt.Println("Simple defer in f")
	}()

	fmt.Println("Calling g.")
	g(0)
	fmt.Println("Returned normally from g.")
}

func g(i int) {
	defer fmt.Println("Defer1 in g", i)
	if i > 3 {
		fmt.Println("Panicking!")
		panic(fmt.Sprint(i))
	}
	defer fmt.Println("Defer2 in g", i)
	fmt.Println("Printing in g", i)
	g(i + 1)
}
