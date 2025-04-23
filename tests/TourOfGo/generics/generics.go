//go:build OMIT
// +build OMIT

package main

import (
	"fmt"
)

// PrimeRK is the prime base used in Rabin-Karp algorithm.
const PrimeRK = 16777619

// HashStr returns the hash and the appropriate multiplicative
// factor for use in Rabin-Karp algorithm.
func HashStr[T string | []byte](sep T) (uint32, uint32) {
	hash := uint32(0)
	for i := 0; i < len(sep); i++ {
		hash = hash*PrimeRK + uint32(sep[i])
	}
	var pow, sq uint32 = 1, PrimeRK
	for i := len(sep); i > 0; i >>= 1 {
		if i&1 != 0 {
			pow *= sq
		}
		sq *= sq
	}
	return hash, pow
}

type Wrapper[T any] struct {
	value T
}

func (p *Wrapper[T]) Get() T {
	return p.value
}

// from cmp/cmp.go
func Or[T comparable](vals ...T) T {
	var zero T
	for _, val := range vals {
		if val != zero {
			return val
		}
	}
	return zero
}

func Dummy[T comparable](dummy string, vals ...T) T {
	var zero T
	for _, val := range vals {
		if val != zero {
			return val
		}
	}
	return zero
}

func Zero[T comparable]() T {
	var zero T
	return zero
}

func main() {
	h1, h2 := HashStr("toto")
	fmt.Printf("Hash: %v, %v\n", h1, h2)

	h3, h4 := HashStr([]byte{1, 2, 3})
	fmt.Printf("Hash: %v, %v\n", h3, h4)

	o1 := Or(1, 2, 3, 4, 5)
	o2 := Or(0, 1, 2, 2, 3, 0, 0)
	fmt.Printf("o1: %v, o2:%v\n", o1, o2)

	fmt.Printf("Zero: %v\n", Zero[int]())
}
