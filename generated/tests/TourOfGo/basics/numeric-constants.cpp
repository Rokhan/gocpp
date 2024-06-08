#include <complex>
#include <functional>
#include <iostream>
#include <iomanip>
#include <map>
#include <string>
#include <tuple>
#include <vector>

#include "tests/TourOfGo/basics/numeric-constants.h"
#include "gocpp/support.h"

// TODO: package import not implemented
// #include "fmt/doc.h"
// #include "fmt/errors.h"
// #include "fmt/format.h"
// #include "fmt/print.h"
// #include "fmt/scan.h"

namespace golang::main
{
    int Big = 1 << 100;
    int Small = Big >> 99;
    int needInt(int x)
    {
        return x * 10 + 1;
    }

    double needFloat(double x)
    {
        return x * 0.1;
    }

    void main()
    {
        mocklib::Println(needInt(Small));
        mocklib::Println(needFloat(Small));
        mocklib::Println(needFloat(Big));
    }

}

int main()
{
    try
    {
        std::cout << std::boolalpha << std::fixed << std::setprecision(5);
        golang::main::main();
        return 0;
    }
    catch(const gocpp::GoPanic& ex)
    {
        std::cout << "Panic: " << ex.what() << std::endl;
        return -1;
    }
}
