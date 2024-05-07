//go:build ignore || OMIT
// +build ignore OMIT

package main

import "golang.org/x/tour/reader"

type MyReader struct{}

func (MyReader) Read(buffer []byte) (int, error) {
	buffer = []byte{'A'}
	return 1, nil
}

func main() {
	reader.Validate(MyReader{})
}
