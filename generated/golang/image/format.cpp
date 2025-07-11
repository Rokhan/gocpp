// generated by GoCpp from file '$(ImportDir)/image/format.go'
#include <complex>
#include <functional>
#include <iostream>
#include <iomanip>
#include <map>
#include <string>
#include <tuple>
#include <vector>

#include "golang/image/format.h"
#include "gocpp/support.h"

#include "golang/bufio/bufio.h"
#include "golang/errors/errors.h"
#include "golang/image/color/color.h"
#include "golang/image/geom.h"
#include "golang/image/image.h"
#include "golang/io/io.h"
#include "golang/sync/atomic/value.h"
#include "golang/sync/mutex.h"

namespace golang::image
{
    namespace rec
    {
        using namespace mocklib::rec;
        using atomic::rec::Load;
        using atomic::rec::Store;
        using mocklib::rec::Lock;
        using mocklib::rec::Unlock;
    }

    // ErrFormat indicates that decoding encountered an unknown format.
    gocpp::error ErrFormat = errors::New("image: unknown format"s);
    // A format holds an image format's name, magic header and how to decode it.
    
    template<typename T> requires gocpp::GoStruct<T>
    format::operator T()
    {
        T result;
        result.name = this->name;
        result.magic = this->magic;
        result.decode = this->decode;
        result.decodeConfig = this->decodeConfig;
        return result;
    }

    template<typename T> requires gocpp::GoStruct<T>
    bool format::operator==(const T& ref) const
    {
        if (name != ref.name) return false;
        if (magic != ref.magic) return false;
        if (decode != ref.decode) return false;
        if (decodeConfig != ref.decodeConfig) return false;
        return true;
    }

    std::ostream& format::PrintTo(std::ostream& os) const
    {
        os << '{';
        os << "" << name;
        os << " " << magic;
        os << " " << decode;
        os << " " << decodeConfig;
        os << '}';
        return os;
    }

    std::ostream& operator<<(std::ostream& os, const struct format& value)
    {
        return value.PrintTo(os);
    }

    // Formats is the list of registered formats.
    mocklib::Mutex formatsMu;
    atomic::Value atomicFormats;
    // RegisterFormat registers an image format for use by [Decode].
    // Name is the name of the format, like "jpeg" or "png".
    // Magic is the magic prefix that identifies the format's encoding. The magic
    // string can contain "?" wildcards that each match any one byte.
    // [Decode] is the function that decodes the encoded image.
    // [DecodeConfig] is the function that decodes just its configuration.
    void RegisterFormat(std::string name, std::string magic, std::function<std::tuple<struct Image, struct gocpp::error> (io::Reader _1)> decode, std::function<std::tuple<struct Config, struct gocpp::error> (io::Reader _1)> decodeConfig)
    {
        rec::Lock(gocpp::recv(formatsMu));
        auto [formats, gocpp_id_0] = gocpp::getValue<gocpp::slice<format>>(rec::Load(gocpp::recv(atomicFormats)));
        rec::Store(gocpp::recv(atomicFormats), append(formats, format {name, magic, decode, decodeConfig}));
        rec::Unlock(gocpp::recv(formatsMu));
    }

    // A reader is an io.Reader that can also peek ahead.
    
    template<typename T>
    reader::reader(T& ref)
    {
        value.reset(new readerImpl<T, std::unique_ptr<T>>(new T(ref)));
    }

    template<typename T>
    reader::reader(const T& ref)
    {
        value.reset(new readerImpl<T, std::unique_ptr<T>>(new T(ref)));
    }

    template<typename T>
    reader::reader(T* ptr)
    {
        value.reset(new readerImpl<T, gocpp::ptr<T>>(ptr));
    }

    std::ostream& reader::PrintTo(std::ostream& os) const
    {
        return os;
    }

    template<typename T, typename StoreT>
    std::tuple<gocpp::slice<unsigned char>, struct gocpp::error> reader::readerImpl<T, StoreT>::vPeek(int _1)
    {
        return rec::Peek(gocpp::PtrRecv<T, false>(value.get()), _1);
    }

    namespace rec
    {
        std::tuple<gocpp::slice<unsigned char>, struct gocpp::error> Peek(const gocpp::PtrRecv<struct reader, false>& self, int _1)
        {
            return self.ptr->value->vPeek(_1);
        }

        std::tuple<gocpp::slice<unsigned char>, struct gocpp::error> Peek(const gocpp::ObjRecv<struct reader>& self, int _1)
        {
            return self.obj.value->vPeek(_1);
        }
    }

    std::ostream& operator<<(std::ostream& os, const struct reader& value)
    {
        return value.PrintTo(os);
    }

    // asReader converts an io.Reader to a reader.
    struct reader asReader(io::Reader r)
    {
        if(auto [rr, ok] = gocpp::getValue<reader>(r); ok)
        {
            return rr;
        }
        return bufio::NewReader(r);
    }

    // match reports whether magic matches b. Magic may contain "?" wildcards.
    bool match(std::string magic, gocpp::slice<unsigned char> b)
    {
        if(len(magic) != len(b))
        {
            return false;
        }
        for(auto [i, c] : b)
        {
            if(magic[i] != c && magic[i] != '?')
            {
                return false;
            }
        }
        return true;
    }

    // sniff determines the format of r's data.
    struct format sniff(struct reader r)
    {
        auto [formats, gocpp_id_1] = gocpp::getValue<gocpp::slice<format>>(rec::Load(gocpp::recv(atomicFormats)));
        for(auto [gocpp_ignored, f] : formats)
        {
            auto [b, err] = rec::Peek(gocpp::recv(r), len(f.magic));
            if(err == nullptr && match(f.magic, b))
            {
                return f;
            }
        }
        return format {};
    }

    // Decode decodes an image that has been encoded in a registered format.
    // The string returned is the format name used during format registration.
    // Format registration is typically done by an init function in the codec-
    // specific package.
    std::tuple<struct Image, std::string, struct gocpp::error> Decode(io::Reader r)
    {
        auto rr = asReader(r);
        auto f = sniff(rr);
        if(f.decode == nullptr)
        {
            return {nullptr, ""s, ErrFormat};
        }
        auto [m, err] = rec::decode(gocpp::recv(f), rr);
        return {m, f.name, err};
    }

    // DecodeConfig decodes the color model and dimensions of an image that has
    // been encoded in a registered format. The string returned is the format name
    // used during format registration. Format registration is typically done by
    // an init function in the codec-specific package.
    std::tuple<struct Config, std::string, struct gocpp::error> DecodeConfig(io::Reader r)
    {
        auto rr = asReader(r);
        auto f = sniff(rr);
        if(f.decodeConfig == nullptr)
        {
            return {Config {}, ""s, ErrFormat};
        }
        auto [c, err] = rec::decodeConfig(gocpp::recv(f), rr);
        return {c, f.name, err};
    }

}

