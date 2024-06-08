#pragma once

#include <functional>
#include <string>
#include <tuple>
#include <vector>

#include "tests/TourOfGo/methods/exercise-reader.fwd.h"
#include "gocpp/support.h"

// TODO: package import not implemented
// #include "golang.org/x/tour/reader/validate.fwd.h"

namespace golang::main
{
    struct MyReader
    {

        using isGoStruct = void;

        std::ostream& PrintTo(std::ostream& os) const;
    };

    std::ostream& operator<<(std::ostream& os, const MyReader& value);
    std::tuple<int, error> Read(MyReader, gocpp::slice<unsigned char> buffer);
    void main();
}

