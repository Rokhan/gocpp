// generated by GoCpp from file '$(ImportDir)/runtime/trace2string.go'
#pragma once

#include <functional>
#include <string>
#include <tuple>
#include <vector>

#include "golang/runtime/trace2string.fwd.h"
#include "gocpp/support.h"

// #include "golang/runtime/lock_sema.h"  [Ignored, known errors]
#include "golang/runtime/runtime2.h"
#include "golang/runtime/string.h"
// #include "golang/runtime/stubs.h"  [Ignored, known errors]
#include "golang/runtime/trace2buf.h"
#include "golang/runtime/trace2event.h"
// #include "golang/runtime/trace2map.h"  [Ignored, known errors]

namespace golang::runtime
{
    extern int maxTraceStringLen;
    struct traceStringTable
    {
        mutex lock;
        traceBuf* buf;
        traceMap tab;

        using isGoStruct = void;

        std::ostream& PrintTo(std::ostream& os) const;
    };

    std::ostream& operator<<(std::ostream& os, const struct traceStringTable& value);
    uint64_t put(struct traceStringTable* t, uintptr_t gen, std::string s);
    uint64_t emit(struct traceStringTable* t, uintptr_t gen, std::string s);
    void writeString(struct traceStringTable* t, uintptr_t gen, uint64_t id, std::string s);
    void reset(struct traceStringTable* t, uintptr_t gen);
}
