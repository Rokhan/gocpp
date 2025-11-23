package main

import (
	"fmt"
	"math"
)

func main() {
	var x, y int = 3, 4
	var f float64 = math.Sqrt(float64(x*x + y*y))
	var z uint = uint(f)
	fmt.Println(x, y, z)

	var r = rune('$')
	fmt.Println(r)

	var s1 = "Hello Word"[5:]
	fmt.Println(s1)

	var s2 = "Hello Word"
	fmt.Println(s2[5:])
}
