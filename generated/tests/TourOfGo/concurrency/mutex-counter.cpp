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


namespace golang
{
    // convertSpecs[ImportSpec] Not implemented => "fmt";
    // convertSpecs[ImportSpec] Not implemented => "sync";
    // convertSpecs[ImportSpec] Not implemented => "time";
    
    SafeCounter SafeCounter::Init(void (init)(SafeCounter&))
    {
        SafeCounter value;
        init(value);
        return value;
    }

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
        gocpp::Defer defer;
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
        gocpp::Defer defer;
        auto c = SafeCounter::Init([](SafeCounter& x) { x.v = gocpp::make(gocpp::Tag<gocpp::map<std::string,int>>()); });
        for(auto i = 0; i < 1000; i++)
        {
            gocpp::global_pool().enqueue_detach([=]{ Inc(gocpp::recv(c), "somekey"); });
        }
        mocklib::Sleep(time::Second);
        mocklib::Println(Value(gocpp::recv(c), "somekey"));
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
