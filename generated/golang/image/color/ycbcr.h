// generated by GoCpp from file '$(ImportDir)/image/color/ycbcr.go'
#pragma once

#include <functional>
#include <string>
#include <tuple>
#include <vector>

#include "golang/image/color/ycbcr.fwd.h"
#include "gocpp/support.h"

#include "golang/image/color/color.h"

namespace golang::color
{
    std::tuple<uint8_t, uint8_t, uint8_t> RGBToYCbCr(uint8_t r, uint8_t g, uint8_t b);
    std::tuple<uint8_t, uint8_t, uint8_t> YCbCrToRGB(uint8_t y, uint8_t cb, uint8_t cr);
    struct YCbCr
    {
        uint8_t Y;
        uint8_t Cb;
        uint8_t Cr;

        using isGoStruct = void;

        template<typename T> requires gocpp::GoStruct<T>
        operator T();

        template<typename T> requires gocpp::GoStruct<T>
        bool operator==(const T& ref) const;

        std::ostream& PrintTo(std::ostream& os) const;
    };

    std::ostream& operator<<(std::ostream& os, const struct YCbCr& value);
    extern Model YCbCrModel;
    struct Color yCbCrModel(struct Color c);
    extern Model NYCbCrAModel;
    struct Color nYCbCrAModel(struct Color c);
    std::tuple<uint8_t, uint8_t, uint8_t, uint8_t> RGBToCMYK(uint8_t r, uint8_t g, uint8_t b);
    std::tuple<uint8_t, uint8_t, uint8_t> CMYKToRGB(uint8_t c, uint8_t m, uint8_t y, uint8_t k);
    struct CMYK
    {
        uint8_t C;
        uint8_t M;
        uint8_t Y;
        uint8_t K;

        using isGoStruct = void;

        template<typename T> requires gocpp::GoStruct<T>
        operator T();

        template<typename T> requires gocpp::GoStruct<T>
        bool operator==(const T& ref) const;

        std::ostream& PrintTo(std::ostream& os) const;
    };

    std::ostream& operator<<(std::ostream& os, const struct CMYK& value);
    extern Model CMYKModel;
    struct Color cmykModel(struct Color c);
    struct NYCbCrA
    {
        YCbCr YCbCr;
        uint8_t A;

        using isGoStruct = void;

        template<typename T> requires gocpp::GoStruct<T>
        operator T();

        template<typename T> requires gocpp::GoStruct<T>
        bool operator==(const T& ref) const;

        std::ostream& PrintTo(std::ostream& os) const;
    };

    std::ostream& operator<<(std::ostream& os, const struct NYCbCrA& value);

    namespace rec
    {
        std::tuple<uint32_t, uint32_t, uint32_t, uint32_t> RGBA(struct YCbCr c);
        std::tuple<uint32_t, uint32_t, uint32_t, uint32_t> RGBA(struct NYCbCrA c);
        std::tuple<uint32_t, uint32_t, uint32_t, uint32_t> RGBA(struct CMYK c);
    }
}

