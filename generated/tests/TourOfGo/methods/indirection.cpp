// generated by GoCpp from file 'tests/TourOfGo/methods/indirection.go'
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

#include "golang/fmt/print.h"

namespace golang::main
{
    
    template<typename T> requires gocpp::GoStruct<T>
    Vertex::operator T()
    {
        T result;
        result.X = this->X;
        result.Y = this->Y;
        return result;
    }

    template<typename T> requires gocpp::GoStruct<T>
    bool Vertex::operator==(const T& ref) const
    {
        if (X != ref.X) return false;
        if (Y != ref.Y) return false;
        return true;
    }

    std::ostream& Vertex::PrintTo(std::ostream& os) const
    {
        os << '{';
        os << "" << X;
        os << " " << Y;
        os << '}';
        return os;
    }

    std::ostream& operator<<(std::ostream& os, const struct Vertex& value)
    {
        return value.PrintTo(os);
    }

    void Scale(struct Vertex* v, double f)
    {
        v->X = v->X * f;
        v->Y = v->Y * f;
    }

    void ScaleFunc(Vertex* v, double f)
    {
        v->X = v->X * f;
        v->Y = v->Y * f;
    }

    void main()
    {
        auto v = Vertex {3, 4};
        Scale(gocpp::recv(v), 2);
        ScaleFunc(& v, 10);
        auto p = new Vertex {4, 3};
        Scale(gocpp::recv(p), 3);
        ScaleFunc(p, 8);
        mocklib::Println(v, p);
    }

}

int main()
{
    try
    {
        std::cout << std::boolalpha << std::fixed << std::setprecision(5);
        golang::main::main();
        return 0;
    }
    catch(const gocpp::GoPanic& ex)
    {
        std::cout << "Panic: " << ex.what() << std::endl;
        return -1;
    }
}
