// generated by GoCpp from file '$(ImportDir)/runtime/type.go'
#include <complex>
#include <functional>
#include <iostream>
#include <iomanip>
#include <map>
#include <string>
#include <tuple>
#include <vector>

#include "golang/runtime/type.h"
#include "gocpp/support.h"

#include "golang/internal/abi/funcpc.h"
#include "golang/internal/abi/type.h"
#include "golang/runtime/iface.h"
#include "golang/runtime/internal/sys/nih.h"
// #include "golang/runtime/lock_sema.h"  [Ignored, known errors]
// #include "golang/runtime/lockrank_off.h"  [Ignored, known errors]
#include "golang/runtime/panic.h"
#include "golang/runtime/plugin.h"
// #include "golang/runtime/print.h"  [Ignored, known errors]
#include "golang/runtime/proc.h"
#include "golang/runtime/race0.h"
#include "golang/runtime/runtime2.h"
#include "golang/runtime/stack.h"
// #include "golang/runtime/symtab.h"  [Ignored, known errors]
// #include "golang/runtime/typekind.h"  [Ignored, known errors]
#include "golang/unsafe/unsafe.h"

namespace golang::runtime
{
    
    template<typename T> requires gocpp::GoStruct<T>
    rtype::operator T()
    {
        T result;
        return result;
    }

    template<typename T> requires gocpp::GoStruct<T>
    bool rtype::operator==(const T& ref) const
    {
        return true;
    }

    std::ostream& rtype::PrintTo(std::ostream& os) const
    {
        os << '{';
        os << '}';
        return os;
    }

    std::ostream& operator<<(std::ostream& os, const struct rtype& value)
    {
        return value.PrintTo(os);
    }

    std::string string(struct rtype t)
    {
        auto s = Name(gocpp::recv(nameOff(gocpp::recv(t), t.Str)));
        if(t.TFlag & abi::TFlagExtraStar != 0)
        {
            return s.make_slice(1);
        }
        return s;
    }

    uncommontype* uncommon(struct rtype t)
    {
        return Uncommon(gocpp::recv(t));
    }

    std::string name(struct rtype t)
    {
        if(t.TFlag & abi::TFlagNamed == 0)
        {
            return "";
        }
        auto s = string(gocpp::recv(t));
        auto i = len(s) - 1;
        auto sqBrackets = 0;
        for(; i >= 0 && (s[i] != '.' || sqBrackets != 0); )
        {
            //Go switch emulation
            {
                auto condition = s[i];
                int conditionId = -1;
                if(condition == ']') { conditionId = 0; }
                else if(condition == '[') { conditionId = 1; }
                switch(conditionId)
                {
                    case 0:
                        sqBrackets++;
                        break;
                    case 1:
                        sqBrackets--;
                        break;
                }
            }
            i--;
        }
        return s.make_slice(i + 1);
    }

    std::string pkgpath(struct rtype t)
    {
        if(auto u = uncommon(gocpp::recv(t)); u != nullptr)
        {
            return Name(gocpp::recv(nameOff(gocpp::recv(t), u->PkgPath)));
        }
        //Go switch emulation
        {
            auto condition = t.Kind_ & kindMask;
            int conditionId = -1;
            if(condition == kindStruct) { conditionId = 0; }
            else if(condition == kindInterface) { conditionId = 1; }
            switch(conditionId)
            {
                case 0:
                    auto st = (structtype*)(unsafe::Pointer(t.Type));
                    return Name(gocpp::recv(st->PkgPath));
                    break;
                case 1:
                    auto it = (interfacetype*)(unsafe::Pointer(t.Type));
                    return Name(gocpp::recv(it->PkgPath));
                    break;
            }
        }
        return "";
    }

    struct gocpp_id_0
    {
        mutex lock;
        int32_t next;
        gocpp::map<int32_t, unsafe::Pointer> m;
        gocpp::map<unsafe::Pointer, int32_t> minv;

        using isGoStruct = void;

        template<typename T> requires gocpp::GoStruct<T>
        operator T()
        {
            T result;
            result.lock = this->lock;
            result.next = this->next;
            result.m = this->m;
            result.minv = this->minv;
            return result;
        }

        template<typename T> requires gocpp::GoStruct<T>
        bool operator==(const T& ref) const
        {
            if (lock != ref.lock) return false;
            if (next != ref.next) return false;
            if (m != ref.m) return false;
            if (minv != ref.minv) return false;
            return true;
        }

        std::ostream& PrintTo(std::ostream& os) const
        {
            os << '{';
            os << "" << lock;
            os << " " << next;
            os << " " << m;
            os << " " << minv;
            os << '}';
            return os;
        }
    };

    std::ostream& operator<<(std::ostream& os, const struct gocpp_id_0& value)
    {
        return value.PrintTo(os);
    }


    gocpp_id_0 reflectOffs;
    void reflectOffsLock()
    {
        lock(& reflectOffs.lock);
        if(raceenabled)
        {
            raceacquire(unsafe::Pointer(& reflectOffs.lock));
        }
    }

    void reflectOffsUnlock()
    {
        if(raceenabled)
        {
            racerelease(unsafe::Pointer(& reflectOffs.lock));
        }
        unlock(& reflectOffs.lock);
    }

    name resolveNameOff(unsafe::Pointer ptrInModule, nameOff off)
    {
        if(off == 0)
        {
            return name {};
        }
        auto base = uintptr_t(ptrInModule);
        for(auto md = & firstmoduledata; md != nullptr; md = md->next)
        {
            if(base >= md->types && base < md->etypes)
            {
                auto res = md->types + uintptr_t(off);
                if(res > md->etypes)
                {
                    println("runtime: nameOff", hex(off), "out of range", hex(md->types), "-", hex(md->etypes));
                    go_throw("runtime: name offset out of range");
                }
                return gocpp::Init<name>([](name& x) { x.Bytes = (unsigned char*)(unsafe::Pointer(res)); });
            }
        }
        reflectOffsLock();
        auto [res, found] = reflectOffs.m[int32_t(off)];
        reflectOffsUnlock();
        if(! found)
        {
            println("runtime: nameOff", hex(off), "base", hex(base), "not in ranges:");
            for(auto next = & firstmoduledata; next != nullptr; next = next->next)
            {
                println("\ttypes", hex(next->types), "etypes", hex(next->etypes));
            }
            go_throw("runtime: name offset base pointer out of range");
        }
        return gocpp::Init<name>([](name& x) { x.Bytes = (unsigned char*)(res); });
    }

    name nameOff(struct rtype t, nameOff off)
    {
        return resolveNameOff(unsafe::Pointer(t.Type), off);
    }

    _type* resolveTypeOff(unsafe::Pointer ptrInModule, typeOff off)
    {
        if(off == 0 || off == - 1)
        {
            return nullptr;
        }
        auto base = uintptr_t(ptrInModule);
        moduledata* md = {};
        for(auto next = & firstmoduledata; next != nullptr; next = next->next)
        {
            if(base >= next->types && base < next->etypes)
            {
                md = next;
                break;
            }
        }
        if(md == nullptr)
        {
            reflectOffsLock();
            auto res = reflectOffs.m[int32_t(off)];
            reflectOffsUnlock();
            if(res == nullptr)
            {
                println("runtime: typeOff", hex(off), "base", hex(base), "not in ranges:");
                for(auto next = & firstmoduledata; next != nullptr; next = next->next)
                {
                    println("\ttypes", hex(next->types), "etypes", hex(next->etypes));
                }
                go_throw("runtime: type offset base pointer out of range");
            }
            return (_type*)(res);
        }
        if(auto t = md->typemap[off]; t != nullptr)
        {
            return t;
        }
        auto res = md->types + uintptr_t(off);
        if(res > md->etypes)
        {
            println("runtime: typeOff", hex(off), "out of range", hex(md->types), "-", hex(md->etypes));
            go_throw("runtime: type offset out of range");
        }
        return (_type*)(unsafe::Pointer(res));
    }

    _type* typeOff(struct rtype t, typeOff off)
    {
        return resolveTypeOff(unsafe::Pointer(t.Type), off);
    }

    unsafe::Pointer textOff(struct rtype t, textOff off)
    {
        if(off == - 1)
        {
            return unsafe::Pointer(abi::FuncPCABIInternal(unreachableMethod));
        }
        auto base = uintptr_t(unsafe::Pointer(t.Type));
        moduledata* md = {};
        for(auto next = & firstmoduledata; next != nullptr; next = next->next)
        {
            if(base >= next->types && base < next->etypes)
            {
                md = next;
                break;
            }
        }
        if(md == nullptr)
        {
            reflectOffsLock();
            auto res = reflectOffs.m[int32_t(off)];
            reflectOffsUnlock();
            if(res == nullptr)
            {
                println("runtime: textOff", hex(off), "base", hex(base), "not in ranges:");
                for(auto next = & firstmoduledata; next != nullptr; next = next->next)
                {
                    println("\ttypes", hex(next->types), "etypes", hex(next->etypes));
                }
                go_throw("runtime: text offset base pointer out of range");
            }
            return res;
        }
        auto res = textAddr(gocpp::recv(md), uint32_t(off));
        return unsafe::Pointer(res);
    }

    std::string pkgPath(name n)
    {
        if(n.Bytes == nullptr || *Data(gocpp::recv(n), 0) & (1 << 2) == 0)
        {
            return "";
        }
        auto [i, l] = ReadVarint(gocpp::recv(n), 1);
        auto off = 1 + i + l;
        if(*Data(gocpp::recv(n), 0) & (1 << 1) != 0)
        {
            auto [i2, l2] = ReadVarint(gocpp::recv(n), off);
            off += i2 + l2;
        }
        nameOff nameOff = {};
        copy((gocpp::array<unsigned char, 4>*)(unsafe::Pointer(& nameOff)).make_slice(0, ), (gocpp::array<unsigned char, 4>*)(unsafe::Pointer(Data(gocpp::recv(n), off))).make_slice(0, ));
        auto pkgPathName = resolveNameOff(unsafe::Pointer(n.Bytes), nameOff);
        return Name(gocpp::recv(pkgPathName));
    }

    struct gocpp_id_1
                        {

                            using isGoStruct = void;

                            template<typename T> requires gocpp::GoStruct<T>
                            operator T()
                            {
                                T result;
                                return result;
                            }

                            template<typename T> requires gocpp::GoStruct<T>
                            bool operator==(const T& ref) const
                            {
                                return true;
                            }

                            std::ostream& PrintTo(std::ostream& os) const
                            {
                                os << '{';
                                os << '}';
                                return os;
                            }
                        };

                        std::ostream& operator<<(std::ostream& os, const struct gocpp_id_1& value)
                        {
                            return value.PrintTo(os);
                        }


    void typelinksinit()
    {
        if(firstmoduledata.next == nullptr)
        {
            return;
        }
        auto typehash = gocpp::make(gocpp::Tag<gocpp::map<uint32_t, gocpp::slice<_type*>>>(), len(firstmoduledata.typelinks));
        auto modules = activeModules();
        auto prev = modules[0];
        for(auto [_, md] : modules.make_slice(1))
        {
            collect:
            for(auto [_, tl] : prev->typelinks)
            {
                _type* t = {};
                if(prev->typemap == nullptr)
                {
                    t = (_type*)(unsafe::Pointer(prev->types + uintptr_t(tl)));
                }
                else
                {
                    t = prev->typemap[typeOff(tl)];
                }
                auto tlist = typehash[t->Hash];
                for(auto [_, tcur] : tlist)
                {
                    if(tcur == t)
                    {
                        goto collect_continue;
                    }
                }
                typehash[t->Hash] = append(tlist, t);
                if(false) {
                collect_continue:
                    continue;
                collect_break:
                    break;
                }
            }
            if(md->typemap == nullptr)
            {
                auto tm = gocpp::make(gocpp::Tag<gocpp::map<typeOff, _type*>>(), len(md->typelinks));
                pinnedTypemaps = append(pinnedTypemaps, tm);
                md->typemap = tm;
                for(auto [_, tl] : md->typelinks)
                {
                    auto t = (_type*)(unsafe::Pointer(md->types + uintptr_t(tl)));
                    for(auto [_, candidate] : typehash[t->Hash])
                    {
                        auto seen = gocpp::map<_typePair, gocpp_id_1> {};
                        if(typesEqual(t, candidate, seen))
                        {
                            t = candidate;
                            break;
                        }
                    }
                    md->typemap[typeOff(tl)] = t;
                }
            }
            prev = md;
        }
    }

    
    template<typename T> requires gocpp::GoStruct<T>
    _typePair::operator T()
    {
        T result;
        result.t1 = this->t1;
        result.t2 = this->t2;
        return result;
    }

    template<typename T> requires gocpp::GoStruct<T>
    bool _typePair::operator==(const T& ref) const
    {
        if (t1 != ref.t1) return false;
        if (t2 != ref.t2) return false;
        return true;
    }

    std::ostream& _typePair::PrintTo(std::ostream& os) const
    {
        os << '{';
        os << "" << t1;
        os << " " << t2;
        os << '}';
        return os;
    }

    std::ostream& operator<<(std::ostream& os, const struct _typePair& value)
    {
        return value.PrintTo(os);
    }

    rtype toRType(abi::Type* t)
    {
        return rtype {t};
    }

    struct gocpp_id_2
    {

        using isGoStruct = void;

        template<typename T> requires gocpp::GoStruct<T>
        operator T()
        {
            T result;
            return result;
        }

        template<typename T> requires gocpp::GoStruct<T>
        bool operator==(const T& ref) const
        {
            return true;
        }

        std::ostream& PrintTo(std::ostream& os) const
        {
            os << '{';
            os << '}';
            return os;
        }
    };

    std::ostream& operator<<(std::ostream& os, const struct gocpp_id_2& value)
    {
        return value.PrintTo(os);
    }


    struct gocpp_id_5
        {

            using isGoStruct = void;

            template<typename T> requires gocpp::GoStruct<T>
            operator T()
            {
                T result;
                return result;
            }

            template<typename T> requires gocpp::GoStruct<T>
            bool operator==(const T& ref) const
            {
                return true;
            }

            std::ostream& PrintTo(std::ostream& os) const
            {
                os << '{';
                os << '}';
                return os;
            }
        };

        std::ostream& operator<<(std::ostream& os, const struct gocpp_id_5& value)
        {
            return value.PrintTo(os);
        }


    bool typesEqual(_type* t, _type* v, gocpp::map<_typePair, gocpp_id_2> seen)
    {
        auto tp = _typePair {t, v};
        if(auto [gocpp_id_4, ok] = seen[tp]; ok)
        {
            return true;
        }
        seen[tp] = gocpp_id_5 {};
        if(t == v)
        {
            return true;
        }
        auto kind = t->Kind_ & kindMask;
        if(kind != v->Kind_ & kindMask)
        {
            return false;
        }
        auto [rt, rv] = std::tuple{toRType(t), toRType(v)};
        if(string(gocpp::recv(rt)) != string(gocpp::recv(rv)))
        {
            return false;
        }
        auto ut = Uncommon(gocpp::recv(t));
        auto uv = Uncommon(gocpp::recv(v));
        if(ut != nullptr || uv != nullptr)
        {
            if(ut == nullptr || uv == nullptr)
            {
                return false;
            }
            auto pkgpatht = Name(gocpp::recv(nameOff(gocpp::recv(rt), ut->PkgPath)));
            auto pkgpathv = Name(gocpp::recv(nameOff(gocpp::recv(rv), uv->PkgPath)));
            if(pkgpatht != pkgpathv)
            {
                return false;
            }
        }
        if(kindBool <= kind && kind <= kindComplex128)
        {
            return true;
        }
        //Go switch emulation
        {
            auto condition = kind;
            int conditionId = -1;
            if(condition == kindString) { conditionId = 0; }
            if(condition == kindUnsafePointer) { conditionId = 1; }
            else if(condition == kindArray) { conditionId = 2; }
            else if(condition == kindChan) { conditionId = 3; }
            else if(condition == kindFunc) { conditionId = 4; }
            else if(condition == kindInterface) { conditionId = 5; }
            else if(condition == kindMap) { conditionId = 6; }
            else if(condition == kindPtr) { conditionId = 7; }
            else if(condition == kindSlice) { conditionId = 8; }
            else if(condition == kindStruct) { conditionId = 9; }
            switch(conditionId)
            {
                case 0:
                case 1:
                    return true;
                    break;
                case 2:
                    auto at = (arraytype*)(unsafe::Pointer(t));
                    auto av = (arraytype*)(unsafe::Pointer(v));
                    return typesEqual(at->Elem, av->Elem, seen) && at->Len == av->Len;
                    break;
                case 3:
                    auto ct = (chantype*)(unsafe::Pointer(t));
                    auto cv = (chantype*)(unsafe::Pointer(v));
                    return ct->Dir == cv->Dir && typesEqual(ct->Elem, cv->Elem, seen);
                    break;
                case 4:
                    auto ft = (functype*)(unsafe::Pointer(t));
                    auto fv = (functype*)(unsafe::Pointer(v));
                    if(ft->OutCount != fv->OutCount || ft->InCount != fv->InCount)
                    {
                        return false;
                    }
                    auto [tin, vin] = std::tuple{InSlice(gocpp::recv(ft)), InSlice(gocpp::recv(fv))};
                    for(auto i = 0; i < len(tin); i++)
                    {
                        if(! typesEqual(tin[i], vin[i], seen))
                        {
                            return false;
                        }
                    }
                    auto [tout, vout] = std::tuple{OutSlice(gocpp::recv(ft)), OutSlice(gocpp::recv(fv))};
                    for(auto i = 0; i < len(tout); i++)
                    {
                        if(! typesEqual(tout[i], vout[i], seen))
                        {
                            return false;
                        }
                    }
                    return true;
                    break;
                case 5:
                    auto it = (interfacetype*)(unsafe::Pointer(t));
                    auto iv = (interfacetype*)(unsafe::Pointer(v));
                    if(Name(gocpp::recv(it->PkgPath)) != Name(gocpp::recv(iv->PkgPath)))
                    {
                        return false;
                    }
                    if(len(it->Methods) != len(iv->Methods))
                    {
                        return false;
                    }
                    for(auto [i, gocpp_ignored] : it->Methods)
                    {
                        auto tm = & it->Methods[i];
                        auto vm = & iv->Methods[i];
                        auto tname = resolveNameOff(unsafe::Pointer(tm), tm->Name);
                        auto vname = resolveNameOff(unsafe::Pointer(vm), vm->Name);
                        if(Name(gocpp::recv(tname)) != Name(gocpp::recv(vname)))
                        {
                            return false;
                        }
                        if(pkgPath(tname) != pkgPath(vname))
                        {
                            return false;
                        }
                        auto tityp = resolveTypeOff(unsafe::Pointer(tm), tm->Typ);
                        auto vityp = resolveTypeOff(unsafe::Pointer(vm), vm->Typ);
                        if(! typesEqual(tityp, vityp, seen))
                        {
                            return false;
                        }
                    }
                    return true;
                    break;
                case 6:
                    auto mt = (maptype*)(unsafe::Pointer(t));
                    auto mv = (maptype*)(unsafe::Pointer(v));
                    return typesEqual(mt->Key, mv->Key, seen) && typesEqual(mt->Elem, mv->Elem, seen);
                    break;
                case 7:
                    auto pt = (ptrtype*)(unsafe::Pointer(t));
                    auto pv = (ptrtype*)(unsafe::Pointer(v));
                    return typesEqual(pt->Elem, pv->Elem, seen);
                    break;
                case 8:
                    auto st = (slicetype*)(unsafe::Pointer(t));
                    auto sv = (slicetype*)(unsafe::Pointer(v));
                    return typesEqual(st->Elem, sv->Elem, seen);
                    break;
                case 9:
                    auto st = (structtype*)(unsafe::Pointer(t));
                    auto sv = (structtype*)(unsafe::Pointer(v));
                    if(len(st->Fields) != len(sv->Fields))
                    {
                        return false;
                    }
                    if(Name(gocpp::recv(st->PkgPath)) != Name(gocpp::recv(sv->PkgPath)))
                    {
                        return false;
                    }
                    for(auto [i, gocpp_ignored] : st->Fields)
                    {
                        auto tf = & st->Fields[i];
                        auto vf = & sv->Fields[i];
                        if(Name(gocpp::recv(tf->Name)) != Name(gocpp::recv(vf->Name)))
                        {
                            return false;
                        }
                        if(! typesEqual(tf->Typ, vf->Typ, seen))
                        {
                            return false;
                        }
                        if(Tag(gocpp::recv(tf->Name)) != Tag(gocpp::recv(vf->Name)))
                        {
                            return false;
                        }
                        if(tf->Offset != vf->Offset)
                        {
                            return false;
                        }
                        if(IsEmbedded(gocpp::recv(tf->Name)) != IsEmbedded(gocpp::recv(vf->Name)))
                        {
                            return false;
                        }
                    }
                    return true;
                    break;
                default:
                    println("runtime: impossible type kind", kind);
                    go_throw("runtime: impossible type kind");
                    return false;
                    break;
            }
        }
    }

}

