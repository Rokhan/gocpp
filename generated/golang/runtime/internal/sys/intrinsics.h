// generated by GoCpp from file '$(ImportDir)/runtime/internal/sys/intrinsics.go'
#pragma once

#include <functional>
#include <string>
#include <tuple>
#include <vector>

#include "golang/runtime/internal/sys/intrinsics.fwd.h"
#include "gocpp/support.h"

namespace golang::sys
{
    extern gocpp::array<unsigned char, 32> deBruijn32tab;
    extern gocpp::array<unsigned char, 64> deBruijn64tab;
    extern std::string ntz8tab;
    int TrailingZeros32(uint32_t x);
    int TrailingZeros64(uint64_t x);
    int TrailingZeros8(uint8_t x);
    extern std::string len8tab;
    int Len64(uint64_t x);
    int OnesCount64(uint64_t x);
    int LeadingZeros64(uint64_t x);
    int LeadingZeros8(uint8_t x);
    int Len8(uint8_t x);
    uint64_t Bswap64(uint64_t x);
    uint32_t Bswap32(uint32_t x);
    void Prefetch(uintptr_t addr);
    void PrefetchStreamed(uintptr_t addr);

    namespace rec
    {
    }
}

