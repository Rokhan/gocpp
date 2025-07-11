// generated by GoCpp from file '$(ImportDir)/runtime/stkframe.go'
#pragma once

#include <functional>
#include <string>
#include <tuple>
#include <vector>

#include "golang/runtime/stkframe.fwd.h"
#include "gocpp/support.h"

#include "golang/internal/abi/symtab.h"
#include "golang/internal/abi/type.h"
#include "golang/runtime/internal/sys/nih.h"
#include "golang/runtime/plugin.h"
#include "golang/runtime/proc.h"
#include "golang/runtime/runtime2.h"
#include "golang/runtime/stack.h"
#include "golang/runtime/symtab.h"

namespace golang::runtime
{
    struct stkframe
    {
        funcInfo fn;
        uintptr_t pc;
        uintptr_t continpc;
        uintptr_t lr;
        uintptr_t sp;
        uintptr_t fp;
        uintptr_t varp;
        uintptr_t argp;

        using isGoStruct = void;

        template<typename T> requires gocpp::GoStruct<T>
        operator T();

        template<typename T> requires gocpp::GoStruct<T>
        bool operator==(const T& ref) const;

        std::ostream& PrintTo(std::ostream& os) const;
    };

    std::ostream& operator<<(std::ostream& os, const struct stkframe& value);
    struct reflectMethodValue
    {
        uintptr_t fn;
        bitvector* stack;
        uintptr_t argLen;

        using isGoStruct = void;

        template<typename T> requires gocpp::GoStruct<T>
        operator T();

        template<typename T> requires gocpp::GoStruct<T>
        bool operator==(const T& ref) const;

        std::ostream& PrintTo(std::ostream& os) const;
    };

    std::ostream& operator<<(std::ostream& os, const struct reflectMethodValue& value);
    extern gocpp::array<stackObjectRecord, 1> methodValueCallFrameObjs;
    void stkobjinit();

    namespace rec
    {
        uintptr_t argBytes(struct stkframe* frame);
        std::tuple<struct bitvector, bool> argMapInternal(struct stkframe* frame);
        std::tuple<struct bitvector, struct bitvector, gocpp::slice<stackObjectRecord>> getStackMap(struct stkframe* frame, bool debug);
    }
}

