#include <complex>
#include <functional>
#include <iostream>
#include <iomanip>
#include <map>
#include <string>
#include <tuple>
#include <vector>

#include "tests/TourOfGo/flowcontrol/if-and-else.h"
#include "gocpp/support.h"


namespace golang
{
    // convertSpecs[ImportSpec] Not implemented => "fmt";
    // convertSpecs[ImportSpec] Not implemented => "math";
    double pow(double x, double n, double lim)
    {
        gocpp::Defer defer;
        if(auto v = mocklib::Pow(x, n); v < lim)
        {
            return v;
        }
        else
        {
            mocklib::Printf("%g >= %g\n", v, lim);
        }
        return lim;
    }

    void main()
    {
        gocpp::Defer defer;
        mocklib::Println(pow(3, 2, 10), pow(3, 3, 20));
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
