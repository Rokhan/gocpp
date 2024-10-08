// generated by GoCpp from file '$(ImportDir)/runtime/mgc.go'
#pragma once

#include "gocpp/support.fwd.h"


namespace golang::runtime
{
    const long _DebugGC = 0;
    const int _FinBlockSize = 4 * 1024;
    const bool concurrentSweep = true;
    const bool debugScanConservative = false;
    const int sweepMinHeapDistance = 1024 * 1024;
    struct gocpp_id_0;
    const int _GCoff = 0;
    const int _GCmark = 1;
    const int _GCmarktermination = 2;
    using gcMarkWorkerMode = int;
    using gcMode = int;
    struct gcTrigger;
    using gcTriggerKind = int;
    const gcMarkWorkerMode gcMarkWorkerNotWorker = 0;
    const gcMarkWorkerMode gcMarkWorkerDedicatedMode = 1;
    const gcMarkWorkerMode gcMarkWorkerFractionalMode = 2;
    const gcMarkWorkerMode gcMarkWorkerIdleMode = 3;
    const gcMode gcBackgroundMode = 0;
    const gcMode gcForceMode = 1;
    const gcMode gcForceBlockMode = 2;
    const gcTriggerKind gcTriggerHeap = 0;
    const gcTriggerKind gcTriggerTime = 1;
    const gcTriggerKind gcTriggerCycle = 2;
}
// #include "golang/internal/cpu/cpu.fwd.h" [Ignored, known errors]
#include "golang/runtime/internal/atomic/types.fwd.h"
#include "golang/runtime/lfstack.fwd.h"
#include "golang/runtime/mheap.fwd.h"
#include "golang/runtime/mstats.fwd.h"
#include "golang/runtime/proc.fwd.h"
#include "golang/runtime/runtime2.fwd.h"

namespace golang::runtime
{
    struct workType;
    struct gcBgMarkWorkerNode;
}
