#include <complex>
#include <functional>
#include <iostream>
#include <iomanip>
#include <map>
#include <string>
#include <tuple>
#include <vector>

#include "tests/TourOfGo/methods/methods-with-pointer-receivers.h"
#include "gocpp/support.h"

// TODO: package import not implemented
// #include "fmt/doc.h"
// #include "fmt/errors.h"
// #include "fmt/format.h"
// #include "fmt/print.h"
// #include "fmt/scan.h"
// #include "math/abs.h"
// #include "math/acosh.h"
// #include "math/asin.h"
// #include "math/asinh.h"
// #include "math/atan.h"
// #include "math/atan2.h"
// #include "math/atanh.h"
// #include "math/bits.h"
// #include "math/cbrt.h"
// #include "math/const.h"
// #include "math/copysign.h"
// #include "math/dim.h"
// #include "math/dim_asm.h"
// #include "math/erf.h"
// #include "math/erfinv.h"
// #include "math/exp.h"
// #include "math/exp2_noasm.h"
// #include "math/exp_amd64.h"
// #include "math/exp_asm.h"
// #include "math/expm1.h"
// #include "math/floor.h"
// #include "math/floor_asm.h"
// #include "math/fma.h"
// #include "math/frexp.h"
// #include "math/gamma.h"
// #include "math/hypot.h"
// #include "math/hypot_asm.h"
// #include "math/j0.h"
// #include "math/j1.h"
// #include "math/jn.h"
// #include "math/ldexp.h"
// #include "math/lgamma.h"
// #include "math/log.h"
// #include "math/log10.h"
// #include "math/log1p.h"
// #include "math/log_asm.h"
// #include "math/logb.h"
// #include "math/mod.h"
// #include "math/modf.h"
// #include "math/modf_noasm.h"
// #include "math/nextafter.h"
// #include "math/pow.h"
// #include "math/pow10.h"
// #include "math/remainder.h"
// #include "math/signbit.h"
// #include "math/sin.h"
// #include "math/sincos.h"
// #include "math/sinh.h"
// #include "math/sqrt.h"
// #include "math/stubs.h"
// #include "math/tan.h"
// #include "math/tanh.h"
// #include "math/trig_reduce.h"
// #include "math/unsafe.h"
// #include "math/dim_amd64.s.h"
// #include "math/exp_amd64.s.h"
// #include "math/floor_amd64.s.h"
// #include "math/hypot_amd64.s.h"
// #include "math/log_amd64.s.h"

namespace golang::main
{
    
    std::ostream& Vertex::PrintTo(std::ostream& os) const
    {
        os << '{';
        os << "" << X;
        os << " " << Y;
        os << '}';
        return os;
    }

    std::ostream& operator<<(std::ostream& os, const Vertex& value)
    {
        return value.PrintTo(os);
    }

    void Scale(Vertex* v, double f)
    {
        v->X = v->X * f;
        v->Y = v->Y * f;
    }

    double Abs(Vertex* v)
    {
        return std::sqrt(v->X * v->X + v->Y * v->Y);
    }

    void main()
    {
        auto v = new Vertex {3, 4};
        mocklib::Printf("Before scaling: %+v, Abs: %v\n", v, Abs(gocpp::recv(v)));
        Scale(gocpp::recv(v), 5);
        mocklib::Printf("After scaling: %+v, Abs: %v\n", v, Abs(gocpp::recv(v)));
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
