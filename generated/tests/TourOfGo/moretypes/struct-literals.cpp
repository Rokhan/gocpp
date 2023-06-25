#include <complex>
#include <functional>
#include <iostream>
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

        const bool isGoStruct = true;

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
    auto v2 = Vertex {!!EXPR_ERROR!! [*ast.KeyValueExpr]};
    auto v3 = Vertex {};
    auto p = [[TOKEN_ERROR: '&' ]] Vertex {1, 2};
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
