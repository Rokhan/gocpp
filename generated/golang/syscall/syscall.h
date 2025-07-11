// generated by GoCpp from file '$(ImportDir)/syscall/syscall.go'
#pragma once

#include <functional>
#include <string>
#include <tuple>
#include <vector>

#include "golang/syscall/syscall.fwd.h"
#include "gocpp/support.h"

#include "golang/syscall/syscall_windows.h"
#include "golang/syscall/types_windows.h"

namespace golang::syscall
{
    gocpp::slice<unsigned char> StringByteSlice(std::string s);
    std::tuple<gocpp::slice<unsigned char>, struct gocpp::error> ByteSliceFromString(std::string s);
    unsigned char* StringBytePtr(std::string s);
    std::tuple<unsigned char*, struct gocpp::error> BytePtrFromString(std::string s);
    extern uintptr_t _zero;
    int Getpagesize();
    void Exit(int code);
    void runtimeSetenv(std::string k, std::string v);
    void runtimeUnsetenv(std::string k);

    namespace rec
    {
        std::tuple<int64_t, int64_t> Unix(struct Timespec* ts);
        std::tuple<int64_t, int64_t> Unix(struct Timeval* tv);
        int64_t Nano(struct Timespec* ts);
        int64_t Nano(struct Timeval* tv);
    }
}

