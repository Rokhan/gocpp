// generated by GoCpp from file '$(ImportDir)/math/exp.go'
#include <complex>
#include <functional>
#include <iostream>
#include <iomanip>
#include <map>
#include <string>
#include <tuple>
#include <vector>

#include "golang/math/exp.h"
#include "gocpp/support.h"

#include "golang/math/bits.h"
#include "golang/math/exp2_noasm.h"
#include "golang/math/exp_asm.h"
#include "golang/math/ldexp.h"

namespace golang::math
{
    namespace rec
    {
        using namespace mocklib::rec;
    }

    // Exp returns e**x, the base-e exponential of x.
    //
    // Special cases are:
    //
    //	Exp(+Inf) = +Inf
    //	Exp(NaN) = NaN
    //
    // Very large values overflow to 0 or +Inf.
    // Very small values underflow to 1.
    double Exp(double x)
    {
        if(haveArchExp)
        {
            return archExp(x);
        }
        return exp(x);
    }

    double exp(double x)
    {
        auto Ln2Hi = 6.93147180369123816490e-01;
        auto Ln2Lo = 1.90821492927058770002e-10;
        auto Log2e = 1.44269504088896338700e+00;
        auto Overflow = 7.09782712893383973096e+02;
        auto Underflow = - 7.45133219101941108420e+02;
        auto NearZero = 1.0 / (1 << 28);
        //Go switch emulation
        {
            int conditionId = -1;
            if(IsNaN(x) || IsInf(x, 1)) { conditionId = 0; }
            else if(IsInf(x, - 1)) { conditionId = 1; }
            else if(x > Overflow) { conditionId = 2; }
            else if(x < Underflow) { conditionId = 3; }
            else if(- NearZero < x && x < NearZero) { conditionId = 4; }
            switch(conditionId)
            {
                case 0:
                    return x;
                    break;
                case 1:
                    return 0;
                    break;
                case 2:
                    return Inf(1);
                    break;
                case 3:
                    return 0;
                    break;
                case 4:
                    return 1 + x;
                    break;
            }
        }
        // reduce; computed as r = hi - lo for extra precision.
        int k = {};
        //Go switch emulation
        {
            int conditionId = -1;
            if(x < 0) { conditionId = 0; }
            else if(x > 0) { conditionId = 1; }
            switch(conditionId)
            {
                case 0:
                    k = int(Log2e * x - 0.5);
                    break;
                case 1:
                    k = int(Log2e * x + 0.5);
                    break;
            }
        }
        auto hi = x - double(k) * Ln2Hi;
        auto lo = double(k) * Ln2Lo;
        return expmulti(hi, lo, k);
    }

    // Exp2 returns 2**x, the base-2 exponential of x.
    //
    // Special cases are the same as [Exp].
    double Exp2(double x)
    {
        if(haveArchExp2)
        {
            return archExp2(x);
        }
        return exp2(x);
    }

    double exp2(double x)
    {
        auto Ln2Hi = 6.93147180369123816490e-01;
        auto Ln2Lo = 1.90821492927058770002e-10;
        auto Overflow = 1.0239999999999999e+03;
        auto Underflow = - 1.0740e+03;
        //Go switch emulation
        {
            int conditionId = -1;
            if(IsNaN(x) || IsInf(x, 1)) { conditionId = 0; }
            else if(IsInf(x, - 1)) { conditionId = 1; }
            else if(x > Overflow) { conditionId = 2; }
            else if(x < Underflow) { conditionId = 3; }
            switch(conditionId)
            {
                case 0:
                    return x;
                    break;
                case 1:
                    return 0;
                    break;
                case 2:
                    return Inf(1);
                    break;
                case 3:
                    return 0;
                    break;
            }
        }
        // argument reduction; x = r×lg(e) + k with |r| ≤ ln(2)/2.
        // computed as r = hi - lo for extra precision.
        int k = {};
        //Go switch emulation
        {
            int conditionId = -1;
            if(x > 0) { conditionId = 0; }
            else if(x < 0) { conditionId = 1; }
            switch(conditionId)
            {
                case 0:
                    k = int(x + 0.5);
                    break;
                case 1:
                    k = int(x - 0.5);
                    break;
            }
        }
        auto t = x - double(k);
        auto hi = t * Ln2Hi;
        auto lo = - t * Ln2Lo;
        return expmulti(hi, lo, k);
    }

    // exp1 returns e**r × 2**k where r = hi - lo and |r| ≤ ln(2)/2.
    double expmulti(double hi, double lo, int k)
    {
        auto P1 = 1.66666666666666657415e-01;
        auto P2 = - 2.77777777770155933842e-03;
        auto P3 = 6.61375632143793436117e-05;
        auto P4 = - 1.65339022054652515390e-06;
        auto P5 = 4.13813679705723846039e-08;
        auto r = hi - lo;
        auto t = r * r;
        auto c = r - t * (P1 + t * (P2 + t * (P3 + t * (P4 + t * P5))));
        auto y = 1 - ((lo - (r * c) / (2 - c)) - hi);
        return Ldexp(y, k);
    }

}

