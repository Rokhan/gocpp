// generated by GoCpp from file 'tests/TourOfGo/moretypes/struct-literals.go'
#include <complex>
#include <functional>
#include <iostream>
#include <iomanip>
#include <map>
#include <string>
#include <tuple>
#include <vector>

#include "tests/TourOfGo/moretypes/struct-literals.h"
#include "gocpp/support.h"

#include "golang/fmt/print.h"

namespace golang::main
{
    namespace rec
    {
        using namespace mocklib::rec;
    }

    
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

    Vertex v1 = Vertex {1, 2};
    Vertex v2 = gocpp::Init<Vertex>([](auto& x) {
        x.X = 1;
    });
    Vertex v3 = Vertex {};
    Vertex* p = new Vertex {1, 2};
    void main()
    {
        mocklib::Println(v1, p, v2, v3);
    }

}

int main()
{
    try
    {
        std::cout << std::boolalpha << std::setprecision(5) << std::fixed;
        golang::main::main();
        return 0;
    }
    catch(const gocpp::GoPanic& ex)
    {
        std::cout << "Panic: " << ex.what() << std::endl;
        return -1;
    }
}
