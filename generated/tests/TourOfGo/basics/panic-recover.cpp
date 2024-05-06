#include <complex>
#include <functional>
#include <iostream>
#include <iomanip>
#include <map>
#include <string>
#include <tuple>
#include <vector>

#include "tests/TourOfGo/basics/panic-recover.h"
#include "gocpp/support.h"


namespace golang
{
    // convertSpecs[ImportSpec] Not implemented => "fmt";
    void main()
    {
        f();
        mocklib::Println("Returned normally from f.");
    }

    void f()
    {
        gocpp::Defer defer;
        defer.push_back([=]{ [=]() mutable -> void
        {
            if(auto r = recover(); r != nullptr)
            {
                mocklib::Println("Recovered in f", r);
            }
        }
(); });
        defer.push_back([=]{ [=]() mutable -> void
        {
            mocklib::Println("Simple defer in f");
        }
(); });
        mocklib::Println("Calling g.");
        g(0);
        mocklib::Println("Returned normally from g.");
    }

    void g(int i)
    {
        gocpp::Defer defer;
        if(i > 3)
        {
            mocklib::Println("Panicking!");
            gocpp::panic(mocklib::Sprintf("%v", i));
        }
        defer.push_back([=]{ mocklib::Println("Defer in g", i); });
        mocklib::Println("Printing in g", i);
        g(i + 1);
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
