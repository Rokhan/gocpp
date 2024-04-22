#include <complex>
#include <functional>
#include <iostream>
#include <iomanip>
#include <map>
#include <string>
#include <tuple>
#include <vector>

#include "tests/TourOfGo/moretypes/range.h"
#include "gocpp/support.h"


namespace golang
{
    // convertSpecs[ImportSpec] Not implemented => "fmt";
    gocpp::slice<int> pow = gocpp::slice<int> {1, 2, 4, 8, 16, 32, 64, 128};
    void main()
    {
        gocpp::Defer defer;
        for(auto [i, v] : pow)
        {
            mocklib::Printf("2**%v = %v\n", i, v);
        }
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
