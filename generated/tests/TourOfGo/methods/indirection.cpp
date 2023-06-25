#include <complex>
#include <functional>
#include <iostream>
#include <string>
#include <tuple>
#include <vector>

#include "tests/TourOfGo/methods/indirection.h"
#include "gocpp/support.h"


namespace golang
{
    // convertSpecs[ImportSpec] Not implemented => "fmt";
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
    void Scale(float f)
    {
        gocpp::Defer defer;
        v.X = v.X * f;
        v.Y = v.Y * f;
    }

    void ScaleFunc(!!TYPE_EXPR_ERROR!! [*ast.StarExpr] v, float f)
    {
        gocpp::Defer defer;
        v.X = v.X * f;
        v.Y = v.Y * f;
    }

    void main()
    {
        gocpp::Defer defer;
        auto v = Vertex {3, 4};
        v.Scale(2);
        ScaleFunc([[TOKEN_ERROR: '&' ]] v, 10);
        auto p = [[TOKEN_ERROR: '&' ]] Vertex {4, 3};
        p.Scale(3);
        ScaleFunc(p, 8);
        mocklib::Println(v, p);
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
