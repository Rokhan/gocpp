// generated by GoCpp from file 'tests/TourOfGo/flowcontrol/exercise-loops-and-functions.go'
#include <complex>
#include <functional>
#include <iostream>
#include <iomanip>
#include <map>
#include <string>
#include <tuple>
#include <vector>

#include "tests/TourOfGo/flowcontrol/exercise-loops-and-functions.h"
#include "gocpp/support.h"

#include "golang/fmt/print.h"

namespace golang::main
{
    namespace rec
    {
        using namespace mocklib::rec;
    }

    double Sqrt(double x)
    {
        if(x <= 0)
        {
            gocpp::panic("error, Sqrt(x) with x<1"s);
        }
        auto z = 1.0;
        for(auto i = 0; i < 15; i++)
        {
            z -= (z * z - 2) / (2 * x);
            if(z > 0 && z < 0.000000001)
            {
                break;
            }
        }
        return z;
    }

    void main()
    {
        mocklib::Println(Sqrt(2));
    }

}

int main()
{
    try
    {
        std::cout << std::boolalpha << std::setprecision(5) << std::fixed;
        golang::main::main();
        return 0;
    }
    catch(const gocpp::GoPanic& ex)
    {
        std::cout << "Panic: " << ex.what() << std::endl;
        return -1;
    }
}
