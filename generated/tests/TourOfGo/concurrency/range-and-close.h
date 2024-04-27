#pragma once

#include <functional>
#include <string>
#include <tuple>
#include <vector>

#include "tests/TourOfGo/concurrency/range-and-close.fwd.h"
#include "gocpp/support.h"

namespace golang
{
    void fibonacci(int n, gocpp::channel<int> c);
    void main();
}

