//go:build ignore || OMIT
// +build ignore OMIT

package main

import (
	"image"
	"image/color"

	"golang.org/x/tour/pic"
)

type Image struct{}

func (Image) ColorModel() color.Model {
	panic("not implemented")
}

func (Image) Bounds() image.Rectangle {
	panic("not implemented")
}

func (Image) At(x, y int) color.Color {
	panic("not implemented")
}

func main() {
	m := Image{}
	pic.ShowImage(m)
}
