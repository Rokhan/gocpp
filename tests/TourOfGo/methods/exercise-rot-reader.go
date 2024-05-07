//go:build ignore || OMIT
// +build ignore OMIT

package main

import (
	"io"
	"os"
	"strings"
)

type rot13Reader struct {
	r io.Reader
}

func (r13 rot13Reader) Read(buf []byte) (int, error) {
	n, err := r13.r.Read(buf)
	if err != nil {
		return n, err
	}

	for i := 0; i < n; i++ {
		buf[i] += 13
	}

	return n, nil
}

func main() {
	s := strings.NewReader("Lbh penpxrq gur pbqr!")
	r := rot13Reader{s}
	io.Copy(os.Stdout, &r)
}
