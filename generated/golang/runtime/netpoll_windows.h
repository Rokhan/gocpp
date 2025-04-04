// generated by GoCpp from file '$(ImportDir)/runtime/netpoll_windows.go'
#pragma once

#include <functional>
#include <string>
#include <tuple>
#include <vector>

#include "golang/runtime/netpoll_windows.fwd.h"
#include "gocpp/support.h"

// #include "golang/runtime/defs_windows.h"  [Ignored, known errors]
#include "golang/runtime/internal/atomic/types.h"
#include "golang/runtime/internal/sys/nih.h"
// #include "golang/runtime/lockrank_off.h"  [Ignored, known errors]
// #include "golang/runtime/netpoll.h"  [Ignored, known errors]
#include "golang/runtime/proc.h"
#include "golang/runtime/runtime2.h"
// #include "golang/runtime/time.h"  [Ignored, known errors]

namespace golang::runtime
{
    struct net_op
    {
        overlapped o;
        pollDesc* pd;
        int32_t mode;
        int32_t errno;
        uint32_t qty;

        using isGoStruct = void;

        template<typename T> requires gocpp::GoStruct<T>
        operator T();

        template<typename T> requires gocpp::GoStruct<T>
        bool operator==(const T& ref) const;

        std::ostream& PrintTo(std::ostream& os) const;
    };

    std::ostream& operator<<(std::ostream& os, const struct net_op& value);
    struct overlappedEntry
    {
        pollDesc* key;
        net_op* op;
        uintptr_t internal;
        uint32_t qty;

        using isGoStruct = void;

        template<typename T> requires gocpp::GoStruct<T>
        operator T();

        template<typename T> requires gocpp::GoStruct<T>
        bool operator==(const T& ref) const;

        std::ostream& PrintTo(std::ostream& os) const;
    };

    std::ostream& operator<<(std::ostream& os, const struct overlappedEntry& value);
    extern uintptr_t iocphandle;
    extern atomic::Uint32 netpollWakeSig;
    void netpollinit();
    bool netpollIsPollDescriptor(uintptr_t fd);
    int32_t netpollopen(uintptr_t fd, pollDesc* pd);
    int32_t netpollclose(uintptr_t fd);
    void netpollarm(pollDesc* pd, int mode);
    void netpollBreak();
    std::tuple<gList, int32_t> netpoll(int64_t delay);
    int32_t handlecompletion(gList* toRun, net_op* op, int32_t errno, uint32_t qty);
}

