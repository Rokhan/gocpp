// generated by GoCpp from file '$(ImportDir)/runtime/mprof.go'
#pragma once

#include "gocpp/support.fwd.h"


namespace golang::runtime
{
    const long buckHashSize = 179999;
    const long maxStack = 32;
    using bucketType = int;
    struct memRecord;
    struct memRecordCycle;
    struct blockRecord;
    struct StackRecord;
    struct MemProfileRecord;
    struct BlockProfileRecord;
    struct gocpp_id_0;
    using goroutineProfileState = uint32_t;
    const runtime::bucketType memProfile = 1 + 0;
    const runtime::bucketType blockProfile = 1 + 1;
    const runtime::bucketType mutexProfile = 1 + 2;
    /*const uint32_t mProfCycleWrap = uint32_t(len(memRecord {}.future)) * (2 << 24) [known mising deps] */;
    const runtime::goroutineProfileState goroutineProfileAbsent = 0;
    const runtime::goroutineProfileState goroutineProfileInProgress = 1;
    const runtime::goroutineProfileState goroutineProfileSatisfied = 2;
}
#include "golang/runtime/internal/atomic/types.fwd.h"
#include "golang/runtime/internal/sys/nih.fwd.h"
#include "golang/runtime/runtime2.fwd.h"

namespace golang::runtime
{
    struct bucket;
    using buckhashArray = gocpp::array<atomic::UnsafePointer, buckHashSize>;
    struct mProfCycleHolder;
    struct lockTimer;
    struct mLockProfile;
    using goroutineProfileStateHolder = atomic::Uint32;
}
