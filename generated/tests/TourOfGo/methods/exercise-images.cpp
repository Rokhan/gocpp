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


namespace golang
{
    // convertSpecs[ImportSpec] Not implemented => "golang.org/x/tour/pic";
    struct Image
    {

        using isGoStruct = void;

        static Image Init(void (init)(Image&))
        {
            Image value;
            init(value);
            return value;
        }

        std::ostream& PrintTo(std::ostream& os) const
        {
            os << '{';
            os << '}';
            return os;
        }
    };

    std::ostream& operator<<(std::ostream& os, const Image& value)
    {
        return value.PrintTo(os);
    }
    void main()
    {
        gocpp::Defer defer;
        auto m = Image {};
        pic::ShowImage(m);
    }

}

int main()
{
    try
    {
        std::cout << std::boolalpha << std::fixed << std::setprecision(5);
        golang::main();
        return 0;
    }
    catch(const gocpp::GoPanic& ex)
    {
        std::cout << "Panic: " << ex.what() << std::endl;
        return -1;
    }
}
