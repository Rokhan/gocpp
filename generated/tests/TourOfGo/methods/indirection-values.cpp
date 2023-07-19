#include <complex>
#include <functional>
#include <iostream>
#include <iomanip>
#include <map>
#include <string>
#include <tuple>
#include <vector>

#include "tests/TourOfGo/methods/indirection-values.h"
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

    double Abs(Vertex v)
    {
        gocpp::Defer defer;
        return std::sqrt(v.X * v.X + v.Y * v.Y);
    }

    double AbsFunc(Vertex v)
    {
        gocpp::Defer defer;
        return std::sqrt(v.X * v.X + v.Y * v.Y);
    }

    void main()
    {
        gocpp::Defer defer;
        auto v = Vertex {3, 4};
        mocklib::Println(Abs(gocpp::recv(v)));
        mocklib::Println(AbsFunc(v));
        auto p = new Vertex {4, 3};
        mocklib::Println(Abs(gocpp::recv(p)));
        mocklib::Println(AbsFunc(*p));
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
