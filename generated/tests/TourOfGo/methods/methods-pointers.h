#pragma once

#include <functional>
#include <string>
#include <tuple>
#include <vector>

#include "gocpp/support.h"

namespace golang
{
    struct Vertex;
    double Abs(Vertex v);
    void Scale(Vertex* v, double f);
    void main();
}
