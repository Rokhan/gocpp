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


namespace golang
{
    // convertSpecs[ImportSpec] Not implemented => "fmt";
    gocpp::array<byte, 4> IPAddr;
    void main()
    {
        gocpp::Defer defer;
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
        golang::main();
        return 0;
    }
    catch(const gocpp::GoPanic& ex)
    {
        std::cout << "Panic: " << ex.what() << std::endl;
        return -1;
    }
}
