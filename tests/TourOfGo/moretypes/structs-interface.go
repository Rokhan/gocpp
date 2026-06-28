//go:build OMIT
// +build OMIT

package main

import (
	"fmt"
)

// Small example extracted from io/io.go
type Reader interface {
	Read() int
}

type WriterTo interface {
	WriteTo() int
}

type Closer interface {
	Close() string
}

type ReadCloser interface {
	Reader
	Closer
}

// NopCloser returns a [ReadCloser] with a no-op Close method wrapping
// the provided [Reader] r.
// If r implements [WriterTo], the returned [ReadCloser] will implement [WriterTo]
// by forwarding calls to r.
func NopCloser(r Reader) ReadCloser {
	if _, ok := r.(WriterTo); ok {
		return &nopCloserWriterTo{r}
	}
	return &nopCloser{r}
}

// TODO: Check why this version crash
// func NopCloser(r Reader) ReadCloser {
// 	if _, ok := r.(WriterTo); ok {
// 		return nopCloserWriterTo{r}
// 	}
// 	return nopCloser{r}
// }

type nopCloser struct {
	Reader
}

func (nopCloser) Close() string { return "nopCloser.Close" }

type nopCloserWriterTo struct {
	Reader
}

func (nopCloserWriterTo) Close() string { return "nopCloserWriterTo.Close" }

func (c nopCloserWriterTo) WriteTo() int {
	return c.Reader.(WriterTo).WriteTo()
}

// --- Test helper types ---

// myReader implements only Reader.
type myReader struct {
	val int
}

func (r myReader) Read() int { return r.val }

// myReaderWriterTo implements both Reader and WriterTo.
type myReaderWriterTo struct {
	val int
}

func (r myReaderWriterTo) Read() int    { return r.val }
func (r myReaderWriterTo) WriteTo() int { return r.val * 2 }

func testCloser() {
	// Case 1: r implements only Reader -> should return nopCloser{r}

	r1 := myReader{val: 1}
	c1 := NopCloser(r1)
	_, isWriterTo1 := c1.(WriterTo)
	fmt.Println("case1 implements WriterTo:", isWriterTo1)
	fmt.Println("case1 Read():", c1.Read())
	fmt.Println("case1 Close():", c1.Close())

	// Case 2: r implements Reader and WriterTo -> should return nopCloserWriterTo{r}
	r2 := myReaderWriterTo{val: 5}
	c2 := NopCloser(r2)
	wt2, isWriterTo2 := c2.(WriterTo)
	fmt.Println("case2 implements WriterTo:", isWriterTo2)
	fmt.Println("case2 Read():", c2.Read())
	fmt.Println("case2 Close():", c2.Close())
	if isWriterTo2 {
		fmt.Println("case2 WriteTo():", wt2.WriteTo())
	}

	// Case 3: r passed as a static Reader interface (only Reader, no WriterTo)
	var r3 Reader = myReader{val: 0}
	c3 := NopCloser(r3)
	_, isWriterTo3 := c3.(WriterTo)
	fmt.Println("case3 implements WriterTo:", isWriterTo3)
	fmt.Println("case3 Read():", c3.Read())

	// Case 4: double-wrapping NopCloser(NopCloser(r)) where inner has WriterTo.
	// The outer nopCloser wraps a ReadCloser; since the inner concrete type
	// (nopCloserWriterTo) implements WriterTo, the outer wrapper should
	// also be detected as implementing WriterTo via forwarding.
	inner := NopCloser(myReaderWriterTo{val: 7})
	outer := NopCloser(inner)
	wt4, isWriterTo4 := outer.(WriterTo)
	fmt.Println("case4 implements WriterTo:", isWriterTo4)
	if isWriterTo4 {
		fmt.Println("case4 WriteTo():", wt4.WriteTo())
	}
	fmt.Println("case4 Read():", outer.Read())
	fmt.Println("case4 Close():", outer.Close())

	// Case 5: double-wrapping where inner does NOT implement WriterTo
	inner2 := NopCloser(myReader{val: 9})
	outer2 := NopCloser(inner2)
	_, isWriterTo5 := outer2.(WriterTo)
	fmt.Println("case5 implements WriterTo:", isWriterTo5)
	fmt.Println("case5 Read():", outer2.Read())
	fmt.Println("case5 Close():", outer2.Close())
}

func main() {

	testCloser()
}
