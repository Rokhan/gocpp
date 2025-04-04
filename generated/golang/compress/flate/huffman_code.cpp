// generated by GoCpp from file '$(ImportDir)/compress/flate/huffman_code.go'
#include <complex>
#include <functional>
#include <iostream>
#include <iomanip>
#include <map>
#include <string>
#include <tuple>
#include <vector>

#include "golang/compress/flate/huffman_code.h"
#include "gocpp/support.h"

#include "golang/compress/flate/inflate.h"
#include "golang/math/bits/bits.h"
#include "golang/math/const.h"
#include "golang/sort/sort.h"

namespace golang::flate
{
    
    template<typename T> requires gocpp::GoStruct<T>
    hcode::operator T()
    {
        T result;
        result.code = this->code;
        result.len = this->len;
        return result;
    }

    template<typename T> requires gocpp::GoStruct<T>
    bool hcode::operator==(const T& ref) const
    {
        if (code != ref.code) return false;
        if (len != ref.len) return false;
        return true;
    }

    std::ostream& hcode::PrintTo(std::ostream& os) const
    {
        os << '{';
        os << "" << code;
        os << " " << len;
        os << '}';
        return os;
    }

    std::ostream& operator<<(std::ostream& os, const struct hcode& value)
    {
        return value.PrintTo(os);
    }

    
    template<typename T> requires gocpp::GoStruct<T>
    huffmanEncoder::operator T()
    {
        T result;
        result.codes = this->codes;
        result.freqcache = this->freqcache;
        result.bitCount = this->bitCount;
        result.lns = this->lns;
        result.lfs = this->lfs;
        return result;
    }

    template<typename T> requires gocpp::GoStruct<T>
    bool huffmanEncoder::operator==(const T& ref) const
    {
        if (codes != ref.codes) return false;
        if (freqcache != ref.freqcache) return false;
        if (bitCount != ref.bitCount) return false;
        if (lns != ref.lns) return false;
        if (lfs != ref.lfs) return false;
        return true;
    }

    std::ostream& huffmanEncoder::PrintTo(std::ostream& os) const
    {
        os << '{';
        os << "" << codes;
        os << " " << freqcache;
        os << " " << bitCount;
        os << " " << lns;
        os << " " << lfs;
        os << '}';
        return os;
    }

    std::ostream& operator<<(std::ostream& os, const struct huffmanEncoder& value)
    {
        return value.PrintTo(os);
    }

    
    template<typename T> requires gocpp::GoStruct<T>
    literalNode::operator T()
    {
        T result;
        result.literal = this->literal;
        result.freq = this->freq;
        return result;
    }

    template<typename T> requires gocpp::GoStruct<T>
    bool literalNode::operator==(const T& ref) const
    {
        if (literal != ref.literal) return false;
        if (freq != ref.freq) return false;
        return true;
    }

    std::ostream& literalNode::PrintTo(std::ostream& os) const
    {
        os << '{';
        os << "" << literal;
        os << " " << freq;
        os << '}';
        return os;
    }

    std::ostream& operator<<(std::ostream& os, const struct literalNode& value)
    {
        return value.PrintTo(os);
    }

    
    template<typename T> requires gocpp::GoStruct<T>
    levelInfo::operator T()
    {
        T result;
        result.level = this->level;
        result.lastFreq = this->lastFreq;
        result.nextCharFreq = this->nextCharFreq;
        result.nextPairFreq = this->nextPairFreq;
        result.needed = this->needed;
        return result;
    }

    template<typename T> requires gocpp::GoStruct<T>
    bool levelInfo::operator==(const T& ref) const
    {
        if (level != ref.level) return false;
        if (lastFreq != ref.lastFreq) return false;
        if (nextCharFreq != ref.nextCharFreq) return false;
        if (nextPairFreq != ref.nextPairFreq) return false;
        if (needed != ref.needed) return false;
        return true;
    }

    std::ostream& levelInfo::PrintTo(std::ostream& os) const
    {
        os << '{';
        os << "" << level;
        os << " " << lastFreq;
        os << " " << nextCharFreq;
        os << " " << nextPairFreq;
        os << " " << needed;
        os << '}';
        return os;
    }

    std::ostream& operator<<(std::ostream& os, const struct levelInfo& value)
    {
        return value.PrintTo(os);
    }

    void set(struct hcode* h, uint16_t code, uint16_t length)
    {
        h->len = length;
        h->code = code;
    }

    literalNode maxNode()
    {
        return literalNode {math::MaxUint16, math::MaxInt32};
    }

    huffmanEncoder* newHuffmanEncoder(int size)
    {
        return gocpp::InitPtr<huffmanEncoder>([](huffmanEncoder& x) { x.codes = gocpp::make(gocpp::Tag<gocpp::slice<hcode>>(), size); });
    }

    huffmanEncoder* generateFixedLiteralEncoding()
    {
        auto h = newHuffmanEncoder(maxNumLit);
        auto codes = h->codes;
        uint16_t ch = {};
        for(ch = 0; ch < maxNumLit; ch++)
        {
            uint16_t bits = {};
            uint16_t size = {};
            //Go switch emulation
            {
                int conditionId = -1;
                if(ch < 144) { conditionId = 0; }
                else if(ch < 256) { conditionId = 1; }
                else if(ch < 280) { conditionId = 2; }
                switch(conditionId)
                {
                    case 0:
                        bits = ch + 48;
                        size = 8;
                        break;
                    case 1:
                        bits = ch + 400 - 144;
                        size = 9;
                        break;
                    case 2:
                        bits = ch - 256;
                        size = 7;
                        break;
                    default:
                        bits = ch + 192 - 280;
                        size = 8;
                        break;
                }
            }
            codes[ch] = gocpp::Init<hcode>([](hcode& x) { x.code = reverseBits(bits, unsigned char(size)); x.len = size; });
        }
        return h;
    }

    huffmanEncoder* generateFixedOffsetEncoding()
    {
        auto h = newHuffmanEncoder(30);
        auto codes = h->codes;
        for(auto [ch, gocpp_ignored] : codes)
        {
            codes[ch] = gocpp::Init<hcode>([](hcode& x) { x.code = reverseBits(uint16_t(ch), 5); x.len = 5; });
        }
        return h;
    }

    huffmanEncoder* fixedLiteralEncoding = generateFixedLiteralEncoding();
    huffmanEncoder* fixedOffsetEncoding = generateFixedOffsetEncoding();
    int bitLength(struct huffmanEncoder* h, gocpp::slice<int32_t> freq)
    {
        int total = {};
        for(auto [i, f] : freq)
        {
            if(f != 0)
            {
                total += int(f) * int(h->codes[i].len);
            }
        }
        return total;
    }

    gocpp::slice<int32_t> bitCounts(struct huffmanEncoder* h, gocpp::slice<literalNode> list, int32_t maxBits)
    {
        if(maxBits >= maxBitsLimit)
        {
            gocpp::panic("flate: maxBits too large");
        }
        auto n = int32_t(len(list));
        list = list.make_slice(0, n + 1);
        list[n] = maxNode();
        if(maxBits > n - 1)
        {
            maxBits = n - 1;
        }
        gocpp::array<levelInfo, maxBitsLimit> levels = {};
        gocpp::array<gocpp::array<int32_t, maxBitsLimit>, maxBitsLimit> leafCounts = {};
        for(auto level = int32_t(1); level <= maxBits; level++)
        {
            levels[level] = gocpp::Init<levelInfo>([](levelInfo& x) { x.level = level; x.lastFreq = list[1].freq; x.nextCharFreq = list[2].freq; x.nextPairFreq = list[0].freq + list[1].freq; });
            leafCounts[level][level] = 2;
            if(level == 1)
            {
                levels[level].nextPairFreq = math::MaxInt32;
            }
        }
        levels[maxBits].needed = 2 * n - 4;
        auto level = maxBits;
        for(; ; )
        {
            auto l = & levels[level];
            if(l->nextPairFreq == math::MaxInt32 && l->nextCharFreq == math::MaxInt32)
            {
                l->needed = 0;
                levels[level + 1].nextPairFreq = math::MaxInt32;
                level++;
                continue;
            }
            auto prevFreq = l->lastFreq;
            if(l->nextCharFreq < l->nextPairFreq)
            {
                auto n = leafCounts[level][level] + 1;
                l->lastFreq = l->nextCharFreq;
                leafCounts[level][level] = n;
                l->nextCharFreq = list[n].freq;
            }
            else
            {
                l->lastFreq = l->nextPairFreq;
                copy(leafCounts[level].make_slice(0, level), leafCounts[level - 1].make_slice(0, level));
                levels[l->level - 1].needed = 2;
            }
            if(l->needed--; l->needed == 0)
            {
                if(l->level == maxBits)
                {
                    break;
                }
                levels[l->level + 1].nextPairFreq = prevFreq + l->lastFreq;
                level++;
            }
            else
            {
                for(; levels[level - 1].needed > 0; )
                {
                    level--;
                }
            }
        }
        if(leafCounts[maxBits][maxBits] != n)
        {
            gocpp::panic("leafCounts[maxBits][maxBits] != n");
        }
        auto bitCount = h->bitCount.make_slice(0, maxBits + 1);
        auto bits = 1;
        auto counts = & leafCounts[maxBits];
        for(auto level = maxBits; level > 0; level--)
        {
            bitCount[bits] = counts[level] - counts[level - 1];
            bits++;
        }
        return bitCount;
    }

    void assignEncodingAndSize(struct huffmanEncoder* h, gocpp::slice<int32_t> bitCount, gocpp::slice<literalNode> list)
    {
        auto code = uint16_t(0);
        for(auto [n, bits] : bitCount)
        {
            code <<= 1;
            if(n == 0 || bits == 0)
            {
                continue;
            }
            auto chunk = list.make_slice(len(list) - int(bits));
            sort(gocpp::recv(h->lns), chunk);
            for(auto [_, node] : chunk)
            {
                h->codes[node.literal] = gocpp::Init<hcode>([](hcode& x) { x.code = reverseBits(code, uint8_t(n)); x.len = uint16_t(n); });
                code++;
            }
            list = list.make_slice(0, len(list) - int(bits));
        }
    }

    void generate(struct huffmanEncoder* h, gocpp::slice<int32_t> freq, int32_t maxBits)
    {
        if(h->freqcache == nullptr)
        {
            h->freqcache = gocpp::make(gocpp::Tag<gocpp::slice<literalNode>>(), maxNumLit + 1);
        }
        auto list = h->freqcache.make_slice(0, len(freq) + 1);
        auto count = 0;
        for(auto [i, f] : freq)
        {
            if(f != 0)
            {
                list[count] = literalNode {uint16_t(i), f};
                count++;
            }
            else
            {
                h->codes[i].len = 0;
            }
        }
        list = list.make_slice(0, count);
        if(count <= 2)
        {
            for(auto [i, node] : list)
            {
                set(gocpp::recv(h->codes[node.literal]), uint16_t(i), 1);
            }
            return;
        }
        sort(gocpp::recv(h->lfs), list);
        auto bitCount = bitCounts(gocpp::recv(h), list, maxBits);
        assignEncodingAndSize(gocpp::recv(h), bitCount, list);
    }

    void sort(byLiteral* s, gocpp::slice<literalNode> a)
    {
        *s = byLiteral(a);
        sort::Sort(s);
    }

    int Len(byLiteral s)
    {
        return len(s);
    }

    bool Less(byLiteral s, int i, int j)
    {
        return s[i].literal < s[j].literal;
    }

    void Swap(byLiteral s, int i, int j)
    {
        std::tie(s[i], s[j]) = std::tuple{s[j], s[i]};
    }

    void sort(byFreq* s, gocpp::slice<literalNode> a)
    {
        *s = byFreq(a);
        sort::Sort(s);
    }

    int Len(byFreq s)
    {
        return len(s);
    }

    bool Less(byFreq s, int i, int j)
    {
        if(s[i].freq == s[j].freq)
        {
            return s[i].literal < s[j].literal;
        }
        return s[i].freq < s[j].freq;
    }

    void Swap(byFreq s, int i, int j)
    {
        std::tie(s[i], s[j]) = std::tuple{s[j], s[i]};
    }

    uint16_t reverseBits(uint16_t number, unsigned char bitLength)
    {
        return bits::Reverse16(number << (16 - bitLength));
    }

}

