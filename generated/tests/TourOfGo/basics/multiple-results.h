#pragma once

#include <functional>
#include <string>
#include <tuple>
#include <vector>

#include "tests/TourOfGo/basics/multiple-results.fwd.h"
#include "gocpp/support.h"

namespace golang
{
    std::tuple<std::string, std::string> swap(std::string x, std::string y);
    void main();
}

