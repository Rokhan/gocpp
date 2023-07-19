#pragma once

#include <functional>
#include <string>
#include <tuple>
#include <vector>

#include "tests/TourOfGo/basics/named-results.fwd.h"
#include "gocpp/support.h"

namespace golang
{
    std::tuple<int, int> split(int sum);
    void main();
}

