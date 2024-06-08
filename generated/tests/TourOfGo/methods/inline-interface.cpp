#include <complex>
#include <functional>
#include <iostream>
#include <iomanip>
#include <map>
#include <string>
#include <tuple>
#include <vector>

#include "tests/TourOfGo/methods/inline-interface.h"
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
    // using MyInt = int;
    // using MyFloat = double;
    double Abs(MyInt i)
    {
        return std::sqrt(double(i * i));
    }

    double Abs(MyFloat f)
    {
        return std::sqrt(double(f * f));
    }

    
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

    double Abs(Vertex v)
    {
        return std::sqrt(v.X * v.X + v.Y * v.Y);
    }

    
        template<typename T>
        gocpp_id_0::gocpp_id_0(T& ref)
        {
            value.reset(new gocpp_id_0Impl<T, std::unique_ptr<T>>(new T(ref)));
        }

        template<typename T>
        gocpp_id_0::gocpp_id_0(const T& ref)
        {
            value.reset(new gocpp_id_0Impl<T, std::unique_ptr<T>>(new T(ref)));
        }

        template<typename T>
        gocpp_id_0::gocpp_id_0(T* ptr)
        {
            value.reset(new gocpp_id_0Impl<T, gocpp::ptr<T>>(ptr));
        }

        std::ostream& gocpp_id_0::PrintTo(std::ostream& os) const
        {
            return os;
        }

        template<typename T, typename StoreT>
        double gocpp_id_0::gocpp_id_0Impl<T, StoreT>::vAbs()
        {
            return Abs(gocpp::PtrRecv<T, false>(value.get()));
        }

        double Abs(const gocpp::PtrRecv<gocpp_id_0, false>& self)
        {
            return self.ptr->value->vAbs();
        }

        double Abs(const gocpp::ObjRecv<gocpp_id_0>& self)
        {
            return self.obj.value->vAbs();
        }

        std::ostream& operator<<(std::ostream& os, const gocpp_id_0& value)
        {
            return value.PrintTo(os);
        }


    void main()
    {
        gocpp_id_0 i = {};
        describe(i);
        i = MyInt(42);
        describe(i);
        i = MyFloat(42.0);
        describe(i);
        i = Vertex {4, 2};
        describe(i);
    }

    
    template<typename T>
    gocpp_id_1::gocpp_id_1(T& ref)
    {
        value.reset(new gocpp_id_1Impl<T, std::unique_ptr<T>>(new T(ref)));
    }

    template<typename T>
    gocpp_id_1::gocpp_id_1(const T& ref)
    {
        value.reset(new gocpp_id_1Impl<T, std::unique_ptr<T>>(new T(ref)));
    }

    template<typename T>
    gocpp_id_1::gocpp_id_1(T* ptr)
    {
        value.reset(new gocpp_id_1Impl<T, gocpp::ptr<T>>(ptr));
    }

    std::ostream& gocpp_id_1::PrintTo(std::ostream& os) const
    {
        return os;
    }

    template<typename T, typename StoreT>
    double gocpp_id_1::gocpp_id_1Impl<T, StoreT>::vAbs()
    {
        return Abs(gocpp::PtrRecv<T, false>(value.get()));
    }

    double Abs(const gocpp::PtrRecv<gocpp_id_1, false>& self)
    {
        return self.ptr->value->vAbs();
    }

    double Abs(const gocpp::ObjRecv<gocpp_id_1>& self)
    {
        return self.obj.value->vAbs();
    }

    std::ostream& operator<<(std::ostream& os, const gocpp_id_1& value)
    {
        return value.PrintTo(os);
    }


    void describe(gocpp_id_1 i)
    {
        if(i != nullptr)
        {
            mocklib::Printf("(%v, %T) => %v\n", i, i, Abs(gocpp::recv(i)));
        }
        else
        {
            mocklib::Printf("(%v, %T)\n", i, i);
        }
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
