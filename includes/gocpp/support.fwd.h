#pragma once

#include <cstdint>

// TODO: try to not need this 
#include <string>

// Temporary definitions to mock broken include files
namespace golang
{
    namespace runtime
    {
        struct g;
        struct sudog;

        struct funcval;
        struct gobuf;
        struct mcache;
        struct adjustinfo;
        struct funcInfo;
        struct itab;
        struct eface;
        struct iface;
        struct _defer;
        struct _panic;
        struct godebugInc;
    }
}

namespace gocpp
{
    template<typename T, typename DefTag> struct defined;

    template<typename T> struct slice;
    template<typename T> struct array_base;
    template<typename T, int N> struct array;    
    template<typename V> struct map_value;
    template<typename K, typename V> struct map;    
    template<typename T, typename E> struct result_or_error;

    // TODO: chose a clear naming scheme ...
    struct complex128;
    struct Defer;
    struct GoPanic;
    struct go_any;
    struct Interface;
    struct string;
    struct unsafe_pointer;

    using rune = int;

    struct ValueSink
    {
        template <typename T>
        constexpr void operator=(T&&) const noexcept {}
    };
    inline constexpr ValueSink _{};

    template<typename T> 
    constexpr int Sizeof()
    {
        return sizeof(T);
    }

    inline constexpr long len(const std::string& input)
    {
        return (long)input.length();
    }

    // sadly not a constexpr because of the use of reinterpret_cast
    // Todo one day with c++26 static reflection ?
    //  -> constexpr std::size_t off = std::meta::offset_of(^^Foo::y); 
    template <typename T, typename M>
    std::size_t Offsetof(M T::* member)
    {
        char buf[sizeof(T)];
        T* obj = reinterpret_cast<T*>(buf);
        return reinterpret_cast<char*>(&(obj->*member)) - reinterpret_cast<char*>(obj);
    }

    struct string : std::string
    {
        using std::string::string;

        constexpr  inline string(const string& src) : std::string(src) { }
        constexpr inline string(string&& src) : std::string(std::move(src)) { }

        constexpr inline string(const std::string& src) : std::string(src) { }
        constexpr inline string(std::string&& src) : std::string(std::move(src)) { }

        constexpr inline string(const rune& src);

        constexpr inline string make_slice(size_t low) const
        {
            return string(this->substr(low));
        }

        constexpr inline string make_slice(size_t low, size_t high) const
        {
            return string(this->substr(low, high - low));
        }

        // Assignment operators
        constexpr inline string& operator=(const string& src)
        {
            std::string::operator=(src);
            return *this;
        }

        constexpr inline string& operator=(string&& src) noexcept
        {
            std::string::operator=(std::move(src));
            return *this;
        }

        constexpr inline string& operator=(const std::string& src)
        {
            std::string::operator=(src);
            return *this;
        }

        constexpr inline string& operator=(std::string&& src) noexcept
        {
            std::string::operator=(std::move(src));
            return *this;
        }

        constexpr inline string& operator=(const char* s)
        {
            std::string::operator=(s ? s : "");
            return *this;
        }

        constexpr inline string& operator=(const rune& r);

        using string_iterator = typename std::string::iterator;

        // (index, value) iterator
        struct range_iterator;

        range_iterator begin();
        range_iterator end();
    };
}

namespace golang
{
    constexpr gocpp::string operator""_s(const char* src, std::size_t)
    {
        return gocpp::string(src);
    }

    using gocpp::len;
    using gocpp::_;
}
