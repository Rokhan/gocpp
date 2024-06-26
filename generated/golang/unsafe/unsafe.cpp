// generated by GoCpp from file '$(ImportDir)/unsafe/unsafe.go'
#include <complex>
#include <functional>
#include <iostream>
#include <iomanip>
#include <map>
#include <string>
#include <tuple>
#include <vector>

#include "golang/unsafe/unsafe.h"
#include "gocpp/support.h"

namespace golang::unsafe
{
    uintptr_t Sizeof(ArbitraryType x)
    /* convertBlockStmt, nil block */;

    uintptr_t Offsetof(ArbitraryType x)
    /* convertBlockStmt, nil block */;

    uintptr_t Alignof(ArbitraryType x)
    /* convertBlockStmt, nil block */;

    Pointer Add(Pointer ptr, IntegerType len)
    /* convertBlockStmt, nil block */;

    gocpp::slice<ArbitraryType> Slice(ArbitraryType* ptr, IntegerType len)
    /* convertBlockStmt, nil block */;

    ArbitraryType* SliceData(gocpp::slice<ArbitraryType> slice)
    /* convertBlockStmt, nil block */;

    std::string String(unsigned char* ptr, IntegerType len)
    /* convertBlockStmt, nil block */;

    unsigned char* StringData(std::string str)
    /* convertBlockStmt, nil block */;

}

