#pragma once

#include <functional>
#include <string>
#include <tuple>
#include <vector>

#include "gocpp/support.h"

namespace golang
{
    struct Vertex;
    void Scale(Vertex* v, double f);
    double Abs(Vertex* v);
    void main();
}

