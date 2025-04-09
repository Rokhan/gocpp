//go:build OMIT
// +build OMIT

package main

import "fmt"

var i, j int = 1, 2

func locabs() (name string, offset int, abs uint64) {
	return "UTC", 0, 0
}

func main() {
	var c, python, java = true, false, "no!"
	fmt.Println(i, j, c, python, java)

	var name, offset, abs = locabs()
	fmt.Println(name, offset, abs)
}
