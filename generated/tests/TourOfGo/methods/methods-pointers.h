// generated by GoCpp from file 'tests/TourOfGo/methods/methods-pointers.go'
#pragma once

#include <functional>
#include <string>
#include <tuple>
#include <vector>

#include "tests/TourOfGo/methods/methods-pointers.fwd.h"
#include "gocpp/support.h"


namespace golang::main
{
    struct Vertex
    {
        double X;
        double Y;

        using isGoStruct = void;

        std::ostream& PrintTo(std::ostream& os) const;
    };

    std::ostream& operator<<(std::ostream& os, const struct Vertex& value);
    double Abs(struct Vertex v);
    void Scale(struct Vertex* v, double f);
    void main();
}

