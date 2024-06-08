#pragma once

#include <functional>
#include <string>
#include <tuple>
#include <vector>

#include "tests/TourOfGo/methods/inline-interface.fwd.h"
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
    using MyInt = int;
    using MyFloat = double;
    double Abs(MyInt i);
    double Abs(MyFloat f);
    struct Vertex
    {
        double X;
        double Y;

        using isGoStruct = void;

        std::ostream& PrintTo(std::ostream& os) const;
    };

    std::ostream& operator<<(std::ostream& os, const Vertex& value);
    double Abs(Vertex v);
    void main();
    struct gocpp_id_0 : gocpp::Interface
    {
        gocpp_id_0(){}
        gocpp_id_0(gocpp_id_0& i) = default;
        gocpp_id_0(const gocpp_id_0& i) = default;
        gocpp_id_0& operator=(gocpp_id_0& i) = default;
        gocpp_id_0& operator=(const gocpp_id_0& i) = default;

        template<typename T>
        gocpp_id_0(T& ref);

        template<typename T>
        gocpp_id_0(const T& ref);

        template<typename T>
        gocpp_id_0(T* ptr);

        using isGoStruct = void;

        std::ostream& PrintTo(std::ostream& os) const;

        struct Igocpp_id_0
        {
            virtual double vAbs() = 0;
        };

        template<typename T, typename StoreT>
        struct gocpp_id_0Impl : Igocpp_id_0
        {
            explicit gocpp_id_0Impl(T* ptr)
            {
                value.reset(ptr);
            }

            double vAbs() override;

            StoreT value;
        };

        std::shared_ptr<Igocpp_id_0> value;
    };

    double Abs(const gocpp::PtrRecv<gocpp_id_0, false>& self);
    double Abs(const gocpp::ObjRecv<gocpp_id_0>& self);

    std::ostream& operator<<(std::ostream& os, const gocpp_id_0& value);
    struct gocpp_id_1 : gocpp::Interface
    {
        gocpp_id_1(){}
        gocpp_id_1(gocpp_id_1& i) = default;
        gocpp_id_1(const gocpp_id_1& i) = default;
        gocpp_id_1& operator=(gocpp_id_1& i) = default;
        gocpp_id_1& operator=(const gocpp_id_1& i) = default;

        template<typename T>
        gocpp_id_1(T& ref);

        template<typename T>
        gocpp_id_1(const T& ref);

        template<typename T>
        gocpp_id_1(T* ptr);

        using isGoStruct = void;

        std::ostream& PrintTo(std::ostream& os) const;

        struct Igocpp_id_1
        {
            virtual double vAbs() = 0;
        };

        template<typename T, typename StoreT>
        struct gocpp_id_1Impl : Igocpp_id_1
        {
            explicit gocpp_id_1Impl(T* ptr)
            {
                value.reset(ptr);
            }

            double vAbs() override;

            StoreT value;
        };

        std::shared_ptr<Igocpp_id_1> value;
    };

    double Abs(const gocpp::PtrRecv<gocpp_id_1, false>& self);
    double Abs(const gocpp::ObjRecv<gocpp_id_1>& self);

    std::ostream& operator<<(std::ostream& os, const gocpp_id_1& value);
    void describe(gocpp_id_1 i);
}

