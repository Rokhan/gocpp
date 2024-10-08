// generated by GoCpp from file '$(ImportDir)/compress/flate/deflate.go'
#pragma once

#include "gocpp/support.fwd.h"


namespace golang::flate
{
    const long NoCompression = 0;
    const long BestSpeed = 1;
    const long BestCompression = 9;
    const long DefaultCompression = - 1;
    const long HuffmanOnly = - 2;
    const long logWindowSize = 15;
    const long baseMatchLength = 3;
    const long minMatchLength = 4;
    const long maxMatchLength = 258;
    const long baseMatchOffset = 1;
    const int maxMatchOffset = 1 << 15;
    const int maxFlateBlockTokens = 1 << 14;
    const long maxStoreBlockSize = 65535;
    const long hashBits = 17;
    const int maxHashOffset = 1 << 24;
    struct compressionLevel;
    const long hashmul = 0x1e35a7bd;
    struct Writer;
    const int windowSize = 1 << logWindowSize;
    const int hashSize = 1 << hashBits;
    const int hashMask = (1 << hashBits) - 1;
}
#include "golang/compress/flate/deflatefast.fwd.h"
#include "golang/compress/flate/huffman_bit_writer.fwd.h"
#include "golang/compress/flate/token.fwd.h"
#include "golang/io/io.fwd.h"
#include "golang/math/const.fwd.h"

namespace golang::flate
{
    const int skipNever = math::MaxInt32;
    struct compressor;
    struct dictWriter;
    const int windowMask = windowSize - 1;
}
