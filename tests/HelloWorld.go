package main

import (
	"fmt"
	//"time"
)

func main() {
	fmt.Printf("Hello, world.\n")
	helloFunc("Hello", "world")
	//time.Sleep(100 * time.Millisecond)
}

func helloFunc(str1 string, str2 string) {
	fmt.Printf(str1 + ", " + str2 + ".\n")
}
