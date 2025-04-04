// generated by GoCpp from file '$(ImportDir)/runtime/mfinal.go'
#pragma once

#include <functional>
#include <string>
#include <tuple>
#include <vector>

#include "golang/runtime/mfinal.fwd.h"
#include "gocpp/support.h"

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
#include "golang/runtime/mprof.h"
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
    struct finblock
    {
        /* sys::NotInHeap _; [Known incomplete type] */
        finblock* alllink;
        finblock* next;
        uint32_t cnt;
        /* int32_t _; [Known incomplete type] */
        /* gocpp::array<finalizer, (_FinBlockSize - 2 * goarch::PtrSize - 2 * 4) / gocpp::Sizeof<finalizer>()> fin; [Known incomplete type] */

        using isGoStruct = void;

        template<typename T> requires gocpp::GoStruct<T>
        operator T();

        template<typename T> requires gocpp::GoStruct<T>
        bool operator==(const T& ref) const;

        std::ostream& PrintTo(std::ostream& os) const;
    };

    std::ostream& operator<<(std::ostream& os, const struct finblock& value);
    struct finalizer
    {
        /* funcval* fn; [Known incomplete type] */
        unsafe::Pointer arg;
        uintptr_t nret;
        _type* fint;
        ptrtype* ot;

        using isGoStruct = void;

        template<typename T> requires gocpp::GoStruct<T>
        operator T();

        template<typename T> requires gocpp::GoStruct<T>
        bool operator==(const T& ref) const;

        std::ostream& PrintTo(std::ostream& os) const;
    };

    std::ostream& operator<<(std::ostream& os, const struct finalizer& value);
    extern gocpp::array_base<unsigned char> finalizer1;
    void lockRankMayQueueFinalizer();
    /* void queuefinalizer(unsafe::Pointer p, funcval* fn, uintptr_t nret, _type* fint, ptrtype* ot); [Ignored, known name conflict] */ 
    /* void iterate_finq(std::function<void (funcval*, unsafe::Pointer, uintptr_t, _type*, ptrtype*)> callback); [Ignored, known name conflict] */ 
    /* g* wakefing(); [Ignored, known name conflict] */ 
    void createfing();
    /* bool finalizercommit(g* gp, unsafe::Pointer lock); [Ignored, known name conflict] */ 
    void runfinq();
    bool isGoPointerWithoutSpan(unsafe::Pointer p);
    bool blockUntilEmptyFinalizerQueue(int64_t timeout);
    void SetFinalizer(go_any obj, go_any finalizer);
    void KeepAlive(go_any x);
}

