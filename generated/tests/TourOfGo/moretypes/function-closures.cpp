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

// TODO: package import not implemented
// #include "fmt/doc.h"
// #include "fmt/errors.h"
// #include "fmt/format.h"
// #include "fmt/print.h"
// #include "fmt/scan.h"

namespace golang::main
{
    std::function<int (int)> adder()
    {
        auto sum = 0;
        return [=](int x) mutable -> int
        {
            sum += x;
            return sum;
        }
;
    }

    void main()
    {
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
        golang::main::main();
        return 0;
    }
    catch(const gocpp::GoPanic& ex)
    {
        std::cout << "Panic: " << ex.what() << std::endl;
        return -1;
    }
}
