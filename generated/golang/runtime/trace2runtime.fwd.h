// generated by GoCpp from file '$(ImportDir)/runtime/trace2runtime.go'
#pragma once

#include "gocpp/support.fwd.h"


namespace golang::runtime
{
    using traceBlockReason = uint8_t;
    using traceGoStopReason = uint8_t;
    const bool debugTraceReentrancy = false;
    const traceBlockReason traceBlockGeneric = 0;
    const traceBlockReason traceBlockForever = 1;
    const traceBlockReason traceBlockNet = 2;
    const traceBlockReason traceBlockSelect = 3;
    const traceBlockReason traceBlockCondWait = 4;
    const traceBlockReason traceBlockSync = 5;
    const traceBlockReason traceBlockChanSend = 6;
    const traceBlockReason traceBlockChanRecv = 7;
    const traceBlockReason traceBlockGCMarkAssist = 8;
    const traceBlockReason traceBlockGCSweep = 9;
    const traceBlockReason traceBlockSystemGoroutine = 10;
    const traceBlockReason traceBlockPreempted = 11;
    const traceBlockReason traceBlockDebugCall = 12;
    const traceBlockReason traceBlockUntilGCEnds = 13;
    const traceBlockReason traceBlockSleep = 14;
    const traceGoStopReason traceGoStopGeneric = 0;
    const traceGoStopReason traceGoStopGoSched = 1;
    const traceGoStopReason traceGoStopPreempted = 2;
}
#include "golang/runtime/internal/atomic/types.fwd.h"
#include "golang/runtime/runtime2.fwd.h"
#include "golang/runtime/trace2buf.fwd.h"
#include "golang/runtime/trace2status.fwd.h"

namespace golang::runtime
{
    struct gTraceState;
    struct mTraceState;
    struct pTraceState;
    struct traceLocker;
}
#include "golang/runtime/extern.fwd.h"
// #include "golang/runtime/lock_sema.fwd.h" [Ignored, known errors]
// #include "golang/runtime/lockrank.fwd.h" [Ignored, known errors]
// #include "golang/runtime/lockrank_off.fwd.h" [Ignored, known errors]
#include "golang/runtime/mgc.fwd.h"
// #include "golang/runtime/mgcpacer.fwd.h" [Ignored, known errors]
#include "golang/runtime/panic.fwd.h"
#include "golang/runtime/proc.fwd.h"
// #include "golang/runtime/runtime1.fwd.h" [Ignored, known errors]
// #include "golang/runtime/stubs.fwd.h" [Ignored, known errors]
#include "golang/runtime/trace2event.fwd.h"
#include "golang/runtime/trace2stack.fwd.h"
