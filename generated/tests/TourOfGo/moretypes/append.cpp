#include <complex>
#include <functional>
#include <iostream>
#include <string>
#include <tuple>
#include <vector>

#include "tests/TourOfGo/moretypes/append.h"
#include "gocpp/support.h"


namespace golang
{
    // convertSpecs[ImportSpec] Not implemented => "fmt";
    void main()
    {
        gocpp::Defer defer;
        gocpp::slice<int> s;
        printSlice(s);
        s = append(s, 0);
        printSlice(s);
        s = append(s, 1);
        printSlice(s);
        s = append(s, 2, 3, 4);
        printSlice(s);
        appendValue(s, 17);
        printSlice(s);
    }

    void printSlice(gocpp::slice<int> s)
    {
        gocpp::Defer defer;
        mocklib::Printf("## len=%v cap=%v %v\n", len(s), cap(s), s);
    }

    void appendValue(gocpp::slice<int> s, int value)
    {
        gocpp::Defer defer;
        s = append(s, value);
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
