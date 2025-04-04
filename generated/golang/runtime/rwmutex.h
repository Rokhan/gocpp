// generated by GoCpp from file '$(ImportDir)/runtime/rwmutex.go'
#pragma once

#include <functional>
#include <string>
#include <tuple>
#include <vector>

#include "golang/runtime/rwmutex.fwd.h"
#include "gocpp/support.h"

#include "golang/runtime/internal/atomic/types.h"
// #include "golang/runtime/lockrank.h"  [Ignored, known errors]
// #include "golang/runtime/lockrank_off.h"  [Ignored, known errors]
#include "golang/runtime/runtime2.h"

namespace golang::runtime
{
    struct rwmutex
    {
        mutex rLock;
        muintptr readers;
        uint32_t readerPass;
        mutex wLock;
        muintptr writer;
        atomic::Int32 readerCount;
        atomic::Int32 readerWait;
        lockRank readRank;

        using isGoStruct = void;

        template<typename T> requires gocpp::GoStruct<T>
        operator T();

        template<typename T> requires gocpp::GoStruct<T>
        bool operator==(const T& ref) const;

        std::ostream& PrintTo(std::ostream& os) const;
    };

    std::ostream& operator<<(std::ostream& os, const struct rwmutex& value);
    void init(struct rwmutex* rw, lockRank readRank, lockRank readRankInternal, lockRank writeRank);
    void rlock(struct rwmutex* rw);
    void runlock(struct rwmutex* rw);
    void lock(struct rwmutex* rw);
    void unlock(struct rwmutex* rw);
}

