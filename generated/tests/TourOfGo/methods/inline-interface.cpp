#include <complex>
#include <functional>
#include <iostream>
#include <iomanip>
#include <map>
#include <string>
#include <tuple>
#include <vector>

#include "tests/TourOfGo/methods/inline-interface.h"
#include "gocpp/support.h"


namespace golang
{
    // convertSpecs[ImportSpec] Not implemented => "fmt";
    // convertSpecs[ImportSpec] Not implemented => "math";
    // using MyInt = int;
    // using MyFloat = double;
    double Abs(MyInt i)
    {
        gocpp::Defer defer;
        return std::sqrt(double(i * i));
    }

    double Abs(MyFloat f)
    {
        gocpp::Defer defer;
        return std::sqrt(double(f * f));
    }

    
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

    void main()
    {
        gocpp::Defer defer;
        !!TYPE_EXPR_ERROR!! [*ast.InterfaceType] i;
        describe(i);
        i = MyInt(42);
        describe(i);
        i = MyFloat(42.0);
        describe(i);
        i = Vertex {4, 2};
        describe(i);
    }

    void describe(!!TYPE_EXPR_ERROR!! [*ast.InterfaceType] i)
    {
        gocpp::Defer defer;
        if(i != nullptr)
        {
            mocklib::Printf("(%v, %T) => %v\n", i, i, Abs(gocpp::recv(i)));
        }
        else
        {
            mocklib::Printf("(%v, %T)\n", i, i);
        }
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
