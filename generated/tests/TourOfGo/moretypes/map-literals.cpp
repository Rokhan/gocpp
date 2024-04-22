#include <complex>
#include <functional>
#include <iostream>
#include <iomanip>
#include <map>
#include <string>
#include <tuple>
#include <vector>

#include "tests/TourOfGo/moretypes/map-literals.h"
#include "gocpp/support.h"


namespace golang
{
    // convertSpecs[ImportSpec] Not implemented => "fmt";
    
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

    gocpp::map<std::string, Vertex> m = gocpp::map<std::string, Vertex> {{ "Bell Labs", Vertex {40.68433, - 74.39967} }, { "Google", Vertex {37.42202, - 122.08408} }};
    void main()
    {
        gocpp::Defer defer;
        mocklib::Println(m);
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
