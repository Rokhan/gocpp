#pragma once

#include <functional>
#include <string>
#include <tuple>
#include <vector>

#include "tests/TourOfGo/methods/methods-pointers.fwd.h"
#include "gocpp/support.h"

namespace golang
{
    struct Vertex
    {
        double X;
        double Y;

        using isGoStruct = void;

        std::ostream& PrintTo(std::ostream& os) const;
    };

    std::ostream& operator<<(std::ostream& os, const Vertex& value);
    double Abs(Vertex v);
    void Scale(Vertex* v, double f);
    void main();
}

