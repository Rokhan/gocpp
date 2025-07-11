// generated by GoCpp from file '$(ImportDir)/runtime/hash64.go'
#include <complex>
#include <functional>
#include <iostream>
#include <iomanip>
#include <map>
#include <string>
#include <tuple>
#include <vector>

#include "golang/runtime/hash64.h"
#include "gocpp/support.h"

#include "golang/runtime/alg.h"
#include "golang/runtime/internal/math/math.h"
#include "golang/runtime/stubs.h"
#include "golang/unsafe/unsafe.h"

namespace golang::runtime
{
    namespace rec
    {
        using namespace mocklib::rec;
    }

    uintptr_t memhashFallback(unsafe::Pointer p, uintptr_t seed, uintptr_t s)
    {
        uintptr_t a = {};
        uintptr_t b = {};
        seed ^= hashkey[0] ^ m1;
        //Go switch emulation
        {
            int conditionId = -1;
            if(s == 0) { conditionId = 0; }
            else if(s < 4) { conditionId = 1; }
            else if(s == 4) { conditionId = 2; }
            else if(s < 8) { conditionId = 3; }
            else if(s == 8) { conditionId = 4; }
            else if(s <= 16) { conditionId = 5; }
            switch(conditionId)
            {
                case 0:
                    return seed;
                    break;
                case 1:
                    a = uintptr_t(*(unsigned char*)(p));
                    a |= uintptr_t(*(unsigned char*)(add(p, s >> 1))) << 8;
                    a |= uintptr_t(*(unsigned char*)(add(p, s - 1))) << 16;
                    break;
                case 2:
                    a = r4(p);
                    b = a;
                    break;
                case 3:
                    a = r4(p);
                    b = r4(add(p, s - 4));
                    break;
                case 4:
                    a = r8(p);
                    b = a;
                    break;
                case 5:
                    a = r8(p);
                    b = r8(add(p, s - 8));
                    break;
                default:
                    auto l = s;
                    if(l > 48)
                    {
                        auto seed1 = seed;
                        auto seed2 = seed;
                        for(; l > 48; l -= 48)
                        {
                            seed = mix(r8(p) ^ m2, r8(add(p, 8)) ^ seed);
                            seed1 = mix(r8(add(p, 16)) ^ m3, r8(add(p, 24)) ^ seed1);
                            seed2 = mix(r8(add(p, 32)) ^ m4, r8(add(p, 40)) ^ seed2);
                            p = add(p, 48);
                        }
                        seed ^= seed1 ^ seed2;
                    }
                    for(; l > 16; l -= 16)
                    {
                        seed = mix(r8(p) ^ m2, r8(add(p, 8)) ^ seed);
                        p = add(p, 16);
                    }
                    a = r8(add(p, l - 16));
                    b = r8(add(p, l - 8));
                    break;
            }
        }
        return mix(m5 ^ s, mix(a ^ m2, b ^ seed));
    }

    uintptr_t memhash32Fallback(unsafe::Pointer p, uintptr_t seed)
    {
        auto a = r4(p);
        return mix(m5 ^ 4, mix(a ^ m2, a ^ seed ^ hashkey[0] ^ m1));
    }

    uintptr_t memhash64Fallback(unsafe::Pointer p, uintptr_t seed)
    {
        auto a = r8(p);
        return mix(m5 ^ 8, mix(a ^ m2, a ^ seed ^ hashkey[0] ^ m1));
    }

    uintptr_t mix(uintptr_t a, uintptr_t b)
    {
        auto [hi, lo] = math::Mul64(uint64_t(a), uint64_t(b));
        return uintptr_t(hi ^ lo);
    }

    uintptr_t r4(unsafe::Pointer p)
    {
        return uintptr_t(readUnaligned32(p));
    }

    uintptr_t r8(unsafe::Pointer p)
    {
        return uintptr_t(readUnaligned64(p));
    }

}

