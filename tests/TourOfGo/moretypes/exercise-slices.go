//go:build ignore || OMIT
// +build ignore OMIT

package main

import "golang.org/x/tour/pic"

func Pic(dx, dy int) [][]uint8 {
	result := make([][]uint8, dx)

	for i := 0; i < dx; i++ {
		result[i] = make([]uint8, dy)
		for j := 0; j < dy; j++ {
			result[i][j] = uint8((i/2 + j/2) * (i/2 - j/2))
		}
	}

	return result
}

func main() {
	pic.Show(Pic)
}
