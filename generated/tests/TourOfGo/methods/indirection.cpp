#include <complex>
#include <functional>
#include <iostream>
#include <iomanip>
#include <map>
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
;
    void Scale(Vertex* v, double f)
    {
        gocpp::Defer defer;
        v.X = v.X * f;
        v.Y = v.Y * f;
    }

    void ScaleFunc(Vertex* v, double f)
    {
        gocpp::Defer defer;
        v.X = v.X * f;
        v.Y = v.Y * f;
    }

    void main()
    {
        gocpp::Defer defer;
        auto v = Vertex {3, 4};
        Scale(v, 2);
        ScaleFunc(& v, 10);
        auto p = new Vertex {4, 3};
        Scale(p, 3);
        ScaleFunc(p, 8);
        mocklib::Println(v, p);
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
