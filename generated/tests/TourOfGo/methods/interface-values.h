#pragma once

#include <functional>
#include <string>
#include <tuple>
#include <vector>

#include "gocpp/support.h"

namespace golang
{
    struct I;
    struct T;
    void M(T* t);
    using F = double;
    void M(F f);
    void main();
    void describe(I i);
}

