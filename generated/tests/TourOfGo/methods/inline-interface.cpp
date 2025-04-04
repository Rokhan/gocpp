// generated by GoCpp from file 'tests/TourOfGo/methods/inline-interface.go'
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

#include "golang/fmt/print.h"
#include "golang/math/sqrt.h"

namespace golang::main
{
    double Abs(MyInt i)
    {
        return std::sqrt(double(i * i));
    }

    double Abs(MyFloat f)
    {
        return std::sqrt(double(f * f));
    }

    
    template<typename T> requires gocpp::GoStruct<T>
    Vertex::operator T()
    {
        T result;
        result.X = this->X;
        result.Y = this->Y;
        return result;
    }

    template<typename T> requires gocpp::GoStruct<T>
    bool Vertex::operator==(const T& ref) const
    {
        if (X != ref.X) return false;
        if (Y != ref.Y) return false;
        return true;
    }

    std::ostream& Vertex::PrintTo(std::ostream& os) const
    {
        os << '{';
        os << "" << X;
        os << " " << Y;
        os << '}';
        return os;
    }

    std::ostream& operator<<(std::ostream& os, const struct Vertex& value)
    {
        return value.PrintTo(os);
    }

    double Abs(struct Vertex v)
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

        std::ostream& operator<<(std::ostream& os, const struct gocpp_id_0& value)
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

    std::ostream& operator<<(std::ostream& os, const struct gocpp_id_1& value)
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
