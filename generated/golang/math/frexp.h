// generated by GoCpp from file '$(ImportDir)/math/frexp.go'
#pragma once

#include <functional>
#include <string>
#include <tuple>
#include <vector>

#include "golang/math/frexp.fwd.h"
#include "gocpp/support.h"

#include "golang/math/bits.h"
#include "golang/math/stubs.h"
#include "golang/math/unsafe.h"

namespace golang::math
{
    std::tuple<double, int> Frexp(double f);
    std::tuple<double, int> frexp(double f);
}
