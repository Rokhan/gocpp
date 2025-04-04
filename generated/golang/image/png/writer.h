// generated by GoCpp from file '$(ImportDir)/image/png/writer.go'
#pragma once

#include <functional>
#include <string>
#include <tuple>
#include <vector>

#include "golang/image/png/writer.fwd.h"
#include "gocpp/support.h"

#include "golang/bufio/bufio.h"
#include "golang/compress/flate/deflate.h"
#include "golang/compress/flate/deflatefast.h"
#include "golang/compress/flate/huffman_bit_writer.h"
#include "golang/compress/flate/huffman_code.h"
#include "golang/compress/flate/token.h"
#include "golang/compress/zlib/writer.h"
#include "golang/hash/hash.h"
#include "golang/image/color/color.h"
#include "golang/image/geom.h"
#include "golang/image/image.h"
#include "golang/io/io.h"

namespace golang::png
{
    struct Encoder
    {
        CompressionLevel CompressionLevel;
        EncoderBufferPool BufferPool;

        using isGoStruct = void;

        template<typename T> requires gocpp::GoStruct<T>
        operator T();

        template<typename T> requires gocpp::GoStruct<T>
        bool operator==(const T& ref) const;

        std::ostream& PrintTo(std::ostream& os) const;
    };

    std::ostream& operator<<(std::ostream& os, const struct Encoder& value);
    struct EncoderBufferPool : gocpp::Interface
    {
        EncoderBufferPool(){}
        EncoderBufferPool(EncoderBufferPool& i) = default;
        EncoderBufferPool(const EncoderBufferPool& i) = default;
        EncoderBufferPool& operator=(EncoderBufferPool& i) = default;
        EncoderBufferPool& operator=(const EncoderBufferPool& i) = default;

        template<typename T>
        EncoderBufferPool(T& ref);

        template<typename T>
        EncoderBufferPool(const T& ref);

        template<typename T>
        EncoderBufferPool(T* ptr);

        using isGoInterface = void;

        std::ostream& PrintTo(std::ostream& os) const;

        struct IEncoderBufferPool
        {
            virtual EncoderBuffer* vGet() = 0;
            virtual void vPut(EncoderBuffer*) = 0;
        };

        template<typename T, typename StoreT>
        struct EncoderBufferPoolImpl : IEncoderBufferPool
        {
            explicit EncoderBufferPoolImpl(T* ptr)
            {
                value.reset(ptr);
            }

            EncoderBuffer* vGet() override;

            void vPut(EncoderBuffer*) override;

            StoreT value;
        };

        std::shared_ptr<IEncoderBufferPool> value;
    };

    EncoderBuffer* Get(const gocpp::PtrRecv<EncoderBufferPool, false>& self);
    EncoderBuffer* Get(const gocpp::ObjRecv<EncoderBufferPool>& self);

    void Put(const gocpp::PtrRecv<EncoderBufferPool, false>& self, EncoderBuffer*);
    void Put(const gocpp::ObjRecv<EncoderBufferPool>& self, EncoderBuffer*);

    std::ostream& operator<<(std::ostream& os, const struct EncoderBufferPool& value);
    struct encoder
    {
        Encoder* enc;
        io::Writer w;
        image::Image m;
        int cb;
        std::string err;
        gocpp::array<unsigned char, 8> header;
        gocpp::array<unsigned char, 4> footer;
        gocpp::array<unsigned char, 4 * 256> tmp;
        gocpp::array<gocpp::slice<uint8_t>, nFilter> cr;
        gocpp::slice<uint8_t> pr;
        zlib::Writer* zw;
        int zwLevel;
        bufio::Writer* bw;

        using isGoStruct = void;

        template<typename T> requires gocpp::GoStruct<T>
        operator T();

        template<typename T> requires gocpp::GoStruct<T>
        bool operator==(const T& ref) const;

        std::ostream& PrintTo(std::ostream& os) const;
    };

    std::ostream& operator<<(std::ostream& os, const struct encoder& value);
    struct opaquer : gocpp::Interface
    {
        opaquer(){}
        opaquer(opaquer& i) = default;
        opaquer(const opaquer& i) = default;
        opaquer& operator=(opaquer& i) = default;
        opaquer& operator=(const opaquer& i) = default;

        template<typename T>
        opaquer(T& ref);

        template<typename T>
        opaquer(const T& ref);

        template<typename T>
        opaquer(T* ptr);

        using isGoInterface = void;

        std::ostream& PrintTo(std::ostream& os) const;

        struct Iopaquer
        {
            virtual bool vOpaque() = 0;
        };

        template<typename T, typename StoreT>
        struct opaquerImpl : Iopaquer
        {
            explicit opaquerImpl(T* ptr)
            {
                value.reset(ptr);
            }

            bool vOpaque() override;

            StoreT value;
        };

        std::shared_ptr<Iopaquer> value;
    };

    bool Opaque(const gocpp::PtrRecv<opaquer, false>& self);
    bool Opaque(const gocpp::ObjRecv<opaquer>& self);

    std::ostream& operator<<(std::ostream& os, const struct opaquer& value);
    bool opaque(image::Image m);
    int abs8(uint8_t d);
    void writeChunk(struct encoder* e, gocpp::slice<unsigned char> b, std::string name);
    void writeIHDR(struct encoder* e);
    void writePLTEAndTRNS(struct encoder* e, color::Palette p);
    std::tuple<int, std::string> Write(struct encoder* e, gocpp::slice<unsigned char> b);
    int filter(gocpp::array<gocpp::slice<unsigned char>, nFilter>* cr, gocpp::slice<unsigned char> pr, int bpp);
    void zeroMemory(gocpp::slice<uint8_t> v);
    std::string writeImage(struct encoder* e, io::Writer w, image::Image m, int cb, int level);
    void writeIDATs(struct encoder* e);
    int levelToZlib(CompressionLevel l);
    void writeIEND(struct encoder* e);
    std::string Encode(io::Writer w, image::Image m);
    std::string Encode(struct Encoder* enc, io::Writer w, image::Image m);
}

