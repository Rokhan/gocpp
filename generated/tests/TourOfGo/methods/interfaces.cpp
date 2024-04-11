#include <complex>
#include <functional>
#include <iostream>
#include <iomanip>
#include <map>
#include <string>
#include <tuple>
#include <vector>

#include "tests/TourOfGo/methods/interfaces.h"
#include "gocpp/support.h"


namespace golang
{
    // convertSpecs[ImportSpec] Not implemented => "fmt";
    // convertSpecs[ImportSpec] Not implemented => "math";
    
    template<typename T>
    Abser::Abser(T& ref)
    {
        value.reset(new AbserImpl<T, std::unique_ptr<T>>(new T(ref)));
    }

    template<typename T>
    Abser::Abser(const T& ref)
    {
        value.reset(new AbserImpl<T, std::unique_ptr<T>>(new T(ref)));
    }

    template<typename T>
    Abser::Abser(T* ptr)
    {
        value.reset(new AbserImpl<T, gocpp::ptr<T>>(ptr));
    }

    std::ostream& Abser::PrintTo(std::ostream& os) const
    {
        return os;
    }

    template<typename T, typename StoreT>
    double Abser::AbserImpl<T, StoreT>::vAbs()
    {
        return Abs(gocpp::PtrRecv<T, true>(value.get()));
    }

    double Abs(const gocpp::PtrRecv<Abser, false>& self)
    {
        return self.ptr->value->vAbs();
    }

    double Abs(const gocpp::ObjRecv<Abser>& self)
    {
        return self.obj.value->vAbs();
    }

    std::ostream& operator<<(std::ostream& os, const Abser& value)
    {
        return value.PrintTo(os);
    }

    void main()
    {
        gocpp::Defer defer;
        Abser a;
        auto f = MyFloat(- mocklib::Sqrt2);
        auto v = Vertex {3, 4};
        a = f;
        a = & v;
        a = v;
        mocklib::Println(Abs(gocpp::recv(a)));
    }

    // using MyFloat = double;
    double Abs(MyFloat f)
    {
        gocpp::Defer defer;
        if(f < 0)
        {
            return double(- f);
        }
        return double(f);
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

    double Abs(Vertex* v)
    {
        gocpp::Defer defer;
        return std::sqrt(v->X * v->X + v->Y * v->Y);
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
