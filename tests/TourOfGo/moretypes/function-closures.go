//go:build OMIT
// +build OMIT

package main

import (
	"fmt"
	"unicode"
)

func adder() func(int) int {
	sum := 0
	return func(x int) int {
		sum += x
		return sum
	}
}

func Map(mapping func(r rune) rune, s []byte) []byte {
	b := make([]byte, 0, len(s))
	// Do nothing, we just need the prototype of mapping function for the test
	return b
}

type SpecialCase []unicode.CaseRange

func ToUpper(r rune) rune {
	// Do nothing, we just need the prototype of ToUpper function for the test
	return r
}

func (special SpecialCase) ToUpper(r rune) rune {
	// Do nothing, we just need the prototype of ToUpper function for the test
	return r
}

func TestLambda0(c SpecialCase, s []byte) []byte {
	return Map(ToUpper, s)
}

func TestLambda1(c SpecialCase, s []byte) []byte {
	return Map(c.ToUpper, s)
}

func TestLambda2(x SpecialCase, y []byte) []byte {
	return Map(x.ToUpper, y)
}

// TODO, add this test when linking with generated stdlib works
// // func TestLambda4(c SpecialCase, s []byte) []byte {
// // 	return Map(unicode.ToUpper, s)
// // }

type compressor struct {
	bulkHasher func([]byte, []uint32)
	fill       func(*compressor, []byte) int // copy data to window
	step       func(*compressor)             // process window
}

func (d *compressor) fillStore(b []byte) int {
	fmt.Println("fillStore called")
	return 0
}

func (d *compressor) store() {}

func (d *compressor) init() (err error) {
	d.fill = (*compressor).fillStore
	d.step = (*compressor).store
	return nil
}

func (d *compressor) write(b []byte) (n int, err error) {
	i := d.fill(d, b)
	return i, nil
}

func main() {
	pos, neg := adder(), adder()
	for i := 0; i < 10; i++ {
		fmt.Println(
			pos(i),
			neg(-2*i),
		)
	}

	writer := &compressor{}
	writer.init()
	writer.write([]byte("Hello, World!"))
}
