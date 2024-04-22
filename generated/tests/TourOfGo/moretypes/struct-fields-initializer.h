#pragma once

#include <functional>
#include <string>
#include <tuple>
#include <vector>

#include "tests/TourOfGo/moretypes/struct-fields-initializer.fwd.h"
#include "gocpp/support.h"

namespace golang
{
    struct Vertex
    {
        int X;
        int Y;
        int Z;

        using isGoStruct = void;

        std::ostream& PrintTo(std::ostream& os) const;
    };

    std::ostream& operator<<(std::ostream& os, const Vertex& value);
    struct Segment
    {
        Vertex Start;
        Vertex End;

        using isGoStruct = void;

        std::ostream& PrintTo(std::ostream& os) const;
    };

    std::ostream& operator<<(std::ostream& os, const Segment& value);
    extern Vertex v1;
    extern Vertex v2;
    extern Vertex v3;
    extern Vertex v4;
    extern Segment s1;
    void main();
}

