// generated by GoCpp from file '$(ImportDir)/runtime/runtime.go'
#pragma once

#include <functional>
#include <string>
#include <tuple>
#include <vector>

#include "golang/runtime/runtime.fwd.h"
#include "gocpp/support.h"

#include "golang/runtime/internal/atomic/types.h"
#include "golang/runtime/lockrank_off.h"
#include "golang/runtime/runtime2.h"

namespace golang::runtime
{
    struct ticksType
    {
        mutex lock;
        int64_t startTicks;
        int64_t startTime;
        atomic::Int64 val;

        using isGoStruct = void;

        template<typename T> requires gocpp::GoStruct<T>
        operator T();

        template<typename T> requires gocpp::GoStruct<T>
        bool operator==(const T& ref) const;

        std::ostream& PrintTo(std::ostream& os) const;
    };

    std::ostream& operator<<(std::ostream& os, const struct ticksType& value);
    int64_t ticksPerSecond();
    extern gocpp::slice<std::string> envs;
    extern gocpp::slice<std::string> argslice;
    gocpp::slice<std::string> syscall_runtime_envs();
    int syscall_Getpagesize();
    gocpp::slice<std::string> os_runtime_args();
    void syscall_Exit(int code);
    extern std::string godebugDefault;
    extern atomic::Pointer<std::function<void (std::string _1, std::string _2)>> godebugUpdate;
    extern atomic::Pointer<std::string> godebugEnv;
    extern atomic::Pointer<std::function<std::function<void ()> (std::string _1)>> godebugNewIncNonDefault;
    void godebug_setUpdate(std::function<void (std::string _1, std::string _2)> update);
    void godebug_setNewIncNonDefault(std::function<std::function<void ()> (std::string _1)> newIncNonDefault);
    struct godebugInc
    {
        std::string name;
        atomic::Pointer<std::function<void ()>> inc;

        using isGoStruct = void;

        template<typename T> requires gocpp::GoStruct<T>
        operator T();

        template<typename T> requires gocpp::GoStruct<T>
        bool operator==(const T& ref) const;

        std::ostream& PrintTo(std::ostream& os) const;
    };

    std::ostream& operator<<(std::ostream& os, const struct godebugInc& value);
    void godebugNotify(bool envChanged);
    void syscall_runtimeSetenv(std::string key, std::string value);
    void syscall_runtimeUnsetenv(std::string key);
    void writeErrStr(std::string s);
    extern gocpp::slice<uintptr_t> auxv;
    gocpp::slice<uintptr_t> getAuxv();
    extern ticksType ticks;

    namespace rec
    {
        void init(struct ticksType* t);
        void IncNonDefault(struct godebugInc* g);
    }
}

