#include <complex>
#include <functional>
#include <iostream>
#include <string>
#include <tuple>
#include <vector>

#include "tests/TourOfGo/methods/exercise-stringer.h"
#include "gocpp/support.h"


namespace golang
{
    // convertSpecs[ImportSpec] Not implemented => "fmt";
    gocpp::array<byte, 4> IPAddr;
    void main()
    {
        gocpp::Defer defer;
        auto hosts = !!TYPE_EXPR_ERROR!! [*ast.MapType] {!!EXPR_ERROR!! [*ast.KeyValueExpr], !!EXPR_ERROR!! [*ast.KeyValueExpr]};
        for(auto [name, ip] : hosts)
        {
            mocklib::Printf("%v: %v\n", name, ip);
        }
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
