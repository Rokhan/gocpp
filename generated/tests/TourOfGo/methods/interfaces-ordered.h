#pragma once

#include <functional>
#include <string>
#include <tuple>
#include <vector>

#include "tests/TourOfGo/methods/interfaces-ordered.fwd.h"
#include "gocpp/support.h"

// TODO: package import not implemented
// #include "fmt/doc.fwd.h"
// #include "fmt/errors.fwd.h"
// #include "fmt/format.fwd.h"
// #include "fmt/print.fwd.h"
// #include "fmt/scan.fwd.h"
// #include "math/abs.fwd.h"
// #include "math/acosh.fwd.h"
// #include "math/asin.fwd.h"
// #include "math/asinh.fwd.h"
// #include "math/atan.fwd.h"
// #include "math/atan2.fwd.h"
// #include "math/atanh.fwd.h"
// #include "math/bits.fwd.h"
// #include "math/cbrt.fwd.h"
// #include "math/const.fwd.h"
// #include "math/copysign.fwd.h"
// #include "math/dim.fwd.h"
// #include "math/dim_asm.fwd.h"
// #include "math/erf.fwd.h"
// #include "math/erfinv.fwd.h"
// #include "math/exp.fwd.h"
// #include "math/exp2_noasm.fwd.h"
// #include "math/exp_amd64.fwd.h"
// #include "math/exp_asm.fwd.h"
// #include "math/expm1.fwd.h"
// #include "math/floor.fwd.h"
// #include "math/floor_asm.fwd.h"
// #include "math/fma.fwd.h"
// #include "math/frexp.fwd.h"
// #include "math/gamma.fwd.h"
// #include "math/hypot.fwd.h"
// #include "math/hypot_asm.fwd.h"
// #include "math/j0.fwd.h"
// #include "math/j1.fwd.h"
// #include "math/jn.fwd.h"
// #include "math/ldexp.fwd.h"
// #include "math/lgamma.fwd.h"
// #include "math/log.fwd.h"
// #include "math/log10.fwd.h"
// #include "math/log1p.fwd.h"
// #include "math/log_asm.fwd.h"
// #include "math/logb.fwd.h"
// #include "math/mod.fwd.h"
// #include "math/modf.fwd.h"
// #include "math/modf_noasm.fwd.h"
// #include "math/nextafter.fwd.h"
// #include "math/pow.fwd.h"
// #include "math/pow10.fwd.h"
// #include "math/remainder.fwd.h"
// #include "math/signbit.fwd.h"
// #include "math/sin.fwd.h"
// #include "math/sincos.fwd.h"
// #include "math/sinh.fwd.h"
// #include "math/sqrt.fwd.h"
// #include "math/stubs.fwd.h"
// #include "math/tan.fwd.h"
// #include "math/tanh.fwd.h"
// #include "math/trig_reduce.fwd.h"
// #include "math/unsafe.fwd.h"
// #include "math/dim_amd64.s.fwd.h"
// #include "math/exp_amd64.s.fwd.h"
// #include "math/floor_amd64.s.fwd.h"
// #include "math/hypot_amd64.s.fwd.h"
// #include "math/log_amd64.s.fwd.h"

namespace golang::main
{
    struct Abser : gocpp::Interface
    {
        Abser(){}
        Abser(Abser& i) = default;
        Abser(const Abser& i) = default;
        Abser& operator=(Abser& i) = default;
        Abser& operator=(const Abser& i) = default;

        template<typename T>
        Abser(T& ref);

        template<typename T>
        Abser(const T& ref);

        template<typename T>
        Abser(T* ptr);

        using isGoStruct = void;

        std::ostream& PrintTo(std::ostream& os) const;

        struct IAbser
        {
            virtual double vAbs() = 0;
        };

        template<typename T, typename StoreT>
        struct AbserImpl : IAbser
        {
            explicit AbserImpl(T* ptr)
            {
                value.reset(ptr);
            }

            double vAbs() override;

            StoreT value;
        };

        std::shared_ptr<IAbser> value;
    };

    double Abs(const gocpp::PtrRecv<Abser, false>& self);
    double Abs(const gocpp::ObjRecv<Abser>& self);

    std::ostream& operator<<(std::ostream& os, const Abser& value);
    struct Vertex
    {
        double X;
        double Y;

        using isGoStruct = void;

        std::ostream& PrintTo(std::ostream& os) const;
    };

    std::ostream& operator<<(std::ostream& os, const Vertex& value);
    using MyFloat = double;
    void main();
    double Abs(MyFloat f);
    double Abs(Vertex* v);
}

