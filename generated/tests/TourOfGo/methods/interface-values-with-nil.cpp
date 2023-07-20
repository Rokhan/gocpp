#include <complex>
#include <functional>
#include <iostream>
#include <iomanip>
#include <map>
#include <string>
#include <tuple>
#include <vector>

#include "tests/TourOfGo/methods/interface-values-with-nil.h"
#include "gocpp/support.h"


namespace golang
{
    // convertSpecs[ImportSpec] Not implemented => "fmt";
    struct I
    {
        I(){}
        I(I& i) = default;
        I(const I& i) = default;
        I& operator=(I& i) = default;
        I& operator=(const I& i) = default;

        template<typename T>
        I(T& ref)
        {
            value.reset(new IImpl<T, std::unique_ptr<T>>(new T(ref)));
        }

        template<typename T>
        I(const T& ref)
        {
            value.reset(new IImpl<T, std::unique_ptr<T>>(new T(ref)));
        }

        template<typename T>
        I(T* ptr)
        {
            value.reset(new IImpl<T, gocpp::ptr<T>>(ptr));
        }

        using isGoStruct = void;

        std::ostream& PrintTo(std::ostream& os) const
        {
            return os;
        }

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

            void vM() override
            {
                return M(gocpp::PtrRecv<T, true>(value.get()));
            }

            StoreT value;
        };

        std::shared_ptr<II> value;
    };

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

    
    T T::Init(void (init)(T&))
    {
        T value;
        init(value);
        return value;
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
        if(t == nullptr)
        {
            mocklib::Println("<nil>");
            return;
        }
        mocklib::Println(t->S);
    }

    void main()
    {
        gocpp::Defer defer;
        I i;
        T* t = nullptr;
        i = t;
        describe(i);
        M(gocpp::recv(i));
        i = new T {"hello"};
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
