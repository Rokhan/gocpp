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
    !!TYPE_SPEC_ERROR!! [*ast.TypeSpec];
    struct T
    {
        std::string S;

        using isGoStruct = void;

        static T Init(void (init)(T&))
        {
            T value;
            init(value);
            return value;
        }

        std::ostream& PrintTo(std::ostream& os) const
        {
            os << '{';
            os << "" << S;
            os << '}';
            return os;
        }
    };

    std::ostream& operator<<(std::ostream& os, const T& value)
    {
        return value.PrintTo(os);
    }

    void M(T* t)
    {
        gocpp::Defer defer;
        if(; t == nullptr)
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
        T* t;
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
