#pragma once

#include <functional>
#include <string>
#include <tuple>
#include <vector>

#include "tests/TourOfGo/methods/exercise-images.fwd.h"
#include "gocpp/support.h"

namespace golang
{
    struct Image
    {

        using isGoStruct = void;

        static Image Init(void (init)(Image&));

        std::ostream& PrintTo(std::ostream& os) const;
    };

    std::ostream& operator<<(std::ostream& os, const Image& value);
    void main();
}

