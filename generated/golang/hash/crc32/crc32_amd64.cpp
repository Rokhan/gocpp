// generated by GoCpp from file '$(ImportDir)/hash/crc32/crc32_amd64.go'
#include <complex>
#include <functional>
#include <iostream>
#include <iomanip>
#include <map>
#include <string>
#include <tuple>
#include <vector>

#include "golang/hash/crc32/crc32_amd64.h"
#include "gocpp/support.h"

#include "golang/hash/crc32/crc32.h"
#include "golang/hash/crc32/crc32_generic.h"
#include "golang/unsafe/unsafe.h"

namespace golang::crc32
{
    uint32_t castagnoliSSE42(uint32_t crc, gocpp::slice<unsigned char> p)
    /* convertBlockStmt, nil block */;

    std::tuple<uint32_t, uint32_t, uint32_t> castagnoliSSE42Triple(uint32_t crcA, uint32_t crcB, uint32_t crcC, gocpp::slice<unsigned char> a, gocpp::slice<unsigned char> b, gocpp::slice<unsigned char> c, uint32_t rounds)
    /* convertBlockStmt, nil block */;

    uint32_t ieeeCLMUL(uint32_t crc, gocpp::slice<unsigned char> p)
    /* convertBlockStmt, nil block */;

    int castagnoliK1 = 168;
    int castagnoliK2 = 1344;
    sse42Table* castagnoliSSE42TableK1;
    sse42Table* castagnoliSSE42TableK2;
    bool archAvailableCastagnoli()
    {
        return cpu.X86.HasSSE42;
    }

    void archInitCastagnoli()
    {
        if(! cpu.X86.HasSSE42)
        {
            gocpp::panic("arch-specific Castagnoli not available");
        }
        castagnoliSSE42TableK1 = go_new(sse42Table);
        castagnoliSSE42TableK2 = go_new(sse42Table);
        gocpp::array<unsigned char, castagnoliK2> tmp = {};
        for(auto b = 0; b < 4; b++)
        {
            for(auto i = 0; i < 256; i++)
            {
                auto val = uint32_t(i) << uint32_t(b * 8);
                castagnoliSSE42TableK1[b][i] = castagnoliSSE42(val, tmp.make_slice(0, castagnoliK1));
                castagnoliSSE42TableK2[b][i] = castagnoliSSE42(val, tmp.make_slice(0, ));
            }
        }
    }

    uint32_t castagnoliShift(sse42Table* table, uint32_t crc)
    {
        return table[3][crc >> 24] ^ table[2][(crc >> 16) & 0xFF] ^ table[1][(crc >> 8) & 0xFF] ^ table[0][crc & 0xFF];
    }

    uint32_t archUpdateCastagnoli(uint32_t crc, gocpp::slice<unsigned char> p)
    {
        if(! cpu.X86.HasSSE42)
        {
            gocpp::panic("not available");
        }
        crc = ^ crc;
        if(len(p) >= castagnoliK1 * 3)
        {
            auto delta = int(uintptr(Pointer(gocpp::recv(unsafe), & p[0])) & 7);
            if(delta != 0)
            {
                delta = 8 - delta;
                crc = castagnoliSSE42(crc, p.make_slice(0, delta));
                p = p.make_slice(delta);
            }
        }
        for(; len(p) >= castagnoliK2 * 3; )
        {
            auto [crcA, crcB, crcC] = castagnoliSSE42Triple(crc, 0, 0, p, p.make_slice(castagnoliK2), p.make_slice(castagnoliK2 * 2), castagnoliK2 / 24);
            auto crcAB = castagnoliShift(castagnoliSSE42TableK2, crcA) ^ crcB;
            crc = castagnoliShift(castagnoliSSE42TableK2, crcAB) ^ crcC;
            p = p.make_slice(castagnoliK2 * 3);
        }
        for(; len(p) >= castagnoliK1 * 3; )
        {
            auto [crcA, crcB, crcC] = castagnoliSSE42Triple(crc, 0, 0, p, p.make_slice(castagnoliK1), p.make_slice(castagnoliK1 * 2), castagnoliK1 / 24);
            auto crcAB = castagnoliShift(castagnoliSSE42TableK1, crcA) ^ crcB;
            crc = castagnoliShift(castagnoliSSE42TableK1, crcAB) ^ crcC;
            p = p.make_slice(castagnoliK1 * 3);
        }
        crc = castagnoliSSE42(crc, p);
        return ^ crc;
    }

    bool archAvailableIEEE()
    {
        return cpu.X86.HasPCLMULQDQ && cpu.X86.HasSSE41;
    }

    slicing8Table* archIeeeTable8;
    void archInitIEEE()
    {
        if(! cpu.X86.HasPCLMULQDQ || ! cpu.X86.HasSSE41)
        {
            gocpp::panic("not available");
        }
        archIeeeTable8 = slicingMakeTable(IEEE);
    }

    uint32_t archUpdateIEEE(uint32_t crc, gocpp::slice<unsigned char> p)
    {
        if(! cpu.X86.HasPCLMULQDQ || ! cpu.X86.HasSSE41)
        {
            gocpp::panic("not available");
        }
        if(len(p) >= 64)
        {
            auto left = len(p) & 15;
            auto go_do = len(p) - left;
            crc = ^ ieeeCLMUL(^ crc, p.make_slice(0, go_do));
            p = p.make_slice(go_do);
        }
        if(len(p) == 0)
        {
            return crc;
        }
        return slicingUpdate(crc, archIeeeTable8, p);
    }

}
