#pragma once

#include <functional>
#include <string>
#include <tuple>
#include <vector>

#include "tests/TourOfGo/concurrency/channels-opt.fwd.h"
#include "gocpp/support.h"

namespace golang
{
    void fill(gocpp::channel<int> c);
    void main();
}

