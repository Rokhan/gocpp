#include <complex>
#include <functional>
#include <iostream>
#include <string>
#include <tuple>
#include <vector>

#include "tests/TourOfGo/methods/methods-continued.h"
#include "gocpp/support.h"


namespace golang
{
    // convertSpecs[ImportSpec] Not implemented => "fmt";
    // convertSpecs[ImportSpec] Not implemented => "math";
    float MyFloat;
    float Abs()
    {
        gocpp::Defer defer;
        if(; f < 0)
        {
            return float(- f);
        }
        return float(f);
    }

    void main()
    {
        gocpp::Defer defer;
        auto f = MyFloat(- math::Sqrt2);
        mocklib::Println(f.Abs());
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
