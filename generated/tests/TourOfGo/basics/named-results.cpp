#include <complex>
#include <functional>
#include <iostream>
#include <string>
#include <tuple>
#include <vector>

#include "tests/TourOfGo/basics/named-results.h"
#include "gocpp/support.h"


namespace golang
{
    // convertSpecs[ImportSpec] Not implemented => "fmt";
    std::tuple<int, int> split(int sum)
    {
        gocpp::Defer defer;
        int x;
        int y;
        x = sum * 4 / 9;
        y = sum - x;
        return {x, y};
    }

    void main()
    {
        gocpp::Defer defer;
        mocklib::Println(split(17));
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
