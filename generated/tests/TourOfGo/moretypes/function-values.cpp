#include <complex>
#include <functional>
#include <iostream>
#include <iomanip>
#include <map>
#include <string>
#include <tuple>
#include <vector>

#include "tests/TourOfGo/moretypes/function-values.h"
#include "gocpp/support.h"


namespace golang
{
    // convertSpecs[ImportSpec] Not implemented => "fmt";
    // convertSpecs[ImportSpec] Not implemented => "math";
    double compute(std::function<double (double, double)> fn)
    {
        gocpp::Defer defer;
        return fn(3, 4);
    }

    void main()
    {
        gocpp::Defer defer;
        auto hypot = [=](double x, double y) mutable -> double
        {
            gocpp::Defer defer;
            return std::sqrt(x * x + y * y);
        }
;
        mocklib::Println(hypot(5, 12));
        mocklib::Println(compute(hypot));
        mocklib::Println(compute(mocklib::Pow));
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
