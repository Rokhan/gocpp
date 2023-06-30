#include <complex>
#include <functional>
#include <iostream>
#include <iomanip>
#include <map>
#include <string>
#include <tuple>
#include <vector>

#include "tests/TourOfGo/methods/methods-continued.h"
#include "gocpp/support.h"


namespace golang
{
    // convertSpecs[ImportSpec] Not implemented => "fmt";
    // convertSpecs[ImportSpec] Not implemented => "math";
    double MyFloat;
    double Abs()
    {
        gocpp::Defer defer;
        if(; f < 0)
        {
            return double(- f);
        }
        return double(f);
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
