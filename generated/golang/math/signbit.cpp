// generated by GoCpp from file '$(ImportDir)/math/signbit.go'
#include <complex>
#include <functional>
#include <iostream>
#include <iomanip>
#include <map>
#include <string>
#include <tuple>
#include <vector>

#include "golang/math/signbit.h"
#include "gocpp/support.h"

#include "golang/math/unsafe.h"

namespace golang::math
{
    bool Signbit(double x)
    {
        return Float64bits(x) & (1 << 63) != 0;
    }

}

