#include <complex>
#include <functional>
#include <iostream>
#include <string>
#include <tuple>
#include <vector>

#include "tests/TourOfGo/basics/multiple-results.h"
#include "gocpp/support.h"


namespace golang
{
    // convertSpecs[ImportSpec] Not implemented => "fmt";
    std::tuple<std::string, std::string> swap(std::string x, std::string y)
    {
        gocpp::Defer defer;
        return {y, x};
    }

    void main()
    {
        gocpp::Defer defer;
        auto [a, b] = swap("hello", "world");
        auto [s, i, f] = std::tuple{"str", 5, 3.14159};
        mocklib::Println(a, b);
        mocklib::Println(s, i, f);
    }

}

int main()
{
    try
    {
        std::cout << std::boolalpha;
        golang::main();
        return 0;
    }
    catch(const gocpp::GoPanic& ex)
    {
        std::cout << "Panic: " << ex.what() << std::endl;
        return -1;
    }
}
