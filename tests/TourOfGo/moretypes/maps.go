//go:build OMIT
// +build OMIT

package main

import "fmt"

type Vertex struct {
	Lat, Long float64
}

var m map[string]Vertex

func main() {
	m = make(map[string]Vertex)
	m["Bell Labs"] = Vertex{
		40.68433, -74.39967,
	}
	fmt.Println(m["Bell Labs"])

	clear(m)
	fmt.Println(m["Bell Labs"])

	testNil()
	testNotNil()
	testAliasing()
	testNamedAndEmptyStruct()
	testNilWritePanic()
	testNilFieldWritePanic()
}

type Set map[string]struct{}

type Registry struct {
	name  string
	items map[string]int
}

func testNil() {
	var nm map[string]int
	fmt.Println(nm == nil, nm != nil, len(nm), nm)
	fmt.Println(nm["x"])
	v, ok := nm["x"]
	fmt.Println(v, ok)
	for k, v := range nm {
		fmt.Println("unreachable", k, v)
	}
	delete(nm, "x")
	clear(nm)
	fmt.Println(len(nm), nm == nil)
}

func testNotNil() {
	made := make(map[string]int)
	lit := map[string]int{}
	full := map[string]int{"a": 1}
	fmt.Println(made == nil, lit == nil, full == nil)

	clear(full)
	fmt.Println(full == nil, len(full)) // clear does not make it nil

	full = nil
	fmt.Println(full == nil, len(full))
}

func fill(m map[string]int) { m["filled"] = 1 }

func testAliasing() {
	a := make(map[string]int)
	b := a
	b["k"] = 1
	fmt.Println(a, b, len(a))

	fill(a)
	fmt.Println(b)

	f := func() { a["closure"] = 2 }
	f()
	fmt.Println(b)

	b = nil // rebinds b only
	fmt.Println(a, b == nil, a == nil)

	r1 := Registry{name: "r1"}
	fmt.Println(r1.items == nil)
	r1.items = make(map[string]int)
	r2 := r1 // struct copy shares the map
	r2.items["x"] = 1
	fmt.Println(r1.items, r2.items)
}

// Same shape as context.removeChild
func removeChild(children map[string]struct{}, key string) {
	if children != nil {
		delete(children, key)
	}
}

func testNamedAndEmptyStruct() {
	var s Set
	fmt.Println(s == nil, len(s))
	removeChild(s, "a")

	s = make(Set)
	s["a"] = struct{}{}
	s2 := s
	s2["b"] = struct{}{}
	fmt.Println(len(s), s != nil)
	removeChild(s, "a")
	fmt.Println(len(s2))
}

func testNilWritePanic() {
	defer func() {
		if r := recover(); r != nil {
			fmt.Println("recovered")
		}
	}()
	var nm map[string]int
	fmt.Println("before")
	nm["x"] = 1
	fmt.Println("not reached")
}

func testNilFieldWritePanic() {
	defer func() {
		if r := recover(); r != nil {
			fmt.Println("recovered (field)")
		}
	}()
	var r Registry
	r.items["x"] = 1
	fmt.Println("not reached")
}
