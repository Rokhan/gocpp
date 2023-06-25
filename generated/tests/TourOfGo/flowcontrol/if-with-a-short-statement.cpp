#include <complex>
#include <functional>
#include <iostream>
#include <string>
#include <tuple>
#include <vector>

#include "tests/TourOfGo/flowcontrol/if-with-a-short-statement.h"
#include "gocpp/support.h"


namespace golang
{
    // convertSpecs[ImportSpec] Not implemented => "fmt";
    // convertSpecs[ImportSpec] Not implemented => "math";
    float pow(float x, float n, float lim)
    {
        gocpp::Defer defer;
        if(auto v = std::pow(x, n); v < lim)
        {
            return v;
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
