// generated by GoCpp from file '$(ImportDir)/strconv/atoi.go'
#pragma once

#include <functional>
#include <string>
#include <tuple>
#include <vector>

#include "golang/strconv/atoi.fwd.h"
#include "gocpp/support.h"


namespace golang::strconv
{
    unsigned char lower(unsigned char c);
    extern gocpp::error ErrRange;
    extern gocpp::error ErrSyntax;
    struct NumError
    {
        std::string Func;
        std::string Num;
        gocpp::error Err;

        using isGoStruct = void;

        template<typename T> requires gocpp::GoStruct<T>
        operator T();

        template<typename T> requires gocpp::GoStruct<T>
        bool operator==(const T& ref) const;

        std::ostream& PrintTo(std::ostream& os) const;
    };

    std::ostream& operator<<(std::ostream& os, const struct NumError& value);
    std::string cloneString(std::string x);
    struct NumError* syntaxError(std::string fn, std::string str);
    struct NumError* rangeError(std::string fn, std::string str);
    struct NumError* baseError(std::string fn, std::string str, int base);
    struct NumError* bitSizeError(std::string fn, std::string str, int bitSize);
    std::tuple<uint64_t, struct gocpp::error> ParseUint(std::string s, int base, int bitSize);
    std::tuple<int64_t, struct gocpp::error> ParseInt(std::string s, int base, int bitSize);
    std::tuple<int, struct gocpp::error> Atoi(std::string s);
    bool underscoreOK(std::string s);

    namespace rec
    {
        std::string Error(struct NumError* e);
        struct gocpp::error Unwrap(struct NumError* e);
    }
}

