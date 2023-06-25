#include <complex>
#include <functional>
#include <iostream>
#include <string>
#include <tuple>
#include <vector>

#include "tests/TourOfGo/methods/interface-values-with-nil.h"
#include "gocpp/support.h"


namespace golang
{
    // convertSpecs[ImportSpec] Not implemented => "fmt";
    !!TYPE_EXPR_ERROR!! [*ast.TypeSpec];
    struct T
    {
        std::string S;

        const bool isGoStruct = true;

        std::ostream& PrintTo(std::ostream& os) const
        {
            os << '{';
            os << "" << S;
            os << '}';
            return os;
        }
    };
    std::ostream& operator<<(std::ostream& os, const T& value)
    {
        return value.PrintTo(os);
    }

;
    void M()
    {
        gocpp::Defer defer;
        if(; t == nullptr)
        {
            mocklib::Println("<nil>");
            return;
        }
        mocklib::Println(t.S);
    }

    void main()
    {
        gocpp::Defer defer;
        I i;
        !!TYPE_EXPR_ERROR!! [*ast.StarExpr] t;
        i = t;
        describe(i);
        i.M();
        i = [[TOKEN_ERROR: '&' ]] T {"hello"};
        describe(i);
        i.M();
    }

    void describe(I i)
    {
        gocpp::Defer defer;
        mocklib::Printf("(%v, %T)\n", i, i);
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
