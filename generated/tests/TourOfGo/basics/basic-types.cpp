#include <complex>
#include <functional>
#include <iostream>
#include <iomanip>
#include <map>
#include <string>
#include <tuple>
#include <vector>

#include "tests/TourOfGo/basics/basic-types.h"
#include "gocpp/support.h"


namespace golang
{
    // convertSpecs[ImportSpec] Not implemented => "fmt";
    // convertSpecs[ImportSpec] Not implemented => "math/cmplx";
    bool ToBe = false;
    uint64_t MaxInt = 1 << 64 - 1;
    gocpp::complex128 z = std::sqrt(- 5 + gocpp::complex128(0, 12));
    void main()
    {
        gocpp::Defer defer;
        mocklib::Printf("Type: %T Value: %v\n", ToBe, ToBe);
        mocklib::Printf("Type: %T Value: %v\n", MaxInt, MaxInt);
        mocklib::Printf("Type: %T Value: %v\n", z, z);
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