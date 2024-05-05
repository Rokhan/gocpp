#include <complex>
#include <functional>
#include <iostream>
#include <iomanip>
#include <map>
#include <string>
#include <tuple>
#include <vector>

#include "tests/TourOfGo/methods/interface-values.h"
#include "gocpp/support.h"


namespace golang
{
    // convertSpecs[ImportSpec] Not implemented => "fmt";
    // convertSpecs[ImportSpec] Not implemented => "math";
    
    template<typename T>
    I::I(T& ref)
    {
        value.reset(new IImpl<T, std::unique_ptr<T>>(new T(ref)));
    }

    template<typename T>
    I::I(const T& ref)
    {
        value.reset(new IImpl<T, std::unique_ptr<T>>(new T(ref)));
    }

    template<typename T>
    I::I(T* ptr)
    {
        value.reset(new IImpl<T, gocpp::ptr<T>>(ptr));
    }

    std::ostream& I::PrintTo(std::ostream& os) const
    {
        return os;
    }

    template<typename T, typename StoreT>
    void I::IImpl<T, StoreT>::vM()
    {
        return M(gocpp::PtrRecv<T, false>(value.get()));
    }

    void M(const gocpp::PtrRecv<I, false>& self)
    {
        return self.ptr->value->vM();
    }

    void M(const gocpp::ObjRecv<I>& self)
    {
        return self.obj.value->vM();
    }

    std::ostream& operator<<(std::ostream& os, const I& value)
    {
        return value.PrintTo(os);
    }

    
    std::ostream& T::PrintTo(std::ostream& os) const
    {
        os << '{';
        os << "" << S;
        os << '}';
        return os;
    }

    std::ostream& operator<<(std::ostream& os, const T& value)
    {
        return value.PrintTo(os);
    }

    void M(T* t)
    {
        gocpp::Defer defer;
        mocklib::Println(t->S);
    }

    // using F = double;
    void M(F f)
    {
        gocpp::Defer defer;
        mocklib::Println(f);
    }

    void main()
    {
        gocpp::Defer defer;
        I i = {};
        i = new T {"Hello"};
        describe(i);
        M(gocpp::recv(i));
        i = F(mocklib::Pi);
        describe(i);
        M(gocpp::recv(i));
    }

    void describe(I i)
    {
        gocpp::Defer defer;
        mocklib::Printf("(%v, %T)\n", i, i);
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
