#pragma once
#include <cstdint>
#include <type_traits>

namespace gocpp
{
    // Defined in support.h (calls gocpp::panic). Never reached in a valid Go program,
    // and makes constant evaluation fail if it is.
    [[noreturn]] void bigint_error(const char* message);

    // Go untyped integer constant: 256 bits, two's complement, little-endian 32-bit limbs.
    // Overflow past 256 bits wraps silently, which Go rejects at compile time anyway.
    struct bigint
    {
        static constexpr int limbs = 8;
        uint32_t w[limbs] = {};

        constexpr bigint() = default;

        template<typename T> requires std::is_integral_v<T>
        constexpr explicit bigint(T v)
        {
            uint64_t u = static_cast<uint64_t>(v);          // modular: sign-extends negatives
            bool neg = false;
            if constexpr (std::is_signed_v<T>) { neg = v < 0; }
            w[0] = static_cast<uint32_t>(u);
            w[1] = static_cast<uint32_t>(u >> 32);
            for(int i = 2; i < limbs; ++i) { w[i] = neg ? 0xFFFFFFFFu : 0u; }
        }

        constexpr bool is_negative() const { return (w[limbs - 1] >> 31) != 0; }

        constexpr bool is_zero() const
        {
            for(int i = 0; i < limbs; ++i) { if(w[i] != 0) return false; }
            return true;
        }

        constexpr uint64_t low64() const { return w[0] | (static_cast<uint64_t>(w[1]) << 32); }

        // ---- conversions: implicit, like Go's constant conversion in `var x int = <const>` ----
        // Integer targets keep the low bits (Go has already checked the value fits).
        template<typename T> requires (std::is_integral_v<T> && !std::is_same_v<T, bool>)
        constexpr operator T() const { return static_cast<T>(low64()); }

        // Rounding is approximate for values above 2^53, which is fine for float constants.
        template<typename T> requires std::is_floating_point_v<T>
        constexpr operator T() const
        {
            bool neg = is_negative();
            bigint m = neg ? -*this : *this;                // magnitude, 2^255 stays correct as unsigned
            T r = 0;
            for(int i = limbs - 1; i >= 0; --i) { r = r * static_cast<T>(4294967296.0) + static_cast<T>(m.w[i]); }
            return neg ? -r : r;
        }

        // ---- unsigned helpers ----
        static constexpr bool ult(const bigint& a, const bigint& b)
        {
            for(int i = limbs - 1; i >= 0; --i)
            {
                if(a.w[i] != b.w[i]) return a.w[i] < b.w[i];
            }
            return false;
        }

        // shift count clamped to 256
        constexpr unsigned count256() const
        {
            if(is_negative()) bigint_error("negative shift count");
            for(int i = 1; i < limbs; ++i) { if(w[i] != 0) return 256; }
            return w[0] > 256 ? 256u : w[0];
        }

        // ---- arithmetic ----
        friend constexpr bigint operator~(const bigint& a)
        {
            bigint r;
            for(int i = 0; i < limbs; ++i) { r.w[i] = ~a.w[i]; }
            return r;
        }

        friend constexpr bigint operator+(const bigint& a, const bigint& b)
        {
            bigint r;
            uint64_t carry = 0;
            for(int i = 0; i < limbs; ++i)
            {
                uint64_t s = static_cast<uint64_t>(a.w[i]) + b.w[i] + carry;
                r.w[i] = static_cast<uint32_t>(s);
                carry = s >> 32;
            }
            return r;
        }

        friend constexpr bigint operator+(const bigint& a) { return a; }
        friend constexpr bigint operator-(const bigint& a) { return ~a + bigint(1); }
        friend constexpr bigint operator-(const bigint& a, const bigint& b) { return a + (-b); }

        // Modular product: identical bits for signed and unsigned operands.
        friend constexpr bigint operator*(const bigint& a, const bigint& b)
        {
            bigint r;
            for(int i = 0; i < limbs; ++i)
            {
                uint64_t carry = 0;
                for(int j = 0; i + j < limbs; ++j)
                {
                    uint64_t t = static_cast<uint64_t>(a.w[i]) * b.w[j] + r.w[i + j] + carry;  // < 2^64
                    r.w[i + j] = static_cast<uint32_t>(t);
                    carry = t >> 32;
                }
            }
            return r;
        }

        // Go division truncates toward zero, and the remainder has the sign of the dividend.
        static constexpr void divmod(const bigint& a, const bigint& b, bigint& q, bigint& r)
        {
            if(b.is_zero()) bigint_error("division by zero");
            bool na = a.is_negative(), nb = b.is_negative();
            bigint n = na ? -a : a;
            bigint d = nb ? -b : b;
            q = bigint();
            r = bigint();
            // shift-and-subtract, |d| <= 2^255 so r<<1 fits
            for(int i = limbs * 32 - 1; i >= 0; --i)
            {
                r = r.shl_bits(1);
                r.w[0] |= (n.w[i / 32] >> (i % 32)) & 1u;
                if(!ult(r, d))
                {
                    r = r - d;
                    q.w[i / 32] |= 1u << (i % 32);
                }
            }
            if(na != nb) q = -q;
            if(na) r = -r;
        }

        friend constexpr bigint operator/(const bigint& a, const bigint& b)
        {
            bigint q, r;
            divmod(a, b, q, r);
            return q;
        }

        friend constexpr bigint operator%(const bigint& a, const bigint& b)
        {
            bigint q, r;
            divmod(a, b, q, r);
            return r;
        }

        // ---- bitwise ----
        friend constexpr bigint operator&(const bigint& a, const bigint& b)
        { bigint r; for(int i = 0; i < limbs; ++i) { r.w[i] = a.w[i] & b.w[i]; } return r; }
        friend constexpr bigint operator|(const bigint& a, const bigint& b)
        { bigint r; for(int i = 0; i < limbs; ++i) { r.w[i] = a.w[i] | b.w[i]; } return r; }
        friend constexpr bigint operator^(const bigint& a, const bigint& b)
        { bigint r; for(int i = 0; i < limbs; ++i) { r.w[i] = a.w[i] ^ b.w[i]; } return r; }

        // Go's &^ has no C++ spelling.
        friend constexpr bigint and_not(const bigint& a, const bigint& b) { return a & ~b; }

        constexpr bigint shl_bits(unsigned c) const
        {
            if(c >= 256) return bigint();
            unsigned limb = c / 32, bit = c % 32;
            bigint r;
            for(int i = limbs - 1; i >= 0; --i)
            {
                int src = i - static_cast<int>(limb);
                uint32_t v = src >= 0 ? (w[src] << bit) : 0u;
                if(bit != 0 && src - 1 >= 0) v |= w[src - 1] >> (32 - bit);
                r.w[i] = v;
            }
            return r;
        }

        // Arithmetic shift: fills with the sign bit.
        constexpr bigint shr_bits(unsigned c) const
        {
            uint32_t fill = is_negative() ? 0xFFFFFFFFu : 0u;
            bigint r;
            if(c >= 256) { for(int i = 0; i < limbs; ++i) { r.w[i] = fill; } return r; }
            unsigned limb = c / 32, bit = c % 32;
            for(int i = 0; i < limbs; ++i)
            {
                unsigned src = i + limb;
                uint32_t lo = src < limbs ? w[src] : fill;
                uint32_t hi = src + 1 < limbs ? w[src + 1] : fill;
                r.w[i] = bit != 0 ? ((lo >> bit) | (hi << (32 - bit))) : lo;
            }
            return r;
        }

        friend constexpr bigint operator<<(const bigint& a, const bigint& n) { return a.shl_bits(n.count256()); }
        friend constexpr bigint operator>>(const bigint& a, const bigint& n) { return a.shr_bits(n.count256()); }

        // ---- comparisons (no <compare> needed) ----
        friend constexpr bool operator==(const bigint& a, const bigint& b)
        {
            for(int i = 0; i < limbs; ++i) { if(a.w[i] != b.w[i]) return false; }
            return true;
        }
        friend constexpr bool operator!=(const bigint& a, const bigint& b) { return !(a == b); }
        friend constexpr bool operator<(const bigint& a, const bigint& b)
        {
            if(a.is_negative() != b.is_negative()) return a.is_negative();
            return ult(a, b);                                // same sign: unsigned order matches
        }
        friend constexpr bool operator>(const bigint& a, const bigint& b) { return b < a; }
        friend constexpr bool operator<=(const bigint& a, const bigint& b) { return !(b < a); }
        friend constexpr bool operator>=(const bigint& a, const bigint& b) { return !(a < b); }

        template<typename N> requires std::is_integral_v<N>
        friend constexpr bigint operator<<(const bigint& a, N n)
        {
            if constexpr(std::is_signed_v<N>) { if(n < 0) bigint_error("negative shift count"); }
            return a.shl_bits(n >= 256 ? 256u : static_cast<unsigned>(n));
        }
        template<typename N> requires std::is_integral_v<N>
        friend constexpr bigint operator>>(const bigint& a, N n)
        {
            if constexpr(std::is_signed_v<N>) { if(n < 0) bigint_error("negative shift count"); }
            return a.shr_bits(n >= 256 ? 256u : static_cast<unsigned>(n));
        }
    };

    // Parses a Go integer literal: decimal, 0x, 0o, 0b, or legacy octal (0777).
    // Underscores and C++ digit separators are skipped.
    constexpr bigint parse_bigint(const char* s)
    {
        unsigned base = 10;
        if(s[0] == '0' && s[1] != 0)
        {
            char c = s[1];
            if(c == 'x' || c == 'X')      { base = 16; s += 2; }
            else if(c == 'o' || c == 'O') { base = 8;  s += 2; }
            else if(c == 'b' || c == 'B') { base = 2;  s += 2; }
            else                          { base = 8;  s += 1; }
        }
        bigint r;
        const bigint b(base);
        for(; *s != 0; ++s)
        {
            char c = *s;
            if(c == '_' || c == '\'') continue;
            unsigned d = (c >= '0' && c <= '9') ? static_cast<unsigned>(c - '0')
                                                : static_cast<unsigned>((c | 0x20) - 'a' + 10);
            r = r * b + bigint(d);
        }
        return r;
    }
}

namespace golang
{
    // Raw literal operator: no range check on the token, so values above 64 bits work.
    // Same namespace as operator""_s, so generated code finds both.
    constexpr gocpp::bigint operator""_bi(const char* s) { return gocpp::parse_bigint(s); }
}