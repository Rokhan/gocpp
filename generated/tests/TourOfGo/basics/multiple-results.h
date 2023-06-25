#pragma once

#include <functional>
#include <string>
#include <tuple>
#include <vector>

#include "gocpp/support.h"

namespace golang
{
    std::tuple<std::string, std::string> swap(std::string x, std::string y);
    void main();
}

