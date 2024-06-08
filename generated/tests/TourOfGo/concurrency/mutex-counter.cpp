#include <complex>
#include <functional>
#include <iostream>
#include <iomanip>
#include <map>
#include <string>
#include <tuple>
#include <vector>

#include "tests/TourOfGo/concurrency/mutex-counter.h"
#include "gocpp/support.h"

// TODO: package import not implemented
// #include "fmt/doc.h"
// #include "fmt/errors.h"
// #include "fmt/format.h"
// #include "fmt/print.h"
// #include "fmt/scan.h"
// #include "sync/cond.h"
// #include "sync/map.h"
// #include "sync/mutex.h"
// #include "sync/once.h"
// #include "sync/oncefunc.h"
// #include "sync/pool.h"
// #include "sync/poolqueue.h"
// #include "sync/runtime.h"
// #include "sync/runtime2.h"
// #include "sync/rwmutex.h"
// #include "sync/waitgroup.h"
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
    
    std::ostream& SafeCounter::PrintTo(std::ostream& os) const
    {
        os << '{';
        os << "" << mu;
        os << " " << v;
        os << '}';
        return os;
    }

    std::ostream& operator<<(std::ostream& os, const SafeCounter& value)
    {
        return value.PrintTo(os);
    }

    void Inc(SafeCounter* c, std::string key)
    {
        Lock(gocpp::recv(c->mu));
        c->v[key]++;
        Unlock(gocpp::recv(c->mu));
    }

    int Value(SafeCounter* c, std::string key)
    {
        gocpp::Defer defer;
        Lock(gocpp::recv(c->mu));
        defer.push_back([=]{ Unlock(gocpp::recv(c->mu)); });
        return c->v[key];
    }

    void main()
    {
        auto c = gocpp::Init<SafeCounter>([](SafeCounter& x) { x.v = gocpp::make(gocpp::Tag<gocpp::map<std::string, int>>()); });
        for(auto i = 0; i < 1000; i++)
        {
            gocpp::go([&]{ Inc(gocpp::recv(c), "somekey"); });
        }
        mocklib::Sleep(mocklib::Second);
        mocklib::Println("result: ", Value(gocpp::recv(c), "somekey"));
        mocklib::Println("expected: ", 1000);
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
