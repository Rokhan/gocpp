#include <complex>
#include <functional>
#include <iostream>
#include <iomanip>
#include <map>
#include <string>
#include <tuple>
#include <vector>

#include "tests/TourOfGo/methods/exercise-stringer.h"
#include "gocpp/support.h"

// TODO: package import not implemented
// #include "fmt/doc.h"
// #include "fmt/errors.h"
// #include "fmt/format.h"
// #include "fmt/print.h"
// #include "fmt/scan.h"

namespace golang::main
{
    std::string String(IPAddr ip)
    {
        return mocklib::Sprintf("%v.%v.%v.%v", ip[0], ip[1], ip[2], ip[3]);
    }

    void main()
    {
        auto hosts = gocpp::map<std::string, IPAddr> {{ "loopback",  {127, 0, 0, 1} }, { "googleDNS",  {8, 8, 8, 8} }};
        for(auto [name, ip] : hosts)
        {
            mocklib::Printf("%v: %v\n", name, ip);
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
