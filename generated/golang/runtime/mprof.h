// generated by GoCpp from file '$(ImportDir)/runtime/mprof.go'
#pragma once

#include <functional>
#include <string>
#include <tuple>
#include <vector>

#include "golang/runtime/mprof.fwd.h"
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
    extern mutex profInsertLock;
    extern mutex profBlockLock;
    extern mutex profMemActiveLock;
    struct bucket
    {
        sys::NotInHeap _1;
        bucket* next;
        bucket* allnext;
        golang::runtime::bucketType typ;
        uintptr_t hash;
        uintptr_t size;
        uintptr_t nstk;

        using isGoStruct = void;

        template<typename T> requires gocpp::GoStruct<T>
        operator T();

        template<typename T> requires gocpp::GoStruct<T>
        bool operator==(const T& ref) const;

        std::ostream& PrintTo(std::ostream& os) const;
    };

    std::ostream& operator<<(std::ostream& os, const struct bucket& value);
    struct memRecordCycle
    {
        uintptr_t allocs;
        uintptr_t frees;
        uintptr_t alloc_bytes;
        uintptr_t free_bytes;

        using isGoStruct = void;

        template<typename T> requires gocpp::GoStruct<T>
        operator T();

        template<typename T> requires gocpp::GoStruct<T>
        bool operator==(const T& ref) const;

        std::ostream& PrintTo(std::ostream& os) const;
    };

    std::ostream& operator<<(std::ostream& os, const struct memRecordCycle& value);
    struct blockRecord
    {
        double count;
        int64_t cycles;

        using isGoStruct = void;

        template<typename T> requires gocpp::GoStruct<T>
        operator T();

        template<typename T> requires gocpp::GoStruct<T>
        bool operator==(const T& ref) const;

        std::ostream& PrintTo(std::ostream& os) const;
    };

    std::ostream& operator<<(std::ostream& os, const struct blockRecord& value);
    extern atomic::UnsafePointer mbuckets;
    extern atomic::UnsafePointer bbuckets;
    extern atomic::UnsafePointer xbuckets;
    extern atomic::UnsafePointer buckhash;
    struct mProfCycleHolder
    {
        /* atomic::Uint32 value; [Known incomplete type] */

        using isGoStruct = void;

        template<typename T> requires gocpp::GoStruct<T>
        operator T();

        template<typename T> requires gocpp::GoStruct<T>
        bool operator==(const T& ref) const;

        std::ostream& PrintTo(std::ostream& os) const;
    };

    std::ostream& operator<<(std::ostream& os, const struct mProfCycleHolder& value);
    struct bucket* newBucket(golang::runtime::bucketType typ, int nstk);
    struct bucket* stkbucket(golang::runtime::bucketType typ, uintptr_t size, gocpp::slice<uintptr_t> stk, bool alloc);
    bool eqslice(gocpp::slice<uintptr_t> x, gocpp::slice<uintptr_t> y);
    void mProf_NextCycle();
    void mProf_Flush();
    void mProf_FlushLocked(uint32_t index);
    void mProf_PostSweep();
    void mProf_Malloc(unsafe::Pointer p, uintptr_t size);
    void mProf_Free(struct bucket* b, uintptr_t size);
    extern uint64_t blockprofilerate;
    void SetBlockProfileRate(int rate);
    void blockevent(int64_t cycles, int skip);
    bool blocksampled(int64_t cycles, int64_t rate);
    void saveblockevent(int64_t cycles, int64_t rate, int skip, golang::runtime::bucketType which);
    struct lockTimer
    {
        /* mutex* lock; [Known incomplete type] */
        int64_t timeRate;
        int64_t timeStart;
        int64_t tickStart;

        using isGoStruct = void;

        template<typename T> requires gocpp::GoStruct<T>
        operator T();

        template<typename T> requires gocpp::GoStruct<T>
        bool operator==(const T& ref) const;

        std::ostream& PrintTo(std::ostream& os) const;
    };

    std::ostream& operator<<(std::ostream& os, const struct lockTimer& value);
    struct mLockProfile
    {
        /* atomic::Int64 waitTime; [Known incomplete type] */
        gocpp::array<uintptr_t, maxStack> stack;
        uintptr_t pending;
        int64_t cycles;
        int64_t cyclesLost;
        bool disabled;

        using isGoStruct = void;

        template<typename T> requires gocpp::GoStruct<T>
        operator T();

        template<typename T> requires gocpp::GoStruct<T>
        bool operator==(const T& ref) const;

        std::ostream& PrintTo(std::ostream& os) const;
    };

    std::ostream& operator<<(std::ostream& os, const struct mLockProfile& value);
    void saveBlockEventStack(int64_t cycles, int64_t rate, gocpp::slice<uintptr_t> stk, golang::runtime::bucketType which);
    extern uint64_t mutexprofilerate;
    int SetMutexProfileFraction(int rate);
    void mutexevent(int64_t cycles, int skip);
    struct StackRecord
    {
        gocpp::array<uintptr_t, 32> Stack0;

        using isGoStruct = void;

        template<typename T> requires gocpp::GoStruct<T>
        operator T();

        template<typename T> requires gocpp::GoStruct<T>
        bool operator==(const T& ref) const;

        std::ostream& PrintTo(std::ostream& os) const;
    };

    std::ostream& operator<<(std::ostream& os, const struct StackRecord& value);
    extern int MemProfileRate;
    extern bool disableMemoryProfiling;
    struct MemProfileRecord
    {
        int64_t AllocBytes;
        int64_t FreeBytes;
        int64_t AllocObjects;
        int64_t FreeObjects;
        gocpp::array<uintptr_t, 32> Stack0;

        using isGoStruct = void;

        template<typename T> requires gocpp::GoStruct<T>
        operator T();

        template<typename T> requires gocpp::GoStruct<T>
        bool operator==(const T& ref) const;

        std::ostream& PrintTo(std::ostream& os) const;
    };

    std::ostream& operator<<(std::ostream& os, const struct MemProfileRecord& value);
    std::tuple<int, bool> MemProfile(gocpp::slice<MemProfileRecord> p, bool inuseZero);
    void record(struct MemProfileRecord* r, struct bucket* b);
    void iterate_memprof(std::function<void (struct bucket* _1, uintptr_t _2, uintptr_t* _3, uintptr_t _4, uintptr_t _5, uintptr_t _6)> fn);
    std::tuple<int, bool> BlockProfile(gocpp::slice<BlockProfileRecord> p);
    std::tuple<int, bool> MutexProfile(gocpp::slice<BlockProfileRecord> p);
    std::tuple<int, bool> ThreadCreateProfile(gocpp::slice<StackRecord> p);
    std::tuple<int, bool> runtime_goroutineProfileWithLabels(gocpp::slice<StackRecord> p, gocpp::slice<unsafe::Pointer> labels);
    std::tuple<int, bool> goroutineProfileWithLabels(gocpp::slice<StackRecord> p, gocpp::slice<unsafe::Pointer> labels);
    std::tuple<int, bool> goroutineProfileWithLabelsConcurrent(gocpp::slice<StackRecord> p, gocpp::slice<unsafe::Pointer> labels);
    void tryRecordGoroutineProfileWB(struct g* gp1);
    void tryRecordGoroutineProfile(struct g* gp1, std::function<void ()> yield);
    void doRecordGoroutineProfile(struct g* gp1);
    std::tuple<int, bool> goroutineProfileWithLabelsSync(gocpp::slice<StackRecord> p, gocpp::slice<unsafe::Pointer> labels);
    std::tuple<int, bool> GoroutineProfile(gocpp::slice<StackRecord> p);
    void saveg(uintptr_t pc, uintptr_t sp, struct g* gp, struct StackRecord* r);
    int Stack(gocpp::slice<unsigned char> buf, bool all);
    extern mutex tracelock;
    void tracealloc(unsafe::Pointer p, uintptr_t size, golang::runtime::_type* typ);
    void tracefree(unsafe::Pointer p, uintptr_t size);
    void tracegc();
    struct memRecord
    {
        /* memRecordCycle active; [Known incomplete type] */
        gocpp::array<memRecordCycle, 3> future;

        using isGoStruct = void;

        template<typename T> requires gocpp::GoStruct<T>
        operator T();

        template<typename T> requires gocpp::GoStruct<T>
        bool operator==(const T& ref) const;

        std::ostream& PrintTo(std::ostream& os) const;
    };

    std::ostream& operator<<(std::ostream& os, const struct memRecord& value);
    extern mProfCycleHolder mProfCycle;
    struct BlockProfileRecord
    {
        int64_t Count;
        int64_t Cycles;
        StackRecord StackRecord;

        using isGoStruct = void;

        template<typename T> requires gocpp::GoStruct<T>
        operator T();

        template<typename T> requires gocpp::GoStruct<T>
        bool operator==(const T& ref) const;

        std::ostream& PrintTo(std::ostream& os) const;
    };

    std::ostream& operator<<(std::ostream& os, const struct BlockProfileRecord& value);
    extern gocpp_id_0 goroutineProfile;
    extern gocpp::array<mutex, len(memRecord {}.future)> profMemFutureLock;

    namespace rec
    {
        void add(struct memRecordCycle* a, struct memRecordCycle* b);
        uint32_t read(struct mProfCycleHolder* c);
        std::tuple<uint32_t, bool> setFlushed(struct mProfCycleHolder* c);
        void increment(struct mProfCycleHolder* c);
        gocpp::slice<uintptr_t> stk(struct bucket* b);
        struct memRecord* mp(struct bucket* b);
        struct blockRecord* bp(struct bucket* b);
        void begin(struct lockTimer* lt);
        void end(struct lockTimer* lt);
        void recordLock(struct mLockProfile* prof, int64_t cycles, struct mutex* l);
        void recordUnlock(struct mLockProfile* prof, struct mutex* l);
        void captureStack(struct mLockProfile* prof);
        void store(struct mLockProfile* prof);
        gocpp::slice<uintptr_t> Stack(struct StackRecord* r);
        int64_t InUseBytes(struct MemProfileRecord* r);
        int64_t InUseObjects(struct MemProfileRecord* r);
        gocpp::slice<uintptr_t> Stack(struct MemProfileRecord* r);
        runtime::goroutineProfileState Load(golang::runtime::goroutineProfileStateHolder* p);
        void Store(golang::runtime::goroutineProfileStateHolder* p, golang::runtime::goroutineProfileState value);
        bool CompareAndSwap(golang::runtime::goroutineProfileStateHolder* p, golang::runtime::goroutineProfileState old, golang::runtime::goroutineProfileState go_new);
    }
}

