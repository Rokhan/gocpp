// generated by GoCpp from file '$(ImportDir)/compress/zlib/reader.go'
#pragma once

#include <functional>
#include <string>
#include <tuple>
#include <vector>

#include "golang/compress/zlib/reader.fwd.h"
#include "gocpp/support.h"

#include "golang/bufio/bufio.h"
#include "golang/compress/flate/inflate.h"
#include "golang/encoding/binary/binary.h"
#include "golang/errors/errors.h"
#include "golang/hash/adler32/adler32.h"
#include "golang/hash/hash.h"
#include "golang/io/io.h"

namespace golang::zlib
{
    extern int zlibDeflate;
    extern int zlibMaxWindow;
    extern std::string ErrChecksum;
    extern std::string ErrDictionary;
    extern std::string ErrHeader;
    struct reader
    {
        flate::Reader r;
        io::ReadCloser decompressor;
        hash::Hash32 digest;
        std::string err;
        gocpp::array<unsigned char, 4> scratch;

        using isGoStruct = void;

        std::ostream& PrintTo(std::ostream& os) const;
    };

    std::ostream& operator<<(std::ostream& os, const reader& value);
    struct Resetter : gocpp::Interface
    {
        Resetter(){}
        Resetter(Resetter& i) = default;
        Resetter(const Resetter& i) = default;
        Resetter& operator=(Resetter& i) = default;
        Resetter& operator=(const Resetter& i) = default;

        template<typename T>
        Resetter(T& ref);

        template<typename T>
        Resetter(const T& ref);

        template<typename T>
        Resetter(T* ptr);

        using isGoStruct = void;

        std::ostream& PrintTo(std::ostream& os) const;

        struct IResetter
        {
            virtual std::string vReset(io::Reader r, gocpp::slice<unsigned char> dict) = 0;
        };

        template<typename T, typename StoreT>
        struct ResetterImpl : IResetter
        {
            explicit ResetterImpl(T* ptr)
            {
                value.reset(ptr);
            }

            std::string vReset(io::Reader r, gocpp::slice<unsigned char> dict) override;

            StoreT value;
        };

        std::shared_ptr<IResetter> value;
    };

    std::string Reset(const gocpp::PtrRecv<Resetter, false>& self, io::Reader r, gocpp::slice<unsigned char> dict);
    std::string Reset(const gocpp::ObjRecv<Resetter>& self, io::Reader r, gocpp::slice<unsigned char> dict);

    std::ostream& operator<<(std::ostream& os, const Resetter& value);
    std::tuple<io::ReadCloser, std::string> NewReader(io::Reader r);
    std::tuple<io::ReadCloser, std::string> NewReaderDict(io::Reader r, gocpp::slice<unsigned char> dict);
    std::tuple<int, std::string> Read(reader* z, gocpp::slice<unsigned char> p);
    std::string Close(reader* z);
    std::string Reset(reader* z, io::Reader r, gocpp::slice<unsigned char> dict);
}
