// generated by GoCpp from file '$(ImportDir)/runtime/mpagecache.go'
#pragma once

#include <functional>
#include <string>
#include <tuple>
#include <vector>

#include "golang/runtime/mpagecache.fwd.h"
#include "gocpp/support.h"

#include "golang/runtime/internal/sys/intrinsics.h"
// #include "golang/runtime/lockrank_off.h"  [Ignored, known errors]
#include "golang/runtime/malloc.h"
// #include "golang/runtime/mgcscavenge.h"  [Ignored, known errors]
#include "golang/runtime/mpagealloc.h"
#include "golang/runtime/mpallocbits.h"
#include "golang/runtime/mranges.h"
#include "golang/runtime/panic.h"
// #include "golang/runtime/stubs.h"  [Ignored, known errors]

namespace golang::runtime
{
    struct pageCache
    {
        uintptr_t base;
        uint64_t cache;
        uint64_t scav;

        using isGoStruct = void;

        std::ostream& PrintTo(std::ostream& os) const;
    };

    std::ostream& operator<<(std::ostream& os, const struct pageCache& value);
    bool empty(struct pageCache* c);
    std::tuple<uintptr_t, uintptr_t> alloc(struct pageCache* c, uintptr_t npages);
    std::tuple<uintptr_t, uintptr_t> allocN(struct pageCache* c, uintptr_t npages);
    void flush(struct pageCache* c, pageAlloc* p);
    pageCache allocToCache(struct pageAlloc* p);
}
