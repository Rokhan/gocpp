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

func Dummy1[T comparable](dummy string, vals ...T) T {
	var zero T
	for _, val := range vals {
		if val != zero {
			return val
		}
	}
	return zero
}

func OneOrDefault[T comparable, U comparable](dummy map[T]U) U {
	var zero U
	for _, val := range dummy {
		if val != zero {
			return val
		}
	}
	return zero
}

func RemoveOne[T comparable](dummy chan T) bool {
	_, ok := <-dummy
	return ok
}

func UnusedGenericParameter[T comparable]() int {
	return 3
}

func Zero[T comparable]() T {
	var zero T
	return zero
}

// from slices/slices.go
func Grow[S ~[]E, E any](s S, n int) S {
	if n < 0 {
		panic("cannot be negative")
	}
	if n -= cap(s) - len(s); n > 0 {
		s = append(s[:cap(s)], make([]E, n)...)[:len(s)]
	}
	return s
}

// from sync/atomic/type.go, simplified
type Pointer[T any] struct{}

// from sync/map.go, simplified
type entry struct {
	p Pointer[any]
}

func (x *Pointer[T]) Store(val *T) {}

// from sync/map.go, simplified
func newEntry(i any) *entry {
	e := &entry{}
	e.p.Store(&i)
	return e
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

	fmt.Printf("Unused: %v\n", UnusedGenericParameter[float64]())
	fmt.Printf("OneOrDefault: %v\n", OneOrDefault(map[int]string{1: "toto"}))

	w1 := Wrapper[int]{value: 42}
	w2 := Wrapper[string]{value: "hello"}
	fmt.Printf("Wrapper: %v, %v\n", w1.Get(), w2.Get())

	s1 := []int{1, 2, 3}
	s2 := Grow(s1, 10)
	fmt.Printf("Grow: %v, %v\n", s1, s2)
}
