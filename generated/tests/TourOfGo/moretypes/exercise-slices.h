#pragma once

#include <functional>
#include <string>
#include <tuple>
#include <vector>

#include "gocpp/support.h"

namespace golang
{
    gocpp::slice<gocpp::slice<uint8>> Pic(int dx, int dy);
    void main();
}

