// generated by GoCpp from file '$(ImportDir)/runtime/os_windows.go'
#pragma once

#include <functional>
#include <string>
#include <tuple>
#include <vector>

#include "golang/runtime/os_windows.fwd.h"
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
#include "golang/runtime/panic.h"
#include "golang/runtime/runtime2.h"
// #include "golang/runtime/signal_windows.h"  [Ignored, known errors]
// #include "golang/runtime/symtab.h"  [Ignored, known errors]
// #include "golang/runtime/time.h"  [Ignored, known errors]
#include "golang/runtime/trace2buf.h"
// #include "golang/runtime/trace2runtime.h"  [Ignored, known errors]
#include "golang/runtime/trace2status.h"
#include "golang/runtime/trace2time.h"

namespace golang::runtime
{
    extern gocpp::array_base<uint16_t> bcryptprimitivesdll;
    extern gocpp::array_base<uint16_t> ntdlldll;
    extern gocpp::array_base<uint16_t> powrprofdll;
    extern gocpp::array_base<uint16_t> winmmdll;
    extern gocpp::array_base<uint16_t> ws2_32dll;
    void tstart_stdcall(m* newm);
    void wintls();
    struct mOS
    {
        mutex threadLock;
        uintptr_t thread;
        uintptr_t waitsema;
        uintptr_t resumesema;
        uintptr_t highResTimer;
        uint32_t preemptExtLock;

        using isGoStruct = void;

        template<typename T> requires gocpp::GoStruct<T>
        operator T();

        template<typename T> requires gocpp::GoStruct<T>
        bool operator==(const T& ref) const;

        std::ostream& PrintTo(std::ostream& os) const;
    };

    std::ostream& operator<<(std::ostream& os, const struct mOS& value);
    int32_t open(unsigned char* name, int32_t mode, int32_t perm);
    int32_t closefd(int32_t fd);
    int32_t read(int32_t fd, unsafe::Pointer p, int32_t n);
    struct sigset
    {

        using isGoStruct = void;

        template<typename T> requires gocpp::GoStruct<T>
        operator T();

        template<typename T> requires gocpp::GoStruct<T>
        bool operator==(const T& ref) const;

        std::ostream& PrintTo(std::ostream& os) const;
    };

    std::ostream& operator<<(std::ostream& os, const struct sigset& value);
    void asmstdcall(unsafe::Pointer fn);
    stdFunction windowsFindfunc(uintptr_t lib, gocpp::slice<unsigned char> name);
    void initSysDirectory();
    std::string windows_GetSystemDirectory();
    uintptr_t windowsLoadSystemLib(gocpp::slice<uint16_t> name);
    void loadOptionalSyscalls();
    void monitorSuspendResume();
    uintptr_t getLoadLibrary();
    uintptr_t getLoadLibraryEx();
    uintptr_t getGetProcAddress();
    int32_t getproccount();
    uintptr_t getPageSize();
    uint32_t getlasterror();
    uint32_t osRelax(bool relax);
    extern bool haveHighResTimer;
    uintptr_t createHighResTimer();
    void initHighResTimer();
    void initLongPathSupport();
    void osinit();
    int readRandom(gocpp::slice<unsigned char> r);
    void goenvs();
    void exit(int32_t code);
    int32_t write1(uintptr_t fd, unsafe::Pointer buf, int32_t n);
    int writeConsole(uintptr_t handle, unsafe::Pointer buf, int32_t bufLen);
    void writeConsoleUTF16(uintptr_t handle, gocpp::slice<uint16_t> b);
    int32_t semasleep(int64_t ns);
    void semawakeup(m* mp);
    void semacreate(m* mp);
    void newosproc(m* mp);
    void newosproc0(m* mp, unsafe::Pointer stk);
    void exitThread(atomic::Uint32* wait);
    void mpreinit(m* mp);
    void sigsave(sigset* p);
    void msigrestore(sigset sigmask);
    void clearSignalHandlers();
    void sigblock(bool exiting);
    void minit();
    void unminit();
    void mdestroy(m* mp);
    void asmstdcall_trampoline(unsafe::Pointer args);
    uintptr_t stdcall_no_g(stdFunction fn, int n, uintptr_t args);
    uintptr_t stdcall(stdFunction fn);
    uintptr_t stdcall0(stdFunction fn);
    uintptr_t stdcall1(stdFunction fn, uintptr_t a0);
    uintptr_t stdcall2(stdFunction fn, uintptr_t a0, uintptr_t a1);
    uintptr_t stdcall3(stdFunction fn, uintptr_t a0, uintptr_t a1, uintptr_t a2);
    uintptr_t stdcall4(stdFunction fn, uintptr_t a0, uintptr_t a1, uintptr_t a2, uintptr_t a3);
    uintptr_t stdcall5(stdFunction fn, uintptr_t a0, uintptr_t a1, uintptr_t a2, uintptr_t a3, uintptr_t a4);
    uintptr_t stdcall6(stdFunction fn, uintptr_t a0, uintptr_t a1, uintptr_t a2, uintptr_t a3, uintptr_t a4, uintptr_t a5);
    uintptr_t stdcall7(stdFunction fn, uintptr_t a0, uintptr_t a1, uintptr_t a2, uintptr_t a3, uintptr_t a4, uintptr_t a5, uintptr_t a6);
    uintptr_t stdcall8(stdFunction fn, uintptr_t a0, uintptr_t a1, uintptr_t a2, uintptr_t a3, uintptr_t a4, uintptr_t a5, uintptr_t a6, uintptr_t a7);
    void osyield_no_g();
    void osyield();
    void usleep_no_g(uint32_t us);
    void usleep(uint32_t us);
    uintptr_t ctrlHandler(uint32_t _type);
    void callbackasm1();
    void profilem(m* mp, uintptr_t thread);
    g* gFromSP(m* mp, uintptr_t sp);
    void profileLoop();
    void setProcessCPUProfiler(int32_t hz);
    void setThreadCPUProfiler(int32_t hz);
    void preemptM(m* mp);
    void osPreemptExtEnter(m* mp);
    void osPreemptExtExit(m* mp);
}

