#pragma once

#include <functional>
#include <string>
#include <tuple>
#include <vector>

#include "tests/TourOfGo/moretypes/structs.fwd.h"
#include "gocpp/support.h"

namespace golang
{
    struct Vertex
    {
        int X;
        int Y;

        using isGoStruct = void;

        std::ostream& PrintTo(std::ostream& os) const;
    };

    std::ostream& operator<<(std::ostream& os, const Vertex& value);
    void main();
}

