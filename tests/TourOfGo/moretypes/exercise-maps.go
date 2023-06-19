// +build OMIT

package main

import (
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

func main() {
	wc.Test(WordCount)
}
