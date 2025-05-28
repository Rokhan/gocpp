//go:build OMIT
// +build OMIT

package main

import "fmt"

const Pi = 3.14

type titi float64

type toto struct{}

func (t toto) Pi() float64 {
	return 3.14
}

func (t toto) toto() float64 {
	return 0 + 0
}

func (t toto) titi(d titi) titi {
	return d
}

func main() {
	const World = "世界"
	fmt.Println("Hello", World)
	fmt.Println("Happy", Pi, "Day")

	const Truth = true
	fmt.Println("Go rules?", Truth)

	fmt.Println("Pi:", Pi)
	t := toto{}
	fmt.Println("toto.Pi:", t.Pi())

	new := "new"
	fmt.Println("new:", new)

	newFunction()
}

func newFunction() {
	tt := new(toto)
	fmt.Println("tt:", tt)
}
