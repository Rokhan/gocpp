#pragma once

#include <functional>
#include <string>
#include <tuple>
#include <vector>

#include "tests/TourOfGo/methods/exercise-rot-reader.fwd.h"
#include "gocpp/support.h"

namespace golang
{
    struct rot13Reader
    {
        io::Reader r;

        using isGoStruct = void;

        std::ostream& PrintTo(std::ostream& os) const;
    };

    std::ostream& operator<<(std::ostream& os, const rot13Reader& value);
    std::tuple<int, error> Read(rot13Reader r13, gocpp::slice<unsigned char> buf);
    void main();
}

