#pragma once

#include <functional>
#include <string>
#include <tuple>
#include <vector>

#include "gocpp/support.h"

namespace golang
{
    void main();
    void printSlice(std::string s, gocpp::slice<int> x);
}

