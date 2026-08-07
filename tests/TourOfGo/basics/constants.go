//go:build OMIT
// +build OMIT

package main

import "fmt"

const Pi = 3.14

func main() {
	const World = "世界"
	fmt.Println("Hello", World)
	fmt.Println("Happy", Pi, "Day")

	fmt.Println(`
    "Tyger, Tyger, burning bright
    In the forests of the night,
    What immortal hand or eye
    Could frame thy fearful symmetry?"`)
	fmt.Println()

	fmt.Println(`\t\n\0"`)

	const Truth = true
	fmt.Println("Go rules?", Truth)
}
