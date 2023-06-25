#pragma once

#include <functional>
#include <string>
#include <tuple>
#include <vector>

#include "gocpp/support.h"

namespace golang
{
    std::tuple<float, error> Sqrt(float x);
    void main();
}

