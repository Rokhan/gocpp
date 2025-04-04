// generated by GoCpp from file '$(ImportDir)/runtime/netpoll.go'
#pragma once

#include <functional>
#include <string>
#include <tuple>
#include <vector>

#include "golang/runtime/netpoll.fwd.h"
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
#include "golang/runtime/proc.h"
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
    struct pollDesc
    {
        sys::NotInHeap _;
        pollDesc* link;
        uintptr_t fd;
        atomic::Uintptr fdseq;
        atomic::Uint32 atomicInfo;
        atomic::Uintptr rg;
        atomic::Uintptr wg;
        mutex lock;
        bool closing;
        uint32_t user;
        uintptr_t rseq;
        timer rt;
        int64_t rd;
        uintptr_t wseq;
        timer wt;
        int64_t wd;
        pollDesc* self;

        using isGoStruct = void;

        template<typename T> requires gocpp::GoStruct<T>
        operator T();

        template<typename T> requires gocpp::GoStruct<T>
        bool operator==(const T& ref) const;

        std::ostream& PrintTo(std::ostream& os) const;
    };

    std::ostream& operator<<(std::ostream& os, const struct pollDesc& value);
    bool closing(pollInfo i);
    bool eventErr(pollInfo i);
    bool expiredReadDeadline(pollInfo i);
    bool expiredWriteDeadline(pollInfo i);
    pollInfo info(struct pollDesc* pd);
    void publishInfo(struct pollDesc* pd);
    void setEventErr(struct pollDesc* pd, bool b, uintptr_t seq);
    struct pollCache
    {
        mutex lock;
        pollDesc* first;

        using isGoStruct = void;

        template<typename T> requires gocpp::GoStruct<T>
        operator T();

        template<typename T> requires gocpp::GoStruct<T>
        bool operator==(const T& ref) const;

        std::ostream& PrintTo(std::ostream& os) const;
    };

    std::ostream& operator<<(std::ostream& os, const struct pollCache& value);
    void poll_runtime_pollServerInit();
    void netpollGenericInit();
    bool netpollinited();
    bool poll_runtime_isPollServerDescriptor(uintptr_t fd);
    std::tuple<pollDesc*, int> poll_runtime_pollOpen(uintptr_t fd);
    void poll_runtime_pollClose(pollDesc* pd);
    void free(struct pollCache* c, pollDesc* pd);
    int poll_runtime_pollReset(pollDesc* pd, int mode);
    int poll_runtime_pollWait(pollDesc* pd, int mode);
    void poll_runtime_pollWaitCanceled(pollDesc* pd, int mode);
    void poll_runtime_pollSetDeadline(pollDesc* pd, int64_t d, int mode);
    void poll_runtime_pollUnblock(pollDesc* pd);
    int32_t netpollready(gList* toRun, pollDesc* pd, int32_t mode);
    int netpollcheckerr(pollDesc* pd, int32_t mode);
    bool netpollblockcommit(g* gp, unsafe::Pointer gpp);
    void netpollgoready(g* gp, int traceskip);
    bool netpollblock(pollDesc* pd, int32_t mode, bool waitio);
    g* netpollunblock(pollDesc* pd, int32_t mode, bool ioready, int32_t* delta);
    void netpolldeadlineimpl(pollDesc* pd, uintptr_t seq, bool read, bool write);
    void netpollDeadline(go_any arg, uintptr_t seq);
    void netpollReadDeadline(go_any arg, uintptr_t seq);
    void netpollWriteDeadline(go_any arg, uintptr_t seq);
    bool netpollAnyWaiters();
    void netpollAdjustWaiters(int32_t delta);
    pollDesc* alloc(struct pollCache* c);
    go_any makeArg(struct pollDesc* pd);
    extern go_any pdEface;
    extern _type* pdType;
}

