#pragma once

#include <functional>
#include <string>
#include <tuple>
#include <vector>

#include "tests/TourOfGo/moretypes/append.fwd.h"
#include "gocpp/support.h"

namespace golang
{
    void main();
    void printSlice(gocpp::slice<int> s);
    void appendValue(gocpp::slice<int> s, int value);
}

