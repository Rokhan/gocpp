// generated by GoCpp from file '$(ImportDir)/math/pow.go'
#include <complex>
#include <functional>
#include <iostream>
#include <iomanip>
#include <map>
#include <string>
#include <tuple>
#include <vector>

#include "golang/math/pow.h"
#include "gocpp/support.h"

#include "golang/math/abs.h"
#include "golang/math/bits.h"
#include "golang/math/exp.h"
#include "golang/math/frexp.h"
#include "golang/math/ldexp.h"
#include "golang/math/log.h"
#include "golang/math/modf.h"
#include "golang/math/signbit.h"
#include "golang/math/sqrt.h"
#include "golang/math/stubs.h"

namespace golang::math
{
    namespace rec
    {
        using namespace mocklib::rec;
    }

    bool isOddInt(double x)
    {
        if(Abs(x) >= (1 << 53))
        {
            return false;
        }
        auto [xi, xf] = Modf(x);
        return xf == 0 && int64_t(xi) & 1 == 1;
    }

    // Pow returns x**y, the base-x exponential of y.
    //
    // Special cases are (in order):
    //
    //	Pow(x, ±0) = 1 for any x
    //	Pow(1, y) = 1 for any y
    //	Pow(x, 1) = x for any x
    //	Pow(NaN, y) = NaN
    //	Pow(x, NaN) = NaN
    //	Pow(±0, y) = ±Inf for y an odd integer < 0
    //	Pow(±0, -Inf) = +Inf
    //	Pow(±0, +Inf) = +0
    //	Pow(±0, y) = +Inf for finite y < 0 and not an odd integer
    //	Pow(±0, y) = ±0 for y an odd integer > 0
    //	Pow(±0, y) = +0 for finite y > 0 and not an odd integer
    //	Pow(-1, ±Inf) = 1
    //	Pow(x, +Inf) = +Inf for |x| > 1
    //	Pow(x, -Inf) = +0 for |x| > 1
    //	Pow(x, +Inf) = +0 for |x| < 1
    //	Pow(x, -Inf) = +Inf for |x| < 1
    //	Pow(+Inf, y) = +Inf for y > 0
    //	Pow(+Inf, y) = +0 for y < 0
    //	Pow(-Inf, y) = Pow(-0, -y)
    //	Pow(x, y) = NaN for finite x < 0 and finite non-integer y
    double Pow(double x, double y)
    {
        if(haveArchPow)
        {
            return archPow(x, y);
        }
        return pow(x, y);
    }

    double pow(double x, double y)
    {
        //Go switch emulation
        {
            int conditionId = -1;
            if(y == 0 || x == 1) { conditionId = 0; }
            else if(y == 1) { conditionId = 1; }
            else if(IsNaN(x) || IsNaN(y)) { conditionId = 2; }
            else if(x == 0) { conditionId = 3; }
            else if(IsInf(y, 0)) { conditionId = 4; }
            else if(IsInf(x, 0)) { conditionId = 5; }
            else if(y == 0.5) { conditionId = 6; }
            else if(y == - 0.5) { conditionId = 7; }
            switch(conditionId)
            {
                case 0:
                    return 1;
                    break;
                case 1:
                    return x;
                    break;
                case 2:
                    return NaN();
                    break;
                case 3:
                    //Go switch emulation
                    {
                        int conditionId = -1;
                        if(y < 0) { conditionId = 0; }
                        else if(y > 0) { conditionId = 1; }
                        switch(conditionId)
                        {
                            case 0:
                                if(Signbit(x) && isOddInt(y))
                                {
                                    return Inf(- 1);
                                }
                                return Inf(1);
                                break;
                            case 1:
                                if(Signbit(x) && isOddInt(y))
                                {
                                    return x;
                                }
                                return 0;
                                break;
                        }
                    }
                    break;
                case 4:
                    //Go switch emulation
                    {
                        int conditionId = -1;
                        if(x == - 1) { conditionId = 0; }
                        else if((Abs(x) < 1) == IsInf(y, 1)) { conditionId = 1; }
                        switch(conditionId)
                        {
                            case 0:
                                return 1;
                                break;
                            case 1:
                                return 0;
                                break;
                            default:
                                return Inf(1);
                                break;
                        }
                    }
                    break;
                case 5:
                    if(IsInf(x, - 1))
                    {
                        return Pow(1 / x, - y);
                    }
                    //Go switch emulation
                    {
                        int conditionId = -1;
                        if(y < 0) { conditionId = 0; }
                        else if(y > 0) { conditionId = 1; }
                        switch(conditionId)
                        {
                            case 0:
                                return 0;
                                break;
                            case 1:
                                return Inf(1);
                                break;
                        }
                    }
                    break;
                case 6:
                    return Sqrt(x);
                    break;
                case 7:
                    return 1 / Sqrt(x);
                    break;
            }
        }
        auto [yi, yf] = Modf(Abs(y));
        if(yf != 0 && x < 0)
        {
            return NaN();
        }
        if(yi >= (1 << 63))
        {
            //Go switch emulation
            {
                int conditionId = -1;
                if(x == - 1) { conditionId = 0; }
                else if((Abs(x) < 1) == (y > 0)) { conditionId = 1; }
                switch(conditionId)
                {
                    case 0:
                        return 1;
                        break;
                    case 1:
                        return 0;
                        break;
                    default:
                        return Inf(1);
                        break;
                }
            }
        }
        auto a1 = 1.0;
        auto ae = 0;
        if(yf != 0)
        {
            if(yf > 0.5)
            {
                yf--;
                yi++;
            }
            a1 = Exp(yf * Log(x));
        }
        auto [x1, xe] = Frexp(x);
        for(auto i = int64_t(yi); i != 0; i >>= 1)
        {
            if(xe < (- 1 << 12) || (1 << 12) < xe)
            {
                ae += xe;
                break;
            }
            if(i & 1 == 1)
            {
                a1 *= x1;
                ae += xe;
            }
            x1 *= x1;
            xe <<= 1;
            if(x1 < .5)
            {
                x1 += x1;
                xe--;
            }
        }
        if(y < 0)
        {
            a1 = 1 / a1;
            ae = - ae;
        }
        return Ldexp(a1, ae);
    }

}

