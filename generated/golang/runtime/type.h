// generated by GoCpp from file '$(ImportDir)/runtime/type.go'
#pragma once

#include <functional>
#include <string>
#include <tuple>
#include <vector>

#include "golang/runtime/type.fwd.h"
#include "gocpp/support.h"

#include "golang/internal/abi/type.h"
#include "golang/runtime/lockrank_off.h"
#include "golang/runtime/runtime2.h"

namespace golang::runtime
{
    struct rtype
    {
        abi::Type* Type;

        using isGoStruct = void;

        template<typename T> requires gocpp::GoStruct<T>
        operator T();

        template<typename T> requires gocpp::GoStruct<T>
        bool operator==(const T& ref) const;

        std::ostream& PrintTo(std::ostream& os) const;
    };

    std::ostream& operator<<(std::ostream& os, const struct rtype& value);
    extern gocpp_id_0 reflectOffs;
    void reflectOffsLock();
    void reflectOffsUnlock();
    runtime::name resolveNameOff(unsafe::Pointer ptrInModule, golang::runtime::nameOff off);
    runtime::_type* resolveTypeOff(unsafe::Pointer ptrInModule, golang::runtime::typeOff off);
    std::string pkgPath(golang::runtime::name n);
    void typelinksinit();
    struct _typePair
    {
        golang::runtime::_type* t1;
        golang::runtime::_type* t2;

        using isGoStruct = void;

        template<typename T> requires gocpp::GoStruct<T>
        operator T();

        template<typename T> requires gocpp::GoStruct<T>
        bool operator==(const T& ref) const;

        std::ostream& PrintTo(std::ostream& os) const;
    };

    std::ostream& operator<<(std::ostream& os, const struct _typePair& value);
    struct rtype toRType(abi::Type* t);
    struct gocpp_id_2
    {

        using isGoStruct = void;

        template<typename T> requires gocpp::GoStruct<T>
        operator T();

        template<typename T> requires gocpp::GoStruct<T>
        bool operator==(const T& ref) const;

        std::ostream& PrintTo(std::ostream& os) const;
    };

    std::ostream& operator<<(std::ostream& os, const struct gocpp_id_2& value);
    bool typesEqual(golang::runtime::_type* t, golang::runtime::_type* v, gocpp::map<_typePair, gocpp_id_2> seen);

    namespace rec
    {
        std::string string(struct rtype t);
        runtime::uncommontype* uncommon(struct rtype t);
        std::string name(struct rtype t);
        std::string pkgpath(struct rtype t);
        runtime::name nameOff(struct rtype t, golang::runtime::nameOff off);
        runtime::_type* typeOff(struct rtype t, golang::runtime::typeOff off);
        unsafe::Pointer textOff(struct rtype t, golang::runtime::textOff off);
    }
}

