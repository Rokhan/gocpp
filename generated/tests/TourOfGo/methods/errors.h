#pragma once

#include <functional>
#include <string>
#include <tuple>
#include <vector>

#include "gocpp/support.h"

namespace golang
{
    struct MyError;
    std::string Error(MyError* e);
    error run();
    void main();
}

