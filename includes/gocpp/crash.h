#pragma once
#include <cstdlib>
#include <cstring>

#if defined(_WIN32)
#ifndef NOMINMAX
#define NOMINMAX
#endif
#ifndef WIN32_LEAN_AND_MEAN
#define WIN32_LEAN_AND_MEAN
#endif
#include <windows.h>
namespace gocpp
{
    inline LONG WINAPI crash_filter(EXCEPTION_POINTERS* p)
    {
        const char* msg = p->ExceptionRecord->ExceptionCode == EXCEPTION_STACK_OVERFLOW
            ? "gocpp: fatal: stack overflow (infinite recursion?)\n"
            : "gocpp: fatal: unhandled hardware exception\n";
        DWORD n;
        WriteFile(GetStdHandle(STD_ERROR_HANDLE), msg, (DWORD)strlen(msg), &n, nullptr);
        return EXCEPTION_CONTINUE_SEARCH; // keep the normal exit code
    }
    inline void install_crash_handler() { SetUnhandledExceptionFilter(crash_filter); }
}
#elif defined(__linux__) || defined(__APPLE__) || defined(__FreeBSD__)
#include <csignal>
#include <unistd.h>
namespace gocpp
{
    inline void install_crash_handler()
    {
        static char altstack[64 * 1024];
        stack_t ss{};
        ss.ss_sp = altstack;
        ss.ss_size = sizeof altstack;
        sigaltstack(&ss, nullptr);

        struct sigaction sa{};
        sa.sa_handler = [](int sig)
        {
            const char msg[] = "gocpp: fatal: SIGSEGV (stack overflow or invalid access)\n";
            write(2, msg, sizeof msg - 1);
            _exit(128 + sig);
        };
        sa.sa_flags = SA_ONSTACK; // needed, the normal stack is exhausted
        sigemptyset(&sa.sa_mask);
        sigaction(SIGSEGV, &sa, nullptr);
    }
}
#else
#include <csignal>
#include <cstdio>
namespace gocpp
{
    inline void install_crash_handler()
    {
        std::signal(SIGSEGV, [](int)
            {
                std::fputs("gocpp: fatal: SIGSEGV (invalid access)\n", stderr); // best effort, not async-signal-safe
                std::_Exit(139);
            });
    }
}
#endif