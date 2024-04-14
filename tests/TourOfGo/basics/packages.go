//go:build ignore || OMIT || no-diff
// +build ignore OMIT

package main

import (
	"fmt"
	"math/rand"
)

func main() {
	fmt.Println("My favorite number is", rand.Intn(10))
}
