#include <complex>
#include <functional>
#include <iostream>
#include <iomanip>
#include <map>
#include <string>
#include <tuple>
#include <vector>

#include "tests/TourOfGo/methods/nil-interface-values.h"
#include "gocpp/support.h"


namespace golang
{
    // convertSpecs[ImportSpec] Not implemented => "fmt";
    !!TYPE_SPEC_ERROR!! [*ast.TypeSpec];
    void main()
    {
        gocpp::Defer defer;
        I i;
        describe(i);
        M(i);
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
