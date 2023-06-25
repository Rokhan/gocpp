#include <complex>
#include <functional>
#include <iostream>
#include <string>
#include <tuple>
#include <vector>

#include "tests/TourOfGo/methods/interfaces-are-satisfied-implicitly.h"
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
        mocklib::Println(t.S);
    }

    void main()
    {
        gocpp::Defer defer;
        I i = T {"hello"};
        i.M();
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
