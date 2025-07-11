// generated by GoCpp from file '$(ImportDir)/runtime/lockrank.go'
#include <complex>
#include <functional>
#include <iostream>
#include <iomanip>
#include <map>
#include <string>
#include <tuple>
#include <vector>

#include "golang/runtime/lockrank.h"
#include "gocpp/support.h"

namespace golang::runtime
{
    namespace rec
    {
        using namespace mocklib::rec;
    }

    // Constants representing the ranks of all non-leaf runtime locks, in rank order.
    // Locks with lower rank must be taken before locks with higher rank,
    // in addition to satisfying the partial order in lockPartialOrder.
    // A few ranks allow self-cycles, which are specified in lockPartialOrder.
    // SCHED
    // TRACEGLOBAL
    // MALLOC
    // MPROF
    // STACKGROW
    // WB
    // TRACE
    // lockRankLeafRank is the rank of lock that does not have a declared rank,
    // and hence is a leaf lock.
    // lockNames gives the names associated with each of the above ranks.
    gocpp::slice<std::string> lockNames = gocpp::Init<gocpp::slice<std::string>>([](auto& x) {
        x[lockRankSysmon] = "sysmon"s;
        x[lockRankScavenge] = "scavenge"s;
        x[lockRankForcegc] = "forcegc"s;
        x[lockRankDefer] = "defer"s;
        x[lockRankSweepWaiters] = "sweepWaiters"s;
        x[lockRankAssistQueue] = "assistQueue"s;
        x[lockRankSweep] = "sweep"s;
        x[lockRankTestR] = "testR"s;
        x[lockRankTestW] = "testW"s;
        x[lockRankAllocmW] = "allocmW"s;
        x[lockRankExecW] = "execW"s;
        x[lockRankCpuprof] = "cpuprof"s;
        x[lockRankPollDesc] = "pollDesc"s;
        x[lockRankWakeableSleep] = "wakeableSleep"s;
        x[lockRankAllocmR] = "allocmR"s;
        x[lockRankExecR] = "execR"s;
        x[lockRankSched] = "sched"s;
        x[lockRankAllg] = "allg"s;
        x[lockRankAllp] = "allp"s;
        x[lockRankTimers] = "timers"s;
        x[lockRankNetpollInit] = "netpollInit"s;
        x[lockRankHchan] = "hchan"s;
        x[lockRankNotifyList] = "notifyList"s;
        x[lockRankSudog] = "sudog"s;
        x[lockRankRoot] = "root"s;
        x[lockRankItab] = "itab"s;
        x[lockRankReflectOffs] = "reflectOffs"s;
        x[lockRankUserArenaState] = "userArenaState"s;
        x[lockRankTraceBuf] = "traceBuf"s;
        x[lockRankTraceStrings] = "traceStrings"s;
        x[lockRankFin] = "fin"s;
        x[lockRankSpanSetSpine] = "spanSetSpine"s;
        x[lockRankMspanSpecial] = "mspanSpecial"s;
        x[lockRankGcBitsArenas] = "gcBitsArenas"s;
        x[lockRankProfInsert] = "profInsert"s;
        x[lockRankProfBlock] = "profBlock"s;
        x[lockRankProfMemActive] = "profMemActive"s;
        x[lockRankProfMemFuture] = "profMemFuture"s;
        x[lockRankGscan] = "gscan"s;
        x[lockRankStackpool] = "stackpool"s;
        x[lockRankStackLarge] = "stackLarge"s;
        x[lockRankHchanLeaf] = "hchanLeaf"s;
        x[lockRankWbufSpans] = "wbufSpans"s;
        x[lockRankMheap] = "mheap"s;
        x[lockRankMheapSpecial] = "mheapSpecial"s;
        x[lockRankGlobalAlloc] = "globalAlloc"s;
        x[lockRankTrace] = "trace"s;
        x[lockRankTraceStackTab] = "traceStackTab"s;
        x[lockRankPanic] = "panic"s;
        x[lockRankDeadlock] = "deadlock"s;
        x[lockRankRaceFini] = "raceFini"s;
        x[lockRankAllocmRInternal] = "allocmRInternal"s;
        x[lockRankExecRInternal] = "execRInternal"s;
        x[lockRankTestRInternal] = "testRInternal"s;
    });
    std::string rec::String(golang::runtime::lockRank rank)
    {
        if(rank == 0)
        {
            return "UNKNOWN"s;
        }
        if(rank == lockRankLeafRank)
        {
            return "LEAF"s;
        }
        if(rank < 0 || int(rank) >= len(lockNames))
        {
            return "BAD RANK"s;
        }
        return lockNames[rank];
    }

    // lockPartialOrder is the transitive closure of the lock rank graph.
    // An entry for rank X lists all of the ranks that can already be held
    // when rank X is acquired.
    //
    // Lock ranks that allow self-cycles list themselves.
    gocpp::slice<gocpp::slice<runtime::lockRank>> lockPartialOrder = gocpp::Init<gocpp::slice<gocpp::slice<runtime::lockRank>>>([](auto& x) {
        x[lockRankSysmon] =  {};
        x[lockRankScavenge] =  {lockRankSysmon};
        x[lockRankForcegc] =  {lockRankSysmon};
        x[lockRankDefer] =  {};
        x[lockRankSweepWaiters] =  {};
        x[lockRankAssistQueue] =  {};
        x[lockRankSweep] =  {};
        x[lockRankTestR] =  {};
        x[lockRankTestW] =  {};
        x[lockRankAllocmW] =  {};
        x[lockRankExecW] =  {};
        x[lockRankCpuprof] =  {};
        x[lockRankPollDesc] =  {};
        x[lockRankWakeableSleep] =  {};
        x[lockRankAllocmR] =  {lockRankSysmon, lockRankScavenge, lockRankForcegc, lockRankSweepWaiters, lockRankAssistQueue, lockRankSweep, lockRankTestR, lockRankCpuprof, lockRankPollDesc, lockRankWakeableSleep};
        x[lockRankExecR] =  {lockRankSysmon, lockRankScavenge, lockRankForcegc, lockRankSweepWaiters, lockRankAssistQueue, lockRankSweep, lockRankTestR, lockRankCpuprof, lockRankPollDesc, lockRankWakeableSleep};
        x[lockRankSched] =  {lockRankSysmon, lockRankScavenge, lockRankForcegc, lockRankSweepWaiters, lockRankAssistQueue, lockRankSweep, lockRankTestR, lockRankCpuprof, lockRankPollDesc, lockRankWakeableSleep, lockRankAllocmR, lockRankExecR};
        x[lockRankAllg] =  {lockRankSysmon, lockRankScavenge, lockRankForcegc, lockRankSweepWaiters, lockRankAssistQueue, lockRankSweep, lockRankTestR, lockRankCpuprof, lockRankPollDesc, lockRankWakeableSleep, lockRankAllocmR, lockRankExecR, lockRankSched};
        x[lockRankAllp] =  {lockRankSysmon, lockRankScavenge, lockRankForcegc, lockRankSweepWaiters, lockRankAssistQueue, lockRankSweep, lockRankTestR, lockRankCpuprof, lockRankPollDesc, lockRankWakeableSleep, lockRankAllocmR, lockRankExecR, lockRankSched};
        x[lockRankTimers] =  {lockRankSysmon, lockRankScavenge, lockRankForcegc, lockRankSweepWaiters, lockRankAssistQueue, lockRankSweep, lockRankTestR, lockRankCpuprof, lockRankPollDesc, lockRankWakeableSleep, lockRankAllocmR, lockRankExecR, lockRankSched, lockRankAllp, lockRankTimers};
        x[lockRankNetpollInit] =  {lockRankSysmon, lockRankScavenge, lockRankForcegc, lockRankSweepWaiters, lockRankAssistQueue, lockRankSweep, lockRankTestR, lockRankCpuprof, lockRankPollDesc, lockRankWakeableSleep, lockRankAllocmR, lockRankExecR, lockRankSched, lockRankAllp, lockRankTimers};
        x[lockRankHchan] =  {lockRankSysmon, lockRankScavenge, lockRankSweep, lockRankTestR, lockRankWakeableSleep, lockRankHchan};
        x[lockRankNotifyList] =  {};
        x[lockRankSudog] =  {lockRankSysmon, lockRankScavenge, lockRankSweep, lockRankTestR, lockRankWakeableSleep, lockRankHchan, lockRankNotifyList};
        x[lockRankRoot] =  {};
        x[lockRankItab] =  {};
        x[lockRankReflectOffs] =  {lockRankItab};
        x[lockRankUserArenaState] =  {};
        x[lockRankTraceBuf] =  {lockRankSysmon, lockRankScavenge};
        x[lockRankTraceStrings] =  {lockRankSysmon, lockRankScavenge, lockRankTraceBuf};
        x[lockRankFin] =  {lockRankSysmon, lockRankScavenge, lockRankForcegc, lockRankSweepWaiters, lockRankAssistQueue, lockRankSweep, lockRankTestR, lockRankExecW, lockRankCpuprof, lockRankPollDesc, lockRankWakeableSleep, lockRankAllocmR, lockRankExecR, lockRankSched, lockRankAllg, lockRankAllp, lockRankTimers, lockRankHchan, lockRankNotifyList, lockRankItab, lockRankReflectOffs, lockRankUserArenaState, lockRankTraceBuf, lockRankTraceStrings};
        x[lockRankSpanSetSpine] =  {lockRankSysmon, lockRankScavenge, lockRankForcegc, lockRankSweepWaiters, lockRankAssistQueue, lockRankSweep, lockRankTestR, lockRankExecW, lockRankCpuprof, lockRankPollDesc, lockRankWakeableSleep, lockRankAllocmR, lockRankExecR, lockRankSched, lockRankAllg, lockRankAllp, lockRankTimers, lockRankHchan, lockRankNotifyList, lockRankItab, lockRankReflectOffs, lockRankUserArenaState, lockRankTraceBuf, lockRankTraceStrings};
        x[lockRankMspanSpecial] =  {lockRankSysmon, lockRankScavenge, lockRankForcegc, lockRankSweepWaiters, lockRankAssistQueue, lockRankSweep, lockRankTestR, lockRankExecW, lockRankCpuprof, lockRankPollDesc, lockRankWakeableSleep, lockRankAllocmR, lockRankExecR, lockRankSched, lockRankAllg, lockRankAllp, lockRankTimers, lockRankHchan, lockRankNotifyList, lockRankItab, lockRankReflectOffs, lockRankUserArenaState, lockRankTraceBuf, lockRankTraceStrings};
        x[lockRankGcBitsArenas] =  {lockRankSysmon, lockRankScavenge, lockRankForcegc, lockRankSweepWaiters, lockRankAssistQueue, lockRankSweep, lockRankTestR, lockRankExecW, lockRankCpuprof, lockRankPollDesc, lockRankWakeableSleep, lockRankAllocmR, lockRankExecR, lockRankSched, lockRankAllg, lockRankAllp, lockRankTimers, lockRankHchan, lockRankNotifyList, lockRankItab, lockRankReflectOffs, lockRankUserArenaState, lockRankTraceBuf, lockRankTraceStrings, lockRankMspanSpecial};
        x[lockRankProfInsert] =  {lockRankSysmon, lockRankScavenge, lockRankForcegc, lockRankSweepWaiters, lockRankAssistQueue, lockRankSweep, lockRankTestR, lockRankExecW, lockRankCpuprof, lockRankPollDesc, lockRankWakeableSleep, lockRankAllocmR, lockRankExecR, lockRankSched, lockRankAllg, lockRankAllp, lockRankTimers, lockRankHchan, lockRankNotifyList, lockRankItab, lockRankReflectOffs, lockRankUserArenaState, lockRankTraceBuf, lockRankTraceStrings};
        x[lockRankProfBlock] =  {lockRankSysmon, lockRankScavenge, lockRankForcegc, lockRankSweepWaiters, lockRankAssistQueue, lockRankSweep, lockRankTestR, lockRankExecW, lockRankCpuprof, lockRankPollDesc, lockRankWakeableSleep, lockRankAllocmR, lockRankExecR, lockRankSched, lockRankAllg, lockRankAllp, lockRankTimers, lockRankHchan, lockRankNotifyList, lockRankItab, lockRankReflectOffs, lockRankUserArenaState, lockRankTraceBuf, lockRankTraceStrings};
        x[lockRankProfMemActive] =  {lockRankSysmon, lockRankScavenge, lockRankForcegc, lockRankSweepWaiters, lockRankAssistQueue, lockRankSweep, lockRankTestR, lockRankExecW, lockRankCpuprof, lockRankPollDesc, lockRankWakeableSleep, lockRankAllocmR, lockRankExecR, lockRankSched, lockRankAllg, lockRankAllp, lockRankTimers, lockRankHchan, lockRankNotifyList, lockRankItab, lockRankReflectOffs, lockRankUserArenaState, lockRankTraceBuf, lockRankTraceStrings};
        x[lockRankProfMemFuture] =  {lockRankSysmon, lockRankScavenge, lockRankForcegc, lockRankSweepWaiters, lockRankAssistQueue, lockRankSweep, lockRankTestR, lockRankExecW, lockRankCpuprof, lockRankPollDesc, lockRankWakeableSleep, lockRankAllocmR, lockRankExecR, lockRankSched, lockRankAllg, lockRankAllp, lockRankTimers, lockRankHchan, lockRankNotifyList, lockRankItab, lockRankReflectOffs, lockRankUserArenaState, lockRankTraceBuf, lockRankTraceStrings, lockRankProfMemActive};
        x[lockRankGscan] =  {lockRankSysmon, lockRankScavenge, lockRankForcegc, lockRankSweepWaiters, lockRankAssistQueue, lockRankSweep, lockRankTestR, lockRankExecW, lockRankCpuprof, lockRankPollDesc, lockRankWakeableSleep, lockRankAllocmR, lockRankExecR, lockRankSched, lockRankAllg, lockRankAllp, lockRankTimers, lockRankNetpollInit, lockRankHchan, lockRankNotifyList, lockRankRoot, lockRankItab, lockRankReflectOffs, lockRankUserArenaState, lockRankTraceBuf, lockRankTraceStrings, lockRankFin, lockRankSpanSetSpine, lockRankMspanSpecial, lockRankGcBitsArenas, lockRankProfInsert, lockRankProfBlock, lockRankProfMemActive, lockRankProfMemFuture};
        x[lockRankStackpool] =  {lockRankSysmon, lockRankScavenge, lockRankForcegc, lockRankSweepWaiters, lockRankAssistQueue, lockRankSweep, lockRankTestR, lockRankExecW, lockRankCpuprof, lockRankPollDesc, lockRankWakeableSleep, lockRankAllocmR, lockRankExecR, lockRankSched, lockRankAllg, lockRankAllp, lockRankTimers, lockRankNetpollInit, lockRankHchan, lockRankNotifyList, lockRankRoot, lockRankItab, lockRankReflectOffs, lockRankUserArenaState, lockRankTraceBuf, lockRankTraceStrings, lockRankFin, lockRankSpanSetSpine, lockRankMspanSpecial, lockRankGcBitsArenas, lockRankProfInsert, lockRankProfBlock, lockRankProfMemActive, lockRankProfMemFuture, lockRankGscan};
        x[lockRankStackLarge] =  {lockRankSysmon, lockRankScavenge, lockRankForcegc, lockRankSweepWaiters, lockRankAssistQueue, lockRankSweep, lockRankTestR, lockRankExecW, lockRankCpuprof, lockRankPollDesc, lockRankWakeableSleep, lockRankAllocmR, lockRankExecR, lockRankSched, lockRankAllg, lockRankAllp, lockRankTimers, lockRankNetpollInit, lockRankHchan, lockRankNotifyList, lockRankRoot, lockRankItab, lockRankReflectOffs, lockRankUserArenaState, lockRankTraceBuf, lockRankTraceStrings, lockRankFin, lockRankSpanSetSpine, lockRankMspanSpecial, lockRankGcBitsArenas, lockRankProfInsert, lockRankProfBlock, lockRankProfMemActive, lockRankProfMemFuture, lockRankGscan};
        x[lockRankHchanLeaf] =  {lockRankSysmon, lockRankScavenge, lockRankForcegc, lockRankSweepWaiters, lockRankAssistQueue, lockRankSweep, lockRankTestR, lockRankExecW, lockRankCpuprof, lockRankPollDesc, lockRankWakeableSleep, lockRankAllocmR, lockRankExecR, lockRankSched, lockRankAllg, lockRankAllp, lockRankTimers, lockRankNetpollInit, lockRankHchan, lockRankNotifyList, lockRankRoot, lockRankItab, lockRankReflectOffs, lockRankUserArenaState, lockRankTraceBuf, lockRankTraceStrings, lockRankFin, lockRankSpanSetSpine, lockRankMspanSpecial, lockRankGcBitsArenas, lockRankProfInsert, lockRankProfBlock, lockRankProfMemActive, lockRankProfMemFuture, lockRankGscan, lockRankHchanLeaf};
        x[lockRankWbufSpans] =  {lockRankSysmon, lockRankScavenge, lockRankForcegc, lockRankDefer, lockRankSweepWaiters, lockRankAssistQueue, lockRankSweep, lockRankTestR, lockRankExecW, lockRankCpuprof, lockRankPollDesc, lockRankWakeableSleep, lockRankAllocmR, lockRankExecR, lockRankSched, lockRankAllg, lockRankAllp, lockRankTimers, lockRankNetpollInit, lockRankHchan, lockRankNotifyList, lockRankSudog, lockRankRoot, lockRankItab, lockRankReflectOffs, lockRankUserArenaState, lockRankTraceBuf, lockRankTraceStrings, lockRankFin, lockRankSpanSetSpine, lockRankMspanSpecial, lockRankGcBitsArenas, lockRankProfInsert, lockRankProfBlock, lockRankProfMemActive, lockRankProfMemFuture, lockRankGscan};
        x[lockRankMheap] =  {lockRankSysmon, lockRankScavenge, lockRankForcegc, lockRankDefer, lockRankSweepWaiters, lockRankAssistQueue, lockRankSweep, lockRankTestR, lockRankExecW, lockRankCpuprof, lockRankPollDesc, lockRankWakeableSleep, lockRankAllocmR, lockRankExecR, lockRankSched, lockRankAllg, lockRankAllp, lockRankTimers, lockRankNetpollInit, lockRankHchan, lockRankNotifyList, lockRankSudog, lockRankRoot, lockRankItab, lockRankReflectOffs, lockRankUserArenaState, lockRankTraceBuf, lockRankTraceStrings, lockRankFin, lockRankSpanSetSpine, lockRankMspanSpecial, lockRankGcBitsArenas, lockRankProfInsert, lockRankProfBlock, lockRankProfMemActive, lockRankProfMemFuture, lockRankGscan, lockRankStackpool, lockRankStackLarge, lockRankWbufSpans};
        x[lockRankMheapSpecial] =  {lockRankSysmon, lockRankScavenge, lockRankForcegc, lockRankDefer, lockRankSweepWaiters, lockRankAssistQueue, lockRankSweep, lockRankTestR, lockRankExecW, lockRankCpuprof, lockRankPollDesc, lockRankWakeableSleep, lockRankAllocmR, lockRankExecR, lockRankSched, lockRankAllg, lockRankAllp, lockRankTimers, lockRankNetpollInit, lockRankHchan, lockRankNotifyList, lockRankSudog, lockRankRoot, lockRankItab, lockRankReflectOffs, lockRankUserArenaState, lockRankTraceBuf, lockRankTraceStrings, lockRankFin, lockRankSpanSetSpine, lockRankMspanSpecial, lockRankGcBitsArenas, lockRankProfInsert, lockRankProfBlock, lockRankProfMemActive, lockRankProfMemFuture, lockRankGscan, lockRankStackpool, lockRankStackLarge, lockRankWbufSpans, lockRankMheap};
        x[lockRankGlobalAlloc] =  {lockRankSysmon, lockRankScavenge, lockRankForcegc, lockRankDefer, lockRankSweepWaiters, lockRankAssistQueue, lockRankSweep, lockRankTestR, lockRankExecW, lockRankCpuprof, lockRankPollDesc, lockRankWakeableSleep, lockRankAllocmR, lockRankExecR, lockRankSched, lockRankAllg, lockRankAllp, lockRankTimers, lockRankNetpollInit, lockRankHchan, lockRankNotifyList, lockRankSudog, lockRankRoot, lockRankItab, lockRankReflectOffs, lockRankUserArenaState, lockRankTraceBuf, lockRankTraceStrings, lockRankFin, lockRankSpanSetSpine, lockRankMspanSpecial, lockRankGcBitsArenas, lockRankProfInsert, lockRankProfBlock, lockRankProfMemActive, lockRankProfMemFuture, lockRankGscan, lockRankStackpool, lockRankStackLarge, lockRankWbufSpans, lockRankMheap, lockRankMheapSpecial};
        x[lockRankTrace] =  {lockRankSysmon, lockRankScavenge, lockRankForcegc, lockRankDefer, lockRankSweepWaiters, lockRankAssistQueue, lockRankSweep, lockRankTestR, lockRankExecW, lockRankCpuprof, lockRankPollDesc, lockRankWakeableSleep, lockRankAllocmR, lockRankExecR, lockRankSched, lockRankAllg, lockRankAllp, lockRankTimers, lockRankNetpollInit, lockRankHchan, lockRankNotifyList, lockRankSudog, lockRankRoot, lockRankItab, lockRankReflectOffs, lockRankUserArenaState, lockRankTraceBuf, lockRankTraceStrings, lockRankFin, lockRankSpanSetSpine, lockRankMspanSpecial, lockRankGcBitsArenas, lockRankProfInsert, lockRankProfBlock, lockRankProfMemActive, lockRankProfMemFuture, lockRankGscan, lockRankStackpool, lockRankStackLarge, lockRankWbufSpans, lockRankMheap};
        x[lockRankTraceStackTab] =  {lockRankSysmon, lockRankScavenge, lockRankForcegc, lockRankDefer, lockRankSweepWaiters, lockRankAssistQueue, lockRankSweep, lockRankTestR, lockRankExecW, lockRankCpuprof, lockRankPollDesc, lockRankWakeableSleep, lockRankAllocmR, lockRankExecR, lockRankSched, lockRankAllg, lockRankAllp, lockRankTimers, lockRankNetpollInit, lockRankHchan, lockRankNotifyList, lockRankSudog, lockRankRoot, lockRankItab, lockRankReflectOffs, lockRankUserArenaState, lockRankTraceBuf, lockRankTraceStrings, lockRankFin, lockRankSpanSetSpine, lockRankMspanSpecial, lockRankGcBitsArenas, lockRankProfInsert, lockRankProfBlock, lockRankProfMemActive, lockRankProfMemFuture, lockRankGscan, lockRankStackpool, lockRankStackLarge, lockRankWbufSpans, lockRankMheap, lockRankTrace};
        x[lockRankPanic] =  {};
        x[lockRankDeadlock] =  {lockRankPanic, lockRankDeadlock};
        x[lockRankRaceFini] =  {lockRankPanic};
        x[lockRankAllocmRInternal] =  {lockRankSysmon, lockRankScavenge, lockRankForcegc, lockRankSweepWaiters, lockRankAssistQueue, lockRankSweep, lockRankTestR, lockRankAllocmW, lockRankCpuprof, lockRankPollDesc, lockRankWakeableSleep, lockRankAllocmR};
        x[lockRankExecRInternal] =  {lockRankSysmon, lockRankScavenge, lockRankForcegc, lockRankSweepWaiters, lockRankAssistQueue, lockRankSweep, lockRankTestR, lockRankExecW, lockRankCpuprof, lockRankPollDesc, lockRankWakeableSleep, lockRankExecR};
        x[lockRankTestRInternal] =  {lockRankTestR, lockRankTestW};
    });
}

