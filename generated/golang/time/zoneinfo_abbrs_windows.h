// generated by GoCpp from file '$(ImportDir)/time/zoneinfo_abbrs_windows.go'
#pragma once

#include <functional>
#include <string>
#include <tuple>
#include <vector>

#include "golang/time/zoneinfo_abbrs_windows.fwd.h"
#include "gocpp/support.h"

namespace golang::time
{
    struct abbr
    {
        std::string std;
        std::string dst;

        using isGoStruct = void;

        template<typename T> requires gocpp::GoStruct<T>
        operator T();

        template<typename T> requires gocpp::GoStruct<T>
        bool operator==(const T& ref) const;

        std::ostream& PrintTo(std::ostream& os) const;
    };

    std::ostream& operator<<(std::ostream& os, const struct abbr& value);
    extern gocpp::map<std::string, abbr> abbrs;

    namespace rec
    {
    }
}

