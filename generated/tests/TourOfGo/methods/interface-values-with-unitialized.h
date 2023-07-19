#pragma once

#include <functional>
#include <string>
#include <tuple>
#include <vector>

#include "tests/TourOfGo/methods/interface-values-with-unitialized.fwd.h"
#include "gocpp/support.h"

namespace golang
{
    struct I;
    struct T
    {
        std::string S;

        using isGoStruct = void;

        static T Init(void (init)(T&));

        std::ostream& PrintTo(std::ostream& os) const;
    };

    std::ostream& operator<<(std::ostream& os, const T& value);
    void M(T* t);
    void main();
    void describe(I i);
}

