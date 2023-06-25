#include <complex>
#include <functional>
#include <iostream>
#include <string>
#include <tuple>
#include <vector>

#include "tests/TourOfGo/moretypes/slices-pointers.h"
#include "gocpp/support.h"


namespace golang
{
    // convertSpecs[ImportSpec] Not implemented => "fmt";
    void main()
    {
        gocpp::Defer defer;
        auto names = gocpp::array<std::string, 4> {"John", "Paul", "George", "Ringo"};
        mocklib::Println(names);
        auto a = names.make_slice(0, 2);
        auto b = names.make_slice(1, 3);
        mocklib::Println(a, b);
        b[0] = "XXX";
        mocklib::Println(a, b);
        mocklib::Println(names);
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
