//go:build OMIT
// +build OMIT

package main

import "fmt"

func fibonacci(c, quit chan int) {
	x, y := 0, 1
	for {
		select {
		case c <- x:
			x, y = y, x+y
		case <-quit:
			fmt.Println("quit")
			return
		}
	}
}

func sum(input chan int, quit chan int) {
	result := 0
	for {
		select {
		case elt := <-input:
			result += elt
		case <-quit:
			fmt.Println("sum =", result)
			return
		}
	}
}

// from src\runtime\trace2.go:967:3
func testInlinedType() {
	var wakeup chan struct{}

	select {
	case wakeup <- struct{}{}:
	default:
	}
}

func main() {
	c := make(chan int)
	quit := make(chan int)
	go func() {
		for i := 0; i < 10; i++ {
			fmt.Println(<-c)
		}
		quit <- 0
	}()
	fibonacci(c, quit)

	inputs := make(chan int)
	go func() {
		for i := 0; i < 10; i++ {
			inputs <- i
		}
		quit <- 0
	}()
	sum(inputs, quit)
}
