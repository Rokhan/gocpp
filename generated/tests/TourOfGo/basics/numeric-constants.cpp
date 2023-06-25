#include <complex>
#include <functional>
#include <iostream>
#include <string>
#include <tuple>
#include <vector>

#include "tests/TourOfGo/basics/numeric-constants.h"
#include "gocpp/support.h"


namespace golang
{
    // convertSpecs[ImportSpec] Not implemented => "fmt";
    auto Big = 1 << 100;
    auto Small = Big >> 99;
    int needInt(int x)
    {
        gocpp::Defer defer;
        return x * 10 + 1;
    }

    float needFloat(float x)
    {
        gocpp::Defer defer;
        return x * 0.1;
    }

    void main()
    {
        gocpp::Defer defer;
        mocklib::Println(needInt(Small));
        mocklib::Println(needFloat(Small));
        mocklib::Println(needFloat(Big));
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
