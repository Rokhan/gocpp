//go:build OMIT
// +build OMIT

package main

import (
	"fmt"
	"strings"

	"golang.org/x/tour/wc"
)

func WordCount(s string) map[string]int {
	fields := strings.Fields(s)
	wc := make(map[string]int)

	for _, f := range fields {
		wc[f]++
	}
	return wc
}

func testWordCount() {
	empty := WordCount("")
	fmt.Println(empty == nil, len(empty), empty) // non-nil, empty

	r := WordCount("a b a c a")
	fmt.Println(r, len(r))
	fmt.Println(r["absent"], len(r)) // lookup must not add a key

	// each call returns an independent map
	r2 := WordCount("a")
	r2["a"] = 100
	fmt.Println(r["a"], r2["a"])
}

func main() {
	wc.Test(WordCount)
	testWordCount()
}
