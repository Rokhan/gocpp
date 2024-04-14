#include <complex>
#include <functional>
#include <iostream>
#include <iomanip>
#include <map>
#include <string>
#include <tuple>
#include <vector>

#include "tests/TourOfGo/methods/type-assertions.h"
#include "gocpp/support.h"


namespace golang
{
    // convertSpecs[ImportSpec] Not implemented => "fmt";
    void main()
    {
        gocpp::Defer defer;
        std::any i = "hello";
        auto s = !!EXPR_ERROR!! [*ast.TypeAssertExpr];
        mocklib::Println(s);
        auto [s, ok] = !!EXPR_ERROR!! [*ast.TypeAssertExpr];
        mocklib::Println(s, ok);
        auto [f, ok] = !!EXPR_ERROR!! [*ast.TypeAssertExpr];
        mocklib::Println(f, ok);
        f = !!EXPR_ERROR!! [*ast.TypeAssertExpr];
        mocklib::Println(f);
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
