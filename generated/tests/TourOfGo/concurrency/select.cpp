#include <complex>
#include <functional>
#include <iostream>
#include <iomanip>
#include <map>
#include <string>
#include <tuple>
#include <vector>

#include "tests/TourOfGo/concurrency/select.h"
#include "gocpp/support.h"


namespace golang
{
    // convertSpecs[ImportSpec] Not implemented => "fmt";
    void fibonacci(gocpp::channel<int> c, gocpp::channel<int> quit)
    {
        gocpp::Defer defer;
        auto [x, y] = std::tuple{0, 1};
        for(; ; )
        {
            //Go select emulation
            {
                int conditionId = -1;
                if(c.trySend(x)) { conditionId = 0; }
                else if(auto [gocpp_ignored , ok] = quit.tryRecv(); ok) { conditionId = 1; }
                switch(conditionId)
                {
                    case 0:
                        std::tie(x, y) = std::tuple{y, x + y};
                        break;
                    case 1:
                        mocklib::Println("quit");
                        return;
                        break;
                }
            }
            std::this_thread::yield();
        }
    }

    void main()
    {
        gocpp::Defer defer;
        auto c = gocpp::make(gocpp::Tag<gocpp::channel<int>>());
        auto quit = gocpp::make(gocpp::Tag<gocpp::channel<int>>());
        gocpp::go([&]{ [=]() mutable -> void
        {
            gocpp::Defer defer;
            for(auto i = 0; i < 10; i++)
            {
                mocklib::Println(c.recv());
            }
            quit.send(0);
        }
(); });
        fibonacci(c, quit);
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
