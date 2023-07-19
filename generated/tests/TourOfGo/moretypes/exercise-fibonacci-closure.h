#pragma once

#include <functional>
#include <string>
#include <tuple>
#include <vector>

#include "tests/TourOfGo/moretypes/exercise-fibonacci-closure.fwd.h"
#include "gocpp/support.h"

namespace golang
{
    std::function<int ()> fibonacci();
    void main();
}

