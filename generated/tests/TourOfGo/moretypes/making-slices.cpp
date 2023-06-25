#include <complex>
#include <functional>
#include <iostream>
#include <string>
#include <tuple>
#include <vector>

#include "tests/TourOfGo/moretypes/making-slices.h"
#include "gocpp/support.h"


namespace golang
{
    // convertSpecs[ImportSpec] Not implemented => "fmt";
    void main()
    {
        gocpp::Defer defer;
        auto a = gocpp::make(gocpp::Tag<gocpp::slice<int>>(), 5);
        printSlice("a", a);
        auto b = gocpp::make(gocpp::Tag<gocpp::slice<int>>(), 0, 5);
        printSlice("b", b);
        auto c = b.make_slice(0, 2);
        printSlice("c", c);
        auto d = c.make_slice(2, 5);
        printSlice("d", d);
    }

    void printSlice(std::string s, gocpp::slice<int> x)
    {
        gocpp::Defer defer;
        mocklib::Printf("%s len=%d cap=%d %v\n", s, len(x), cap(x), x);
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
