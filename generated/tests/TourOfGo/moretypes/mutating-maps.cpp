#include <complex>
#include <functional>
#include <iostream>
#include <string>
#include <tuple>
#include <vector>

#include "tests/TourOfGo/moretypes/mutating-maps.h"
#include "gocpp/support.h"


namespace golang
{
    // convertSpecs[ImportSpec] Not implemented => "fmt";
    void main()
    {
        gocpp::Defer defer;
        auto m = gocpp::make(!!EXPR_ERROR!! [*ast.MapType]);
        m["Answer"] = 42;
        mocklib::Println("The value:", m["Answer"]);
        m["Answer"] = 48;
        mocklib::Println("The value:", m["Answer"]);
        delete(m, "Answer");
        mocklib::Println("The value:", m["Answer"]);
        auto [v, ok] = m["Answer"];
        mocklib::Println("The value:", v, "Present?", ok);
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
