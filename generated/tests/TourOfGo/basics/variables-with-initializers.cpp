// generated by GoCpp from file 'tests/TourOfGo/basics/variables-with-initializers.go'
#include <complex>
#include <functional>
#include <iostream>
#include <iomanip>
#include <map>
#include <string>
#include <tuple>
#include <vector>

#include "tests/TourOfGo/basics/variables-with-initializers.h"
#include "gocpp/support.h"

#include "golang/fmt/print.h"

namespace golang::main
{
    int i = 1;
    int j = 2;
    void main()
    {
        auto c = true;
        auto python = false;
        auto java = "no!";
        mocklib::Println(i, j, c, python, java);
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
