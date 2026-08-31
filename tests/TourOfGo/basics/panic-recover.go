//go:build ignore || OMIT

package main

import (
	"fmt"
)

func main() {
	f()
	fmt.Println("Returned normally from f.")

	// As it's not called in a defer statement, r should always be nil.
	if r := recover(); r != nil {
		fmt.Println("R should always be nil, r =", r)
	}

}

func f() {
	defer func() {
		if r := recover(); r != nil {
			fmt.Println("Recovered in f", r)
		}
	}()

	defer func() {
		fmt.Println("Simple defer in f")
	}()

	fmt.Println("Calling g.")
	g(0)
	fmt.Println("Returned normally from g.")
}

func g(i int) {
	defer fmt.Println("Defer1 in g", i)
	if i > 3 {
		fmt.Println("Panicking!")
		panic(fmt.Sprint(i))
	}
	defer fmt.Println("Defer2 in g", i)
	fmt.Println("Printing in g", i)
	g(i + 1)
}

// Simplified version of 'scanOne' from "fmt/scan.go"

// scanOne scans a single value, deriving the scanner from the type of the argument.
func scanOne(arg any) {

	switch v := arg.(type) {
	case *bool:
		*v = true
	case *int:
		*v = 0
	default:
		errorString("can't scan type")
	}
}

type scanError struct {
	err error
}

func errorString(err string) {
	//panic(scanError{errors.New(err)})
	panic(scanError{fmt.Errorf("%s", err)})
}

// errorHandler turns local panics into error returns.
func errorHandler(errp *error) {
	if e := recover(); e != nil {
		if se, ok := e.(scanError); ok { // catch local error
			*errp = se.err
			// } else if eof, ok := e.(error); ok && eof == io.EOF { // out of input
			// 	*errp = eof
		} else {
			panic(e)
		}
	}
}

// doScan does the real work for scanning without a format string.
func doScan(a []any) (numProcessed int, err error) {
	defer errorHandler(&err)
	for _, arg := range a {
		scanOne(arg)
		numProcessed++
	}

	return
}
