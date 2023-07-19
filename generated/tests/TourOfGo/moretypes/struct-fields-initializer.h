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

        static Vertex Init(void (init)(Vertex&));

        std::ostream& PrintTo(std::ostream& os) const;
    };

    std::ostream& operator<<(std::ostream& os, const Vertex& value);
    struct Segment
    {
        Vertex Start;
        Vertex End;

        using isGoStruct = void;

        static Segment Init(void (init)(Segment&));

        std::ostream& PrintTo(std::ostream& os) const;
    };

    std::ostream& operator<<(std::ostream& os, const Segment& value);
    void main();
}

