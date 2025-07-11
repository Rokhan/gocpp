// generated by GoCpp from file '$(ImportDir)/strconv/itoa.go'
#pragma once

#include <functional>
#include <string>
#include <tuple>
#include <vector>

#include "golang/strconv/itoa.fwd.h"
#include "gocpp/support.h"


namespace golang::strconv
{
    std::string FormatUint(uint64_t i, int base);
    std::string FormatInt(int64_t i, int base);
    std::string Itoa(int i);
    gocpp::slice<unsigned char> AppendInt(gocpp::slice<unsigned char> dst, int64_t i, int base);
    gocpp::slice<unsigned char> AppendUint(gocpp::slice<unsigned char> dst, uint64_t i, int base);
    std::string small(int i);
    extern std::string smallsString;
    extern std::string digits;
    std::tuple<gocpp::slice<unsigned char>, std::string> formatBits(gocpp::slice<unsigned char> dst, uint64_t u, int base, bool neg, bool append_);
    bool isPowerOfTwo(int x);

    namespace rec
    {
    }
}

