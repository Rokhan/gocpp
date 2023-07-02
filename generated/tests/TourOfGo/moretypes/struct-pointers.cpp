#include <complex>
#include <functional>
#include <iostream>
#include <iomanip>
#include <map>
#include <string>
#include <tuple>
#include <vector>

#include "tests/TourOfGo/moretypes/struct-pointers.h"
#include "gocpp/support.h"


namespace golang
{
    // convertSpecs[ImportSpec] Not implemented => "fmt";
    struct Vertex
    {
        int X;
        int Y;

        using isGoStruct = void;

        std::ostream& PrintTo(std::ostream& os) const
        {
            os << '{';
            os << "" << X;
            os << " " << Y;
            os << '}';
            return os;
        }
    };

    std::ostream& operator<<(std::ostream& os, const Vertex& value)
    {
        return value.PrintTo(os);
    }
;
    void main()
    {
        gocpp::Defer defer;
        auto v = Vertex {1, 2};
        auto p = & v;
        p.X = 1e9;
        mocklib::Println(v);
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
