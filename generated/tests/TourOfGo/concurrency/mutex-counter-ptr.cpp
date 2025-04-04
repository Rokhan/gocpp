// generated by GoCpp from file 'tests/TourOfGo/concurrency/mutex-counter-ptr.go'
#include <complex>
#include <functional>
#include <iostream>
#include <iomanip>
#include <map>
#include <string>
#include <tuple>
#include <vector>

#include "tests/TourOfGo/concurrency/mutex-counter-ptr.h"
#include "gocpp/support.h"

#include "golang/fmt/print.h"
#include "golang/sync/mutex.h"
#include "golang/time/sleep.h"
#include "golang/time/time.h"

namespace golang::main
{
    
    template<typename T> requires gocpp::GoStruct<T>
    SafeCounter::operator T()
    {
        T result;
        result.mu = this->mu;
        result.v = this->v;
        return result;
    }

    template<typename T> requires gocpp::GoStruct<T>
    bool SafeCounter::operator==(const T& ref) const
    {
        if (mu != ref.mu) return false;
        if (v != ref.v) return false;
        return true;
    }

    std::ostream& SafeCounter::PrintTo(std::ostream& os) const
    {
        os << '{';
        os << "" << mu;
        os << " " << v;
        os << '}';
        return os;
    }

    std::ostream& operator<<(std::ostream& os, const struct SafeCounter& value)
    {
        return value.PrintTo(os);
    }

    void Inc(struct SafeCounter* c, std::string key)
    {
        Lock(gocpp::recv(c->mu));
        c->v[key]++;
        Unlock(gocpp::recv(c->mu));
    }

    int Value(struct SafeCounter* c, std::string key)
    {
        gocpp::Defer defer;
        Lock(gocpp::recv(c->mu));
        defer.push_back([=]{ Unlock(gocpp::recv(c->mu)); });
        return c->v[key];
    }

    void main()
    {
        auto c = gocpp::InitPtr<SafeCounter>([](SafeCounter& x) { x.v = gocpp::make(gocpp::Tag<gocpp::map<std::string, int>>()); });
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
