// generated by GoCpp from file '$(ImportDir)/strconv/ftoaryu.go'
#include <complex>
#include <functional>
#include <iostream>
#include <iomanip>
#include <map>
#include <string>
#include <tuple>
#include <vector>

#include "golang/strconv/ftoaryu.h"
#include "gocpp/support.h"

#include "golang/math/bits/bits.h"
#include "golang/strconv/eisel_lemire.h"
#include "golang/strconv/ftoa.h"
#include "golang/strconv/itoa.h"

namespace golang::strconv
{
    namespace rec
    {
        using namespace mocklib::rec;
    }

    // ryuFtoaFixed32 formats mant*(2^exp) with prec decimal digits.
    void ryuFtoaFixed32(struct decimalSlice* d, uint32_t mant, int exp, int prec)
    {
        if(prec < 0)
        {
            gocpp::panic("ryuFtoaFixed32 called with negative prec"s);
        }
        if(prec > 9)
        {
            gocpp::panic("ryuFtoaFixed32 called with prec > 9"s);
        }
        if(mant == 0)
        {
            std::tie(d->nd, d->dp) = std::tuple{0, 0};
            return;
        }
        auto e2 = exp;
        if(auto b = bits::Len32(mant); b < 25)
        {
            mant <<= (unsigned int)(25 - b);
            e2 += b - 25;
        }
        auto q = - mulByLog2Log10(e2 + 24) + prec - 1;
        auto exact = q <= 27 && q >= 0;
        auto [di, dexp2, d0] = mult64bitPow10(mant, e2, q);
        if(dexp2 >= 0)
        {
            gocpp::panic("not enough significant bits after mult64bitPow10"s);
        }
        if(q < 0 && q >= - 10 && divisibleByPower5(uint64_t(mant), - q))
        {
            exact = true;
            d0 = true;
        }
        auto extra = (unsigned int)(- dexp2);
        auto extraMask = uint32_t((1 << extra) - 1);
        uint32_t dfrac;
        std::tie(di, dfrac) = std::tuple{di >> extra, di & extraMask};
        auto roundUp = false;
        if(exact)
        {
            roundUp = dfrac > (1 << (extra - 1)) || (dfrac == (1 << (extra - 1)) && ! d0) || (dfrac == (1 << (extra - 1)) && d0 && di & 1 == 1);
        }
        else
        {
            roundUp = (dfrac >> (extra - 1)) == 1;
        }
        if(dfrac != 0)
        {
            d0 = false;
        }
        formatDecimal(d, uint64_t(di), ! d0, roundUp, prec);
        d->dp -= q;
    }

    // ryuFtoaFixed64 formats mant*(2^exp) with prec decimal digits.
    void ryuFtoaFixed64(struct decimalSlice* d, uint64_t mant, int exp, int prec)
    {
        if(prec > 18)
        {
            gocpp::panic("ryuFtoaFixed64 called with prec > 18"s);
        }
        if(mant == 0)
        {
            std::tie(d->nd, d->dp) = std::tuple{0, 0};
            return;
        }
        auto e2 = exp;
        if(auto b = bits::Len64(mant); b < 55)
        {
            mant = mant << (unsigned int)(55 - b);
            e2 += b - 55;
        }
        auto q = - mulByLog2Log10(e2 + 54) + prec - 1;
        auto exact = q <= 55 && q >= 0;
        auto [di, dexp2, d0] = mult128bitPow10(mant, e2, q);
        if(dexp2 >= 0)
        {
            gocpp::panic("not enough significant bits after mult128bitPow10"s);
        }
        if(q < 0 && q >= - 22 && divisibleByPower5(mant, - q))
        {
            exact = true;
            d0 = true;
        }
        auto extra = (unsigned int)(- dexp2);
        auto extraMask = uint64_t((1 << extra) - 1);
        uint64_t dfrac;
        std::tie(di, dfrac) = std::tuple{di >> extra, di & extraMask};
        auto roundUp = false;
        if(exact)
        {
            roundUp = dfrac > (1 << (extra - 1)) || (dfrac == (1 << (extra - 1)) && ! d0) || (dfrac == (1 << (extra - 1)) && d0 && di & 1 == 1);
        }
        else
        {
            roundUp = (dfrac >> (extra - 1)) == 1;
        }
        if(dfrac != 0)
        {
            d0 = false;
        }
        formatDecimal(d, di, ! d0, roundUp, prec);
        d->dp -= q;
    }

    gocpp::array<uint64_t, 20> uint64pow10 = gocpp::array<uint64_t, 20> {1, 1e1, 1e2, 1e3, 1e4, 1e5, 1e6, 1e7, 1e8, 1e9, 1e10, 1e11, 1e12, 1e13, 1e14, 1e15, 1e16, 1e17, 1e18, 1e19};
    // formatDecimal fills d with at most prec decimal digits
    // of mantissa m. The boolean trunc indicates whether m
    // is truncated compared to the original number being formatted.
    void formatDecimal(struct decimalSlice* d, uint64_t m, bool trunc, bool roundUp, int prec)
    {
        auto max = uint64pow10[prec];
        auto trimmed = 0;
        for(; m >= max; )
        {
            auto [a, b] = std::tuple{m / 10, m % 10};
            m = a;
            trimmed++;
            if(b > 5)
            {
                roundUp = true;
            }
            else
            if(b < 5)
            {
                roundUp = false;
            }
            else
            {
                roundUp = trunc || m & 1 == 1;
            }
            if(b != 0)
            {
                trunc = true;
            }
        }
        if(roundUp)
        {
            m++;
        }
        if(m >= max)
        {
            m /= 10;
            trimmed++;
        }
        auto n = (unsigned int)(prec);
        d->nd = prec;
        auto v = m;
        for(; v >= 100; )
        {
            uint64_t v1 = {};
            uint64_t v2 = {};
            if((v >> 32) == 0)
            {
                std::tie(v1, v2) = std::tuple{uint64_t(uint32_t(v) / 100), uint64_t(uint32_t(v) % 100)};
            }
            else
            {
                std::tie(v1, v2) = std::tuple{v / 100, v % 100};
            }
            n -= 2;
            d->d[n + 1] = smallsString[2 * v2 + 1];
            d->d[n + 0] = smallsString[2 * v2 + 0];
            v = v1;
        }
        if(v > 0)
        {
            n--;
            d->d[n] = smallsString[2 * v + 1];
        }
        if(v >= 10)
        {
            n--;
            d->d[n] = smallsString[2 * v];
        }
        for(; d->d[d->nd - 1] == '0'; )
        {
            d->nd--;
            trimmed++;
        }
        d->dp = d->nd + trimmed;
    }

    // ryuFtoaShortest formats mant*2^exp with prec decimal digits.
    void ryuFtoaShortest(struct decimalSlice* d, uint64_t mant, int exp, struct floatInfo* flt)
    {
        if(mant == 0)
        {
            std::tie(d->nd, d->dp) = std::tuple{0, 0};
            return;
        }
        if(exp <= 0 && bits::TrailingZeros64(mant) >= - exp)
        {
            mant >>= (unsigned int)(- exp);
            ryuDigits(d, mant, mant, mant, true, false);
            return;
        }
        auto [ml, mc, mu, e2] = computeBounds(mant, exp, flt);
        if(e2 == 0)
        {
            ryuDigits(d, ml, mc, mu, true, false);
            return;
        }
        auto q = mulByLog2Log10(- e2) + 1;
        // We are going to multiply by 10^q using 128-bit arithmetic.
        // The exponent is the same for all 3 numbers.
        uint64_t dl = {};
        uint64_t dc = {};
        uint64_t du = {};
        bool dl0 = {};
        bool dc0 = {};
        bool du0 = {};
        if(flt == & float32info)
        {
            uint32_t dl32 = {};
            uint32_t dc32 = {};
            uint32_t du32 = {};
            std::tie(dl32, gocpp_id_0, dl0) = mult64bitPow10(uint32_t(ml), e2, q);
            std::tie(dc32, gocpp_id_1, dc0) = mult64bitPow10(uint32_t(mc), e2, q);
            std::tie(du32, e2, du0) = mult64bitPow10(uint32_t(mu), e2, q);
            std::tie(dl, dc, du) = std::tuple{uint64_t(dl32), uint64_t(dc32), uint64_t(du32)};
        }
        else
        {
            std::tie(dl, gocpp_id_2, dl0) = mult128bitPow10(ml, e2, q);
            std::tie(dc, gocpp_id_3, dc0) = mult128bitPow10(mc, e2, q);
            std::tie(du, e2, du0) = mult128bitPow10(mu, e2, q);
        }
        if(e2 >= 0)
        {
            gocpp::panic("not enough significant bits after mult128bitPow10"s);
        }
        if(q > 55)
        {
            std::tie(dl0, dc0, du0) = std::tuple{false, false, false};
        }
        if(q < 0 && q >= - 24)
        {
            if(divisibleByPower5(ml, - q))
            {
                dl0 = true;
            }
            if(divisibleByPower5(mc, - q))
            {
                dc0 = true;
            }
            if(divisibleByPower5(mu, - q))
            {
                du0 = true;
            }
        }
        auto extra = (unsigned int)(- e2);
        auto extraMask = uint64_t((1 << extra) - 1);
        auto [dl_tmp, fracl] = std::tuple{dl >> extra, dl & extraMask};
        auto& dl = dl_tmp;
        auto [dc_tmp, fracc] = std::tuple{dc >> extra, dc & extraMask};
        auto& dc = dc_tmp;
        auto [du_tmp, fracu] = std::tuple{du >> extra, du & extraMask};
        auto& du = du_tmp;
        auto uok = ! du0 || fracu > 0;
        if(du0 && fracu == 0)
        {
            uok = mant & 1 == 0;
        }
        if(! uok)
        {
            du--;
        }
        auto cup = false;
        if(dc0)
        {
            cup = fracc > (1 << (extra - 1)) || (fracc == (1 << (extra - 1)) && dc & 1 == 1);
        }
        else
        {
            cup = (fracc >> (extra - 1)) == 1;
        }
        auto lok = dl0 && fracl == 0 && (mant & 1 == 0);
        if(! lok)
        {
            dl++;
        }
        auto c0 = dc0 && fracc == 0;
        ryuDigits(d, dl, dc, du, c0, cup);
        d->dp -= q;
    }

    // mulByLog2Log10 returns math.Floor(x * log(2)/log(10)) for an integer x in
    // the range -1600 <= x && x <= +1600.
    //
    // The range restriction lets us work in faster integer arithmetic instead of
    // slower floating point arithmetic. Correctness is verified by unit tests.
    int mulByLog2Log10(int x)
    {
        return (x * 78913) >> 18;
    }

    // mulByLog10Log2 returns math.Floor(x * log(10)/log(2)) for an integer x in
    // the range -500 <= x && x <= +500.
    //
    // The range restriction lets us work in faster integer arithmetic instead of
    // slower floating point arithmetic. Correctness is verified by unit tests.
    int mulByLog10Log2(int x)
    {
        return (x * 108853) >> 15;
    }

    // computeBounds returns a floating-point vector (l, c, u)×2^e2
    // where the mantissas are 55-bit (or 26-bit) integers, describing the interval
    // represented by the input float64 or float32.
    std::tuple<uint64_t, uint64_t, uint64_t, int> computeBounds(uint64_t mant, int exp, struct floatInfo* flt)
    {
        uint64_t lower;
        uint64_t central;
        uint64_t upper;
        int e2;
        if(mant != (1 << flt->mantbits) || exp == flt->bias + 1 - int(flt->mantbits))
        {
            std::tie(lower, central, upper) = std::tuple{2 * mant - 1, 2 * mant, 2 * mant + 1};
            e2 = exp - 1;
            return {lower, central, upper, e2};
        }
        else
        {
            std::tie(lower, central, upper) = std::tuple{4 * mant - 1, 4 * mant, 4 * mant + 2};
            e2 = exp - 2;
            return {lower, central, upper, e2};
        }
    }

    void ryuDigits(struct decimalSlice* d, uint64_t lower, uint64_t central, uint64_t upper, bool c0, bool cup)
    {
        auto [lhi, llo] = divmod1e9(lower);
        auto [chi, clo] = divmod1e9(central);
        auto [uhi, ulo] = divmod1e9(upper);
        if(uhi == 0)
        {
            ryuDigits32(d, llo, clo, ulo, c0, cup, 8);
        }
        else
        if(lhi < uhi)
        {
            if(llo != 0)
            {
                lhi++;
            }
            c0 = c0 && clo == 0;
            cup = (clo > 5e8) || (clo == 5e8 && cup);
            ryuDigits32(d, lhi, chi, uhi, c0, cup, 8);
            d->dp += 9;
        }
        else
        {
            d->nd = 0;
            auto n = (unsigned int)(9);
            for(auto v = chi; v > 0; )
            {
                auto [v1, v2] = std::tuple{v / 10, v % 10};
                v = v1;
                n--;
                d->d[n] = (unsigned char)(v2 + '0');
            }
            d->d = d->d.make_slice(n);
            d->nd = int(9 - n);
            ryuDigits32(d, llo, clo, ulo, c0, cup, d->nd + 8);
        }
        for(; d->nd > 0 && d->d[d->nd - 1] == '0'; )
        {
            d->nd--;
        }
        for(; d->nd > 0 && d->d[0] == '0'; )
        {
            d->nd--;
            d->dp--;
            d->d = d->d.make_slice(1);
        }
    }

    // ryuDigits32 emits decimal digits for a number less than 1e9.
    void ryuDigits32(struct decimalSlice* d, uint32_t lower, uint32_t central, uint32_t upper, bool c0, bool cup, int endindex)
    {
        if(upper == 0)
        {
            d->dp = endindex + 1;
            return;
        }
        auto trimmed = 0;
        auto cNextDigit = 0;
        for(; upper > 0; )
        {
            auto l = (lower + 9) / 10;
            auto [c, cdigit] = std::tuple{central / 10, central % 10};
            auto u = upper / 10;
            if(l > u)
            {
                break;
            }
            if(l == c + 1 && c < u)
            {
                c++;
                cdigit = 0;
                cup = false;
            }
            trimmed++;
            c0 = c0 && cNextDigit == 0;
            cNextDigit = int(cdigit);
            std::tie(lower, central, upper) = std::tuple{l, c, u};
        }
        if(trimmed > 0)
        {
            cup = cNextDigit > 5 || (cNextDigit == 5 && ! c0) || (cNextDigit == 5 && c0 && central & 1 == 1);
        }
        if(central < upper && cup)
        {
            central++;
        }
        endindex -= trimmed;
        auto v = central;
        auto n = endindex;
        for(; n > d->nd; )
        {
            auto [v1, v2] = std::tuple{v / 100, v % 100};
            d->d[n] = smallsString[2 * v2 + 1];
            d->d[n - 1] = smallsString[2 * v2 + 0];
            n -= 2;
            v = v1;
        }
        if(n == d->nd)
        {
            d->d[n] = (unsigned char)(v + '0');
        }
        d->nd = endindex + 1;
        d->dp = d->nd + trimmed;
    }

    // mult64bitPow10 takes a floating-point input with a 25-bit
    // mantissa and multiplies it with 10^q. The resulting mantissa
    // is m*P >> 57 where P is a 64-bit element of the detailedPowersOfTen tables.
    // It is typically 31 or 32-bit wide.
    // The returned boolean is true if all trimmed bits were zero.
    //
    // That is:
    //
    //	m*2^e2 * round(10^q) = resM * 2^resE + ε
    //	exact = ε == 0
    std::tuple<uint32_t, int, bool> mult64bitPow10(uint32_t m, int e2, int q)
    {
        uint32_t resM;
        int resE;
        bool exact;
        if(q == 0)
        {
            return {m << 6, e2 - 6, true};
        }
        if(q < detailedPowersOfTenMinExp10 || detailedPowersOfTenMaxExp10 < q)
        {
            gocpp::panic("mult64bitPow10: power of 10 is out of range"s);
        }
        auto pow = detailedPowersOfTen[q - detailedPowersOfTenMinExp10][1];
        if(q < 0)
        {
            pow += 1;
        }
        auto [hi, lo] = bits::Mul64(uint64_t(m), pow);
        e2 += mulByLog10Log2(q) - 63 + 57;
        return {uint32_t((hi << 7) | (lo >> 57)), e2, (lo << 7) == 0};
    }

    // mult128bitPow10 takes a floating-point input with a 55-bit
    // mantissa and multiplies it with 10^q. The resulting mantissa
    // is m*P >> 119 where P is a 128-bit element of the detailedPowersOfTen tables.
    // It is typically 63 or 64-bit wide.
    // The returned boolean is true is all trimmed bits were zero.
    //
    // That is:
    //
    //	m*2^e2 * round(10^q) = resM * 2^resE + ε
    //	exact = ε == 0
    std::tuple<uint64_t, int, bool> mult128bitPow10(uint64_t m, int e2, int q)
    {
        uint64_t resM;
        int resE;
        bool exact;
        if(q == 0)
        {
            return {m << 8, e2 - 8, true};
        }
        if(q < detailedPowersOfTenMinExp10 || detailedPowersOfTenMaxExp10 < q)
        {
            gocpp::panic("mult128bitPow10: power of 10 is out of range"s);
        }
        auto pow = detailedPowersOfTen[q - detailedPowersOfTenMinExp10];
        if(q < 0)
        {
            pow[0] += 1;
        }
        e2 += mulByLog10Log2(q) - 127 + 119;
        auto [l1, l0] = bits::Mul64(m, pow[0]);
        auto [h1, h0] = bits::Mul64(m, pow[1]);
        auto [mid, carry] = bits::Add64(l1, h0, 0);
        h1 += carry;
        return {(h1 << 9) | (mid >> 55), e2, (mid << 9) == 0 && l0 == 0};
    }

    bool divisibleByPower5(uint64_t m, int k)
    {
        if(m == 0)
        {
            return true;
        }
        for(auto i = 0; i < k; i++)
        {
            if(m % 5 != 0)
            {
                return false;
            }
            m /= 5;
        }
        return true;
    }

    // divmod1e9 computes quotient and remainder of division by 1e9,
    // avoiding runtime uint64 division on 32-bit platforms.
    std::tuple<uint32_t, uint32_t> divmod1e9(uint64_t x)
    {
        if(! host32bit)
        {
            return {uint32_t(x / 1e9), uint32_t(x % 1e9)};
        }
        auto [hi, gocpp_id_4] = bits::Mul64(x >> 1, 0x89705f4136b4a598);
        auto q = hi >> 28;
        return {uint32_t(q), uint32_t(x - q * 1e9)};
    }

}

