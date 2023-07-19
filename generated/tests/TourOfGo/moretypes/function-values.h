#pragma once

#include <functional>
#include <string>
#include <tuple>
#include <vector>

#include "tests/TourOfGo/moretypes/function-values.fwd.h"
#include "gocpp/support.h"

namespace golang
{
    double compute(std::function<double (double, double)> fn);
    void main();
}

