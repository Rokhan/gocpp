// generated by GoCpp from file '$(ImportDir)/math/unsafe.go'
#include <complex>
#include <functional>
#include <iostream>
#include <iomanip>
#include <map>
#include <string>
#include <tuple>
#include <vector>

#include "golang/math/unsafe.h"
#include "gocpp/support.h"

#include "golang/unsafe/unsafe.h"

namespace golang::math
{
    uint32_t Float32bits(double f)
    {
        return *(*uint32_t)(Pointer(gocpp::recv(unsafe), & f));
    }

    double Float32frombits(uint32_t b)
    {
        return *(*float)(Pointer(gocpp::recv(unsafe), & b));
    }

    uint64_t Float64bits(double f)
    {
        return *(*uint64_t)(Pointer(gocpp::recv(unsafe), & f));
    }

    double Float64frombits(uint64_t b)
    {
        return *(*double)(Pointer(gocpp::recv(unsafe), & b));
    }

}
