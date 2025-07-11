// generated by GoCpp from file '$(ImportDir)/time/sleep.go'
#pragma once

#include <functional>
#include <string>
#include <tuple>
#include <vector>

#include "golang/time/sleep.fwd.h"
#include "gocpp/support.h"

#include "golang/time/time.h"
#include "golang/time/zoneinfo.h"

namespace golang::time
{
    void Sleep(golang::time::Duration d);
    struct runtimeTimer
    {
        uintptr_t pp;
        int64_t when;
        int64_t period;
        std::function<void (go_any _1, uintptr_t _2)> f;
        go_any arg;
        uintptr_t seq;
        int64_t nextwhen;
        uint32_t status;

        using isGoStruct = void;

        template<typename T> requires gocpp::GoStruct<T>
        operator T();

        template<typename T> requires gocpp::GoStruct<T>
        bool operator==(const T& ref) const;

        std::ostream& PrintTo(std::ostream& os) const;
    };

    std::ostream& operator<<(std::ostream& os, const struct runtimeTimer& value);
    int64_t when(golang::time::Duration d);
    void startTimer(runtimeTimer*);
    bool stopTimer(runtimeTimer*);
    bool resetTimer(runtimeTimer*, int64_t);
    void modTimer(struct runtimeTimer* t, int64_t when, int64_t period, std::function<void (go_any _1, uintptr_t _2)> f, go_any arg, uintptr_t seq);
    struct Timer* NewTimer(golang::time::Duration d);
    void sendTime(go_any c, uintptr_t seq);
    gocpp::channel<Time> After(golang::time::Duration d);
    struct Timer* AfterFunc(golang::time::Duration d, std::function<void ()> f);
    void goFunc(go_any arg, uintptr_t seq);
    struct Timer
    {
        gocpp::channel<Time> C;
        runtimeTimer r;

        using isGoStruct = void;

        template<typename T> requires gocpp::GoStruct<T>
        operator T();

        template<typename T> requires gocpp::GoStruct<T>
        bool operator==(const T& ref) const;

        std::ostream& PrintTo(std::ostream& os) const;
    };

    std::ostream& operator<<(std::ostream& os, const struct Timer& value);

    namespace rec
    {
        bool Stop(struct Timer* t);
        bool Reset(struct Timer* t, golang::time::Duration d);
    }
}

