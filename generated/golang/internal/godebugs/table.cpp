// generated by GoCpp from file '$(ImportDir)/internal/godebugs/table.go'
#include <complex>
#include <functional>
#include <iostream>
#include <iomanip>
#include <map>
#include <string>
#include <tuple>
#include <vector>

#include "golang/internal/godebugs/table.h"
#include "gocpp/support.h"

namespace golang::godebugs
{
    
    template<typename T> requires gocpp::GoStruct<T>
    Info::operator T()
    {
        T result;
        result.Name = this->Name;
        result.Package = this->Package;
        result.Changed = this->Changed;
        result.Old = this->Old;
        result.Opaque = this->Opaque;
        return result;
    }

    template<typename T> requires gocpp::GoStruct<T>
    bool Info::operator==(const T& ref) const
    {
        if (Name != ref.Name) return false;
        if (Package != ref.Package) return false;
        if (Changed != ref.Changed) return false;
        if (Old != ref.Old) return false;
        if (Opaque != ref.Opaque) return false;
        return true;
    }

    std::ostream& Info::PrintTo(std::ostream& os) const
    {
        os << '{';
        os << "" << Name;
        os << " " << Package;
        os << " " << Changed;
        os << " " << Old;
        os << " " << Opaque;
        os << '}';
        return os;
    }

    std::ostream& operator<<(std::ostream& os, const struct Info& value)
    {
        return value.PrintTo(os);
    }

    gocpp::slice<Info> All = gocpp::slice<Info> {gocpp::Init<>([](& x) { x.Name = "execerrdot"; x.Package = "os/exec"; }), gocpp::Init<>([](& x) { x.Name = "gocachehash"; x.Package = "cmd/go"; }), gocpp::Init<>([](& x) { x.Name = "gocachetest"; x.Package = "cmd/go"; }), gocpp::Init<>([](& x) { x.Name = "gocacheverify"; x.Package = "cmd/go"; }), gocpp::Init<>([](& x) { x.Name = "gotypesalias"; x.Package = "go/types"; }), gocpp::Init<>([](& x) { x.Name = "http2client"; x.Package = "net/http"; }), gocpp::Init<>([](& x) { x.Name = "http2debug"; x.Package = "net/http"; x.Opaque = true; }), gocpp::Init<>([](& x) { x.Name = "http2server"; x.Package = "net/http"; }), gocpp::Init<>([](& x) { x.Name = "httplaxcontentlength"; x.Package = "net/http"; x.Changed = 22; x.Old = "1"; }), gocpp::Init<>([](& x) { x.Name = "httpmuxgo121"; x.Package = "net/http"; x.Changed = 22; x.Old = "1"; }), gocpp::Init<>([](& x) { x.Name = "installgoroot"; x.Package = "go/build"; }), gocpp::Init<>([](& x) { x.Name = "jstmpllitinterp"; x.Package = "html/template"; }), gocpp::Init<>([](& x) { x.Name = "multipartmaxheaders"; x.Package = "mime/multipart"; }), gocpp::Init<>([](& x) { x.Name = "multipartmaxparts"; x.Package = "mime/multipart"; }), gocpp::Init<>([](& x) { x.Name = "multipathtcp"; x.Package = "net"; }), gocpp::Init<>([](& x) { x.Name = "netdns"; x.Package = "net"; x.Opaque = true; }), gocpp::Init<>([](& x) { x.Name = "panicnil"; x.Package = "runtime"; x.Changed = 21; x.Old = "1"; }), gocpp::Init<>([](& x) { x.Name = "randautoseed"; x.Package = "math/rand"; }), gocpp::Init<>([](& x) { x.Name = "tarinsecurepath"; x.Package = "archive/tar"; }), gocpp::Init<>([](& x) { x.Name = "tls10server"; x.Package = "crypto/tls"; x.Changed = 22; x.Old = "1"; }), gocpp::Init<>([](& x) { x.Name = "tlsmaxrsasize"; x.Package = "crypto/tls"; }), gocpp::Init<>([](& x) { x.Name = "tlsrsakex"; x.Package = "crypto/tls"; x.Changed = 22; x.Old = "1"; }), gocpp::Init<>([](& x) { x.Name = "tlsunsafeekm"; x.Package = "crypto/tls"; x.Changed = 22; x.Old = "1"; }), gocpp::Init<>([](& x) { x.Name = "x509sha1"; x.Package = "crypto/x509"; }), gocpp::Init<>([](& x) { x.Name = "x509usefallbackroots"; x.Package = "crypto/x509"; }), gocpp::Init<>([](& x) { x.Name = "x509usepolicies"; x.Package = "crypto/x509"; }), gocpp::Init<>([](& x) { x.Name = "zipinsecurepath"; x.Package = "archive/zip"; })};
    Info* Lookup(std::string name)
    {
        auto lo = 0;
        auto hi = len(All);
        for(; lo < hi; )
        {
            auto m = int((unsigned int)(lo + hi) >> 1);
            auto mid = All[m].Name;
            if(name == mid)
            {
                return & All[m];
            }
            if(name < mid)
            {
                hi = m;
            }
            else
            {
                lo = m + 1;
            }
        }
        return nullptr;
    }

}

