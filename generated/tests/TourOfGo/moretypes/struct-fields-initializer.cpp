#include <complex>
#include <functional>
#include <iostream>
#include <iomanip>
#include <map>
#include <string>
#include <tuple>
#include <vector>

#include "tests/TourOfGo/moretypes/struct-fields-initializer.h"
#include "gocpp/support.h"


namespace golang
{
    // convertSpecs[ImportSpec] Not implemented => "fmt";
    
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
        os << " " << Z;
        os << '}';
        return os;
    }

    std::ostream& operator<<(std::ostream& os, const Vertex& value)
    {
        return value.PrintTo(os);
    }

    
    Segment Segment::Init(void (init)(Segment&))
    {
        Segment value;
        init(value);
        return value;
    }

    std::ostream& Segment::PrintTo(std::ostream& os) const
    {
        os << '{';
        os << "" << Start;
        os << " " << End;
        os << '}';
        return os;
    }

    std::ostream& operator<<(std::ostream& os, const Segment& value)
    {
        return value.PrintTo(os);
    }

    auto v1 = Vertex {1, 2, 3};
    auto v2 = Vertex::Init([](Vertex& x) { x.X = 1; });
    auto v3 = Vertex {};
    auto v4 = Vertex::Init([](Vertex& x) { x.X = 1; x.Z = 3; });
    auto s1 = Segment::Init([](Segment& x) { x.Start = Vertex::Init([](Vertex& x) { x.X = 1; x.Z = 3; x.Y = 2; }); x.End = Vertex {1, 1, 1}; });
    void main()
    {
        gocpp::Defer defer;
        mocklib::Println(v1, v2, v3, v4, s1);
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
