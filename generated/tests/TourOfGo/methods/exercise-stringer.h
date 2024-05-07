#pragma once

#include <functional>
#include <string>
#include <tuple>
#include <vector>

#include "tests/TourOfGo/methods/exercise-stringer.fwd.h"
#include "gocpp/support.h"

namespace golang
{
    using IPAddr = gocpp::array<unsigned char, 4>;
    std::string String(IPAddr ip);
    void main();
}

