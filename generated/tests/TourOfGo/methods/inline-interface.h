#pragma once

#include <functional>
#include <string>
#include <tuple>
#include <vector>

#include "tests/TourOfGo/methods/inline-interface.fwd.h"
#include "gocpp/support.h"

namespace golang
{
    using MyInt = int;
    using MyFloat = double;
    double Abs(MyInt i);
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
    double Abs(Vertex v);
    void main();
    void describe(!!TYPE_EXPR_ERROR!! [*ast.InterfaceType] i);
}

