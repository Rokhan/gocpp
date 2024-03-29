#include <complex>
#include <functional>
#include <iostream>
#include <iomanip>
#include <map>
#include <string>
#include <tuple>
#include <vector>

#include "tests/TourOfGo/methods/methods-with-pointer-receivers.h"
#include "gocpp/support.h"


namespace golang
{
    // convertSpecs[ImportSpec] Not implemented => "fmt";
    // convertSpecs[ImportSpec] Not implemented => "math";
    
    Vertex Vertex::Init(void (init)(Vertex&))
    {
        Vertex value;
        init(value);
        return value;
    }

    std::ostream& Vertex::PrintTo(std::ostream& os) const
    {
        os << '{';
        os << "" << X;
        os << " " << Y;
        os << '}';
        return os;
    }

    std::ostream& operator<<(std::ostream& os, const Vertex& value)
    {
        return value.PrintTo(os);
    }

    void Scale(Vertex* v, double f)
    {
        gocpp::Defer defer;
        v->X = v->X * f;
        v->Y = v->Y * f;
    }

    double Abs(Vertex* v)
    {
        gocpp::Defer defer;
        return std::sqrt(v->X * v->X + v->Y * v->Y);
    }

    void main()
    {
        gocpp::Defer defer;
        auto v = new Vertex {3, 4};
        mocklib::Printf("Before scaling: %+v, Abs: %v\n", v, Abs(gocpp::recv(v)));
        Scale(gocpp::recv(v), 5);
        mocklib::Printf("After scaling: %+v, Abs: %v\n", v, Abs(gocpp::recv(v)));
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
