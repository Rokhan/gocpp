#pragma once

#include <functional>
#include <string>
#include <tuple>
#include <vector>

#include "tests/TourOfGo/methods/exercise-errors.fwd.h"
#include "gocpp/support.h"

namespace golang
{
    std::tuple<double, error> Sqrt(double x);
    void main();
}

