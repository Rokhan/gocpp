// generated by GoCpp from file '$(ImportDir)/internal/cpu/cpu_x86.go'
#pragma once

#include <functional>
#include <string>
#include <tuple>
#include <vector>

#include "golang/internal/cpu/cpu_x86.fwd.h"
#include "gocpp/support.h"

#include "golang/internal/cpu/cpu.h"

namespace golang::cpu
{
    extern int CacheLinePadSize;
    std::tuple<uint32_t, uint32_t, uint32_t, uint32_t> cpuid(uint32_t eaxArg, uint32_t ecxArg);
    std::tuple<uint32_t, uint32_t> xgetbv();
    int32_t getGOAMD64level();
    extern int cpuid_SSE2;
    extern int cpuid_SSE3;
    extern int cpuid_PCLMULQDQ;
    extern int cpuid_SSSE3;
    extern int cpuid_FMA;
    extern int cpuid_SSE41;
    extern int cpuid_SSE42;
    extern int cpuid_POPCNT;
    extern int cpuid_AES;
    extern int cpuid_OSXSAVE;
    extern int cpuid_AVX;
    extern int cpuid_BMI1;
    extern int cpuid_AVX2;
    extern int cpuid_BMI2;
    extern int cpuid_ERMS;
    extern int cpuid_AVX512F;
    extern int cpuid_ADX;
    extern int cpuid_SHA;
    extern int cpuid_AVX512BW;
    extern int cpuid_AVX512VL;
    extern int cpuid_RDTSCP;
    void doinit();
    bool isSet(uint32_t hwc, uint32_t value);
    std::string Name();
    gocpp::slice<unsigned char> appendBytes(gocpp::slice<unsigned char> b, gocpp::slice<uint32_t> args);
    template<typename... Args>
    gocpp::slice<unsigned char> appendBytes(gocpp::slice<unsigned char> b, Args... args)
    {
        return appendBytes(b, gocpp::ToSlice<uint32_t>(args...));
    }

}
