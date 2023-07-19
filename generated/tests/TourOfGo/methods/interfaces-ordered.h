#pragma once

#include <functional>
#include <string>
#include <tuple>
#include <vector>

#include "tests/TourOfGo/methods/interfaces-ordered.fwd.h"
#include "gocpp/support.h"

namespace golang
{
    struct Abser;
    struct Vertex
    {
        double X;
        double Y;

        using isGoStruct = void;

        static Vertex Init(void (init)(Vertex&));

        std::ostream& PrintTo(std::ostream& os) const;
    };

    std::ostream& operator<<(std::ostream& os, const Vertex& value);
    using MyFloat = double;
    void main();
    double Abs(MyFloat f);
    double Abs(Vertex* v);
}

