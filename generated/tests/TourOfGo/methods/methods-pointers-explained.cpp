#include <complex>
#include <functional>
#include <iostream>
#include <string>
#include <tuple>
#include <vector>

#include "tests/TourOfGo/methods/methods-pointers-explained.h"
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
    float Abs(Vertex v)
    {
        gocpp::Defer defer;
        return std::sqrt(v.X * v.X + v.Y * v.Y);
    }

    void Scale(!!TYPE_EXPR_ERROR!! [*ast.StarExpr] v, float f)
    {
        gocpp::Defer defer;
        v.X = v.X * f;
        v.Y = v.Y * f;
    }

    void main()
    {
        gocpp::Defer defer;
        auto v = Vertex {3, 4};
        Scale([[TOKEN_ERROR: '&' ]] v, 10);
        mocklib::Println(Abs(v));
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
