#include <complex>
#include <functional>
#include <iostream>
#include <iomanip>
#include <map>
#include <string>
#include <tuple>
#include <vector>

#include "tests/TourOfGo/moretypes/function-closures.h"
#include "gocpp/support.h"


namespace golang
{
    // convertSpecs[ImportSpec] Not implemented => "fmt";
    std::function<int (int)> adder()
    {
        gocpp::Defer defer;
        auto sum = 0;
        return [=](int x) mutable -> int
        {
            gocpp::Defer defer;
            sum += x;
            return sum;
        }
;
    }

    void main()
    {
        gocpp::Defer defer;
        auto [pos, neg] = std::tuple{adder(), adder()};
        for(auto i = 0; i < 10; i++)
        {
            mocklib::Println(pos(i), neg(- 2 * i));
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
