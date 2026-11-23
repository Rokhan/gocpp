#pragma once

#include "gocpp/support.fwd.h"

namespace gocpp
{
    [[noreturn]] void panic(const gocpp::string& message);
    [[noreturn]] void panic(const char* const message);

    template<typename T>
    constexpr T max(T a)
    {
        return a;
    }

    template<typename T1, typename T2, typename... Ts>
    constexpr std::common_type_t<T1, T2, Ts...> max(T1 a, T2 b, Ts... args)
    {
        return max((a > b ? a : b), args...);
    }

    template<typename T>
    constexpr T min(T a)
    {
        return a;
    }

    template<typename T1, typename T2, typename... Ts>
    constexpr std::common_type_t<T1, T2, Ts...> min(T1 a, T2 b, Ts... args)
    {
        return min((a < b ? a : b), args...);
    }
}