#include <complex>
#include <functional>
#include <iostream>
#include <iomanip>
#include <map>
#include <string>
#include <tuple>
#include <vector>

#include "tests/TourOfGo/basics/basic-types.h"
#include "gocpp/support.h"

// TODO: package import not implemented
// #include "fmt/doc.h"
// #include "fmt/errors.h"
// #include "fmt/format.h"
// #include "fmt/print.h"
// #include "fmt/scan.h"
// #include "math/cmplx/abs.h"
// #include "math/cmplx/asin.h"
// #include "math/cmplx/conj.h"
// #include "math/cmplx/exp.h"
// #include "math/cmplx/isinf.h"
// #include "math/cmplx/isnan.h"
// #include "math/cmplx/log.h"
// #include "math/cmplx/phase.h"
// #include "math/cmplx/polar.h"
// #include "math/cmplx/pow.h"
// #include "math/cmplx/rect.h"
// #include "math/cmplx/sin.h"
// #include "math/cmplx/sqrt.h"
// #include "math/cmplx/tan.h"

namespace golang::main
{
    bool ToBe = false;
    uint64_t MaxInt = (1 << 64) - 1;
    gocpp::complex128 z = std::sqrt(- 5 + gocpp::complex128(0, 12));
    void main()
    {
        mocklib::Printf("Type: %T Value: %v\n", ToBe, ToBe);
        mocklib::Printf("Type: %T Value: %v\n", MaxInt, MaxInt);
        mocklib::Printf("Type: %T Value: %v\n", z, z);
    }

}

int main()
{
    try
    {
        std::cout << std::boolalpha << std::fixed << std::setprecision(5);
        golang::main::main();
        return 0;
    }
    catch(const gocpp::GoPanic& ex)
    {
        std::cout << "Panic: " << ex.what() << std::endl;
        return -1;
    }
}
