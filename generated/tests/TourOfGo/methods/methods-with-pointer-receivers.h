#pragma once

#include <functional>
#include <string>
#include <tuple>
#include <vector>

#include "tests/TourOfGo/methods/methods-with-pointer-receivers.fwd.h"
#include "gocpp/support.h"

namespace golang
{
    struct Vertex
    {
        double X;
        double Y;

        using isGoStruct = void;

        static Vertex Init(void (init)(Vertex&));

        std::ostream& PrintTo(std::ostream& os) const;
    };

    std::ostream& operator<<(std::ostream& os, const Vertex& value);
    void Scale(Vertex* v, double f);
    double Abs(Vertex* v);
    void main();
}

