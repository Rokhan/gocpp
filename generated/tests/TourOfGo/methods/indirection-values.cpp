#include <complex>
#include <functional>
#include <iostream>
#include <string>
#include <tuple>
#include <vector>

#include "tests/TourOfGo/methods/indirection-values.h"
#include "gocpp/support.h"


namespace golang
{
    // convertSpecs[ImportSpec] Not implemented => "fmt";
    // convertSpecs[ImportSpec] Not implemented => "math";
    struct Vertex
    {
        float X;
        float Y;

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
    float Abs()
    {
        gocpp::Defer defer;
        return std::sqrt(v.X * v.X + v.Y * v.Y);
    }

    float AbsFunc(Vertex v)
    {
        gocpp::Defer defer;
        return std::sqrt(v.X * v.X + v.Y * v.Y);
    }

    void main()
    {
        gocpp::Defer defer;
        auto v = Vertex {3, 4};
        mocklib::Println(v.Abs());
        mocklib::Println(AbsFunc(v));
        auto p = [[TOKEN_ERROR: '&' ]] Vertex {4, 3};
        mocklib::Println(p.Abs());
        mocklib::Println(AbsFunc(!!EXPR_ERROR!! [*ast.StarExpr]));
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
