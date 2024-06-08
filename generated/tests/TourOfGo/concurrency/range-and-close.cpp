#include <complex>
#include <functional>
#include <iostream>
#include <iomanip>
#include <map>
#include <string>
#include <tuple>
#include <vector>

#include "tests/TourOfGo/concurrency/range-and-close.h"
#include "gocpp/support.h"

// TODO: package import not implemented
// #include "fmt/doc.h"
// #include "fmt/errors.h"
// #include "fmt/format.h"
// #include "fmt/print.h"
// #include "fmt/scan.h"

namespace golang::main
{
    void fibonacci(int n, gocpp::channel<int> c)
    {
        auto [x, y] = std::tuple{0, 1};
        for(auto i = 0; i < n; i++)
        {
            c.send(x);
            std::tie(x, y) = std::tuple{y, x + y};
        }
        close(c);
    }

    void main()
    {
        auto c = gocpp::make(gocpp::Tag<gocpp::channel<int>>(), 10);
        gocpp::go([&]{ fibonacci(cap(c), c); });
        for(auto [i, gocpp_ignored] : c)
        {
            mocklib::Println(i);
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
