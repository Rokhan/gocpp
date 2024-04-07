#pragma once

#include <functional>
#include <string>
#include <tuple>
#include <vector>

#include "tests/TourOfGo/concurrency/goroutines.fwd.h"
#include "gocpp/support.h"

namespace golang
{
    void say(std::string s);
    void main();
}

