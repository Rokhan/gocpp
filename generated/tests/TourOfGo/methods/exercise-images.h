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

        std::ostream& PrintTo(std::ostream& os) const;
    };

    std::ostream& operator<<(std::ostream& os, const Image& value);
    color::Model ColorModel(Image);
    image::Rectangle Bounds(Image);
    color::Color At(Image, int x, int y);
    void main();
}

