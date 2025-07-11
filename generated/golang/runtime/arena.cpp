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

#include "golang/internal/abi/type.h"
#include "golang/internal/chacha8rand/chacha8.h"
#include "golang/internal/cpu/cpu.h"
#include "golang/internal/goarch/goarch.h"
#include "golang/internal/goexperiment/exp_allocheaders_on.h"
#include "golang/runtime/asan0.h"
#include "golang/runtime/cgocall.h"
#include "golang/runtime/chan.h"
#include "golang/runtime/coro.h"
#include "golang/runtime/debuglog_off.h"
#include "golang/runtime/error.h"
#include "golang/runtime/internal/atomic/atomic_amd64.h"
#include "golang/runtime/internal/atomic/stubs.h"
#include "golang/runtime/internal/atomic/types.h"
#include "golang/runtime/internal/math/math.h"
#include "golang/runtime/internal/sys/nih.h"
#include "golang/runtime/lock_sema.h"
#include "golang/runtime/lockrank.h"
#include "golang/runtime/lockrank_off.h"
#include "golang/runtime/malloc.h"
#include "golang/runtime/mbarrier.h"
#include "golang/runtime/mbitmap_allocheaders.h"
#include "golang/runtime/mcache.h"
#include "golang/runtime/mcentral.h"
#include "golang/runtime/mcheckmark.h"
#include "golang/runtime/mem.h"
#include "golang/runtime/mfinal.h"
#include "golang/runtime/mfixalloc.h"
#include "golang/runtime/mgc.h"
#include "golang/runtime/mgcmark.h"
#include "golang/runtime/mgcpacer.h"
#include "golang/runtime/mgcscavenge.h"
#include "golang/runtime/mheap.h"
#include "golang/runtime/mpagealloc.h"
#include "golang/runtime/mpallocbits.h"
#include "golang/runtime/mprof.h"
#include "golang/runtime/mranges.h"
#include "golang/runtime/msan0.h"
#include "golang/runtime/mspanset.h"
#include "golang/runtime/mstats.h"
#include "golang/runtime/os_windows.h"
#include "golang/runtime/panic.h"
#include "golang/runtime/proc.h"
#include "golang/runtime/race0.h"
#include "golang/runtime/runtime1.h"
#include "golang/runtime/runtime2.h"
#include "golang/runtime/signal_windows.h"
#include "golang/runtime/slice.h"
#include "golang/runtime/string.h"
#include "golang/runtime/stubs.h"
#include "golang/runtime/symtab.h"
#include "golang/runtime/time.h"
#include "golang/runtime/trace2buf.h"
#include "golang/runtime/trace2runtime.h"
#include "golang/runtime/trace2status.h"
#include "golang/runtime/trace2time.h"
#include "golang/runtime/type.h"
#include "golang/runtime/typekind.h"
#include "golang/unsafe/unsafe.h"

namespace golang::runtime
{
    namespace rec
    {
        using namespace mocklib::rec;
        using atomic::rec::Add;
        using atomic::rec::Load;
        using atomic::rec::Store;
    }

    // arena_newArena is a wrapper around newUserArena.
    //
    //go:linkname arena_newArena arena.runtime_arena_newArena
    unsafe::Pointer arena_newArena()
    {
        return unsafe::Pointer(newUserArena());
    }

    // arena_arena_New is a wrapper around (*userArena).new, except that typ
    // is an any (must be a *_type, still) and typ must be a type descriptor
    // for a pointer to the type to actually be allocated, i.e. pass a *T
    // to allocate a T. This is necessary because this function returns a *T.
    //
    //go:linkname arena_arena_New arena.runtime_arena_arena_New
    go_any arena_arena_New(unsafe::Pointer arena, go_any typ)
    {
        auto t = (runtime::_type*)(efaceOf(& typ)->data);
        if(t->Kind_ & kindMask != kindPtr)
        {
            go_throw("arena_New: non-pointer type"s);
        }
        auto te = (runtime::ptrtype*)(unsafe::Pointer(t))->Elem;
        auto x = rec::go_new(gocpp::recv(((userArena*)(arena))), te);
        go_any result = {};
        auto e = efaceOf(& result);
        e->_type = t;
        e->data = x;
        return result;
    }

    // arena_arena_Slice is a wrapper around (*userArena).slice.
    //
    //go:linkname arena_arena_Slice arena.runtime_arena_arena_Slice
    void arena_arena_Slice(unsafe::Pointer arena, go_any slice, int cap)
    {
        rec::slice(gocpp::recv(((userArena*)(arena))), slice, cap);
    }

    // arena_arena_Free is a wrapper around (*userArena).free.
    //
    //go:linkname arena_arena_Free arena.runtime_arena_arena_Free
    void arena_arena_Free(unsafe::Pointer arena)
    {
        rec::free(gocpp::recv(((userArena*)(arena))));
    }

    // arena_heapify takes a value that lives in an arena and makes a copy
    // of it on the heap. Values that don't live in an arena are returned unmodified.
    //
    //go:linkname arena_heapify arena.runtime_arena_heapify
    go_any arena_heapify(go_any s)
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
                    v = stringStructOf((std::string*)(e->data))->str;
                    break;
                case 1:
                    v = (runtime::slice*)(e->data)->array;
                    break;
                case 2:
                    v = e->data;
                    break;
                default:
                    gocpp::panic("arena: Clone only supports pointers, slices, and strings"s);
                    break;
            }
        }
        auto span = spanOf(uintptr_t(v));
        if(span == nullptr || ! span->isUserArenaChunk)
        {
            return s;
        }
        // Heap-allocate storage for a copy.
        go_any x = {};
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
                    auto len = (runtime::slice*)(e->data)->len;
                    auto et = (runtime::slicetype*)(unsafe::Pointer(t))->Elem;
                    auto sl = new(slice);
                    *sl = runtime::slice {makeslicecopy(et, len, len, (runtime::slice*)(e->data)->array), len, len};
                    auto xe = efaceOf(& x);
                    xe->_type = t;
                    xe->data = unsafe::Pointer(sl);
                    break;
                case 2:
                    auto et = (runtime::ptrtype*)(unsafe::Pointer(t))->Elem;
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

    // userArenaChunkBytes is the size of a user arena chunk.
    // userArenaChunkPages is the number of pages a user arena chunk uses.
    // userArenaChunkMaxAllocBytes is the maximum size of an object that can
    // be allocated from an arena. This number is chosen to cap worst-case
    // fragmentation of user arenas to 25%. Larger allocations are redirected
    // to the heap.
    void init()
    {
        if(userArenaChunkPages * pageSize != userArenaChunkBytes)
        {
            go_throw("user arena chunk size is not a multiple of the page size"s);
        }
        if(userArenaChunkBytes % physPageSize != 0)
        {
            go_throw("user arena chunk size is not a multiple of the physical page size"s);
        }
        if(userArenaChunkBytes < heapArenaBytes)
        {
            if(heapArenaBytes % userArenaChunkBytes != 0)
            {
                go_throw("user arena chunk size is smaller than a heap arena, but doesn't divide it"s);
            }
        }
        else
        {
            if(userArenaChunkBytes % heapArenaBytes != 0)
            {
                go_throw("user arena chunks size is larger than a heap arena, but not a multiple"s);
            }
        }
        lockInit(& userArenaState.lock, lockRankUserArenaState);
    }

    // userArenaChunkReserveBytes returns the amount of additional bytes to reserve for
    // heap metadata.
    uintptr_t userArenaChunkReserveBytes()
    {
        if(goexperiment::AllocHeaders)
        {
            return userArenaChunkBytes / goarch::PtrSize / 8 + gocpp::Sizeof<runtime::_type>();
        }
        return 0;
    }

    
    template<typename T> requires gocpp::GoStruct<T>
    userArena::operator T()
    {
        T result;
        result.fullList = this->fullList;
        result.active = this->active;
        result.refs = this->refs;
        result.defunct = this->defunct;
        return result;
    }

    template<typename T> requires gocpp::GoStruct<T>
    bool userArena::operator==(const T& ref) const
    {
        if (fullList != ref.fullList) return false;
        if (active != ref.active) return false;
        if (refs != ref.refs) return false;
        if (defunct != ref.defunct) return false;
        return true;
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

    std::ostream& operator<<(std::ostream& os, const struct userArena& value)
    {
        return value.PrintTo(os);
    }

    // newUserArena creates a new userArena ready to be used.
    struct userArena* newUserArena()
    {
        auto a = new(userArena);
        SetFinalizer(a, [=](struct userArena* a) mutable -> void
        {
            rec::free(gocpp::recv(a));
        });
        rec::refill(gocpp::recv(a));
        return a;
    }

    // new allocates a new object of the provided type into the arena, and returns
    // its pointer.
    //
    // This operation is not safe to call concurrently with other operations on the
    // same arena.
    unsafe::Pointer rec::go_new(struct userArena* a, golang::runtime::_type* typ)
    {
        return rec::alloc(gocpp::recv(a), typ, - 1);
    }

    // slice allocates a new slice backing store. slice must be a pointer to a slice
    // (i.e. *[]T), because userArenaSlice will update the slice directly.
    //
    // cap determines the capacity of the slice backing store and must be non-negative.
    //
    // This operation is not safe to call concurrently with other operations on the
    // same arena.
    void rec::slice(struct userArena* a, go_any sl, int cap)
    {
        if(cap < 0)
        {
            gocpp::panic("userArena.slice: negative cap"s);
        }
        auto i = efaceOf(& sl);
        auto typ = i->_type;
        if(typ->Kind_ & kindMask != kindPtr)
        {
            gocpp::panic("slice result of non-ptr type"s);
        }
        typ = (runtime::ptrtype*)(unsafe::Pointer(typ))->Elem;
        if(typ->Kind_ & kindMask != kindSlice)
        {
            gocpp::panic("slice of non-ptr-to-slice type"s);
        }
        typ = (runtime::slicetype*)(unsafe::Pointer(typ))->Elem;
        *((runtime::slice*)(i->data)) = runtime::slice {rec::alloc(gocpp::recv(a), typ, cap), cap, cap};
    }

    // free returns the userArena's chunks back to mheap and marks it as defunct.
    //
    // Must be called at most once for any given arena.
    //
    // This operation is not safe to call concurrently with other operations on the
    // same arena.
    void rec::free(struct userArena* a)
    {
        if(rec::Load(gocpp::recv(a->defunct)))
        {
            gocpp::panic("arena double free"s);
        }
        rec::Store(gocpp::recv(a->defunct), true);
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
            go_throw("full list doesn't match refs list in length"s);
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

    // alloc reserves space in the current chunk or calls refill and reserves space
    // in a new chunk. If cap is negative, the type will be taken literally, otherwise
    // it will be considered as an element type for a slice backing store with capacity
    // cap.
    unsafe::Pointer rec::alloc(struct userArena* a, golang::runtime::_type* typ, int cap)
    {
        auto s = a->active;
        unsafe::Pointer x = {};
        for(; ; )
        {
            x = rec::userArenaNextFree(gocpp::recv(s), typ, cap);
            if(x != nullptr)
            {
                break;
            }
            s = rec::refill(gocpp::recv(a));
        }
        return x;
    }

    // refill inserts the current arena chunk onto the full list and obtains a new
    // one, either from the partial list or allocating a new one, both from mheap.
    struct mspan* rec::refill(struct userArena* a)
    {
        auto s = a->active;
        if(s != nullptr)
        {
            if(rec::size(gocpp::recv(s->userArenaChunkFree)) > userArenaChunkMaxAllocBytes)
            {
                go_throw("wasted too much memory in an arena chunk"s);
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
                go_throw("out of memory"s);
            }
        }
        a->refs = append(a->refs, x);
        a->active = s;
        return s;
    }

    
    template<typename T> requires gocpp::GoStruct<T>
    liveUserArenaChunk::operator T()
    {
        T result;
        result.mspan = this->mspan;
        result.x = this->x;
        return result;
    }

    template<typename T> requires gocpp::GoStruct<T>
    bool liveUserArenaChunk::operator==(const T& ref) const
    {
        if (mspan != ref.mspan) return false;
        if (x != ref.x) return false;
        return true;
    }

    std::ostream& liveUserArenaChunk::PrintTo(std::ostream& os) const
    {
        os << '{';
        os << "" << mspan;
        os << " " << x;
        os << '}';
        return os;
    }

    std::ostream& operator<<(std::ostream& os, const struct liveUserArenaChunk& value)
    {
        return value.PrintTo(os);
    }

    struct gocpp_id_0
    {
        mutex lock;
        gocpp::slice<liveUserArenaChunk> reuse;
        gocpp::slice<liveUserArenaChunk> fault;

        using isGoStruct = void;

        template<typename T> requires gocpp::GoStruct<T>
        operator T()
        {
            T result;
            result.lock = this->lock;
            result.reuse = this->reuse;
            result.fault = this->fault;
            return result;
        }

        template<typename T> requires gocpp::GoStruct<T>
        bool operator==(const T& ref) const
        {
            if (lock != ref.lock) return false;
            if (reuse != ref.reuse) return false;
            if (fault != ref.fault) return false;
            return true;
        }

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

    std::ostream& operator<<(std::ostream& os, const struct gocpp_id_0& value)
    {
        return value.PrintTo(os);
    }


    gocpp_id_0 userArenaState;
    // userArenaNextFree reserves space in the user arena for an item of the specified
    // type. If cap is not -1, this is for an array of cap elements of type t.
    unsafe::Pointer rec::userArenaNextFree(struct mspan* s, golang::runtime::_type* typ, int cap)
    {
        auto size = typ->Size_;
        if(cap > 0)
        {
            if(size > ~ uintptr_t(0) / uintptr_t(cap))
            {
                go_throw("out of memory"s);
            }
            size *= uintptr_t(cap);
        }
        if(size == 0 || cap == 0)
        {
            return unsafe::Pointer(& zerobase);
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
            go_throw("malloc deadlock"s);
        }
        if(mp->gsignal == getg())
        {
            go_throw("malloc during signal"s);
        }
        mp->mallocing = 1;
        unsafe::Pointer ptr = {};
        if(typ->PtrBytes == 0)
        {
            auto [v, ok] = rec::takeFromBack(gocpp::recv(s->userArenaChunkFree), size, typ->Align_);
            if(ok)
            {
                ptr = unsafe::Pointer(v);
            }
        }
        else
        {
            auto [v, ok] = rec::takeFromFront(gocpp::recv(s->userArenaChunkFree), size, typ->Align_);
            if(ok)
            {
                ptr = unsafe::Pointer(v);
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
            go_throw("arena chunk needs zeroing, but should already be zeroed"s);
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
                go_throw("mallocgc called without a P or outside bootstrapping"s);
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

    // userArenaHeapBitsSetSliceType is the equivalent of heapBitsSetType but for
    // Go slice backing store values allocated in a user arena chunk. It sets up the
    // heap bitmap for n consecutive values with type typ allocated at address ptr.
    void userArenaHeapBitsSetSliceType(golang::runtime::_type* typ, int n, unsafe::Pointer ptr, struct mspan* s)
    {
        auto [mem, overflow] = math::MulUintptr(typ->Size_, uintptr_t(n));
        if(overflow || n < 0 || mem > maxAlloc)
        {
            gocpp::panic(plainError("runtime: allocation size out of range"s));
        }
        for(auto i = 0; i < n; i++)
        {
            userArenaHeapBitsSetType(typ, add(ptr, uintptr_t(i) * typ->Size_), s);
        }
    }

    // newUserArenaChunk allocates a user arena chunk, which maps to a single
    // heap arena and single span. Returns a pointer to the base of the chunk
    // (this is really important: we need to keep the chunk alive) and the span.
    std::tuple<unsafe::Pointer, struct mspan*> newUserArenaChunk()
    {
        if(gcphase == _GCmarktermination)
        {
            go_throw("newUserArenaChunk called with gcphase == _GCmarktermination"s);
        }
        deductAssistCredit(userArenaChunkBytes);
        auto mp = acquirem();
        if(mp->mallocing != 0)
        {
            go_throw("malloc deadlock"s);
        }
        if(mp->gsignal == getg())
        {
            go_throw("malloc during signal"s);
        }
        mp->mallocing = 1;
        // Allocate a new user arena.
        mspan* span = {};
        systemstack([=]() mutable -> void
        {
            span = rec::allocUserArenaChunk(gocpp::recv(mheap_));
        });
        if(span == nullptr)
        {
            go_throw("out of memory"s);
        }
        auto x = unsafe::Pointer(rec::base(gocpp::recv(span)));
        if(gcphase != _GCoff)
        {
            gcmarknewobject(span, rec::base(gocpp::recv(span)));
        }
        if(raceenabled)
        {
            racemalloc(unsafe::Pointer(rec::base(gocpp::recv(span))), span->elemsize);
        }
        if(msanenabled)
        {
            msanmalloc(unsafe::Pointer(rec::base(gocpp::recv(span))), span->elemsize);
        }
        if(asanenabled)
        {
            auto rzSize = computeRZlog(span->elemsize);
            span->elemsize -= rzSize;
            if(goexperiment::AllocHeaders)
            {
                span->largeType->Size_ = span->elemsize;
            }
            auto rzStart = rec::base(gocpp::recv(span)) + span->elemsize;
            span->userArenaChunkFree = makeAddrRange(rec::base(gocpp::recv(span)), rzStart);
            asanpoison(unsafe::Pointer(rzStart), span->limit - rzStart);
            asanunpoison(unsafe::Pointer(rec::base(gocpp::recv(span))), span->elemsize);
        }
        if(auto rate = MemProfileRate; rate > 0)
        {
            auto c = getMCache(mp);
            if(c == nullptr)
            {
                go_throw("newUserArenaChunk called without a P or outside bootstrapping"s);
            }
            if(rate != 1 && userArenaChunkBytes < c->nextSample)
            {
                c->nextSample -= userArenaChunkBytes;
            }
            else
            {
                profilealloc(mp, unsafe::Pointer(rec::base(gocpp::recv(span))), userArenaChunkBytes);
            }
        }
        mp->mallocing = 0;
        releasem(mp);
        if(auto t = (gocpp::Init<gcTrigger>([=](auto& x) {
            x.kind = gcTriggerHeap;
        })); rec::test(gocpp::recv(t)))
        {
            gcStart(t);
        }
        if(debug.malloc)
        {
            if(debug.allocfreetrace != 0)
            {
                tracealloc(unsafe::Pointer(rec::base(gocpp::recv(span))), userArenaChunkBytes, nullptr);
            }
            if(inittrace.active && inittrace.id == getg()->goid)
            {
                inittrace.bytes += uint64_t(userArenaChunkBytes);
            }
        }
        if(uintptr_t(x) % physPageSize != 0)
        {
            go_throw("user arena chunk is not aligned to the physical page size"s);
        }
        return {x, span};
    }

    // isUnusedUserArenaChunk indicates that the arena chunk has been set to fault
    // and doesn't contain any scannable memory anymore. However, it might still be
    // mSpanInUse as it sits on the quarantine list, since it needs to be swept.
    //
    // This is not safe to execute unless the caller has ownership of the mspan or
    // the world is stopped (preemption is prevented while the relevant state changes).
    //
    // This is really only meant to be used by accounting tests in the runtime to
    // distinguish when a span shouldn't be counted (since mSpanInUse might not be
    // enough).
    bool rec::isUnusedUserArenaChunk(struct mspan* s)
    {
        return s->isUserArenaChunk && s->spanclass == makeSpanClass(0, true);
    }

    // setUserArenaChunkToFault sets the address space for the user arena chunk to fault
    // and releases any underlying memory resources.
    //
    // Must be in a non-preemptible state to ensure the consistency of statistics
    // exported to MemStats.
    void rec::setUserArenaChunkToFault(struct mspan* s)
    {
        if(! s->isUserArenaChunk)
        {
            go_throw("invalid span in heapArena for user arena"s);
        }
        if(s->npages * pageSize != userArenaChunkBytes)
        {
            go_throw("span on userArena.faultList has invalid size"s);
        }
        s->spanclass = makeSpanClass(0, true);
        sysFault(unsafe::Pointer(rec::base(gocpp::recv(s))), s->npages * pageSize);
        rec::add(gocpp::recv(gcController.heapInUse), - int64_t(s->npages * pageSize));
        rec::Add(gocpp::recv(gcController.totalFree), int64_t(s->elemsize));
        auto stats = rec::acquire(gocpp::recv(memstats.heapStats));
        atomic::Xaddint64(& stats->committed, - int64_t(s->npages * pageSize));
        atomic::Xaddint64(& stats->inHeap, - int64_t(s->npages * pageSize));
        atomic::Xadd64(& stats->largeFreeCount, 1);
        atomic::Xadd64(& stats->largeFree, int64_t(s->elemsize));
        rec::release(gocpp::recv(memstats.heapStats));
        rec::update(gocpp::recv(gcController), - int64_t(s->elemsize), 0);
        if(raceenabled)
        {
            racefree(unsafe::Pointer(rec::base(gocpp::recv(s))), s->elemsize);
        }
        systemstack([=]() mutable -> void
        {
            lock(& mheap_.lock);
            rec::insert(gocpp::recv(mheap_.userArena.quarantineList), s);
            unlock(& mheap_.lock);
        });
    }

    // inUserArenaChunk returns true if p points to a user arena chunk.
    bool inUserArenaChunk(uintptr_t p)
    {
        auto s = spanOf(p);
        if(s == nullptr)
        {
            return false;
        }
        return s->isUserArenaChunk;
    }

    // freeUserArenaChunk releases the user arena represented by s back to the runtime.
    //
    // x must be a live pointer within s.
    //
    // The runtime will set the user arena to fault once it's safe (the GC is no longer running)
    // and then once the user arena is no longer referenced by the application, will allow it to
    // be reused.
    void freeUserArenaChunk(struct mspan* s, unsafe::Pointer x)
    {
        if(! s->isUserArenaChunk)
        {
            go_throw("span is not for a user arena"s);
        }
        if(s->npages * pageSize != userArenaChunkBytes)
        {
            go_throw("invalid user arena span size"s);
        }
        if(raceenabled)
        {
            racefree(unsafe::Pointer(rec::base(gocpp::recv(s))), s->elemsize);
        }
        if(msanenabled)
        {
            msanfree(unsafe::Pointer(rec::base(gocpp::recv(s))), s->elemsize);
        }
        if(asanenabled)
        {
            asanpoison(unsafe::Pointer(rec::base(gocpp::recv(s))), s->elemsize);
        }
        auto mp = acquirem();
        if(gcphase == _GCoff)
        {
            lock(& userArenaState.lock);
            auto faultList = userArenaState.fault;
            userArenaState.fault = nullptr;
            unlock(& userArenaState.lock);
            rec::setUserArenaChunkToFault(gocpp::recv(s));
            for(auto [gocpp_ignored, lc] : faultList)
            {
                rec::setUserArenaChunkToFault(gocpp::recv(lc.mspan));
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

    // allocUserArenaChunk attempts to reuse a free user arena chunk represented
    // as a span.
    //
    // Must be in a non-preemptible state to ensure the consistency of statistics
    // exported to MemStats.
    //
    // Acquires the heap lock. Must run on the system stack for that reason.
    //
    //go:systemstack
    struct mspan* rec::allocUserArenaChunk(struct mheap* h)
    {
        mspan* s = {};
        uintptr_t base = {};
        lock(& h->lock);
        if(! rec::isEmpty(gocpp::recv(h->userArena.readyList)))
        {
            s = h->userArena.readyList.first;
            rec::remove(gocpp::recv(h->userArena.readyList), s);
            base = rec::base(gocpp::recv(s));
        }
        else
        {
            auto hintList = & h->userArena.arenaHints;
            if(raceenabled)
            {
                hintList = & h->arenaHints;
            }
            auto [v, size] = rec::sysAlloc(gocpp::recv(h), userArenaChunkBytes, hintList, false);
            if(size % userArenaChunkBytes != 0)
            {
                go_throw("sysAlloc size is not divisible by userArenaChunkBytes"s);
            }
            if(size > userArenaChunkBytes)
            {
                for(auto i = userArenaChunkBytes; i < size; i += userArenaChunkBytes)
                {
                    auto s = rec::allocMSpanLocked(gocpp::recv(h));
                    rec::init(gocpp::recv(s), uintptr_t(v) + i, userArenaChunkPages);
                    rec::insertBack(gocpp::recv(h->userArena.readyList), s);
                }
                size = userArenaChunkBytes;
            }
            base = uintptr_t(v);
            if(base == 0)
            {
                unlock(& h->lock);
                return nullptr;
            }
            s = rec::allocMSpanLocked(gocpp::recv(h));
        }
        unlock(& h->lock);
        sysMap(unsafe::Pointer(base), userArenaChunkBytes, & gcController.heapReleased);
        sysUsed(unsafe::Pointer(base), userArenaChunkBytes, userArenaChunkBytes);
        auto spc = makeSpanClass(0, false);
        rec::initSpan(gocpp::recv(h), s, spanAllocHeap, spc, base, userArenaChunkPages);
        s->isUserArenaChunk = true;
        s->elemsize -= userArenaChunkReserveBytes();
        s->limit = rec::base(gocpp::recv(s)) + s->elemsize;
        s->freeindex = 1;
        s->allocCount = 1;
        rec::add(gocpp::recv(gcController.heapInUse), int64_t(userArenaChunkBytes));
        rec::add(gocpp::recv(gcController.heapReleased), - int64_t(userArenaChunkBytes));
        auto stats = rec::acquire(gocpp::recv(memstats.heapStats));
        atomic::Xaddint64(& stats->inHeap, int64_t(userArenaChunkBytes));
        atomic::Xaddint64(& stats->committed, int64_t(userArenaChunkBytes));
        atomic::Xadd64(& stats->largeAlloc, int64_t(s->elemsize));
        atomic::Xadd64(& stats->largeAllocCount, 1);
        rec::release(gocpp::recv(memstats.heapStats));
        rec::Add(gocpp::recv(gcController.totalAlloc), int64_t(s->elemsize));
        rec::update(gocpp::recv(gcController), int64_t(s->elemsize), 0);
        rec::initHeapBits(gocpp::recv(s), true);
        memclrNoHeapPointers(unsafe::Pointer(rec::base(gocpp::recv(s))), s->elemsize);
        s->needzero = 0;
        s->freeIndexForScan = 1;
        s->userArenaChunkFree = makeAddrRange(base, base + s->elemsize);
        rec::push(gocpp::recv(rec::fullSwept(gocpp::recv(h->central[spc].mcentral), h->sweepgen)), s);
        if(goexperiment::AllocHeaders)
        {
            *(uintptr_t*)(unsafe::Pointer(& s->largeType)) = uintptr_t(unsafe::Pointer(s->limit));
            *(uintptr_t*)(unsafe::Pointer(& s->largeType->GCData)) = s->limit + gocpp::Sizeof<runtime::_type>();
            s->largeType->PtrBytes = 0;
            s->largeType->Size_ = s->elemsize;
        }
        return s;
    }

}

