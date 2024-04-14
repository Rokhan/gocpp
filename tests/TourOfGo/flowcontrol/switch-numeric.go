//go:build ignore || OMIT || no-diff
// +build ignore OMIT

package main

import (
	"fmt"
	"time"
)

func main() {
	fmt.Print("Roman Time")
	hour := 1 + (time.Now().Hour() % 12)
	switch hour {
	case 1:
		fmt.Println("I")
	case 2:
		fmt.Println("II")
	case 3:
		fmt.Println("III")
	case 4:
		fmt.Println("IV")
	case 5:
		fmt.Println("V")
	case 6:
		fmt.Println("VI")
	case 7:
		fmt.Println("VII")
	case 8:
		fmt.Println("VIII")
	case 9:
		fmt.Println("IX")
	case 10:
		fmt.Println("X")
	case 11:
		fmt.Println("XI")
	case 12:
		fmt.Println("XII")
	default:
		panic("Should not happen")
	}
}
