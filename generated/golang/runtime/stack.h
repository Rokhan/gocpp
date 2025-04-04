// generated by GoCpp from file '$(ImportDir)/runtime/stack.go'
#pragma once

#include <functional>
#include <string>
#include <tuple>
#include <vector>

#include "golang/runtime/stack.fwd.h"
#include "gocpp/support.h"

// #include "golang/internal/abi/symtab.h"  [Ignored, known errors]
#include "golang/internal/abi/type.h"
#include "golang/internal/chacha8rand/chacha8.h"
// #include "golang/runtime/cgocall.h"  [Ignored, known errors]
#include "golang/runtime/chan.h"
#include "golang/runtime/coro.h"
#include "golang/runtime/debuglog_off.h"
#include "golang/runtime/internal/atomic/types.h"
#include "golang/runtime/internal/sys/nih.h"
// #include "golang/runtime/lockrank.h"  [Ignored, known errors]
// #include "golang/runtime/lockrank_off.h"  [Ignored, known errors]
// #include "golang/runtime/mcache.h"  [Ignored, known errors]
#include "golang/runtime/mheap.h"
#include "golang/runtime/mprof.h"
#include "golang/runtime/mranges.h"
// #include "golang/runtime/os_windows.h"  [Ignored, known errors]
#include "golang/runtime/panic.h"
#include "golang/runtime/plugin.h"
#include "golang/runtime/proc.h"
#include "golang/runtime/runtime2.h"
// #include "golang/runtime/signal_windows.h"  [Ignored, known errors]
#include "golang/runtime/stkframe.h"
// #include "golang/runtime/symtab.h"  [Ignored, known errors]
// #include "golang/runtime/time.h"  [Ignored, known errors]
#include "golang/runtime/trace2buf.h"
// #include "golang/runtime/trace2runtime.h"  [Ignored, known errors]
#include "golang/runtime/trace2status.h"
#include "golang/runtime/trace2time.h"

namespace golang::runtime
{
    extern long stackPoisonCopy;
    struct stackpoolItem
    {
        sys::NotInHeap _;
        mutex mu;
        /* mSpanList span; [Known incomplete type] */

        using isGoStruct = void;

        template<typename T> requires gocpp::GoStruct<T>
        operator T();

        template<typename T> requires gocpp::GoStruct<T>
        bool operator==(const T& ref) const;

        std::ostream& PrintTo(std::ostream& os) const;
    };

    std::ostream& operator<<(std::ostream& os, const struct stackpoolItem& value);
    void stackinit();
    int stacklog2(uintptr_t n);
    gclinkptr stackpoolalloc(uint8_t order);
    void stackpoolfree(gclinkptr x, uint8_t order);
    void stackcacherefill(mcache* c, uint8_t order);
    void stackcacherelease(mcache* c, uint8_t order);
    void stackcache_clear(mcache* c);
    stack stackalloc(uint32_t n);
    void stackfree(stack stk);
    extern uintptr_t maxstacksize;
    extern uintptr_t maxstackceiling;
    extern gocpp::slice<std::string> ptrnames;
    struct adjustinfo
    {
        stack old;
        uintptr_t delta;
        uintptr_t sghi;

        using isGoStruct = void;

        template<typename T> requires gocpp::GoStruct<T>
        operator T();

        template<typename T> requires gocpp::GoStruct<T>
        bool operator==(const T& ref) const;

        std::ostream& PrintTo(std::ostream& os) const;
    };

    std::ostream& operator<<(std::ostream& os, const struct adjustinfo& value);
    void adjustpointer(adjustinfo* adjinfo, unsafe::Pointer vpp);
    struct bitvector
    {
        int32_t n;
        uint8_t* bytedata;

        using isGoStruct = void;

        template<typename T> requires gocpp::GoStruct<T>
        operator T();

        template<typename T> requires gocpp::GoStruct<T>
        bool operator==(const T& ref) const;

        std::ostream& PrintTo(std::ostream& os) const;
    };

    std::ostream& operator<<(std::ostream& os, const struct bitvector& value);
    uint8_t ptrbit(struct bitvector* bv, uintptr_t i);
    void adjustpointers(unsafe::Pointer scanp, bitvector* bv, adjustinfo* adjinfo, funcInfo f);
    void adjustframe(stkframe* frame, adjustinfo* adjinfo);
    void adjustctxt(g* gp, adjustinfo* adjinfo);
    void adjustdefers(g* gp, adjustinfo* adjinfo);
    void adjustpanics(g* gp, adjustinfo* adjinfo);
    void adjustsudogs(g* gp, adjustinfo* adjinfo);
    void fillstack(stack stk, unsigned char b);
    uintptr_t findsghi(g* gp, stack stk);
    uintptr_t syncadjustsudogs(g* gp, uintptr_t used, adjustinfo* adjinfo);
    void copystack(g* gp, uintptr_t newsize);
    int32_t round2(int32_t x);
    void newstack();
    void nilfunc();
    void gostartcallfn(gobuf* gobuf, funcval* fv);
    bool isShrinkStackSafe(g* gp);
    void shrinkstack(g* gp);
    void freeStackSpans();
    struct stackObjectRecord
    {
        int32_t off;
        int32_t size;
        int32_t _ptrdata;
        uint32_t gcdataoff;

        using isGoStruct = void;

        template<typename T> requires gocpp::GoStruct<T>
        operator T();

        template<typename T> requires gocpp::GoStruct<T>
        bool operator==(const T& ref) const;

        std::ostream& PrintTo(std::ostream& os) const;
    };

    std::ostream& operator<<(std::ostream& os, const struct stackObjectRecord& value);
    bool useGCProg(struct stackObjectRecord* r);
    uintptr_t ptrdata(struct stackObjectRecord* r);
    unsigned char* gcdata(struct stackObjectRecord* r);
    void morestackc();
    extern uint32_t startingStackSize;
    void gcComputeStartingStackSize();
}

