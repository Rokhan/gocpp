// generated by GoCpp from file '$(ImportDir)/runtime/trace2event.go'
#pragma once

#include <functional>
#include <string>
#include <tuple>
#include <vector>

#include "golang/runtime/trace2event.fwd.h"
#include "gocpp/support.h"

#include "golang/runtime/internal/sys/consts.h"
#include "golang/runtime/runtime2.h"
#include "golang/runtime/trace2buf.h"
// #include "golang/runtime/trace2runtime.h"  [Ignored, known errors]
#include "golang/runtime/trace2stack.h"
#include "golang/runtime/trace2status.h"
#include "golang/runtime/trace2string.h"
#include "golang/runtime/trace2time.h"

namespace golang::runtime
{
    extern traceEv traceEvNone;
    extern traceEv traceEvEventBatch;
    extern traceEv traceEvStacks;
    extern traceEv traceEvStack;
    extern traceEv traceEvStrings;
    extern traceEv traceEvString;
    extern traceEv traceEvCPUSamples;
    extern traceEv traceEvCPUSample;
    extern traceEv traceEvFrequency;
    extern traceEv traceEvProcsChange;
    extern traceEv traceEvProcStart;
    extern traceEv traceEvProcStop;
    extern traceEv traceEvProcSteal;
    extern traceEv traceEvProcStatus;
    extern traceEv traceEvGoCreate;
    extern traceEv traceEvGoCreateSyscall;
    extern traceEv traceEvGoStart;
    extern traceEv traceEvGoDestroy;
    extern traceEv traceEvGoDestroySyscall;
    extern traceEv traceEvGoStop;
    extern traceEv traceEvGoBlock;
    extern traceEv traceEvGoUnblock;
    extern traceEv traceEvGoSyscallBegin;
    extern traceEv traceEvGoSyscallEnd;
    extern traceEv traceEvGoSyscallEndBlocked;
    extern traceEv traceEvGoStatus;
    extern traceEv traceEvSTWBegin;
    extern traceEv traceEvSTWEnd;
    extern traceEv traceEvGCActive;
    extern traceEv traceEvGCBegin;
    extern traceEv traceEvGCEnd;
    extern traceEv traceEvGCSweepActive;
    extern traceEv traceEvGCSweepBegin;
    extern traceEv traceEvGCSweepEnd;
    extern traceEv traceEvGCMarkAssistActive;
    extern traceEv traceEvGCMarkAssistBegin;
    extern traceEv traceEvGCMarkAssistEnd;
    extern traceEv traceEvHeapAlloc;
    extern traceEv traceEvHeapGoal;
    extern traceEv traceEvGoLabel;
    extern traceEv traceEvUserTaskBegin;
    extern traceEv traceEvUserTaskEnd;
    extern traceEv traceEvUserRegionBegin;
    extern traceEv traceEvUserRegionEnd;
    extern traceEv traceEvUserLog;
    struct traceEventWriter
    {
        traceWriter w;

        using isGoStruct = void;

        std::ostream& PrintTo(std::ostream& os) const;
    };

    std::ostream& operator<<(std::ostream& os, const struct traceEventWriter& value);
    traceEventWriter eventWriter(struct traceLocker tl, traceGoStatus goStatus, traceProcStatus procStatus);
    void commit(struct traceEventWriter e, traceEv ev, gocpp::slice<traceArg> args);
    template<typename... Args>
    void commit(struct traceEventWriter e, traceEv ev, Args... args)
    {
        return commit(e, ev, gocpp::ToSlice<traceArg>(args...));
    }

    traceEventWriter write(struct traceEventWriter e, traceEv ev, gocpp::slice<traceArg> args);
    template<typename... Args>
    traceEventWriter write(struct traceEventWriter e, traceEv ev, Args... args)
    {
        return write(e, ev, gocpp::ToSlice<traceArg>(args...));
    }

    void end(struct traceEventWriter e);
    traceWriter event(struct traceWriter w, traceEv ev, gocpp::slice<traceArg> args);
    template<typename... Args>
    traceWriter event(struct traceWriter w, traceEv ev, Args... args)
    {
        return event(w, ev, gocpp::ToSlice<traceArg>(args...));
    }

    traceArg stack(struct traceLocker tl, int skip);
    traceArg startPC(struct traceLocker tl, uintptr_t pc);
    traceArg string(struct traceLocker tl, std::string s);
    traceArg uniqueString(struct traceLocker tl, std::string s);
}
