// generated by GoCpp from file '$(ImportDir)/runtime/mgcsweep.go'
#pragma once

#include <functional>
#include <string>
#include <tuple>
#include <vector>

#include "golang/runtime/mgcsweep.fwd.h"
#include "gocpp/support.h"

#include "golang/internal/abi/type.h"
#include "golang/internal/chacha8rand/chacha8.h"
// #include "golang/internal/cpu/cpu.h"  [Ignored, known errors]
// #include "golang/runtime/cgocall.h"  [Ignored, known errors]
#include "golang/runtime/chan.h"
#include "golang/runtime/coro.h"
#include "golang/runtime/debuglog_off.h"
#include "golang/runtime/internal/atomic/types.h"
#include "golang/runtime/internal/sys/nih.h"
// #include "golang/runtime/lockrank.h"  [Ignored, known errors]
// #include "golang/runtime/lockrank_off.h"  [Ignored, known errors]
#include "golang/runtime/malloc.h"
// #include "golang/runtime/mbitmap_allocheaders.h"  [Ignored, known errors]
// #include "golang/runtime/mcache.h"  [Ignored, known errors]
#include "golang/runtime/mcentral.h"
#include "golang/runtime/mcheckmark.h"
#include "golang/runtime/mfixalloc.h"
// #include "golang/runtime/mgcscavenge.h"  [Ignored, known errors]
#include "golang/runtime/mheap.h"
#include "golang/runtime/mpagealloc.h"
#include "golang/runtime/mpallocbits.h"
#include "golang/runtime/mprof.h"
#include "golang/runtime/mranges.h"
#include "golang/runtime/mspanset.h"
#include "golang/runtime/mstats.h"
// #include "golang/runtime/os_windows.h"  [Ignored, known errors]
#include "golang/runtime/panic.h"
#include "golang/runtime/runtime2.h"
// #include "golang/runtime/signal_windows.h"  [Ignored, known errors]
// #include "golang/runtime/symtab.h"  [Ignored, known errors]
// #include "golang/runtime/time.h"  [Ignored, known errors]
#include "golang/runtime/trace2buf.h"
// #include "golang/runtime/trace2runtime.h"  [Ignored, known errors]
#include "golang/runtime/trace2status.h"
#include "golang/runtime/trace2time.h"

namespace golang::runtime
{
    struct sweepdata
    {
        mutex lock;
        g* g;
        bool parked;
        activeSweep active;
        sweepClass centralIndex;

        using isGoStruct = void;

        template<typename T> requires gocpp::GoStruct<T>
        operator T();

        template<typename T> requires gocpp::GoStruct<T>
        bool operator==(const T& ref) const;

        std::ostream& PrintTo(std::ostream& os) const;
    };

    std::ostream& operator<<(std::ostream& os, const struct sweepdata& value);
    sweepClass load(sweepClass* s);
    void update(sweepClass* s, sweepClass sNew);
    void clear(sweepClass* s);
    std::tuple<spanClass, bool> split(sweepClass s);
    mspan* nextSpanForSweep(struct mheap* h);
    struct activeSweep
    {
        atomic::Uint32 state;

        using isGoStruct = void;

        template<typename T> requires gocpp::GoStruct<T>
        operator T();

        template<typename T> requires gocpp::GoStruct<T>
        bool operator==(const T& ref) const;

        std::ostream& PrintTo(std::ostream& os) const;
    };

    std::ostream& operator<<(std::ostream& os, const struct activeSweep& value);
    sweepLocker begin(struct activeSweep* a);
    void end(struct activeSweep* a, sweepLocker sl);
    bool markDrained(struct activeSweep* a);
    uint32_t sweepers(struct activeSweep* a);
    bool isDone(struct activeSweep* a);
    void reset(struct activeSweep* a);
    void finishsweep_m();
    void bgsweep(gocpp::channel<int> c);
    struct sweepLocker
    {
        uint32_t sweepGen;
        bool valid;

        using isGoStruct = void;

        template<typename T> requires gocpp::GoStruct<T>
        operator T();

        template<typename T> requires gocpp::GoStruct<T>
        bool operator==(const T& ref) const;

        std::ostream& PrintTo(std::ostream& os) const;
    };

    std::ostream& operator<<(std::ostream& os, const struct sweepLocker& value);
    struct sweepLocked
    {

        using isGoStruct = void;

        template<typename T> requires gocpp::GoStruct<T>
        operator T();

        template<typename T> requires gocpp::GoStruct<T>
        bool operator==(const T& ref) const;

        std::ostream& PrintTo(std::ostream& os) const;
    };

    std::ostream& operator<<(std::ostream& os, const struct sweepLocked& value);
    std::tuple<sweepLocked, bool> tryAcquire(struct sweepLocker* l, mspan* s);
    uintptr_t sweepone();
    bool isSweepDone();
    void ensureSwept(struct mspan* s);
    bool sweep(struct sweepLocked* sl, bool preserve);
    void reportZombies(struct mspan* s);
    void deductSweepCredit(uintptr_t spanBytes, uintptr_t callerSweepPages);
    void clobberfree(unsafe::Pointer x, uintptr_t size);
    void gcPaceSweeper(uint64_t trigger);
}

