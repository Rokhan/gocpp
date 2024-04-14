//go:build OMIT
// +build OMIT

package main

import (
	"fmt"
	"time"
)

func say(s string) {
	for i := 0; i < 5; i++ {
		time.Sleep(100 * time.Millisecond)
		fmt.Println(s)
	}
}

func main() {
	go say("world")
	time.Sleep(50 * time.Millisecond)
	say("hello")
}
