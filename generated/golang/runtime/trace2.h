// generated by GoCpp from file '$(ImportDir)/runtime/trace2.go'
#pragma once

#include <functional>
#include <string>
#include <tuple>
#include <vector>

#include "golang/runtime/trace2.fwd.h"
#include "gocpp/support.h"

#include "golang/internal/abi/type.h"
#include "golang/internal/chacha8rand/chacha8.h"
// #include "golang/runtime/cgocall.h"  [Ignored, known errors]
#include "golang/runtime/chan.h"
#include "golang/runtime/coro.h"
#include "golang/runtime/debuglog_off.h"
#include "golang/runtime/internal/atomic/types.h"
#include "golang/runtime/internal/sys/nih.h"
// #include "golang/runtime/lockrank.h"  [Ignored, known errors]
// #include "golang/runtime/lockrank_off.h"  [Ignored, known errors]
#include "golang/runtime/mprof.h"
// #include "golang/runtime/os_windows.h"  [Ignored, known errors]
#include "golang/runtime/panic.h"
#include "golang/runtime/profbuf.h"
#include "golang/runtime/runtime2.h"
// #include "golang/runtime/signal_windows.h"  [Ignored, known errors]
// #include "golang/runtime/symtab.h"  [Ignored, known errors]
// #include "golang/runtime/time.h"  [Ignored, known errors]
#include "golang/runtime/trace2buf.h"
#include "golang/runtime/trace2event.h"
// #include "golang/runtime/trace2map.h"  [Ignored, known errors]
// #include "golang/runtime/trace2region.h"  [Ignored, known errors]
// #include "golang/runtime/trace2runtime.h"  [Ignored, known errors]
#include "golang/runtime/trace2stack.h"
#include "golang/runtime/trace2status.h"
#include "golang/runtime/trace2string.h"
#include "golang/runtime/trace2time.h"

namespace golang::runtime
{
    extern uint32_t traceAdvanceSema;
    extern uint32_t traceShutdownSema;
    std::string StartTrace();
    void StopTrace();
    void traceAdvance(bool stopTrace);
    uintptr_t traceNextGen(uintptr_t gen);
    void traceRegisterLabelsAndReasons(uintptr_t gen);
    gocpp::slice<unsigned char> ReadTrace();
    std::tuple<gocpp::slice<unsigned char>, bool> readTrace0();
    g* traceReader();
    g* traceReaderAvailable();
    struct traceAdvancerState
    {
        wakeableSleep* timer;
        gocpp::channel<gocpp_id_2> done;

        using isGoStruct = void;

        template<typename T> requires gocpp::GoStruct<T>
        operator T();

        template<typename T> requires gocpp::GoStruct<T>
        bool operator==(const T& ref) const;

        std::ostream& PrintTo(std::ostream& os) const;
    };

    std::ostream& operator<<(std::ostream& os, const struct traceAdvancerState& value);
    void start(struct traceAdvancerState* s);
    void stop(struct traceAdvancerState* s);
    struct wakeableSleep
    {
        timer* timer;
        mutex lock;
        gocpp::channel<gocpp_id_5> wakeup;

        using isGoStruct = void;

        template<typename T> requires gocpp::GoStruct<T>
        operator T();

        template<typename T> requires gocpp::GoStruct<T>
        bool operator==(const T& ref) const;

        std::ostream& PrintTo(std::ostream& os) const;
    };

    std::ostream& operator<<(std::ostream& os, const struct wakeableSleep& value);
    wakeableSleep* newWakeableSleep();
    void sleep(struct wakeableSleep* s, int64_t ns);
    void wake(struct wakeableSleep* s);
    void close(struct wakeableSleep* s);
}

