// generated by GoCpp from file '$(ImportDir)/syscall/syscall.go'
#include <complex>
#include <functional>
#include <iostream>
#include <iomanip>
#include <map>
#include <string>
#include <tuple>
#include <vector>

#include "golang/syscall/syscall.h"
#include "gocpp/support.h"

#include "golang/internal/bytealg/indexbyte_native.h"
#include "golang/syscall/syscall_windows.h"
#include "golang/syscall/types_windows.h"
#include "golang/syscall/zerrors_windows.h"

namespace golang::syscall
{
    gocpp::slice<unsigned char> StringByteSlice(std::string s)
    {
        auto [a, err] = ByteSliceFromString(s);
        if(err != nullptr)
        {
            gocpp::panic("syscall: string with NUL passed to StringByteSlice");
        }
        return a;
    }

    std::tuple<gocpp::slice<unsigned char>, std::string> ByteSliceFromString(std::string s)
    {
        if(bytealg::IndexByteString(s, 0) != - 1)
        {
            return {nullptr, EINVAL};
        }
        auto a = gocpp::make(gocpp::Tag<gocpp::slice<unsigned char>>(), len(s) + 1);
        copy(a, s);
        return {a, nullptr};
    }

    unsigned char* StringBytePtr(std::string s)
    {
        return & StringByteSlice(s)[0];
    }

    std::tuple<unsigned char*, std::string> BytePtrFromString(std::string s)
    {
        auto [a, err] = ByteSliceFromString(s);
        if(err != nullptr)
        {
            return {nullptr, err};
        }
        return {& a[0], nullptr};
    }

    uintptr_t _zero;
    std::tuple<int64_t, int64_t> Unix(struct Timespec* ts)
    {
        int64_t sec;
        int64_t nsec;
        return {int64_t(ts->Sec), int64_t(ts->Nsec)};
    }

    std::tuple<int64_t, int64_t> Unix(struct Timeval* tv)
    {
        int64_t sec;
        int64_t nsec;
        return {int64_t(tv->Sec), int64_t(tv->Usec) * 1000};
    }

    int64_t Nano(struct Timespec* ts)
    {
        return int64_t(ts->Sec) * 1e9 + int64_t(ts->Nsec);
    }

    int64_t Nano(struct Timeval* tv)
    {
        return int64_t(tv->Sec) * 1e9 + int64_t(tv->Usec) * 1000;
    }

    int Getpagesize()
    /* convertBlockStmt, nil block */;

    void Exit(int code)
    /* convertBlockStmt, nil block */;

    void runtimeSetenv(std::string k, std::string v)
    /* convertBlockStmt, nil block */;

    void runtimeUnsetenv(std::string k)
    /* convertBlockStmt, nil block */;

}

