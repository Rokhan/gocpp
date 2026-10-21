//go:build OMIT
// +build OMIT

package main

import "fmt"

func main() {
	m := make(map[string]int)

	m["Answer"] = 42
	fmt.Println("The value:", m["Answer"])

	m["Answer"] = 48
	fmt.Println("The value:", m["Answer"])

	delete(m, "Answer")
	fmt.Println("The value:", m["Answer"])

	v, ok := m["Answer"]
	fmt.Println("The value:", v, "Present?", ok)

	testReadsDoNotInsert()
	testCompoundOps()
	testCopyAndSwap()
	testAppendIdiom()
	testValueTypes()
	testNested()
	testDeleteDuringRange()
	testNilMutationPanic()
	testCommaOkAssign()
}

func testReadsDoNotInsert() {
	m := map[string]int{"a": 1}
	_ = m["absent"]
	v, ok := m["absent"]
	fmt.Println(v, ok, len(m))
	if m["zzz"] == 0 {
		fmt.Println("zero", len(m))
	}
	if _, ok := m["yyy"]; !ok {
		fmt.Println("missing", len(m), m)
	}
}

func testCompoundOps() {
	m := make(map[string]int)
	m["inc"]++
	m["dec"]--
	m["add"] += 5
	m["sub"] -= 3
	m["or"] |= 4
	m["shl"] <<= 2 // writes a zero, but must still insert the key
	fmt.Println(m, len(m))

	s := make(map[string]string)
	s["k"] += "x"
	s["k"] += "y"
	fmt.Println(s)
}

func testCopyAndSwap() {
	m := map[string]int{"a": 1, "b": 2}
	m["c"] = m["a"]
	m["a"], m["b"] = m["b"], m["a"]
	fmt.Println(m)

	m["new"] = m["missing"] // inserts 0 under "new", nothing under "missing"
	fmt.Println(m)
}

func testAppendIdiom() {
	g := make(map[string][]int)
	g["a"] = append(g["a"], 1)
	g["a"] = append(g["a"], 2)
	g["b"] = append(g["b"], 3)
	fmt.Println(g, len(g["zzz"]), len(g))
}

type Vertex struct{ Lat, Long float64 }

func testValueTypes() {
	m := map[string]Vertex{}
	m["a"] = Vertex{1, 2}
	fmt.Println(m["a"].Lat, m["missing"].Long, len(m)) // field read on proxy

	p := map[string]*Vertex{"a": {1, 2}}
	p["a"].Lat = 10 // write through the pointer, no map write
	fmt.Println(*p["a"], p["nope"] == nil)
}

func testNested() {
	n := map[string]map[string]int{}
	fmt.Println(n["x"]["y"], len(n)) // nil inner map read
	n["a"] = make(map[string]int)
	n["a"]["b"] = 1
	n["a"]["b"]++
	fmt.Println(n)
}

func testDeleteDuringRange() {
	m := map[int]int{1: 1, 2: 2, 3: 3, 4: 4}
	for k := range m {
		if k%2 == 0 {
			delete(m, k)
		}
	}
	fmt.Println(m)
}

func testNilMutationPanic() {
	defer func() {
		if r := recover(); r != nil {
			fmt.Println("recovered")
		}
	}()
	var m map[string]int
	delete(m, "a") // legal
	m["a"]++       // panics
	fmt.Println("not reached")
}

func testCommaOkAssign() {
	m := map[string]int{"a": 1}
	var v int
	var ok bool
	v, ok = m["a"]
	fmt.Println(v, ok)
	v, ok = m["zz"]
	fmt.Println(v, ok, len(m))
	var w, found = m["a"]
	fmt.Println(w, found)
}
