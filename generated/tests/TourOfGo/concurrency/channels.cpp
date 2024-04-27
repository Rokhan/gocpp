#include <complex>
#include <functional>
#include <iostream>
#include <iomanip>
#include <map>
#include <string>
#include <tuple>
#include <vector>

#include "tests/TourOfGo/concurrency/channels.h"
#include "gocpp/support.h"


namespace golang
{
    // convertSpecs[ImportSpec] Not implemented => "fmt";
    void sum(gocpp::slice<int> s, gocpp::channel<int> c)
    {
        gocpp::Defer defer;
        auto sum = 0;
        for(auto [_, v] : s)
        {
            sum += v;
        }
        c.send(sum);
    }

    void main()
    {
        gocpp::Defer defer;
        auto s = gocpp::slice<int> {7, 2, 8, - 9, 4, 0};
        auto c = gocpp::make(gocpp::Tag<gocpp::channel<int>>());
        gocpp::global_pool().enqueue_detach([&]{ sum(s.make_slice(0, len(s) / 2), c); });
        gocpp::global_pool().enqueue_detach([&]{ sum(s.make_slice(len(s) / 2), c); });
        auto [x, y] = std::tuple{c.recv(), c.recv()};
        mocklib::Println(x, y, x + y);
        c = gocpp::make(gocpp::Tag<gocpp::channel<int>>());
        gocpp::global_pool().enqueue_detach([&]{ sum(s.make_slice(0, len(s) / 2), c); });
        gocpp::global_pool().enqueue_detach([&]{ sum(s.make_slice(len(s) / 2), c); });
        x = c.recv();
        y = c.recv();
        mocklib::Println(x, y, x + y);
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
