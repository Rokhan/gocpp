// generated by GoCpp from file '$(ImportDir)/runtime/trace2cpu.go'
#pragma once

#include <functional>
#include <string>
#include <tuple>
#include <vector>

#include "golang/runtime/trace2cpu.fwd.h"
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
#include "golang/runtime/malloc.h"
#include "golang/runtime/mcache.h"
#include "golang/runtime/mgc.h"
#include "golang/runtime/mgclimit.h"
#include "golang/runtime/mgcwork.h"
#include "golang/runtime/mheap.h"
#include "golang/runtime/mpagecache.h"
#include "golang/runtime/mprof.h"
#include "golang/runtime/mranges.h"
#include "golang/runtime/mwbbuf.h"
#include "golang/runtime/os_windows.h"
#include "golang/runtime/pagetrace_off.h"
#include "golang/runtime/panic.h"
#include "golang/runtime/pinner.h"
#include "golang/runtime/proc.h"
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
    void traceInitReadCPU();
    void traceStartReadCPU();
    void traceStopReadCPU();
    bool traceReadCPU(uintptr_t gen);
    void traceCPUFlush(uintptr_t gen);
    void traceCPUSample(struct g* gp, struct m* mp, struct p* pp, gocpp::slice<uintptr_t> stk);

    namespace rec
    {
    }
}

