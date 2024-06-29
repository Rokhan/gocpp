package main

import (
	"fmt"
	"image/color"
)

type Zzz = color.Color

func main() {
	fmt.Printf("Hello, world.\n")
	var hello = "Hello"
	var world = "World"
	helloFunc(hello, world, "!")
	//time.Sleep(100 * time.Millisecond)

	type Yyy = color.Color
	var _ Yyy

	var a = 5
	var b = 8 + 7
	fmt.Printf("result = %d\n", a*b+4)
	fmt.Printf("\n")
	printN("zzz1", square(3))
	var n = square(2)
	printN("zzz2", n)
}

func square(num int) int {
	return num * num
}

func helloFunc(str1 string, str2 string, str3 string) {
	fmt.Printf(str1 + ", " + str2 + str3)
}

func printN(str1 string, n int) {
	fmt.Printf(str1+"%d\n", n)
}
