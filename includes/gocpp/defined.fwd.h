#pragma once
#include <compare>
#include <concepts>
#include <iosfwd>
#include <type_traits>

namespace gocpp
{
    // primary: see support.h
    template<typename T, typename DefTag> struct defined;

    // BasicValue includes bool and char types
    template<typename T>
    concept BasicValue = std::is_arithmetic_v<T>;

    #define GOCPP_DEFINED_BINOP(op)                                                        \
        friend constexpr defined operator op(defined a, defined b)                         \
            requires requires(T x, T y) { x op y; }                                        \
        { return defined(static_cast<T>(a.value op b.value)); }                            \
        friend constexpr defined operator op(defined a, T b)                               \
            requires requires(T x, T y) { x op y; }                                        \
        { return defined(static_cast<T>(a.value op b)); }                                  \
        friend constexpr defined operator op(T a, defined b)                               \
            requires requires(T x, T y) { x op y; }                                        \
        { return defined(static_cast<T>(a op b.value)); }

    #define GOCPP_DEFINED_ASSIGN(op)                                                       \
        constexpr defined& operator op##=(defined o)                                       \
            requires requires(T x, T y) { x op y; }                                        \
        { value = static_cast<T>(value op o.value); return *this; }                        \
        constexpr defined& operator op##=(T o)                                             \
            requires requires(T x, T y) { x op y; }                                        \
        { value = static_cast<T>(value op o); return *this; }

    template<typename T, typename DefTag> requires BasicValue<T>
    struct defined<T, DefTag>
    {
        using underlying_type = T;
        T value{};

        constexpr defined() = default;

        // var k Kind = 3
        constexpr defined(T v) : value(v) {}

        // Kind(x)
        template<BasicValue U> requires (!std::same_as<U, T>)
        constexpr explicit defined(U v) : value(static_cast<T>(v)) {}

        // arr[k], double(k), case labels...
        constexpr operator T() const { return value; }

        GOCPP_DEFINED_BINOP(+) GOCPP_DEFINED_BINOP(-) GOCPP_DEFINED_BINOP(*)
        GOCPP_DEFINED_BINOP(/) GOCPP_DEFINED_BINOP(%) GOCPP_DEFINED_BINOP(&)
        GOCPP_DEFINED_BINOP(|) GOCPP_DEFINED_BINOP(^) GOCPP_DEFINED_BINOP(<<)
        GOCPP_DEFINED_BINOP(>>)

        GOCPP_DEFINED_ASSIGN(+) GOCPP_DEFINED_ASSIGN(-) GOCPP_DEFINED_ASSIGN(*)
        GOCPP_DEFINED_ASSIGN(/) GOCPP_DEFINED_ASSIGN(%) GOCPP_DEFINED_ASSIGN(&)
        GOCPP_DEFINED_ASSIGN(|) GOCPP_DEFINED_ASSIGN(^) GOCPP_DEFINED_ASSIGN(<<)
        GOCPP_DEFINED_ASSIGN(>>)

        // Shifts: the result has the type of the left operand, the count is any integer.
        template<std::integral N> requires std::integral<T>
        friend constexpr defined operator<<(defined a, N n) { return defined(static_cast<T>(a.value << n)); }
        template<std::integral N> requires std::integral<T>
        friend constexpr defined operator>>(defined a, N n) { return defined(static_cast<T>(a.value >> n)); }

        constexpr defined operator-() const { return defined(static_cast<T>(-value)); }
        constexpr defined operator+() const { return *this; }
        constexpr defined operator~() const requires std::integral<T> { return defined(static_cast<T>(~value)); }

        constexpr defined& operator++() { ++value; return *this; }
        constexpr defined  operator++(int) { auto c = *this; ++value; return c; }
        constexpr defined& operator--() { --value; return *this; }
        constexpr defined  operator--(int) { auto c = *this; --value; return c; }

        friend constexpr bool operator==(defined a, defined b) { return a.value == b.value; }
        friend constexpr bool operator==(defined a, T b)       { return a.value == b; }
        friend constexpr auto operator<=>(defined a, defined b) { return a.value <=> b.value; }
        friend constexpr auto operator<=>(defined a, T b)       { return a.value <=> b; }
    };

    template<typename T, typename DefTag> requires BasicValue<T>
    std::ostream& operator<<(std::ostream& os, const defined<T, DefTag>& v);

    #undef GOCPP_DEFINED_BINOP
    #undef GOCPP_DEFINED_ASSIGN
}