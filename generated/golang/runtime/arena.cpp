// generated by GoCpp from file '$(ImportDir)/runtime/arena.go'
#include <complex>
#include <functional>
#include <iostream>
#include <iomanip>
#include <map>
#include <string>
#include <tuple>
#include <vector>

#include "golang/runtime/arena.h"
#include "gocpp/support.h"

// #include "golang/internal/goarch/goarch.h"  [Ignored, known errors]
#include "golang/internal/goexperiment/exp_allocheaders_on.h"
#include "golang/runtime/internal/atomic/atomic_amd64.h"
#include "golang/runtime/internal/atomic/stubs.h"
#include "golang/runtime/internal/atomic/types.h"
#include "golang/runtime/internal/math/math.h"
#include "golang/runtime/asan0.h"
#include "golang/runtime/error.h"
#include "golang/runtime/lock_sema.h"
// #include "golang/runtime/lockrank.h"  [Ignored, known errors]
// #include "golang/runtime/lockrank_off.h"  [Ignored, known errors]
#include "golang/runtime/malloc.h"
#include "golang/runtime/mbarrier.h"
// #include "golang/runtime/mbitmap_allocheaders.h"  [Ignored, known errors]
// #include "golang/runtime/mcache.h"  [Ignored, known errors]
#include "golang/runtime/mcentral.h"
#include "golang/runtime/mem.h"
#include "golang/runtime/mfinal.h"
#include "golang/runtime/mgc.h"
#include "golang/runtime/mgcmark.h"
#include "golang/runtime/mgcpacer.h"
#include "golang/runtime/mheap.h"
#include "golang/runtime/mprof.h"
// #include "golang/runtime/mranges.h"  [Ignored, known errors]
#include "golang/runtime/msan0.h"
#include "golang/runtime/mspanset.h"
// #include "golang/runtime/mstats.h"  [Ignored, known errors]
#include "golang/runtime/panic.h"
// #include "golang/runtime/race0.h"  [Ignored, known errors]
// #include "golang/runtime/runtime1.h"  [Ignored, known errors]
#include "golang/runtime/runtime2.h"
// #include "golang/runtime/slice.h"  [Ignored, known errors]
#include "golang/runtime/string.h"
// #include "golang/runtime/stubs.h"  [Ignored, known errors]
#include "golang/runtime/type.h"
// #include "golang/runtime/typekind.h"  [Ignored, known errors]
#include "golang/unsafe/unsafe.h"

namespace golang::runtime
{
    unsafe::Pointer arena_newArena()
    {
        return Pointer(gocpp::recv(unsafe), newUserArena());
    }

    any arena_arena_New(unsafe::Pointer arena, any typ)
    {
        auto t = (*_type)(efaceOf(& typ)->data);
        if(t->Kind_ & kindMask != kindPtr)
        {
            go_throw("arena_New: non-pointer type");
        }
        auto te = (*ptrtype)(Pointer(gocpp::recv(unsafe), t))->Elem;
        auto x = go_new(gocpp::recv(((*userArena)(arena))), te);
        any result = {};
        auto e = efaceOf(& result);
        e->_type = t;
        e->data = x;
        return result;
    }

    void arena_arena_Slice(unsafe::Pointer arena, any slice, int cap)
    {
        slice(gocpp::recv(((*userArena)(arena))), slice, cap);
    }

    void arena_arena_Free(unsafe::Pointer arena)
    {
        free(gocpp::recv(((*userArena)(arena))));
    }

    any arena_heapify(any s)
    {
        unsafe::Pointer v = {};
        auto e = efaceOf(& s);
        auto t = e->_type;
        //Go switch emulation
        {
            auto condition = t->Kind_ & kindMask;
            int conditionId = -1;
            if(condition == kindString) { conditionId = 0; }
            else if(condition == kindSlice) { conditionId = 1; }
            else if(condition == kindPtr) { conditionId = 2; }
            switch(conditionId)
            {
                case 0:
                    v = stringStructOf((*string)(e->data))->str;
                    break;
                case 1:
                    v = (*slice)(e->data)->array;
                    break;
                case 2:
                    v = e->data;
                    break;
                default:
                    gocpp::panic("arena: Clone only supports pointers, slices, and strings");
                    break;
            }
        }
        auto span = spanOf(uintptr(v));
        if(span == nullptr || ! span->isUserArenaChunk)
        {
            return s;
        }
        any x = {};
        //Go switch emulation
        {
            auto condition = t->Kind_ & kindMask;
            int conditionId = -1;
            if(condition == kindString) { conditionId = 0; }
            else if(condition == kindSlice) { conditionId = 1; }
            else if(condition == kindPtr) { conditionId = 2; }
            switch(conditionId)
            {
                case 0:
                    auto s1 = gocpp::getValue<std::string>(s);
                    auto [s2, b] = rawstring(len(s1));
                    copy(b, s1);
                    x = s2;
                    break;
                case 1:
                    auto len = (*slice)(e->data)->len;
                    auto et = (*slicetype)(Pointer(gocpp::recv(unsafe), t))->Elem;
                    auto sl = go_new(slice);
                    *sl = slice {makeslicecopy(et, len, len, (*slice)(e->data)->array), len, len};
                    auto xe = efaceOf(& x);
                    xe->_type = t;
                    xe->data = Pointer(gocpp::recv(unsafe), sl);
                    break;
                case 2:
                    auto et = (*ptrtype)(Pointer(gocpp::recv(unsafe), t))->Elem;
                    auto e2 = newobject(et);
                    typedmemmove(et, e2, e->data);
                    auto xe = efaceOf(& x);
                    xe->_type = t;
                    xe->data = e2;
                    break;
            }
        }
        return x;
    }

    int userArenaChunkBytesMax = 8 << 20;
    uintptr_t userArenaChunkBytes = uintptr(int64(userArenaChunkBytesMax - heapArenaBytes) & (int64(userArenaChunkBytesMax - heapArenaBytes) >> 63) + heapArenaBytes);
    uintptr_t userArenaChunkPages = userArenaChunkBytes / pageSize;
    uintptr_t userArenaChunkMaxAllocBytes = userArenaChunkBytes / 4;
    void init()
    {
        if(userArenaChunkPages * pageSize != userArenaChunkBytes)
        {
            go_throw("user arena chunk size is not a multiple of the page size");
        }
        if(userArenaChunkBytes % physPageSize != 0)
        {
            go_throw("user arena chunk size is not a multiple of the physical page size");
        }
        if(userArenaChunkBytes < heapArenaBytes)
        {
            if(heapArenaBytes % userArenaChunkBytes != 0)
            {
                go_throw("user arena chunk size is smaller than a heap arena, but doesn't divide it");
            }
        }
        else
        {
            if(userArenaChunkBytes % heapArenaBytes != 0)
            {
                go_throw("user arena chunks size is larger than a heap arena, but not a multiple");
            }
        }
        lockInit(& userArenaState.lock, lockRankUserArenaState);
    }

    uintptr_t userArenaChunkReserveBytes()
    {
        if(goexperiment.AllocHeaders)
        {
            return userArenaChunkBytes / goarch.PtrSize / 8 + Sizeof(gocpp::recv(unsafe), _type {});
        }
        return 0;
    }

    
    std::ostream& userArena::PrintTo(std::ostream& os) const
    {
        os << '{';
        os << "" << fullList;
        os << " " << active;
        os << " " << refs;
        os << " " << defunct;
        os << '}';
        return os;
    }

    std::ostream& operator<<(std::ostream& os, const userArena& value)
    {
        return value.PrintTo(os);
    }

    userArena* newUserArena()
    {
        auto a = go_new(userArena);
        SetFinalizer(a, [=](userArena* a) mutable -> void
        {
            free(gocpp::recv(a));
        }
);
        refill(gocpp::recv(a));
        return a;
    }

    unsafe::Pointer go_new(userArena* a, _type* typ)
    {
        return alloc(gocpp::recv(a), typ, - 1);
    }

    void slice(userArena* a, any sl, int cap)
    {
        if(cap < 0)
        {
            gocpp::panic("userArena.slice: negative cap");
        }
        auto i = efaceOf(& sl);
        auto typ = i->_type;
        if(typ->Kind_ & kindMask != kindPtr)
        {
            gocpp::panic("slice result of non-ptr type");
        }
        typ = (*ptrtype)(Pointer(gocpp::recv(unsafe), typ))->Elem;
        if(typ->Kind_ & kindMask != kindSlice)
        {
            gocpp::panic("slice of non-ptr-to-slice type");
        }
        typ = (*slicetype)(Pointer(gocpp::recv(unsafe), typ))->Elem;
        *((*slice)(i->data)) = slice {alloc(gocpp::recv(a), typ, cap), cap, cap};
    }

    void free(userArena* a)
    {
        if(Load(gocpp::recv(a->defunct)))
        {
            gocpp::panic("arena double free");
        }
        Store(gocpp::recv(a->defunct), true);
        SetFinalizer(a, nullptr);
        auto s = a->fullList;
        auto i = len(a->refs) - 2;
        for(; s != nullptr; )
        {
            a->fullList = s->next;
            s->next = nullptr;
            freeUserArenaChunk(s, a->refs[i]);
            s = a->fullList;
            i--;
        }
        if(a->fullList != nullptr || i >= 0)
        {
            go_throw("full list doesn't match refs list in length");
        }
        s = a->active;
        if(s != nullptr)
        {
            if(raceenabled || msanenabled || asanenabled)
            {
                freeUserArenaChunk(s, a->refs[len(a->refs) - 1]);
            }
            else
            {
                lock(& userArenaState.lock);
                userArenaState.reuse = append(userArenaState.reuse, liveUserArenaChunk {s, a->refs[len(a->refs) - 1]});
                unlock(& userArenaState.lock);
            }
        }
        a->active = nullptr;
        a->refs = nullptr;
    }

    unsafe::Pointer alloc(userArena* a, _type* typ, int cap)
    {
        auto s = a->active;
        unsafe::Pointer x = {};
        for(; ; )
        {
            x = userArenaNextFree(gocpp::recv(s), typ, cap);
            if(x != nullptr)
            {
                break;
            }
            s = refill(gocpp::recv(a));
        }
        return x;
    }

    mspan* refill(userArena* a)
    {
        auto s = a->active;
        if(s != nullptr)
        {
            if(size(gocpp::recv(s->userArenaChunkFree)) > userArenaChunkMaxAllocBytes)
            {
                go_throw("wasted too much memory in an arena chunk");
            }
            s->next = a->fullList;
            a->fullList = s;
            a->active = nullptr;
            s = nullptr;
        }
        unsafe::Pointer x = {};
        lock(& userArenaState.lock);
        if(len(userArenaState.reuse) > 0)
        {
            auto n = len(userArenaState.reuse) - 1;
            x = userArenaState.reuse[n].x;
            s = userArenaState.reuse[n].mspan;
            userArenaState.reuse[n].x = nullptr;
            userArenaState.reuse[n].mspan = nullptr;
            userArenaState.reuse = userArenaState.reuse.make_slice(0, n);
        }
        unlock(& userArenaState.lock);
        if(s == nullptr)
        {
            std::tie(x, s) = newUserArenaChunk();
            if(s == nullptr)
            {
                go_throw("out of memory");
            }
        }
        a->refs = append(a->refs, x);
        a->active = s;
        return s;
    }

    
    std::ostream& liveUserArenaChunk::PrintTo(std::ostream& os) const
    {
        os << '{';
        os << "" << x;
        os << '}';
        return os;
    }

    std::ostream& operator<<(std::ostream& os, const liveUserArenaChunk& value)
    {
        return value.PrintTo(os);
    }

    struct gocpp_id_0
    {
        mutex lock;
        gocpp::slice<liveUserArenaChunk> reuse;
        gocpp::slice<liveUserArenaChunk> fault;

        using isGoStruct = void;

        std::ostream& PrintTo(std::ostream& os) const
        {
            os << '{';
            os << "" << lock;
            os << " " << reuse;
            os << " " << fault;
            os << '}';
            return os;
        }
    };
    gocpp_id_0 userArenaState;
    unsafe::Pointer userArenaNextFree(mspan* s, _type* typ, int cap)
    {
        auto size = typ->Size_;
        if(cap > 0)
        {
            if(size > ^ uintptr(0) / uintptr(cap))
            {
                go_throw("out of memory");
            }
            size *= uintptr(cap);
        }
        if(size == 0 || cap == 0)
        {
            return Pointer(gocpp::recv(unsafe), & zerobase);
        }
        if(size > userArenaChunkMaxAllocBytes)
        {
            if(cap >= 0)
            {
                return newarray(typ, cap);
            }
            return newobject(typ);
        }
        auto mp = acquirem();
        if(mp->mallocing != 0)
        {
            go_throw("malloc deadlock");
        }
        if(mp->gsignal == getg())
        {
            go_throw("malloc during signal");
        }
        mp->mallocing = 1;
        unsafe::Pointer ptr = {};
        if(typ->PtrBytes == 0)
        {
            auto [v, ok] = takeFromBack(gocpp::recv(s->userArenaChunkFree), size, typ->Align_);
            if(ok)
            {
                ptr = Pointer(gocpp::recv(unsafe), v);
            }
        }
        else
        {
            auto [v, ok] = takeFromFront(gocpp::recv(s->userArenaChunkFree), size, typ->Align_);
            if(ok)
            {
                ptr = Pointer(gocpp::recv(unsafe), v);
            }
        }
        if(ptr == nullptr)
        {
            mp->mallocing = 0;
            releasem(mp);
            return nullptr;
        }
        if(s->needzero != 0)
        {
            go_throw("arena chunk needs zeroing, but should already be zeroed");
        }
        if(typ->PtrBytes != 0)
        {
            if(cap >= 0)
            {
                userArenaHeapBitsSetSliceType(typ, cap, ptr, s);
            }
            else
            {
                userArenaHeapBitsSetType(typ, ptr, s);
            }
            auto c = getMCache(mp);
            if(c == nullptr)
            {
                go_throw("mallocgc called without a P or outside bootstrapping");
            }
            if(cap > 0)
            {
                c->scanAlloc += size - (typ->Size_ - typ->PtrBytes);
            }
            else
            {
                c->scanAlloc += typ->PtrBytes;
            }
        }
        publicationBarrier();
        mp->mallocing = 0;
        releasem(mp);
        return ptr;
    }

    void userArenaHeapBitsSetSliceType(_type* typ, int n, unsafe::Pointer ptr, mspan* s)
    {
        auto [mem, overflow] = math::MulUintptr(typ->Size_, uintptr(n));
        if(overflow || n < 0 || mem > maxAlloc)
        {
            gocpp::panic(plainError("runtime: allocation size out of range"));
        }
        for(auto i = 0; i < n; i++)
        {
            userArenaHeapBitsSetType(typ, add(ptr, uintptr(i) * typ->Size_), s);
        }
    }

    std::tuple<unsafe::Pointer, mspan*> newUserArenaChunk()
    {
        if(gcphase == _GCmarktermination)
        {
            go_throw("newUserArenaChunk called with gcphase == _GCmarktermination");
        }
        deductAssistCredit(userArenaChunkBytes);
        auto mp = acquirem();
        if(mp->mallocing != 0)
        {
            go_throw("malloc deadlock");
        }
        if(mp->gsignal == getg())
        {
            go_throw("malloc during signal");
        }
        mp->mallocing = 1;
        mspan* span = {};
        systemstack([=]() mutable -> void
        {
            span = allocUserArenaChunk(gocpp::recv(mheap_));
        }
);
        if(span == nullptr)
        {
            go_throw("out of memory");
        }
        auto x = Pointer(gocpp::recv(unsafe), base(gocpp::recv(span)));
        if(gcphase != _GCoff)
        {
            gcmarknewobject(span, base(gocpp::recv(span)));
        }
        if(raceenabled)
        {
            racemalloc(Pointer(gocpp::recv(unsafe), base(gocpp::recv(span))), span->elemsize);
        }
        if(msanenabled)
        {
            msanmalloc(Pointer(gocpp::recv(unsafe), base(gocpp::recv(span))), span->elemsize);
        }
        if(asanenabled)
        {
            auto rzSize = computeRZlog(span->elemsize);
            span->elemsize -= rzSize;
            if(goexperiment.AllocHeaders)
            {
                span->largeType->Size_ = span->elemsize;
            }
            auto rzStart = base(gocpp::recv(span)) + span->elemsize;
            span->userArenaChunkFree = makeAddrRange(base(gocpp::recv(span)), rzStart);
            asanpoison(Pointer(gocpp::recv(unsafe), rzStart), span->limit - rzStart);
            asanunpoison(Pointer(gocpp::recv(unsafe), base(gocpp::recv(span))), span->elemsize);
        }
        if(auto rate = MemProfileRate; rate > 0)
        {
            auto c = getMCache(mp);
            if(c == nullptr)
            {
                go_throw("newUserArenaChunk called without a P or outside bootstrapping");
            }
            if(rate != 1 && userArenaChunkBytes < c->nextSample)
            {
                c->nextSample -= userArenaChunkBytes;
            }
            else
            {
                profilealloc(mp, Pointer(gocpp::recv(unsafe), base(gocpp::recv(span))), userArenaChunkBytes);
            }
        }
        mp->mallocing = 0;
        releasem(mp);
        if(auto t = (gocpp::Init<gcTrigger>([](gcTrigger& x) { x.kind = gcTriggerHeap; })); test(gocpp::recv(t)))
        {
            gcStart(t);
        }
        if(debug.malloc)
        {
            if(debug.allocfreetrace != 0)
            {
                tracealloc(Pointer(gocpp::recv(unsafe), base(gocpp::recv(span))), userArenaChunkBytes, nullptr);
            }
            if(inittrace.active && inittrace.id == getg()->goid)
            {
                inittrace.bytes += uint64_t(userArenaChunkBytes);
            }
        }
        if(uintptr(x) % physPageSize != 0)
        {
            go_throw("user arena chunk is not aligned to the physical page size");
        }
        return {x, span};
    }

    bool isUnusedUserArenaChunk(mspan* s)
    {
        return s->isUserArenaChunk && s->spanclass == makeSpanClass(0, true);
    }

    void setUserArenaChunkToFault(mspan* s)
    {
        if(! s->isUserArenaChunk)
        {
            go_throw("invalid span in heapArena for user arena");
        }
        if(s->npages * pageSize != userArenaChunkBytes)
        {
            go_throw("span on userArena.faultList has invalid size");
        }
        s->spanclass = makeSpanClass(0, true);
        sysFault(Pointer(gocpp::recv(unsafe), base(gocpp::recv(s))), s->npages * pageSize);
        add(gocpp::recv(gcController.heapInUse), - int64(s->npages * pageSize));
        Add(gocpp::recv(gcController.totalFree), int64(s->elemsize));
        auto stats = acquire(gocpp::recv(memstats.heapStats));
        Xaddint64(gocpp::recv(atomic), & stats->committed, - int64(s->npages * pageSize));
        Xaddint64(gocpp::recv(atomic), & stats->inHeap, - int64(s->npages * pageSize));
        Xadd64(gocpp::recv(atomic), & stats->largeFreeCount, 1);
        Xadd64(gocpp::recv(atomic), & stats->largeFree, int64(s->elemsize));
        release(gocpp::recv(memstats.heapStats));
        update(gocpp::recv(gcController), - int64(s->elemsize), 0);
        if(raceenabled)
        {
            racefree(Pointer(gocpp::recv(unsafe), base(gocpp::recv(s))), s->elemsize);
        }
        systemstack([=]() mutable -> void
        {
            lock(& mheap_.lock);
            insert(gocpp::recv(mheap_.userArena.quarantineList), s);
            unlock(& mheap_.lock);
        }
);
    }

    bool inUserArenaChunk(uintptr_t p)
    {
        auto s = spanOf(p);
        if(s == nullptr)
        {
            return false;
        }
        return s->isUserArenaChunk;
    }

    void freeUserArenaChunk(mspan* s, unsafe::Pointer x)
    {
        if(! s->isUserArenaChunk)
        {
            go_throw("span is not for a user arena");
        }
        if(s->npages * pageSize != userArenaChunkBytes)
        {
            go_throw("invalid user arena span size");
        }
        if(raceenabled)
        {
            racefree(Pointer(gocpp::recv(unsafe), base(gocpp::recv(s))), s->elemsize);
        }
        if(msanenabled)
        {
            msanfree(Pointer(gocpp::recv(unsafe), base(gocpp::recv(s))), s->elemsize);
        }
        if(asanenabled)
        {
            asanpoison(Pointer(gocpp::recv(unsafe), base(gocpp::recv(s))), s->elemsize);
        }
        auto mp = acquirem();
        if(gcphase == _GCoff)
        {
            lock(& userArenaState.lock);
            auto faultList = userArenaState.fault;
            userArenaState.fault = nullptr;
            unlock(& userArenaState.lock);
            setUserArenaChunkToFault(gocpp::recv(s));
            for(auto [_, lc] : faultList)
            {
                setUserArenaChunkToFault(gocpp::recv(lc.mspan));
            }
            KeepAlive(x);
            KeepAlive(faultList);
        }
        else
        {
            lock(& userArenaState.lock);
            userArenaState.fault = append(userArenaState.fault, liveUserArenaChunk {s, x});
            unlock(& userArenaState.lock);
        }
        releasem(mp);
    }

    mspan* allocUserArenaChunk(mheap* h)
    {
        mspan* s = {};
        uintptr_t base = {};
        lock(& h->lock);
        if(! isEmpty(gocpp::recv(h->userArena.readyList)))
        {
            s = h->userArena.readyList.first;
            remove(gocpp::recv(h->userArena.readyList), s);
            base = base(gocpp::recv(s));
        }
        else
        {
            auto hintList = & h->userArena.arenaHints;
            if(raceenabled)
            {
                hintList = & h->arenaHints;
            }
            auto [v, size] = sysAlloc(gocpp::recv(h), userArenaChunkBytes, hintList, false);
            if(size % userArenaChunkBytes != 0)
            {
                go_throw("sysAlloc size is not divisible by userArenaChunkBytes");
            }
            if(size > userArenaChunkBytes)
            {
                for(auto i = userArenaChunkBytes; i < size; i += userArenaChunkBytes)
                {
                    auto s = allocMSpanLocked(gocpp::recv(h));
                    init(gocpp::recv(s), uintptr(v) + i, userArenaChunkPages);
                    insertBack(gocpp::recv(h->userArena.readyList), s);
                }
                size = userArenaChunkBytes;
            }
            base = uintptr(v);
            if(base == 0)
            {
                unlock(& h->lock);
                return nullptr;
            }
            s = allocMSpanLocked(gocpp::recv(h));
        }
        unlock(& h->lock);
        sysMap(Pointer(gocpp::recv(unsafe), base), userArenaChunkBytes, & gcController.heapReleased);
        sysUsed(Pointer(gocpp::recv(unsafe), base), userArenaChunkBytes, userArenaChunkBytes);
        auto spc = makeSpanClass(0, false);
        initSpan(gocpp::recv(h), s, spanAllocHeap, spc, base, userArenaChunkPages);
        s->isUserArenaChunk = true;
        s->elemsize -= userArenaChunkReserveBytes();
        s->limit = base(gocpp::recv(s)) + s->elemsize;
        s->freeindex = 1;
        s->allocCount = 1;
        add(gocpp::recv(gcController.heapInUse), int64(userArenaChunkBytes));
        add(gocpp::recv(gcController.heapReleased), - int64(userArenaChunkBytes));
        auto stats = acquire(gocpp::recv(memstats.heapStats));
        Xaddint64(gocpp::recv(atomic), & stats->inHeap, int64(userArenaChunkBytes));
        Xaddint64(gocpp::recv(atomic), & stats->committed, int64(userArenaChunkBytes));
        Xadd64(gocpp::recv(atomic), & stats->largeAlloc, int64(s->elemsize));
        Xadd64(gocpp::recv(atomic), & stats->largeAllocCount, 1);
        release(gocpp::recv(memstats.heapStats));
        Add(gocpp::recv(gcController.totalAlloc), int64(s->elemsize));
        update(gocpp::recv(gcController), int64(s->elemsize), 0);
        initHeapBits(gocpp::recv(s), true);
        memclrNoHeapPointers(Pointer(gocpp::recv(unsafe), base(gocpp::recv(s))), s->elemsize);
        s->needzero = 0;
        s->freeIndexForScan = 1;
        s->userArenaChunkFree = makeAddrRange(base, base + s->elemsize);
        push(gocpp::recv(fullSwept(gocpp::recv(h->central[spc].mcentral), h->sweepgen)), s);
        if(goexperiment.AllocHeaders)
        {
            *(*uintptr)(Pointer(gocpp::recv(unsafe), & s->largeType)) = uintptr(Pointer(gocpp::recv(unsafe), s->limit));
            *(*uintptr)(Pointer(gocpp::recv(unsafe), & s->largeType->GCData)) = s->limit + Sizeof(gocpp::recv(unsafe), _type {});
            s->largeType->PtrBytes = 0;
            s->largeType->Size_ = s->elemsize;
        }
        return s;
    }

}
