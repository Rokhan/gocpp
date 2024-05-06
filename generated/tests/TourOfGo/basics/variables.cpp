#include <complex>
#include <functional>
#include <iostream>
#include <iomanip>
#include <map>
#include <string>
#include <tuple>
#include <vector>

#include "tests/TourOfGo/basics/variables.h"
#include "gocpp/support.h"


namespace golang
{
    // convertSpecs[ImportSpec] Not implemented => "fmt";
    bool c;
    bool python;
    bool java;
    int ii = 3;
    int jj = 4;
    int kk = 5;
    void main()
    {
        int i = {};
        mocklib::Println(i, c, python, java);
        mocklib::Println(ii, jj, kk);
        std::tie(ii, jj, kk) = std::tuple{6, 7, 8};
        mocklib::Println(ii, jj, kk);
        auto [ii, zz, kk] = std::tuple{9, 10, 11};
        mocklib::Println(ii, zz, kk);
        {
            auto [ii, zz, ll] = std::tuple{12, 13, 14};
            mocklib::Println(ii, zz, ll);
        }
        mocklib::Println(ii, zz, kk);
        if(true)
        {
            auto [ii, zz, ll] = std::tuple{15, 16, 17};
            mocklib::Println(ii, zz, ll);
        }
        mocklib::Println(ii, zz, kk);
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
