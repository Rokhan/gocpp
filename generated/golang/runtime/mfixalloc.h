// generated by GoCpp from file '$(ImportDir)/runtime/mfixalloc.go'
#pragma once

#include <functional>
#include <string>
#include <tuple>
#include <vector>

#include "golang/runtime/mfixalloc.fwd.h"
#include "gocpp/support.h"

#include "golang/runtime/internal/sys/nih.h"
#include "golang/runtime/malloc.h"
#include "golang/runtime/mstats.h"
#include "golang/runtime/panic.h"
// #include "golang/runtime/stubs.h"  [Ignored, known errors]
#include "golang/unsafe/unsafe.h"

namespace golang::runtime
{
    struct fixalloc
    {
        uintptr_t size;
        std::function<void (unsafe::Pointer arg, unsafe::Pointer p)> first;
        unsafe::Pointer arg;
        mlink* list;
        uintptr_t chunk;
        uint32_t nchunk;
        uint32_t nalloc;
        uintptr_t inuse;
        sysMemStat* stat;
        bool zero;

        using isGoStruct = void;

        std::ostream& PrintTo(std::ostream& os) const;
    };

    std::ostream& operator<<(std::ostream& os, const fixalloc& value);
    struct mlink
    {
        sys::NotInHeap _;
        mlink* next;

        using isGoStruct = void;

        std::ostream& PrintTo(std::ostream& os) const;
    };

    std::ostream& operator<<(std::ostream& os, const mlink& value);
    void init(fixalloc* f, uintptr_t size, std::function<void (unsafe::Pointer arg, unsafe::Pointer p)> first, unsafe::Pointer arg, sysMemStat* stat);
    unsafe::Pointer alloc(fixalloc* f);
    void free(fixalloc* f, unsafe::Pointer p);
}
