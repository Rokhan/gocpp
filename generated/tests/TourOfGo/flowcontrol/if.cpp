#include <complex>
#include <functional>
#include <iostream>
#include <iomanip>
#include <map>
#include <string>
#include <tuple>
#include <vector>

#include "tests/TourOfGo/flowcontrol/if.h"
#include "gocpp/support.h"


namespace golang
{
    // convertSpecs[ImportSpec] Not implemented => "fmt";
    // convertSpecs[ImportSpec] Not implemented => "math";
    std::string sqrt(double x)
    {
        gocpp::Defer defer;
        if(; x < 0)
        {
            return sqrt(- x) + "i";
        }
        return mocklib::Sprint(std::sqrt(x));
    }

    void main()
    {
        gocpp::Defer defer;
        mocklib::Println(sqrt(2), sqrt(- 4));
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
