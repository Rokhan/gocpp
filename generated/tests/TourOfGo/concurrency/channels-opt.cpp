#include <complex>
#include <functional>
#include <iostream>
#include <iomanip>
#include <map>
#include <string>
#include <tuple>
#include <vector>

#include "tests/TourOfGo/concurrency/channels-opt.h"
#include "gocpp/support.h"


namespace golang
{
    // convertSpecs[ImportSpec] Not implemented => "fmt";
    // convertSpecs[ImportSpec] Not implemented => "time";
    void fill(gocpp::channel<int> c)
    {
        gocpp::Defer defer;
        for(; ; )
        {
            mocklib::Sleep(5 * mocklib::Millisecond);
            c.send(0);
        }
    }

    void main()
    {
        gocpp::Defer defer;
        auto c = gocpp::make(gocpp::Tag<gocpp::channel<int>>(), 5);
        gocpp::go([&]{ fill(c); });
        auto [xx, ok] = c.recv();
        mocklib::Println(xx, ok);
        int zz;
        std::tie(zz, ok) = c.recv();
        mocklib::Println(zz, ok);
        close(c);
        bool okok;
        std::tie(zz, okok) = c.recv();
        mocklib::Println(zz, okok);
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
