#include <complex>
#include <functional>
#include <iostream>
#include <iomanip>
#include <map>
#include <string>
#include <tuple>
#include <vector>

#include "tests/TourOfGo/moretypes/array.h"
#include "gocpp/support.h"

// TODO: package import not implemented
// #include "fmt/doc.h"
// #include "fmt/errors.h"
// #include "fmt/format.h"
// #include "fmt/print.h"
// #include "fmt/scan.h"

namespace golang::main
{
    void main()
    {
        gocpp::array<std::string, 2> a = {};
        a[0] = "Hello";
        a[1] = "World";
        mocklib::Println(a[0], a[1]);
        mocklib::Println(a);
        auto primes = gocpp::array<int, 6> {2, 3, 5, 7, 11, 13};
        mocklib::Println(primes);
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
