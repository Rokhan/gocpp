// +build OMIT

package main

import "fmt"

func main() {
	sum := 0
	for i := 0; i < 10; i++ {
		if i%2 == 0 {
			continue
		}
		sum += i
	}
	fmt.Println(sum)

	sum = 0
	for i := 0; i < 10; i++ {
		if i == 5 {
			break
		}
		sum += i
	}
	fmt.Println(sum)
}
