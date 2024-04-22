//go:build ignore || OMIT
// +build ignore OMIT

package main

import (
	"fmt"

	"golang.org/x/tour/tree"
)

// Walk walks the tree t sending all values
// from the tree to the channel ch.
func Walk(t *tree.Tree, ch chan int) {
	panic("Not implemented")
}

// Same determines whether the trees
// t1 and t2 contain the same values.
func Same(t1, t2 *tree.Tree) bool {
	panic("Not implemented")
}

func main() {
	var tree tree.Tree
	fmt.Printf("%T", tree)
}
