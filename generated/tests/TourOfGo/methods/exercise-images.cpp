#include <complex>
#include <functional>
#include <iostream>
#include <iomanip>
#include <map>
#include <string>
#include <tuple>
#include <vector>

#include "tests/TourOfGo/methods/exercise-images.h"
#include "gocpp/support.h"

// TODO: package import not implemented
// #include "image/format.h"
// #include "image/geom.h"
// #include "image/image.h"
// #include "image/names.h"
// #include "image/ycbcr.h"
// #include "image/color/color.h"
// #include "image/color/ycbcr.h"
// #include "golang.org/x/tour/pic/pic.h"

namespace golang::main
{
    
    std::ostream& Image::PrintTo(std::ostream& os) const
    {
        os << '{';
        os << '}';
        return os;
    }

    std::ostream& operator<<(std::ostream& os, const Image& value)
    {
        return value.PrintTo(os);
    }

    color::Model ColorModel(Image)
    {
        gocpp::panic("not implemented");
    }

    image::Rectangle Bounds(Image)
    {
        gocpp::panic("not implemented");
    }

    color::Color At(Image, int x, int y)
    {
        gocpp::panic("not implemented");
    }

    void main()
    {
        auto m = Image {};
        pic::ShowImage(m);
    }

}

int main()
{
    try
    {
        std::cout << std::boolalpha << std::fixed << std::setprecision(5);
        golang::main::main();
        return 0;
    }
    catch(const gocpp::GoPanic& ex)
    {
        std::cout << "Panic: " << ex.what() << std::endl;
        return -1;
    }
}
