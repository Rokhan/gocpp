#include <complex>
#include <functional>
#include <iostream>
#include <string>
#include <tuple>
#include <vector>

#include "tests/TourOfGo/moretypes/map-literals-continued.h"
#include "gocpp/support.h"


namespace golang
{
    // convertSpecs[ImportSpec] Not implemented => "fmt";
    struct Vertex
    {
        float Lat;
        float Long;

        const bool isGoStruct = true;

        std::ostream& PrintTo(std::ostream& os) const
        {
            os << '{';
            os << "" << Lat;
            os << " " << Long;
            os << '}';
            return os;
        }
    };
    std::ostream& operator<<(std::ostream& os, const Vertex& value)
    {
        return value.PrintTo(os);
    }

;
    auto m = !!TYPE_EXPR_ERROR!! [*ast.MapType] {!!EXPR_ERROR!! [*ast.KeyValueExpr], !!EXPR_ERROR!! [*ast.KeyValueExpr]};
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
        std::cout << std::boolalpha;
        golang::main();
        return 0;
    }
    catch(const gocpp::GoPanic& ex)
    {
        std::cout << "Panic: " << ex.what() << std::endl;
        return -1;
    }
}
