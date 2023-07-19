#pragma once

#include <functional>
#include <string>
#include <tuple>
#include <vector>

#include "tests/TourOfGo/methods/interfaces.fwd.h"
#include "gocpp/support.h"

namespace golang
{
    struct Abser;
    void main();
    using MyFloat = double;
    double Abs(MyFloat f);
    struct Vertex
    {
        double X;
        double Y;

        using isGoStruct = void;

        static Vertex Init(void (init)(Vertex&));

        std::ostream& PrintTo(std::ostream& os) const;
    };

    std::ostream& operator<<(std::ostream& os, const Vertex& value);
    double Abs(Vertex* v);
}

