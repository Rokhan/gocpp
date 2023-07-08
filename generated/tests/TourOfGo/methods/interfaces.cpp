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
        auto f = MyFloat(- mocklib::Sqrt2);
        auto v = Vertex {3, 4};
        a = f;
        a = & v;
        a = v;
        mocklib::Println(Abs(gocpp::recv(a)));
    }

    // using MyFloat = double;
    double Abs(MyFloat f)
    {
        gocpp::Defer defer;
        if(; f < 0)
        {
            return double(- f);
        }
        return double(f);
    }

    struct Vertex
    {
        double X;
        double Y;

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

    double Abs(Vertex* v)
    {
        gocpp::Defer defer;
        return std::sqrt(v->X * v->X + v->Y * v->Y);
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
