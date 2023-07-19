#pragma once

#include <functional>
#include <string>
#include <tuple>
#include <vector>

#include "tests/TourOfGo/moretypes/slice-len-cap.fwd.h"
#include "gocpp/support.h"

namespace golang
{
    void main();
    void printSlice(gocpp::slice<int> s);
}

