#pragma once

#include <functional>
#include <string>
#include <tuple>
#include <vector>

#include "gocpp/support.h"

namespace golang
{
    struct Abser;
    struct Vertex;
    using MyFloat = double;
    void main();
    double Abs(MyFloat f);
    double Abs(Vertex* v);
}

