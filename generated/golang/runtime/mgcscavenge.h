// generated by GoCpp from file '$(ImportDir)/runtime/mgcscavenge.go'
#pragma once

#include <functional>
#include <string>
#include <tuple>
#include <vector>

#include "golang/runtime/mgcscavenge.fwd.h"
#include "gocpp/support.h"

#include "golang/internal/abi/type.h"
#include "golang/internal/chacha8rand/chacha8.h"
#include "golang/runtime/cgocall.h"
#include "golang/runtime/chan.h"
#include "golang/runtime/coro.h"
#include "golang/runtime/debuglog_off.h"
#include "golang/runtime/internal/atomic/types.h"
#include "golang/runtime/internal/sys/nih.h"
#include "golang/runtime/lockrank.h"
#include "golang/runtime/lockrank_off.h"
#include "golang/runtime/mpagealloc.h"
#include "golang/runtime/mpallocbits.h"
#include "golang/runtime/mprof.h"
#include "golang/runtime/mranges.h"
#include "golang/runtime/mstats.h"
#include "golang/runtime/os_windows.h"
#include "golang/runtime/panic.h"
#include "golang/runtime/runtime2.h"
#include "golang/runtime/signal_windows.h"
#include "golang/runtime/symtab.h"
#include "golang/runtime/time.h"
#include "golang/runtime/trace2buf.h"
#include "golang/runtime/trace2runtime.h"
#include "golang/runtime/trace2status.h"
#include "golang/runtime/trace2time.h"

namespace golang::runtime
{
    uint64_t heapRetained();
    void gcPaceScavenger(int64_t memoryLimit, uint64_t heapGoal, uint64_t lastHeapGoal);
    extern gocpp_id_0 scavenge;
    void bgscavenge(gocpp::channel<int> c);
    void printScavTrace(uintptr_t releasedBg, uintptr_t releasedEager, bool forced);
    uint64_t fillAligned(uint64_t x, unsigned int m);
    struct atomicScavChunkData
    {
        atomic::Uint64 value;

        using isGoStruct = void;

        template<typename T> requires gocpp::GoStruct<T>
        operator T();

        template<typename T> requires gocpp::GoStruct<T>
        bool operator==(const T& ref) const;

        std::ostream& PrintTo(std::ostream& os) const;
    };

    std::ostream& operator<<(std::ostream& os, const struct atomicScavChunkData& value);
    struct scavChunkData
    {
        uint16_t inUse;
        uint16_t lastInUse;
        uint32_t gen;
        golang::runtime::scavChunkFlags scavChunkFlags;

        using isGoStruct = void;

        template<typename T> requires gocpp::GoStruct<T>
        operator T();

        template<typename T> requires gocpp::GoStruct<T>
        bool operator==(const T& ref) const;

        std::ostream& PrintTo(std::ostream& os) const;
    };

    std::ostream& operator<<(std::ostream& os, const struct scavChunkData& value);
    struct scavChunkData unpackScavChunkData(uint64_t sc);
    struct piController
    {
        double kp;
        double ti;
        double tt;
        double min;
        double max;
        double errIntegral;
        bool errOverflow;
        bool inputOverflow;

        using isGoStruct = void;

        template<typename T> requires gocpp::GoStruct<T>
        operator T();

        template<typename T> requires gocpp::GoStruct<T>
        bool operator==(const T& ref) const;

        std::ostream& PrintTo(std::ostream& os) const;
    };

    std::ostream& operator<<(std::ostream& os, const struct piController& value);
    struct scavengerState
    {
        mutex lock;
        g* g;
        bool parked;
        timer* timer;
        atomic::Uint32 sysmonWake;
        double targetCPUFraction;
        double sleepRatio;
        piController sleepController;
        int64_t controllerCooldown;
        bool printControllerReset;
        std::function<int64_t (int64_t n)> sleepStub;
        std::function<std::tuple<uintptr_t, int64_t> (uintptr_t n)> scavenge;
        std::function<bool ()> shouldStop;
        std::function<int32_t ()> gomaxprocs;

        using isGoStruct = void;

        template<typename T> requires gocpp::GoStruct<T>
        operator T();

        template<typename T> requires gocpp::GoStruct<T>
        bool operator==(const T& ref) const;

        std::ostream& PrintTo(std::ostream& os) const;
    };

    std::ostream& operator<<(std::ostream& os, const struct scavengerState& value);
    struct scavengeIndex
    {
        gocpp::slice<atomicScavChunkData> chunks;
        atomic::Uintptr min;
        atomic::Uintptr max;
        atomic::Uintptr minHeapIdx;
        atomicOffAddr searchAddrBg;
        atomicOffAddr searchAddrForce;
        offAddr freeHWM;
        uint32_t gen;
        bool test;

        using isGoStruct = void;

        template<typename T> requires gocpp::GoStruct<T>
        operator T();

        template<typename T> requires gocpp::GoStruct<T>
        bool operator==(const T& ref) const;

        std::ostream& PrintTo(std::ostream& os) const;
    };

    std::ostream& operator<<(std::ostream& os, const struct scavengeIndex& value);
    extern scavengerState scavenger;

    namespace rec
    {
        void init(struct scavengerState* s);
        void park(struct scavengerState* s);
        void ready(struct scavengerState* s);
        void wake(struct scavengerState* s);
        void sleep(struct scavengerState* s, double worked);
        void controllerFailed(struct scavengerState* s);
        std::tuple<uintptr_t, double> run(struct scavengerState* s);
        uintptr_t scavenge(struct pageAlloc* p, uintptr_t nbytes, std::function<bool ()> shouldStop, bool force);
        uintptr_t scavengeOne(struct pageAlloc* p, golang::runtime::chunkIdx ci, unsigned int searchIdx, uintptr_t max);
        std::tuple<unsigned int, unsigned int> findScavengeCandidate(struct pallocData* m, unsigned int searchIdx, uintptr_t minimum, uintptr_t max);
        uintptr_t init(struct scavengeIndex* s, bool test, golang::runtime::sysMemStat* sysStat);
        uintptr_t grow(struct scavengeIndex* s, uintptr_t base, uintptr_t limit, golang::runtime::sysMemStat* sysStat);
        std::tuple<runtime::chunkIdx, unsigned int> find(struct scavengeIndex* s, bool force);
        void alloc(struct scavengeIndex* s, golang::runtime::chunkIdx ci, unsigned int npages);
        void free(struct scavengeIndex* s, golang::runtime::chunkIdx ci, unsigned int page, unsigned int npages);
        void nextGen(struct scavengeIndex* s);
        void setEmpty(struct scavengeIndex* s, golang::runtime::chunkIdx ci);
        struct scavChunkData load(struct atomicScavChunkData* sc);
        void store(struct atomicScavChunkData* sc, struct scavChunkData ssc);
        uint64_t pack(struct scavChunkData sc);
        bool isEmpty(golang::runtime::scavChunkFlags* sc);
        void setEmpty(golang::runtime::scavChunkFlags* sc);
        void setNonEmpty(golang::runtime::scavChunkFlags* sc);
        bool shouldScavenge(struct scavChunkData sc, uint32_t currGen, bool force);
        void alloc(struct scavChunkData* sc, unsigned int npages, uint32_t newGen);
        void free(struct scavChunkData* sc, unsigned int npages, uint32_t newGen);
        std::tuple<double, bool> next(struct piController* c, double input, double setpoint, double period);
        void reset(struct piController* c);
    }
}

