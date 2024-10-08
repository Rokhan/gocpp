// generated by GoCpp from file 'tests/TourOfGo/moretypes/range-continued.go'
#include <complex>
#include <functional>
#include <iostream>
#include <iomanip>
#include <map>
#include <string>
#include <tuple>
#include <vector>

#include "tests/TourOfGo/moretypes/range-continued.h"
#include "gocpp/support.h"

#include "golang/fmt/print.h"

namespace golang::main
{
    void main()
    {
        auto pow = gocpp::make(gocpp::Tag<gocpp::slice<int>>(), 10);
        for(auto [i, gocpp_ignored] : pow)
        {
            pow[i] = 1 << (unsigned int)(i);
        }
        for(auto [_, value] : pow)
        {
            mocklib::Printf("%v\n", value);
        }
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
