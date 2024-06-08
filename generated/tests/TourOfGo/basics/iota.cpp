#include <complex>
#include <functional>
#include <iostream>
#include <iomanip>
#include <map>
#include <string>
#include <tuple>
#include <vector>

#include "tests/TourOfGo/basics/iota.h"
#include "gocpp/support.h"

// TODO: package import not implemented
// #include "fmt/doc.h"
// #include "fmt/errors.h"
// #include "fmt/format.h"
// #include "fmt/print.h"
// #include "fmt/scan.h"

namespace golang::main
{
    int c0 = 0;
    int c1 = 1;
    int c2 = 2;
    int a = 1 << 0;
    int b = 1 << 1;
    int c = 1 << 2;
    int z0 = 0;
    int za = 1 << 1;
    int zb = 1 << 2;
    int zc = 1 << 3;
    int u = 0 * 42;
    double v = 1 * 42;
    int w = 2 * 42;
    int x = 0;
    int y = 0;
    int bit0 = 1 << 0;
    int mask0 = (1 << 0) - 1;
    int bit1 = 1 << 1;
    int mask1 = (1 << 1) - 1;
    int gocpp_id_0 = 1 << 2;
    int gocpp_id_1 = (1 << 2) - 1;
    int bit3 = 1 << 3;
    int mask3 = (1 << 3) - 1;
    void main()
    {
        mocklib::Printf("%v %v %v\n", c0, c1, c2);
        mocklib::Printf("%v %v %v\n", a, b, c);
        mocklib::Printf("%v %v %v %v\n", z0, za, zb, zc);
        mocklib::Printf("%v %v %v\n", u, v, w);
        mocklib::Printf("%v %v\n", x, y);
        mocklib::Printf("%v %v %v\n", bit0, bit1, bit3);
        mocklib::Printf("%v %v %v\n", mask0, mask1, mask3);
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
