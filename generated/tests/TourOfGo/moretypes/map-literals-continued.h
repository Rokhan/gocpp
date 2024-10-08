// generated by GoCpp from file 'tests/TourOfGo/moretypes/map-literals-continued.go'
#pragma once

#include <functional>
#include <string>
#include <tuple>
#include <vector>

#include "tests/TourOfGo/moretypes/map-literals-continued.fwd.h"
#include "gocpp/support.h"


namespace golang::main
{
    struct Vertex
    {
        double Lat;
        double Long;

        using isGoStruct = void;

        std::ostream& PrintTo(std::ostream& os) const;
    };

    std::ostream& operator<<(std::ostream& os, const struct Vertex& value);
    extern gocpp::map<std::string, Vertex> m;
    void main();
}

