#pragma once

#include <functional>
#include <string>
#include <tuple>
#include <vector>

#include "tests/TourOfGo/concurrency/channels.fwd.h"
#include "gocpp/support.h"

namespace golang
{
    void sum(gocpp::slice<int> s, gocpp::channel<int> c);
    void main();
}

