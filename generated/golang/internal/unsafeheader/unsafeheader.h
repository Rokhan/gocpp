// generated by GoCpp from file '$(ImportDir)/internal/unsafeheader/unsafeheader.go'
#pragma once

#include <functional>
#include <string>
#include <tuple>
#include <vector>

#include "golang/internal/unsafeheader/unsafeheader.fwd.h"
#include "gocpp/support.h"


namespace golang::unsafeheader
{
    struct Slice
    {
        unsafe::Pointer Data;
        int Len;
        int Cap;

        using isGoStruct = void;

        template<typename T> requires gocpp::GoStruct<T>
        operator T();

        template<typename T> requires gocpp::GoStruct<T>
        bool operator==(const T& ref) const;

        std::ostream& PrintTo(std::ostream& os) const;
    };

    std::ostream& operator<<(std::ostream& os, const struct Slice& value);
    struct String
    {
        unsafe::Pointer Data;
        int Len;

        using isGoStruct = void;

        template<typename T> requires gocpp::GoStruct<T>
        operator T();

        template<typename T> requires gocpp::GoStruct<T>
        bool operator==(const T& ref) const;

        std::ostream& PrintTo(std::ostream& os) const;
    };

    std::ostream& operator<<(std::ostream& os, const struct String& value);

    namespace rec
    {
    }
}

