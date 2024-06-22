//go:build OMIT
// +build OMIT

package main

import (
	"fmt"
)

func dummy() (string, bool) {
	return "dummyStr", true
}

var okok bool = false

func test_if() {
	if s1, ok := dummy(); ok {
		fmt.Println(s1)
	}

	if s2, ok := dummy(); ok {
		fmt.Println(s2)
	}

	if s3, okok := dummy(); okok {
		fmt.Println(s3)
	}

	fmt.Println(okok)
}

func test_for() {
	for s1, ok := dummy(); ok; {
		fmt.Println(s1)
		break
	}

	for s2, ok := dummy(); ok; {
		fmt.Println(s2)
		break
	}

	for s3, okok := dummy(); okok; {
		fmt.Println(s3)
		break
	}

	fmt.Println(okok)
}

func test_switch() {
	switch s1, ok := dummy(); ok {
	case true:
		fmt.Println(s1)
	default:
		fmt.Println("default")
	}

	switch s2, ok := dummy(); ok {
	case true:
		fmt.Println(s2)
	default:
		fmt.Println("default")
	}

	switch s3, okok := dummy(); okok {
	case true:
		fmt.Println(s3)
	default:
		fmt.Println("default")
	}

	fmt.Println(okok)
}

func main() {
	test_if()
	test_for()
	test_switch()
}
