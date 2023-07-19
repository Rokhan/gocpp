#pragma once

#include <functional>
#include <string>
#include <tuple>
#include <vector>

#include "tests/TourOfGo/moretypes/function-closures.fwd.h"
#include "gocpp/support.h"

namespace golang
{
    std::function<int (int)> adder();
    void main();
}

