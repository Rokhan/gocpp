#include <complex>
#include <functional>
#include <iostream>
#include <iomanip>
#include <map>
#include <string>
#include <tuple>
#include <vector>

#include "tests/TourOfGo/moretypes/exercise-fibonacci-closure.h"
#include "gocpp/support.h"


namespace golang
{
    // convertSpecs[ImportSpec] Not implemented => "fmt";
    std::function<int ()> fibonacci()
    {
        gocpp::Defer defer;
        auto f0 = 0;
        auto f1 = 1;
        return [=]() mutable -> int
        {
            gocpp::Defer defer;
            auto result = f0;
            auto f2 = f0 + f1;
            f0 = f1;
            f1 = f2;
            return result;
        }
;
    }

    void main()
    {
        gocpp::Defer defer;
        auto f = fibonacci();
        for(auto i = 0; i < 10; i++)
        {
            mocklib::Println(f());
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
