//go:build OMIT
// +build OMIT

package main

import "fmt"

// Array of struct
type semTable1 [10]struct {
	value int
}

const ten int = 10

type semTable2 [ten]struct {
	value int
}

// From bytes/bytes.go, simplified for tests
type asciiSet [8]uint32

func makeASCIISet(chars string) (as asciiSet) {
	for i := 0; i < len(chars); i++ {
		c := chars[i]
		as[c/32] |= 1 << (c % 32)
	}
	return as
}

func makeASCIISetPtr(chars string) (asPtr *asciiSet) {
	as := makeASCIISet(chars)
	return &as
}

func (as *asciiSet) contains(c byte) bool {
	return (as[c/32] & (1 << (c % 32))) != 0
}

func contains(as *[8]uint32, c byte) bool {
	return (as[c/32] & (1 << (c % 32))) != 0
}

func testPtrArray1() {
	var as1 asciiSet
	as1 = makeASCIISet("abc")
	var as2 [8]uint32 = as1
	fmt.Println(as1.contains('a'))
	fmt.Println(contains(&as2, 'a'))
	fmt.Println(as1.contains('z'))
	fmt.Println(contains(&as2, 'z'))

	for i, v := range as2 {
		fmt.Println(i, " -> ", v)
	}
}

var global_as1a = makeASCIISet("abcde")
var global_as1b = makeASCIISet("abcde")
var global_as2 asciiSet = makeASCIISet("12345")

var global_asPtr0 = makeASCIISetPtr("xyz")
var global_asPtr1a = &global_as1a
var global_asPtr1b = &global_as1b
var global_asPtr2 *asciiSet = &global_as2

func testPtrArray2() {
	fmt.Println("simple compare, array:", global_as2 == global_as2)
	fmt.Println("simple compare, array:", global_as2 == global_as1a)
	// Check we really compare content, not just pointer
	fmt.Println("simple compare, array:", global_as1a == global_as1b)
	fmt.Println("simple compare, array ptr:", global_asPtr2 == global_asPtr2)
	// Check we compare pointer, not the content
	fmt.Println("simple compare, array ptr:", global_asPtr1a == global_asPtr1b)
	fmt.Println("compare with ptr:", &global_as2 == global_asPtr2)

	for i, v := range global_as2 {
		fmt.Println(i, " -> ", v)
	}
	for i, v := range global_asPtr2 {
		fmt.Println(i, " -> ", v)
	}
}

func main() {
	var a [2]string
	a[0] = "Hello"
	a[1] = "World"
	fmt.Println(a[0], a[1])
	fmt.Println(a)

	primes := [6]int{2, 3, 5, 7, 11, 13}
	fmt.Println(primes)

	var ints = [...]int{1, 2, 3}
	fmt.Println(ints)

	var st1 = semTable1{{1}, {1}}
	fmt.Println(st1)

	var st2 = semTable2{{1}, {1}}
	fmt.Println(st2)

	chars := [5]byte{'H', 'e', 'l', 'l', 'o'}
	fmt.Println(chars)

	var hw1 = `Hello, World!`
	var hwBytes1 = []byte(hw1)
	fmt.Println(hwBytes1)

	var hw2 = "Hello, World!"
	var hwBytes2 = []byte(hw2)
	fmt.Println(hwBytes2)

	var buf [32]byte
	n := len(buf)
	fmt.Println("Length of buf:", n)

	w := arrayLen(&buf)
	fmt.Println("Length of buf from arrayLen:", w)

	testPtrArray1()
	testPtrArray2()
}

func arrayLen(buf *[32]byte) int {
	w := len(buf)
	return w
}
