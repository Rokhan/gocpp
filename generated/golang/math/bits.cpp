// generated by GoCpp from file '$(ImportDir)/math/bits.go'
#include <complex>
#include <functional>
#include <iostream>
#include <iomanip>
#include <map>
#include <string>
#include <tuple>
#include <vector>

#include "golang/math/bits.h"
#include "gocpp/support.h"

#include "golang/math/abs.h"
#include "golang/math/const.h"
#include "golang/math/unsafe.h"

namespace golang::math
{
    double Inf(int sign)
    {
        uint64_t v = {};
        if(sign >= 0)
        {
            v = uvinf;
        }
        else
        {
            v = uvneginf;
        }
        return Float64frombits(v);
    }

    double NaN()
    {
        return Float64frombits(uvnan);
    }

    bool IsNaN(double f)
    {
        bool is;
        return f != f;
    }

    bool IsInf(double f, int sign)
    {
        return sign >= 0 && f > MaxFloat64 || sign <= 0 && f < - MaxFloat64;
    }

    std::tuple<double, int> normalize(double x)
    {
        double y;
        int exp;
        auto SmallestNormal = 2.2250738585072014e-308;
        if(Abs(x) < SmallestNormal)
        {
            double y;
            int exp;
            return {x * (1 << 52), - 52};
        }
        return {x, 0};
    }

}

