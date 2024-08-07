// generated by GoCpp from file '$(ImportDir)/runtime/mcache.go'
#pragma once

#include <functional>
#include <string>
#include <tuple>
#include <vector>

#include "golang/runtime/mcache.fwd.h"
#include "gocpp/support.h"

#include "golang/runtime/internal/atomic/atomic_amd64.h"
#include "golang/runtime/internal/atomic/types.h"
#include "golang/runtime/internal/sys/nih.h"
// #include "golang/runtime/lock_sema.h"  [Ignored, known errors]
#include "golang/runtime/malloc.h"
// #include "golang/runtime/mbitmap_allocheaders.h"  [Ignored, known errors]
#include "golang/runtime/mcentral.h"
#include "golang/runtime/mfixalloc.h"
// #include "golang/runtime/mgcpacer.h"  [Ignored, known errors]
// #include "golang/runtime/mgcsweep.h"  [Ignored, known errors]
#include "golang/runtime/mheap.h"
#include "golang/runtime/mspanset.h"
#include "golang/runtime/mstats.h"
#include "golang/runtime/panic.h"
#include "golang/runtime/runtime2.h"
#include "golang/runtime/sizeclasses.h"
#include "golang/runtime/stack.h"
// #include "golang/runtime/stubs.h"  [Ignored, known errors]
#include "golang/unsafe/unsafe.h"

namespace golang::runtime
{
    struct mcache
    {
        sys::NotInHeap _;
        uintptr_t nextSample;
        uintptr_t scanAlloc;
        uintptr_t tiny;
        uintptr_t tinyoffset;
        uintptr_t tinyAllocs;
        gocpp::array<mspan*, numSpanClasses> alloc;
        gocpp::array<stackfreelist, _NumStackOrders> stackcache;
        atomic::Uint32 flushGen;

        using isGoStruct = void;

        std::ostream& PrintTo(std::ostream& os) const;
    };

    std::ostream& operator<<(std::ostream& os, const struct mcache& value);
    struct gclink
    {
        gclinkptr next;

        using isGoStruct = void;

        std::ostream& PrintTo(std::ostream& os) const;
    };

    std::ostream& operator<<(std::ostream& os, const struct gclink& value);
    gclink* ptr(gclinkptr p);
    struct stackfreelist
    {
        gclinkptr list;
        uintptr_t size;

        using isGoStruct = void;

        std::ostream& PrintTo(std::ostream& os) const;
    };

    std::ostream& operator<<(std::ostream& os, const struct stackfreelist& value);
    mcache* allocmcache();
    void freemcache(mcache* c);
    mcache* getMCache(m* mp);
    void refill(struct mcache* c, spanClass spc);
    mspan* allocLarge(struct mcache* c, uintptr_t size, bool noscan);
    void releaseAll(struct mcache* c);
    void prepareForSweep(struct mcache* c);
}

