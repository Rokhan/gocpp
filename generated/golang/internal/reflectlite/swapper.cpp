// generated by GoCpp from file '$(ImportDir)/internal/reflectlite/swapper.go'
#include <complex>
#include <functional>
#include <iostream>
#include <iomanip>
#include <map>
#include <string>
#include <tuple>
#include <vector>

#include "golang/internal/reflectlite/swapper.h"
#include "gocpp/support.h"

#include "golang/internal/abi/type.h"
#include "golang/internal/goarch/goarch.h"
#include "golang/internal/reflectlite/type.h"
#include "golang/internal/reflectlite/value.h"
#include "golang/internal/unsafeheader/unsafeheader.h"
#include "golang/unsafe/unsafe.h"

namespace golang::reflectlite
{
    namespace rec
    {
        using namespace mocklib::rec;
        using abi::rec::Kind;
        using abi::rec::Size;
    }

    // Swapper returns a function that swaps the elements in the provided
    // slice.
    //
    // Swapper panics if the provided interface is not a slice.
    std::function<void (int i, int j)> Swapper(go_any slice)
    {
        auto v = ValueOf(slice);
        if(rec::Kind(gocpp::recv(v)) != Slice)
        {
            gocpp::panic(gocpp::InitPtr<ValueError>([=](auto& x) {
                x.Method = "Swapper"s;
                x.Kind = rec::Kind(gocpp::recv(v));
            }));
        }
        //Go switch emulation
        {
            auto condition = rec::Len(gocpp::recv(v));
            int conditionId = -1;
            if(condition == 0) { conditionId = 0; }
            else if(condition == 1) { conditionId = 1; }
            switch(conditionId)
            {
                case 0:
                    return [=](int i, int j) mutable -> void
                    {
                        gocpp::panic("reflect: slice index out of range"s);
                    };
                    break;
                case 1:
                    return [=](int i, int j) mutable -> void
                    {
                        if(i != 0 || j != 0)
                        {
                            gocpp::panic("reflect: slice index out of range"s);
                        }
                    };
                    break;
            }
        }
        auto typ = rec::common(gocpp::recv(rec::Elem(gocpp::recv(rec::Type(gocpp::recv(v))))));
        auto size = rec::Size(gocpp::recv(typ));
        auto hasPtr = typ->PtrBytes != 0;
        if(hasPtr)
        {
            if(size == goarch::PtrSize)
            {
                auto ps = *(gocpp::slice<unsafe::Pointer>*)(v.ptr);
                return [=](int i, int j) mutable -> void
                {
                    std::tie(ps[i], ps[j]) = std::tuple{ps[j], ps[i]};
                };
            }
            if(rec::Kind(gocpp::recv(typ)) == String)
            {
                auto ss = *(gocpp::slice<std::string>*)(v.ptr);
                return [=](int i, int j) mutable -> void
                {
                    std::tie(ss[i], ss[j]) = std::tuple{ss[j], ss[i]};
                };
            }
        }
        else
        {
            //Go switch emulation
            {
                auto condition = size;
                int conditionId = -1;
                if(condition == 8) { conditionId = 0; }
                else if(condition == 4) { conditionId = 1; }
                else if(condition == 2) { conditionId = 2; }
                else if(condition == 1) { conditionId = 3; }
                switch(conditionId)
                {
                    case 0:
                        auto is = *(gocpp::slice<int64_t>*)(v.ptr);
                        return [=](int i, int j) mutable -> void
                        {
                            std::tie(is[i], is[j]) = std::tuple{is[j], is[i]};
                        };
                        break;
                    case 1:
                        auto is = *(gocpp::slice<int32_t>*)(v.ptr);
                        return [=](int i, int j) mutable -> void
                        {
                            std::tie(is[i], is[j]) = std::tuple{is[j], is[i]};
                        };
                        break;
                    case 2:
                        auto is = *(gocpp::slice<int16_t>*)(v.ptr);
                        return [=](int i, int j) mutable -> void
                        {
                            std::tie(is[i], is[j]) = std::tuple{is[j], is[i]};
                        };
                        break;
                    case 3:
                        auto is = *(gocpp::slice<int8_t>*)(v.ptr);
                        return [=](int i, int j) mutable -> void
                        {
                            std::tie(is[i], is[j]) = std::tuple{is[j], is[i]};
                        };
                        break;
                }
            }
        }
        auto s = (unsafeheader::Slice*)(v.ptr);
        auto tmp = unsafe_New(typ);
        return [=](int i, int j) mutable -> void
        {
            if((unsigned int)(i) >= (unsigned int)(s->Len) || (unsigned int)(j) >= (unsigned int)(s->Len))
            {
                gocpp::panic("reflect: slice index out of range"s);
            }
            auto val1 = arrayAt(s->Data, i, size, "i < s.Len"s);
            auto val2 = arrayAt(s->Data, j, size, "j < s.Len"s);
            typedmemmove(typ, tmp, val1);
            typedmemmove(typ, val1, val2);
            typedmemmove(typ, val2, tmp);
        };
    }

}

