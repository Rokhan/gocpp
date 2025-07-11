// generated by GoCpp from file '$(ImportDir)/strconv/ftoaryu.go'
#pragma once

#include <functional>
#include <string>
#include <tuple>
#include <vector>

#include "golang/strconv/ftoaryu.fwd.h"
#include "gocpp/support.h"

#include "golang/strconv/ftoa.h"

namespace golang::strconv
{
    void ryuFtoaFixed32(struct decimalSlice* d, uint32_t mant, int exp, int prec);
    void ryuFtoaFixed64(struct decimalSlice* d, uint64_t mant, int exp, int prec);
    extern gocpp::array<uint64_t, 20> uint64pow10;
    void formatDecimal(struct decimalSlice* d, uint64_t m, bool trunc, bool roundUp, int prec);
    void ryuFtoaShortest(struct decimalSlice* d, uint64_t mant, int exp, struct floatInfo* flt);
    int mulByLog2Log10(int x);
    int mulByLog10Log2(int x);
    std::tuple<uint64_t, uint64_t, uint64_t, int> computeBounds(uint64_t mant, int exp, struct floatInfo* flt);
    void ryuDigits(struct decimalSlice* d, uint64_t lower, uint64_t central, uint64_t upper, bool c0, bool cup);
    void ryuDigits32(struct decimalSlice* d, uint32_t lower, uint32_t central, uint32_t upper, bool c0, bool cup, int endindex);
    std::tuple<uint32_t, int, bool> mult64bitPow10(uint32_t m, int e2, int q);
    std::tuple<uint64_t, int, bool> mult128bitPow10(uint64_t m, int e2, int q);
    bool divisibleByPower5(uint64_t m, int k);
    std::tuple<uint32_t, uint32_t> divmod1e9(uint64_t x);

    namespace rec
    {
    }
}

