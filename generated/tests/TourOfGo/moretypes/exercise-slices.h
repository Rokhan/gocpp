#pragma once

#include <functional>
#include <string>
#include <tuple>
#include <vector>

#include "tests/TourOfGo/moretypes/exercise-slices.fwd.h"
#include "gocpp/support.h"

namespace golang
{
    gocpp::slice<gocpp::slice<uint8_t>> Pic(int dx, int dy);
    void main();
}

