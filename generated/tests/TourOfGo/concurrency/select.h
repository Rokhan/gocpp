#pragma once

#include <functional>
#include <string>
#include <tuple>
#include <vector>

#include "tests/TourOfGo/concurrency/select.fwd.h"
#include "gocpp/support.h"

namespace golang
{
    void fibonacci(gocpp::channel<int> c, gocpp::channel<int> quit);
    void main();
}

