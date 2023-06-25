#include <complex>
#include <functional>
#include <iostream>
#include <string>
#include <tuple>
#include <vector>

#include "tests/TourOfGo/moretypes/function-values.h"
#include "gocpp/support.h"


namespace golang
{
    // convertSpecs[ImportSpec] Not implemented => "fmt";
    // convertSpecs[ImportSpec] Not implemented => "math";
    float compute(std::function<float ()> fn)
    {
        gocpp::Defer defer;
        return fn(3, 4);
    }

    void main()
    {
        gocpp::Defer defer;
        auto hypot = [=](float x, float y) mutable -> float
        {
            gocpp::Defer defer;
            return std::sqrt(x * x + y * y);
        }
;
        mocklib::Println(hypot(5, 12));
        mocklib::Println(compute(hypot));
        mocklib::Println(compute(std::pow));
    }

}

int main()
{
    try
    {
        std::cout << std::boolalpha;
        golang::main();
        return 0;
    }
    catch(const gocpp::GoPanic& ex)
    {
        std::cout << "Panic: " << ex.what() << std::endl;
        return -1;
    }
}
