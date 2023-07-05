#pragma once

#include <functional>
#include <string>
#include <tuple>
#include <vector>

#include "gocpp/support.h"

namespace golang
{
    void main();
    using MyFloat = double;
    double Abs(MyFloat f);
    struct Vertex;
    double Abs(Vertex* v);
}

