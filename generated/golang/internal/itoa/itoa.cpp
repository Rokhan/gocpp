// generated by GoCpp from file '$(ImportDir)/internal/itoa/itoa.go'
#include <complex>
#include <functional>
#include <iostream>
#include <iomanip>
#include <map>
#include <string>
#include <tuple>
#include <vector>

#include "golang/internal/itoa/itoa.h"
#include "gocpp/support.h"

namespace golang::itoa
{
    namespace rec
    {
        using namespace mocklib::rec;
    }

    // Itoa converts val to a decimal string.
    std::string Itoa(int val)
    {
        if(val < 0)
        {
            return "-"s + Uitoa((unsigned int)(- val));
        }
        return Uitoa((unsigned int)(val));
    }

    // Uitoa converts val to a decimal string.
    std::string Uitoa(unsigned int val)
    {
        if(val == 0)
        {
            return "0"s;
        }
        gocpp::array<unsigned char, 20> buf = {};
        auto i = len(buf) - 1;
        for(; val >= 10; )
        {
            auto q = val / 10;
            buf[i] = (unsigned char)('0' + val - q * 10);
            i--;
            val = q;
        }
        buf[i] = (unsigned char)('0' + val);
        return std::string(buf.make_slice(i));
    }

    std::string hex = "0123456789abcdef"s;
    // Uitox converts val (a uint) to a hexadecimal string.
    std::string Uitox(unsigned int val)
    {
        if(val == 0)
        {
            return "0x0"s;
        }
        gocpp::array<unsigned char, 20> buf = {};
        auto i = len(buf) - 1;
        for(; val >= 16; )
        {
            auto q = val / 16;
            buf[i] = hex[val % 16];
            i--;
            val = q;
        }
        buf[i] = hex[val % 16];
        i--;
        buf[i] = 'x';
        i--;
        buf[i] = '0';
        return std::string(buf.make_slice(i));
    }

}

