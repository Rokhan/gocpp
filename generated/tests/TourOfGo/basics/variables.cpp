#include <complex>
#include <functional>
#include <iostream>
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
        gocpp::Defer defer;
        int i;
        mocklib::Println(i, c, python, java);
        mocklib::Println(ii, jj, kk);
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
