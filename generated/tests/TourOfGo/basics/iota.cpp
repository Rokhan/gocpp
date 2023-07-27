#include <complex>
#include <functional>
#include <iostream>
#include <iomanip>
#include <map>
#include <string>
#include <tuple>
#include <vector>

#include "tests/TourOfGo/basics/iota.h"
#include "gocpp/support.h"


namespace golang
{
    // convertSpecs[ImportSpec] Not implemented => "fmt";
    auto c0 = iota;
    auto c1 = iota;
    auto c2 = iota;
    auto a = 1 << iota;
    auto b = 1 << iota;
    auto c = 1 << iota;
    auto u = iota * 42;
    double v = iota * 42;
    auto w = iota * 42;
    auto x = iota;
    auto y = iota;
    auto bit0 = 1 << iota;
    auto mask0 = 1 << iota - 1;
    auto bit1;
    auto mask1;
    auto _;
    auto _;
    auto bit3;
    auto mask3;
    void main()
    {
        gocpp::Defer defer;
        mocklib::Printf("%v %v %v\n", c0, c1, c2);
        mocklib::Printf("%v %v %v\n", a, b, c);
        mocklib::Printf("%v %v %v\n", u, v, w);
        mocklib::Printf("%v %v\n", x, y);
        mocklib::Printf("%v %v %v\n", bit0, bit1, bit3);
        mocklib::Printf("%v %v %v\n", mask0, mask1, mask3);
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
