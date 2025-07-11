// generated by GoCpp from file '$(ImportDir)/unicode/utf8/utf8.go'
#pragma once

#include <functional>
#include <string>
#include <tuple>
#include <vector>

#include "golang/unicode/utf8/utf8.fwd.h"
#include "gocpp/support.h"

namespace golang::utf8
{
    extern gocpp::array<uint8_t, 256> first;
    struct acceptRange
    {
        uint8_t lo;
        uint8_t hi;

        using isGoStruct = void;

        template<typename T> requires gocpp::GoStruct<T>
        operator T();

        template<typename T> requires gocpp::GoStruct<T>
        bool operator==(const T& ref) const;

        std::ostream& PrintTo(std::ostream& os) const;
    };

    std::ostream& operator<<(std::ostream& os, const struct acceptRange& value);
    bool FullRune(gocpp::slice<unsigned char> p);
    bool FullRuneInString(std::string s);
    std::tuple<gocpp::rune, int> DecodeRune(gocpp::slice<unsigned char> p);
    std::tuple<gocpp::rune, int> DecodeRuneInString(std::string s);
    std::tuple<gocpp::rune, int> DecodeLastRune(gocpp::slice<unsigned char> p);
    std::tuple<gocpp::rune, int> DecodeLastRuneInString(std::string s);
    int RuneLen(gocpp::rune r);
    int EncodeRune(gocpp::slice<unsigned char> p, gocpp::rune r);
    gocpp::slice<unsigned char> AppendRune(gocpp::slice<unsigned char> p, gocpp::rune r);
    gocpp::slice<unsigned char> appendRuneNonASCII(gocpp::slice<unsigned char> p, gocpp::rune r);
    int RuneCount(gocpp::slice<unsigned char> p);
    int RuneCountInString(std::string s);
    bool RuneStart(unsigned char b);
    bool Valid(gocpp::slice<unsigned char> p);
    bool ValidString(std::string s);
    bool ValidRune(gocpp::rune r);
    extern gocpp::array<acceptRange, 16> acceptRanges;

    namespace rec
    {
    }
}

