#pragma once

#include <functional>
#include <string>
#include <tuple>
#include <vector>

#include "tests/HelloWorld.fwd.h"
#include "gocpp/support.h"

namespace golang
{
    void main();
    int square(int num);
    void helloFunc(std::string str1, std::string str2, std::string str3);
    void printN(std::string str1, int n);
}

