// generated by GoCpp from file '$(ImportDir)/strings/reader.go'
#pragma once

#include <functional>
#include <string>
#include <tuple>
#include <vector>

#include "golang/strings/reader.fwd.h"
#include "gocpp/support.h"

#include "golang/io/io.h"

namespace golang::strings
{
    struct Reader
    {
        std::string s;
        int64_t i;
        int prevRune;

        using isGoStruct = void;

        template<typename T> requires gocpp::GoStruct<T>
        operator T();

        template<typename T> requires gocpp::GoStruct<T>
        bool operator==(const T& ref) const;

        std::ostream& PrintTo(std::ostream& os) const;
    };

    std::ostream& operator<<(std::ostream& os, const struct Reader& value);
    struct Reader* NewReader(std::string s);

    namespace rec
    {
        int Len(struct Reader* r);
        int64_t Size(struct Reader* r);
        std::tuple<int, struct gocpp::error> Read(struct Reader* r, gocpp::slice<unsigned char> b);
        std::tuple<int, struct gocpp::error> ReadAt(struct Reader* r, gocpp::slice<unsigned char> b, int64_t off);
        std::tuple<unsigned char, struct gocpp::error> ReadByte(struct Reader* r);
        struct gocpp::error UnreadByte(struct Reader* r);
        std::tuple<gocpp::rune, int, struct gocpp::error> ReadRune(struct Reader* r);
        struct gocpp::error UnreadRune(struct Reader* r);
        std::tuple<int64_t, struct gocpp::error> Seek(struct Reader* r, int64_t offset, int whence);
        std::tuple<int64_t, struct gocpp::error> WriteTo(struct Reader* r, io::Writer w);
        void Reset(struct Reader* r, std::string s);
    }
}

