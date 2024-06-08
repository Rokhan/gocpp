#pragma once

#include <functional>
#include <string>
#include <tuple>
#include <vector>

#include "tests/TourOfGo/methods/exercise-images.fwd.h"
#include "gocpp/support.h"

// TODO: package import not implemented
// #include "image/format.fwd.h"
// #include "image/geom.fwd.h"
// #include "image/image.fwd.h"
// #include "image/names.fwd.h"
// #include "image/ycbcr.fwd.h"
// #include "image/color/color.fwd.h"
// #include "image/color/ycbcr.fwd.h"
// #include "golang.org/x/tour/pic/pic.fwd.h"

namespace golang::main
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

