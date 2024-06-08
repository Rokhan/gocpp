#pragma once

#include <functional>
#include <string>
#include <tuple>
#include <vector>

#include "tests/TourOfGo/methods/interface-values.fwd.h"
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
    struct I : gocpp::Interface
    {
        I(){}
        I(I& i) = default;
        I(const I& i) = default;
        I& operator=(I& i) = default;
        I& operator=(const I& i) = default;

        template<typename T>
        I(T& ref);

        template<typename T>
        I(const T& ref);

        template<typename T>
        I(T* ptr);

        using isGoStruct = void;

        std::ostream& PrintTo(std::ostream& os) const;

        struct II
        {
            virtual void vM() = 0;
        };

        template<typename T, typename StoreT>
        struct IImpl : II
        {
            explicit IImpl(T* ptr)
            {
                value.reset(ptr);
            }

            void vM() override;

            StoreT value;
        };

        std::shared_ptr<II> value;
    };

    void M(const gocpp::PtrRecv<I, false>& self);
    void M(const gocpp::ObjRecv<I>& self);

    std::ostream& operator<<(std::ostream& os, const I& value);
    struct T
    {
        std::string S;

        using isGoStruct = void;

        std::ostream& PrintTo(std::ostream& os) const;
    };

    std::ostream& operator<<(std::ostream& os, const T& value);
    void M(T* t);
    using F = double;
    void M(F f);
    void main();
    void describe(I i);
}

