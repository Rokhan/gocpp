// generated by GoCpp from file 'tests/TourOfGo/moretypes/struct-literals.go'
#pragma once

#include <functional>
#include <string>
#include <tuple>
#include <vector>

#include "tests/TourOfGo/moretypes/struct-literals.fwd.h"
#include "gocpp/support.h"


namespace golang::main
{
    struct Vertex
    {
        int X;
        int Y;

        using isGoStruct = void;

        std::ostream& PrintTo(std::ostream& os) const;
    };

    std::ostream& operator<<(std::ostream& os, const struct Vertex& value);
    extern Vertex v1;
    extern Vertex v2;
    extern Vertex v3;
    extern Vertex* p;
    void main();
}

