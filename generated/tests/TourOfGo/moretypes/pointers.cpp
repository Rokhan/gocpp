#include <complex>
#include <functional>
#include <iostream>
#include <string>
#include <tuple>
#include <vector>

#include "tests/TourOfGo/moretypes/pointers.h"
#include "gocpp/support.h"


namespace golang
{
    // convertSpecs[ImportSpec] Not implemented => "fmt";
    void main()
    {
        gocpp::Defer defer;
        auto [i, j] = std::tuple{42, 2701};
        auto p = [[TOKEN_ERROR: '&' ]] i;
        mocklib::Println(!!EXPR_ERROR!! [*ast.StarExpr]);
        !!EXPR_ERROR!! [*ast.StarExpr] = 21;
        mocklib::Println(i);
        p = [[TOKEN_ERROR: '&' ]] j;
        !!EXPR_ERROR!! [*ast.StarExpr] = !!EXPR_ERROR!! [*ast.StarExpr] / 37;
        mocklib::Println(j);
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
