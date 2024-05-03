#include <complex>
#include <functional>
#include <iostream>
#include <iomanip>
#include <map>
#include <string>
#include <tuple>
#include <vector>

#include "tests/TourOfGo/basics/variables-mixed-declaration.h"
#include "gocpp/support.h"


namespace golang
{
    // convertSpecs[ImportSpec] Not implemented => "fmt";
    void main()
    {
        gocpp::Defer defer;
        auto [s1, i1] = std::tuple{"string1", 1};
        mocklib::Println(s1, i1);
        auto [s1, i2] = std::tuple{"string2", 2};
        mocklib::Println(s1, i2);
        auto [s2, i2] = std::tuple{"string3", 3};
        mocklib::Println(s2, i2);
        std::tie(s2, i2) = std::tuple{"string4", 4};
        mocklib::Println(s2, i2);
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
