// generated by GoCpp from file '$(ImportDir)/compress/flate/huffman_code.go'
#pragma once

#include <functional>
#include <string>
#include <tuple>
#include <vector>

#include "golang/compress/flate/huffman_code.fwd.h"
#include "gocpp/support.h"

#include "golang/compress/flate/inflate.h"
#include "golang/math/bits/bits.h"
#include "golang/math/const.h"
#include "golang/sort/sort.h"

namespace golang::flate
{
    struct hcode
    {
        uint16_t code;
        uint16_t len;

        using isGoStruct = void;

        std::ostream& PrintTo(std::ostream& os) const;
    };

    std::ostream& operator<<(std::ostream& os, const struct hcode& value);
    struct huffmanEncoder
    {
        gocpp::slice<hcode> codes;
        gocpp::slice<literalNode> freqcache;
        gocpp::array<int32_t, 17> bitCount;
        byLiteral lns;
        byFreq lfs;

        using isGoStruct = void;

        std::ostream& PrintTo(std::ostream& os) const;
    };

    std::ostream& operator<<(std::ostream& os, const struct huffmanEncoder& value);
    struct literalNode
    {
        uint16_t literal;
        int32_t freq;

        using isGoStruct = void;

        std::ostream& PrintTo(std::ostream& os) const;
    };

    std::ostream& operator<<(std::ostream& os, const struct literalNode& value);
    struct levelInfo
    {
        int32_t level;
        int32_t lastFreq;
        int32_t nextCharFreq;
        int32_t nextPairFreq;
        int32_t needed;

        using isGoStruct = void;

        std::ostream& PrintTo(std::ostream& os) const;
    };

    std::ostream& operator<<(std::ostream& os, const struct levelInfo& value);
    void set(struct hcode* h, uint16_t code, uint16_t length);
    literalNode maxNode();
    huffmanEncoder* newHuffmanEncoder(int size);
    huffmanEncoder* generateFixedLiteralEncoding();
    huffmanEncoder* generateFixedOffsetEncoding();
    int bitLength(struct huffmanEncoder* h, gocpp::slice<int32_t> freq);
    extern int maxBitsLimit;
    gocpp::slice<int32_t> bitCounts(struct huffmanEncoder* h, gocpp::slice<literalNode> list, int32_t maxBits);
    void assignEncodingAndSize(struct huffmanEncoder* h, gocpp::slice<int32_t> bitCount, gocpp::slice<literalNode> list);
    void generate(struct huffmanEncoder* h, gocpp::slice<int32_t> freq, int32_t maxBits);
    void sort(byLiteral* s, gocpp::slice<literalNode> a);
    int Len(byLiteral s);
    bool Less(byLiteral s, int i, int j);
    void Swap(byLiteral s, int i, int j);
    void sort(byFreq* s, gocpp::slice<literalNode> a);
    int Len(byFreq s);
    bool Less(byFreq s, int i, int j);
    void Swap(byFreq s, int i, int j);
    uint16_t reverseBits(uint16_t number, unsigned char bitLength);
}
