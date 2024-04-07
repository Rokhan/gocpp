#include <complex>
#include <functional>
#include <iostream>
#include <iomanip>
#include <map>
#include <string>
#include <tuple>
#include <vector>

#include "tests/TourOfGo/concurrency/goroutines.h"
#include "gocpp/support.h"


namespace golang
{
    // convertSpecs[ImportSpec] Not implemented => "fmt";
    // convertSpecs[ImportSpec] Not implemented => "time";
    void say(std::string s)
    {
        gocpp::Defer defer;
        for(auto i = 0; i < 5; i++)
        {
            mocklib::Sleep(100 * mocklib::Millisecond);
            mocklib::Println(s);
        }
    }

    void main()
    {
        gocpp::Defer defer;
        gocpp::global_pool().enqueue_detach([=]{ say("world"); });
        mocklib::Sleep(50 * mocklib::Millisecond);
        say("hello");
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
