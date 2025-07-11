// generated by GoCpp from file '$(ImportDir)/compress/flate/huffman_code.go'
#pragma once

#include <functional>
#include <string>
#include <tuple>
#include <vector>

#include "golang/compress/flate/huffman_code.fwd.h"
#include "gocpp/support.h"


namespace golang::flate
{
    struct hcode
    {
        uint16_t code;
        uint16_t len;

        using isGoStruct = void;

        template<typename T> requires gocpp::GoStruct<T>
        operator T();

        template<typename T> requires gocpp::GoStruct<T>
        bool operator==(const T& ref) const;

        std::ostream& PrintTo(std::ostream& os) const;
    };

    std::ostream& operator<<(std::ostream& os, const struct hcode& value);
    struct literalNode
    {
        uint16_t literal;
        int32_t freq;

        using isGoStruct = void;

        template<typename T> requires gocpp::GoStruct<T>
        operator T();

        template<typename T> requires gocpp::GoStruct<T>
        bool operator==(const T& ref) const;

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

        template<typename T> requires gocpp::GoStruct<T>
        operator T();

        template<typename T> requires gocpp::GoStruct<T>
        bool operator==(const T& ref) const;

        std::ostream& PrintTo(std::ostream& os) const;
    };

    std::ostream& operator<<(std::ostream& os, const struct levelInfo& value);
    struct literalNode maxNode();
    struct huffmanEncoder* newHuffmanEncoder(int size);
    struct huffmanEncoder* generateFixedLiteralEncoding();
    struct huffmanEncoder* generateFixedOffsetEncoding();
    uint16_t reverseBits(uint16_t number, unsigned char bitLength);
    struct huffmanEncoder
    {
        gocpp::slice<hcode> codes;
        gocpp::slice<literalNode> freqcache;
        gocpp::array<int32_t, 17> bitCount;
        byLiteral lns;
        byFreq lfs;

        using isGoStruct = void;

        template<typename T> requires gocpp::GoStruct<T>
        operator T();

        template<typename T> requires gocpp::GoStruct<T>
        bool operator==(const T& ref) const;

        std::ostream& PrintTo(std::ostream& os) const;
    };

    std::ostream& operator<<(std::ostream& os, const struct huffmanEncoder& value);
    extern huffmanEncoder* fixedLiteralEncoding;
    extern huffmanEncoder* fixedOffsetEncoding;

    namespace rec
    {
        void set(struct hcode* h, uint16_t code, uint16_t length);
        int bitLength(struct huffmanEncoder* h, gocpp::slice<int32_t> freq);
        gocpp::slice<int32_t> bitCounts(struct huffmanEncoder* h, gocpp::slice<literalNode> list, int32_t maxBits);
        void assignEncodingAndSize(struct huffmanEncoder* h, gocpp::slice<int32_t> bitCount, gocpp::slice<literalNode> list);
        void generate(struct huffmanEncoder* h, gocpp::slice<int32_t> freq, int32_t maxBits);
        void sort(golang::flate::byLiteral* s, gocpp::slice<literalNode> a);
        int Len(golang::flate::byLiteral s);
        bool Less(golang::flate::byLiteral s, int i, int j);
        void Swap(golang::flate::byLiteral s, int i, int j);
        void sort(golang::flate::byFreq* s, gocpp::slice<literalNode> a);
        int Len(golang::flate::byFreq s);
        bool Less(golang::flate::byFreq s, int i, int j);
        void Swap(golang::flate::byFreq s, int i, int j);
    }
}

