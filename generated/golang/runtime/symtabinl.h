// generated by GoCpp from file '$(ImportDir)/runtime/symtabinl.go'
#pragma once

#include <functional>
#include <string>
#include <tuple>
#include <vector>

#include "golang/runtime/symtabinl.fwd.h"
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
    struct inlinedCall
    {
        abi::FuncID funcID;
        gocpp::array<unsigned char, 3> _1;
        int32_t nameOff;
        int32_t parentPc;
        int32_t startLine;

        using isGoStruct = void;

        template<typename T> requires gocpp::GoStruct<T>
        operator T();

        template<typename T> requires gocpp::GoStruct<T>
        bool operator==(const T& ref) const;

        std::ostream& PrintTo(std::ostream& os) const;
    };

    std::ostream& operator<<(std::ostream& os, const struct inlinedCall& value);
    struct inlineUnwinder
    {
        funcInfo f;
        gocpp::array<inlinedCall, 1 << 20>* inlTree;

        using isGoStruct = void;

        template<typename T> requires gocpp::GoStruct<T>
        operator T();

        template<typename T> requires gocpp::GoStruct<T>
        bool operator==(const T& ref) const;

        std::ostream& PrintTo(std::ostream& os) const;
    };

    std::ostream& operator<<(std::ostream& os, const struct inlineUnwinder& value);
    struct inlineFrame
    {
        uintptr_t pc;
        int32_t index;

        using isGoStruct = void;

        template<typename T> requires gocpp::GoStruct<T>
        operator T();

        template<typename T> requires gocpp::GoStruct<T>
        bool operator==(const T& ref) const;

        std::ostream& PrintTo(std::ostream& os) const;
    };

    std::ostream& operator<<(std::ostream& os, const struct inlineFrame& value);
    std::tuple<struct inlineUnwinder, struct inlineFrame> newInlineUnwinder(struct funcInfo f, uintptr_t pc);

    namespace rec
    {
        struct inlineFrame resolveInternal(struct inlineUnwinder* u, uintptr_t pc);
        bool valid(struct inlineFrame uf);
        struct inlineFrame next(struct inlineUnwinder* u, struct inlineFrame uf);
        bool isInlined(struct inlineUnwinder* u, struct inlineFrame uf);
        struct srcFunc srcFunc(struct inlineUnwinder* u, struct inlineFrame uf);
        std::tuple<std::string, int> fileLine(struct inlineUnwinder* u, struct inlineFrame uf);
    }
}

