#include <complex>
#include <functional>
#include <iostream>
#include <iomanip>
#include <map>
#include <string>
#include <tuple>
#include <vector>

#include "tests/TourOfGo/moretypes/slice-len-cap.h"
#include "gocpp/support.h"


namespace golang
{
    // convertSpecs[ImportSpec] Not implemented => "fmt";
    void main()
    {
        auto s = gocpp::slice<int> {2, 3, 5, 7, 11, 13};
        printSlice(s);
        s = s.make_slice(0, 0);
        printSlice(s);
        s = s.make_slice(0, 4);
        printSlice(s);
        s = s.make_slice(2);
        printSlice(s);
    }

    void printSlice(gocpp::slice<int> s)
    {
        mocklib::Printf("len=%v cap=%v %v\n", len(s), cap(s), s);
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
