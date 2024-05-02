//go:build OMIT
// +build OMIT

package main

import (
	"fmt"
	"time"
)

func fill(c chan int) {
	for {
		time.Sleep(5 * time.Millisecond)
		c <- 0
	}
}

func main() {
	c := make(chan int, 5)

	go fill(c)

	// optional result with double declaration
	xx, ok := <-c
	fmt.Println(xx, ok)

	// optional result with single declaration (2 forms)
	zz, ok := <-c
	fmt.Println(zz, ok)

	close(c)

	// optional result with single declaration (2 forms)
	zz, okok := <-c
	fmt.Println(zz, okok)
}
