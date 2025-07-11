// generated by GoCpp from file '$(ImportDir)/cmp/cmp.go'
#include <complex>
#include <functional>
#include <iostream>
#include <iomanip>
#include <map>
#include <string>
#include <tuple>
#include <vector>

#include "golang/cmp/cmp.h"
#include "gocpp/support.h"

// Package cmp provides types and functions related to comparing
// ordered values.
namespace golang::cmp
{
    namespace rec
    {
        using namespace mocklib::rec;
    }

    // Ordered is a constraint that permits any ordered type: any type
    // that supports the operators < <= >= >.
    // If future releases of Go add new ordered types,
    // this constraint will be modified to include them.
    //
    // Note that floating-point types may contain NaN ("not-a-number") values.
    // An operator such as == or < will always report false when
    // comparing a NaN value with any other value, NaN or not.
    // See the [Compare] function for a consistent way to compare NaN values.
    
    template<typename T>
    Ordered::Ordered(T& ref)
    {
        value.reset(new OrderedImpl<T, std::unique_ptr<T>>(new T(ref)));
    }

    template<typename T>
    Ordered::Ordered(const T& ref)
    {
        value.reset(new OrderedImpl<T, std::unique_ptr<T>>(new T(ref)));
    }

    template<typename T>
    Ordered::Ordered(T* ptr)
    {
        value.reset(new OrderedImpl<T, gocpp::ptr<T>>(ptr));
    }

    std::ostream& Ordered::PrintTo(std::ostream& os) const
    {
        return os;
    }


    namespace rec
    {    }

    std::ostream& operator<<(std::ostream& os, const struct Ordered& value)
    {
        return value.PrintTo(os);
    }

    // Less reports whether x is less than y.
    // For floating-point types, a NaN is considered less than any non-NaN,
    // and -0.0 is not less than (is equal to) 0.0.

    template<typename T>
    bool Less(T x, T y)
    {
        return (isNaN(x) && ! isNaN(y)) || x < y;
    }

    // Compare returns
    //
    //	-1 if x is less than y,
    //	 0 if x equals y,
    //	+1 if x is greater than y.
    //
    // For floating-point types, a NaN is considered less than any non-NaN,
    // a NaN is considered equal to a NaN, and -0.0 is equal to 0.0.

    template<typename T>
    int Compare(T x, T y)
    {
        auto xNaN = isNaN(x);
        auto yNaN = isNaN(y);
        if(xNaN && yNaN)
        {
            return 0;
        }
        if(xNaN || x < y)
        {
            return - 1;
        }
        if(yNaN || x > y)
        {
            return + 1;
        }
        return 0;
    }

    // isNaN reports whether x is a NaN without requiring the math package.
    // This will always return false if T is not floating-point.

    template<typename T>
    bool isNaN(T x)
    {
        return x != x;
    }

    // Or returns the first of its arguments that is not equal to the zero value.
    // If no argument is non-zero, it returns the zero value.

    template<typename T>
    T Or(gocpp::slice<T> vals)
    {
        T zero = {};
        for(auto [gocpp_ignored, val] : vals)
        {
            if(val != zero)
            {
                return val;
            }
        }
        return zero;
    }

}

