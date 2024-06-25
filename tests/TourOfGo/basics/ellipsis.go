//go:build OMIT
// +build OMIT

package main

import (
	"fmt"
	"math/cmplx"
)

var (
	ToBe   bool       = false
	MaxInt uint64     = 1<<64 - 1
	z      complex128 = cmplx.Sqrt(-5 + 12i)
)

func DummyPrintList(format string, elts []interface{}) {
	for _, elt := range elts {
		fmt.Printf("%v, ", elt)
	}
	fmt.Println()
}

func DummyPrintf(format string, a ...interface{}) {
	DummyPrintList(format, a)
	return
}

func main() {
	DummyPrintf("tototot", 1, 2, 3)
}

//  Idea to force types with variadic: https://godbolt.org/z/o1G8dbjb9
//
// #include <functional>
// #include <vector>
//
// template<typename ForcedType, typename DummyType>
// struct Ref : std::reference_wrapper<ForcedType>
// {
//     Ref(ForcedType& ref) : std::reference_wrapper<ForcedType>(ref) {}
// };
//
// template<typename ForcedType, typename... Args>
// void funcRef(Ref<ForcedType, Args>... args){}
//
// template<typename... Args>
// void func(Args... args)
// {
//     funcRef(Ref<int, Args>(args)...);
// }
//
// int main(int argc, char *argv[])
// {
//     func(1,2,3);
//     return 0;
// }
