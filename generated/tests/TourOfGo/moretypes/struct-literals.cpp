#include <complex>
#include <functional>
#include <iostream>
#include <iomanip>
#include <map>
#include <string>
#include <tuple>
#include <vector>

#include "tests/TourOfGo/moretypes/struct-literals.h"
#include "gocpp/support.h"


namespace golang
{
    // convertSpecs[ImportSpec] Not implemented => "fmt";
    struct Vertex
    {
        int X;
        int Y;

        using isGoStruct = void;

        static Vertex Init(void (init)(Vertex&))
        {
            Vertex value;
            init(value);
            return value;
        }

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
    auto v1 = Vertex {1, 2};
    auto v2 = Vertex::Init([](Vertex& x) { x.X = 1; });
    auto v3 = Vertex {};
    auto p = new Vertex {1, 2};
    void main()
    {
        gocpp::Defer defer;
        mocklib::Println(v1, p, v2, v3);
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
