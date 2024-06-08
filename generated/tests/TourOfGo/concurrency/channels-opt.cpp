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

// TODO: package import not implemented
// #include "fmt/doc.h"
// #include "fmt/errors.h"
// #include "fmt/format.h"
// #include "fmt/print.h"
// #include "fmt/scan.h"
// #include "time/format.h"
// #include "time/format_rfc3339.h"
// #include "time/sleep.h"
// #include "time/sys_windows.h"
// #include "time/tick.h"
// #include "time/time.h"
// #include "time/zoneinfo.h"
// #include "time/zoneinfo_abbrs_windows.h"
// #include "time/zoneinfo_goroot.h"
// #include "time/zoneinfo_read.h"
// #include "time/zoneinfo_windows.h"

namespace golang::main
{
    void fill(gocpp::channel<int> c)
    {
        for(; ; )
        {
            mocklib::Sleep(5 * mocklib::Millisecond);
            c.send(0);
        }
    }

    void main()
    {
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
        golang::main::main();
        return 0;
    }
    catch(const gocpp::GoPanic& ex)
    {
        std::cout << "Panic: " << ex.what() << std::endl;
        return -1;
    }
}
