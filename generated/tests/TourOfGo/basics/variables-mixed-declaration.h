// generated by GoCpp from file 'tests/TourOfGo/basics/variables-mixed-declaration.go'
#pragma once

#include <functional>
#include <string>
#include <tuple>
#include <vector>

#include "tests/TourOfGo/basics/variables-mixed-declaration.fwd.h"
#include "gocpp/support.h"


namespace golang::main
{
    std::tuple<std::string, int, gocpp::slice<std::string>> f1();
    std::tuple<std::string, int, gocpp::array<std::string, 3>> f2();
    void main();

    namespace rec
    {
    }
}

