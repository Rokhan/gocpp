//go:build OMIT
// +build OMIT

package main

import (
	"fmt"
)

func main() {
	fmt.Println(fetcher["https://golang.org/"].body)
	for _, url := range fetcher["https://golang.org/"].urls {
		fmt.Println(" -> ", url)
	}

	fmt.Print("Small primes:")
	for _, prime := range smallPrimes {
		fmt.Printf(" %v", prime)
	}
	fmt.Println()
}

type ints []int

var smallPrimes = ints{2, 3, 5, 7, 11, 13, 17, 19, 23, 29}

// fakeFetcher is Fetcher that returns canned results.
type fakeFetcher map[string]*fakeResult

type fakeResult struct {
	body string
	urls []string
}

var fetcher = fakeFetcher{
	"https://golang.org/": &fakeResult{
		"The Go Programming Language",
		[]string{
			"https://golang.org/pkg/",
			"https://golang.org/cmd/",
		},
	},
	"https://golang.org/pkg/": &fakeResult{
		"Packages",
		[]string{
			"https://golang.org/",
			"https://golang.org/cmd/",
			"https://golang.org/pkg/fmt/",
			"https://golang.org/pkg/os/",
		},
	},
	"https://golang.org/pkg/fmt/": &fakeResult{
		"Package fmt",
		[]string{
			"https://golang.org/",
			"https://golang.org/pkg/",
		},
	},
	"https://golang.org/pkg/os/": &fakeResult{
		"Package os",
		[]string{
			"https://golang.org/",
			"https://golang.org/pkg/",
		},
	},
}
