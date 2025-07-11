// generated by GoCpp from file '$(ImportDir)/runtime/profbuf.go'
#pragma once

#include <functional>
#include <string>
#include <tuple>
#include <vector>

#include "golang/runtime/profbuf.fwd.h"
#include "gocpp/support.h"

#include "golang/runtime/internal/atomic/types.h"
#include "golang/runtime/runtime2.h"

namespace golang::runtime
{
    struct profBuf
    {
        golang::runtime::profAtomic r;
        golang::runtime::profAtomic w;
        atomic::Uint64 overflow;
        atomic::Uint64 overflowTime;
        atomic::Uint32 eof;
        uintptr_t hdrsize;
        gocpp::slice<uint64_t> data;
        gocpp::slice<unsafe::Pointer> tags;
        golang::runtime::profIndex rNext;
        gocpp::slice<uint64_t> overflowBuf;
        /* note wait; [Known incomplete type] */

        using isGoStruct = void;

        template<typename T> requires gocpp::GoStruct<T>
        operator T();

        template<typename T> requires gocpp::GoStruct<T>
        bool operator==(const T& ref) const;

        std::ostream& PrintTo(std::ostream& os) const;
    };

    std::ostream& operator<<(std::ostream& os, const struct profBuf& value);
    int countSub(uint32_t x, uint32_t y);
    struct profBuf* newProfBuf(int hdrsize, int bufwords, int tags);
    extern gocpp::array<unsafe::Pointer, 1> overflowTag;

    namespace rec
    {
        runtime::profIndex load(golang::runtime::profAtomic* x);
        void store(golang::runtime::profAtomic* x, golang::runtime::profIndex go_new);
        bool cas(golang::runtime::profAtomic* x, golang::runtime::profIndex old, golang::runtime::profIndex go_new);
        uint32_t dataCount(golang::runtime::profIndex x);
        uint32_t tagCount(golang::runtime::profIndex x);
        runtime::profIndex addCountsAndClearFlags(golang::runtime::profIndex x, int data, int tag);
        bool hasOverflow(struct profBuf* b);
        std::tuple<uint32_t, uint64_t> takeOverflow(struct profBuf* b);
        void incrementOverflow(struct profBuf* b, int64_t now);
        bool canWriteRecord(struct profBuf* b, int nstk);
        bool canWriteTwoRecords(struct profBuf* b, int nstk1, int nstk2);
        void write(struct profBuf* b, unsafe::Pointer* tagPtr, int64_t now, gocpp::slice<uint64_t> hdr, gocpp::slice<uintptr_t> stk);
        void close(struct profBuf* b);
        void wakeupExtra(struct profBuf* b);
        std::tuple<gocpp::slice<uint64_t>, gocpp::slice<unsafe::Pointer>, bool> read(struct profBuf* b, golang::runtime::profBufReadMode mode);
    }
}

