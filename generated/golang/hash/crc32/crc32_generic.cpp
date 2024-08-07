// generated by GoCpp from file '$(ImportDir)/hash/crc32/crc32_generic.go'
#include <complex>
#include <functional>
#include <iostream>
#include <iomanip>
#include <map>
#include <string>
#include <tuple>
#include <vector>

#include "golang/hash/crc32/crc32_generic.h"
#include "gocpp/support.h"

#include "golang/hash/crc32/crc32.h"

namespace golang::crc32
{
    Table* simpleMakeTable(uint32_t poly)
    {
        auto t = go_new(Table);
        simplePopulateTable(poly, t);
        return t;
    }

    void simplePopulateTable(uint32_t poly, Table* t)
    {
        for(auto i = 0; i < 256; i++)
        {
            auto crc = uint32_t(i);
            for(auto j = 0; j < 8; j++)
            {
                if(crc & 1 == 1)
                {
                    crc = (crc >> 1) ^ poly;
                }
                else
                {
                    crc >>= 1;
                }
            }
            t[i] = crc;
        }
    }

    uint32_t simpleUpdate(uint32_t crc, Table* tab, gocpp::slice<unsigned char> p)
    {
        crc = ~ crc;
        for(auto [_, v] : p)
        {
            crc = tab[unsigned char(crc) ^ v] ^ (crc >> 8);
        }
        return ~ crc;
    }

    slicing8Table* slicingMakeTable(uint32_t poly)
    {
        auto t = go_new(slicing8Table);
        simplePopulateTable(poly, & t[0]);
        for(auto i = 0; i < 256; i++)
        {
            auto crc = t[0][i];
            for(auto j = 1; j < 8; j++)
            {
                crc = t[0][crc & 0xFF] ^ (crc >> 8);
                t[j][i] = crc;
            }
        }
        return t;
    }

    uint32_t slicingUpdate(uint32_t crc, slicing8Table* tab, gocpp::slice<unsigned char> p)
    {
        if(len(p) >= slicing8Cutoff)
        {
            crc = ~ crc;
            for(; len(p) > 8; )
            {
                crc ^= uint32_t(p[0]) | (uint32_t(p[1]) << 8) | (uint32_t(p[2]) << 16) | (uint32_t(p[3]) << 24);
                crc = tab[0][p[7]] ^ tab[1][p[6]] ^ tab[2][p[5]] ^ tab[3][p[4]] ^ tab[4][crc >> 24] ^ tab[5][(crc >> 16) & 0xFF] ^ tab[6][(crc >> 8) & 0xFF] ^ tab[7][crc & 0xFF];
                p = p.make_slice(8);
            }
            crc = ~ crc;
        }
        if(len(p) == 0)
        {
            return crc;
        }
        return simpleUpdate(crc, & tab[0], p);
    }

}

