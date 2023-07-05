#include <complex>
#include <functional>
#include <iostream>
#include <iomanip>
#include <map>
#include <string>
#include <tuple>
#include <vector>

#include "tests/TourOfGo/methods/exercise-rot-reader.h"
#include "gocpp/support.h"


namespace golang
{
    // convertSpecs[ImportSpec] Not implemented => "io";
    // convertSpecs[ImportSpec] Not implemented => "os";
    // convertSpecs[ImportSpec] Not implemented => "strings";
    struct rot13Reader
    {
        !!TYPE_EXPR_ERROR!! [*ast.SelectorExpr] r;

        using isGoStruct = void;

        static rot13Reader Init(void (init)(rot13Reader&))
        {
            rot13Reader value;
            init(value);
            return value;
        }

        std::ostream& PrintTo(std::ostream& os) const
        {
            os << '{';
            os << "" << r;
            os << '}';
            return os;
        }
    };

    std::ostream& operator<<(std::ostream& os, const rot13Reader& value)
    {
        return value.PrintTo(os);
    }
;
    void main()
    {
        gocpp::Defer defer;
        auto s = strings::NewReader("Lbh penpxrq gur pbqr!");
        auto r = rot13Reader {s};
        Copy(io, os.Stdout, & r);
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
