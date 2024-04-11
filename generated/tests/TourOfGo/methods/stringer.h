#pragma once

#include <functional>
#include <string>
#include <tuple>
#include <vector>

#include "tests/TourOfGo/methods/stringer.fwd.h"
#include "gocpp/support.h"

namespace golang
{
    struct Person
    {
        std::string Name;
        int Age;

        using isGoStruct = void;

        std::ostream& PrintTo(std::ostream& os) const;
    };

    std::ostream& operator<<(std::ostream& os, const Person& value);
    std::string String(Person p);
    void main();
}

