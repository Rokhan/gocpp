#include <complex>
#include <functional>
#include <iostream>
#include <iomanip>
#include <map>
#include <string>
#include <tuple>
#include <vector>

#include "tests/TourOfGo/moretypes/maps.h"
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
        os << "" << Lat;
        os << " " << Long;
        os << '}';
        return os;
    }

    std::ostream& operator<<(std::ostream& os, const Vertex& value)
    {
        return value.PrintTo(os);
    }

    gocpp::map<std::string, Vertex> m;
    void main()
    {
        gocpp::Defer defer;
        m = gocpp::make(gocpp::Tag<gocpp::map<std::string, Vertex>>());
        m["Bell Labs"] = Vertex {40.68433, - 74.39967};
        mocklib::Println(m["Bell Labs"]);
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
