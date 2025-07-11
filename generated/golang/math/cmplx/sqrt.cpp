// generated by GoCpp from file '$(ImportDir)/math/cmplx/sqrt.go'
#include <complex>
#include <functional>
#include <iostream>
#include <iomanip>
#include <map>
#include <string>
#include <tuple>
#include <vector>

#include "golang/math/cmplx/sqrt.h"
#include "gocpp/support.h"

#include "golang/math/abs.h"
#include "golang/math/bits.h"
#include "golang/math/copysign.h"
#include "golang/math/hypot.h"
#include "golang/math/sqrt.h"

namespace golang::cmplx
{
    namespace rec
    {
        using namespace mocklib::rec;
    }

    // Sqrt returns the square root of x.
    // The result r is chosen so that real(r) ≥ 0 and imag(r) has the same sign as imag(x).
    struct gocpp::complex128 Sqrt(struct gocpp::complex128 x)
    {
        if(imag(x) == 0)
        {
            if(real(x) == 0)
            {
                return complex(0, imag(x));
            }
            if(real(x) < 0)
            {
                return complex(0, math::Copysign(std::sqrt(- real(x)), imag(x)));
            }
            return complex(std::sqrt(real(x)), imag(x));
        }
        else
        if(math::IsInf(imag(x), 0))
        {
            return complex(math::Inf(1.0), imag(x));
        }
        if(real(x) == 0)
        {
            if(imag(x) < 0)
            {
                auto r = std::sqrt(- 0.5 * imag(x));
                return complex(r, - r);
            }
            auto r = std::sqrt(0.5 * imag(x));
            return complex(r, r);
        }
        auto a = real(x);
        auto b = imag(x);
        double scale = {};
        if(math::Abs(a) > 4 || math::Abs(b) > 4)
        {
            a *= 0.25;
            b *= 0.25;
            scale = 2;
        }
        else
        {
            a *= 1.8014398509481984e16;
            b *= 1.8014398509481984e16;
            scale = 7.450580596923828125e-9;
        }
        auto r = math::Hypot(a, b);
        double t = {};
        if(a > 0)
        {
            t = std::sqrt(0.5 * r + 0.5 * a);
            r = scale * math::Abs((0.5 * b) / t);
            t *= scale;
        }
        else
        {
            r = std::sqrt(0.5 * r - 0.5 * a);
            t = scale * math::Abs((0.5 * b) / r);
            r *= scale;
        }
        if(b < 0)
        {
            return complex(t, - r);
        }
        return complex(t, r);
    }

}

