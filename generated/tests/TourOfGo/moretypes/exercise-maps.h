#pragma once

#include <functional>
#include <string>
#include <tuple>
#include <vector>

#include "gocpp/support.h"

namespace golang
{
    gocpp::map<std::string,int> WordCount(std::string s);
    void main();
}

