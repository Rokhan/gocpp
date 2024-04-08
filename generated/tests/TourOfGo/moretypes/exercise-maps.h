#pragma once

#include <functional>
#include <string>
#include <tuple>
#include <vector>

#include "tests/TourOfGo/moretypes/exercise-maps.fwd.h"
#include "gocpp/support.h"

namespace golang
{
    gocpp::map<std::string, int> WordCount(std::string s);
    void main();
}

