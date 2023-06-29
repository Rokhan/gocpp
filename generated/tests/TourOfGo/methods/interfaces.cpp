#include <complex>
#include <functional>
#include <iostream>
#include <iomanip>
#include <map>
#include <string>
#include <tuple>
#include <vector>

#include "tests/TourOfGo/methods/interfaces.h"
#include "gocpp/support.h"


namespace golang
{
    // convertSpecs[ImportSpec] Not implemented => "fmt";
    // convertSpecs[ImportSpec] Not implemented => "math";
    !!TYPE_SPEC_ERROR!! [*ast.TypeSpec];
    void main()
    {
        gocpp::Defer defer;
        Abser a;
        auto f = MyFloat(- math::Sqrt2);
        auto v = Vertex {3, 4};
        a = f;
        a = [[TOKEN_ERROR: '&' ]] v;
        a = v;
        mocklib::Println(a.Abs());
    }

    float MyFloat;
    float Abs()
    {
        gocpp::Defer defer;
        if(; f < 0)
        {
            return float(- f);
        }
        return float(f);
    }

    struct Vertex
    {
        float X;
        float Y;

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
    float Abs()
    {
        gocpp::Defer defer;
        return std::sqrt(v.X * v.X + v.Y * v.Y);
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
