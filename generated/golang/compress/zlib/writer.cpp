// generated by GoCpp from file '$(ImportDir)/compress/zlib/writer.go'
#include <complex>
#include <functional>
#include <iostream>
#include <iomanip>
#include <map>
#include <string>
#include <tuple>
#include <vector>

#include "golang/compress/zlib/writer.h"
#include "gocpp/support.h"

#include "golang/compress/flate/deflate.h"
#include "golang/encoding/binary/binary.h"
#include "golang/fmt/errors.h"
#include "golang/hash/adler32/adler32.h"
#include "golang/hash/hash.h"
#include "golang/io/io.h"

namespace golang::zlib
{
    int NoCompression = flate.NoCompression;
    int BestSpeed = flate.BestSpeed;
    int BestCompression = flate.BestCompression;
    int DefaultCompression = flate.DefaultCompression;
    int HuffmanOnly = flate.HuffmanOnly;
    
    std::ostream& Writer::PrintTo(std::ostream& os) const
    {
        os << '{';
        os << "" << w;
        os << " " << level;
        os << " " << dict;
        os << " " << compressor;
        os << " " << digest;
        os << " " << err;
        os << " " << scratch;
        os << " " << wroteHeader;
        os << '}';
        return os;
    }

    std::ostream& operator<<(std::ostream& os, const Writer& value)
    {
        return value.PrintTo(os);
    }

    Writer* NewWriter(io::Writer w)
    {
        auto [z, _] = NewWriterLevelDict(w, DefaultCompression, nullptr);
        return z;
    }

    std::tuple<Writer*, std::string> NewWriterLevel(io::Writer w, int level)
    {
        return NewWriterLevelDict(w, level, nullptr);
    }

    std::tuple<Writer*, std::string> NewWriterLevelDict(io::Writer w, int level, gocpp::slice<unsigned char> dict)
    {
        if(level < HuffmanOnly || level > BestCompression)
        {
            return {nullptr, fmt::Errorf("zlib: invalid compression level: %d", level)};
        }
        return {gocpp::InitPtr<Writer>([](Writer& x) { x.w = w; x.level = level; x.dict = dict; }), nullptr};
    }

    void Reset(Writer* z, io::Writer w)
    {
        z->w = w;
        if(z->compressor != nullptr)
        {
            Reset(gocpp::recv(z->compressor), w);
        }
        if(z->digest != nullptr)
        {
            Reset(gocpp::recv(z->digest));
        }
        z->err = nullptr;
        z->scratch = gocpp::array<unsigned char, 4> {};
        z->wroteHeader = false;
    }

    std::string writeHeader(Writer* z)
    {
        std::string err;
        z->wroteHeader = true;
        z->scratch[0] = 0x78;
        //Go switch emulation
        {
            auto condition = z->level;
            int conditionId = -1;
            if(condition == - 2) { conditionId = 0; }
            if(condition == 0) { conditionId = 1; }
            if(condition == 1) { conditionId = 2; }
            else if(condition == 2) { conditionId = 3; }
            else if(condition == 3) { conditionId = 4; }
            else if(condition == 4) { conditionId = 5; }
            else if(condition == 5) { conditionId = 6; }
            else if(condition == 6) { conditionId = 7; }
            else if(condition == - 1) { conditionId = 8; }
            else if(condition == 7) { conditionId = 9; }
            else if(condition == 8) { conditionId = 10; }
            else if(condition == 9) { conditionId = 11; }
            switch(conditionId)
            {
                std::string err;
                case 0:
                case 1:
                case 2:
                    z->scratch[1] = 0 << 6;
                    break;
                case 3:
                case 4:
                case 5:
                case 6:
                    z->scratch[1] = 1 << 6;
                    break;
                case 7:
                case 8:
                    z->scratch[1] = 2 << 6;
                    break;
                case 9:
                case 10:
                case 11:
                    z->scratch[1] = 3 << 6;
                    break;
                default:
                    gocpp::panic("unreachable");
                    break;
            }
        }
        if(z->dict != nullptr)
        {
            std::string err;
            z->scratch[1] |= 1 << 5;
        }
        z->scratch[1] += uint8_t(31 - Uint16(gocpp::recv(binary.BigEndian), z->scratch.make_slice(0, 2)) % 31);
        if(std::tie(_, err) = Write(gocpp::recv(z->w), z->scratch.make_slice(0, 2)); err != nullptr)
        {
            std::string err;
            return err;
        }
        if(z->dict != nullptr)
        {
            std::string err;
            PutUint32(gocpp::recv(binary.BigEndian), z->scratch.make_slice(0, ), Checksum(gocpp::recv(adler32), z->dict));
            if(std::tie(_, err) = Write(gocpp::recv(z->w), z->scratch.make_slice(0, 4)); err != nullptr)
            {
                std::string err;
                return err;
            }
        }
        if(z->compressor == nullptr)
        {
            std::string err;
            std::tie(z->compressor, err) = NewWriterDict(gocpp::recv(flate), z->w, z->level, z->dict);
            if(err != nullptr)
            {
                std::string err;
                return err;
            }
            z->digest = New(gocpp::recv(adler32));
        }
        return nullptr;
    }

    std::tuple<int, std::string> Write(Writer* z, gocpp::slice<unsigned char> p)
    {
        int n;
        std::string err;
        if(! z->wroteHeader)
        {
            int n;
            std::string err;
            z->err = writeHeader(gocpp::recv(z));
        }
        if(z->err != nullptr)
        {
            int n;
            std::string err;
            return {0, z->err};
        }
        if(len(p) == 0)
        {
            int n;
            std::string err;
            return {0, nullptr};
        }
        std::tie(n, err) = Write(gocpp::recv(z->compressor), p);
        if(err != nullptr)
        {
            int n;
            std::string err;
            z->err = err;
            return {n, err};
        }
        Write(gocpp::recv(z->digest), p);
        return {n, err};
    }

    std::string Flush(Writer* z)
    {
        if(! z->wroteHeader)
        {
            z->err = writeHeader(gocpp::recv(z));
        }
        if(z->err != nullptr)
        {
            return z->err;
        }
        z->err = Flush(gocpp::recv(z->compressor));
        return z->err;
    }

    std::string Close(Writer* z)
    {
        if(! z->wroteHeader)
        {
            z->err = writeHeader(gocpp::recv(z));
        }
        if(z->err != nullptr)
        {
            return z->err;
        }
        z->err = Close(gocpp::recv(z->compressor));
        if(z->err != nullptr)
        {
            return z->err;
        }
        auto checksum = Sum32(gocpp::recv(z->digest));
        PutUint32(gocpp::recv(binary.BigEndian), z->scratch.make_slice(0, ), checksum);
        std::tie(_, z->err) = Write(gocpp::recv(z->w), z->scratch.make_slice(0, 4));
        return z->err;
    }

}
