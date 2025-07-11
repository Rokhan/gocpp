// generated by GoCpp from file '$(ImportDir)/runtime/plugin.go'
#pragma once

#include <functional>
#include <string>
#include <tuple>
#include <vector>

#include "golang/runtime/plugin.fwd.h"
#include "gocpp/support.h"

#include "golang/internal/abi/type.h"
#include "golang/runtime/internal/sys/nih.h"
#include "golang/runtime/proc.h"
#include "golang/runtime/runtime2.h"
#include "golang/runtime/stack.h"
#include "golang/runtime/symtab.h"

namespace golang::runtime
{
    std::tuple<std::string, gocpp::map<std::string, go_any>, gocpp::slice<initTask*>, std::string> plugin_lastmoduleinit();
    void pluginftabverify(struct moduledata* md);
    bool inRange(uintptr_t r0, uintptr_t r1, uintptr_t v0, uintptr_t v1);
    struct ptabEntry
    {
        golang::runtime::nameOff name;
        golang::runtime::typeOff typ;

        using isGoStruct = void;

        template<typename T> requires gocpp::GoStruct<T>
        operator T();

        template<typename T> requires gocpp::GoStruct<T>
        bool operator==(const T& ref) const;

        std::ostream& PrintTo(std::ostream& os) const;
    };

    std::ostream& operator<<(std::ostream& os, const struct ptabEntry& value);

    namespace rec
    {
    }
}

