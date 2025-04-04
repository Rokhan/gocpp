// generated by GoCpp from file '$(ImportDir)/runtime/mwbbuf.go'
#include <complex>
#include <functional>
#include <iostream>
#include <iomanip>
#include <map>
#include <string>
#include <tuple>
#include <vector>

#include "golang/runtime/mwbbuf.h"
#include "gocpp/support.h"

#include "golang/internal/abi/type.h"
#include "golang/internal/chacha8rand/chacha8.h"
#include "golang/internal/goarch/goarch.h"
// #include "golang/runtime/cgocall.h"  [Ignored, known errors]
#include "golang/runtime/chan.h"
#include "golang/runtime/coro.h"
#include "golang/runtime/debuglog_off.h"
#include "golang/runtime/internal/atomic/atomic_amd64.h"
#include "golang/runtime/internal/atomic/types.h"
#include "golang/runtime/internal/sys/nih.h"
// #include "golang/runtime/lockrank.h"  [Ignored, known errors]
// #include "golang/runtime/lockrank_off.h"  [Ignored, known errors]
#include "golang/runtime/malloc.h"
#include "golang/runtime/mbitmap.h"
// #include "golang/runtime/mbitmap_allocheaders.h"  [Ignored, known errors]
// #include "golang/runtime/mcache.h"  [Ignored, known errors]
#include "golang/runtime/mcheckmark.h"
#include "golang/runtime/mgc.h"
// #include "golang/runtime/mgclimit.h"  [Ignored, known errors]
#include "golang/runtime/mgcmark.h"
#include "golang/runtime/mgcwork.h"
#include "golang/runtime/mheap.h"
#include "golang/runtime/mpagecache.h"
#include "golang/runtime/mprof.h"
#include "golang/runtime/mranges.h"
// #include "golang/runtime/os_windows.h"  [Ignored, known errors]
// #include "golang/runtime/pagetrace_off.h"  [Ignored, known errors]
#include "golang/runtime/panic.h"
#include "golang/runtime/pinner.h"
#include "golang/runtime/proc.h"
#include "golang/runtime/runtime2.h"
// #include "golang/runtime/signal_windows.h"  [Ignored, known errors]
// #include "golang/runtime/stubs.h"  [Ignored, known errors]
// #include "golang/runtime/symtab.h"  [Ignored, known errors]
// #include "golang/runtime/time.h"  [Ignored, known errors]
#include "golang/runtime/trace2buf.h"
// #include "golang/runtime/trace2runtime.h"  [Ignored, known errors]
#include "golang/runtime/trace2status.h"
#include "golang/runtime/trace2time.h"
#include "golang/unsafe/unsafe.h"

namespace golang::runtime
{
    
    template<typename T> requires gocpp::GoStruct<T>
    wbBuf::operator T()
    {
        T result;
        result.next = this->next;
        result.end = this->end;
        result.buf = this->buf;
        return result;
    }

    template<typename T> requires gocpp::GoStruct<T>
    bool wbBuf::operator==(const T& ref) const
    {
        if (next != ref.next) return false;
        if (end != ref.end) return false;
        if (buf != ref.buf) return false;
        return true;
    }

    std::ostream& wbBuf::PrintTo(std::ostream& os) const
    {
        os << '{';
        os << "" << next;
        os << " " << end;
        os << " " << buf;
        os << '}';
        return os;
    }

    std::ostream& operator<<(std::ostream& os, const struct wbBuf& value)
    {
        return value.PrintTo(os);
    }

    void reset(struct wbBuf* b)
    {
        auto start = uintptr_t(unsafe::Pointer(& b->buf[0]));
        b->next = start;
        if(testSmallBuf)
        {
            b->end = uintptr_t(unsafe::Pointer(& b->buf[wbMaxEntriesPerCall + 1]));
        }
        else
        {
            b->end = start + uintptr_t(len(b->buf)) * gocpp::Sizeof<uintptr_t>();
        }
        if((b->end - b->next) % gocpp::Sizeof<uintptr_t>() != 0)
        {
            go_throw("bad write barrier buffer bounds");
        }
    }

    void discard(struct wbBuf* b)
    {
        b->next = uintptr_t(unsafe::Pointer(& b->buf[0]));
    }

    bool empty(struct wbBuf* b)
    {
        return b->next == uintptr_t(unsafe::Pointer(& b->buf[0]));
    }

    gocpp::array<uintptr_t, 1>* get1(struct wbBuf* b)
    {
        if(b->next + goarch::PtrSize > b->end)
        {
            wbBufFlush();
        }
        auto p = (gocpp::array<uintptr_t, 1>*)(unsafe::Pointer(b->next));
        b->next += goarch::PtrSize;
        return p;
    }

    gocpp::array<uintptr_t, 2>* get2(struct wbBuf* b)
    {
        if(b->next + 2 * goarch::PtrSize > b->end)
        {
            wbBufFlush();
        }
        auto p = (gocpp::array<uintptr_t, 2>*)(unsafe::Pointer(b->next));
        b->next += 2 * goarch::PtrSize;
        return p;
    }

    void wbBufFlush()
    {
        if(getg()->m->dying > 0)
        {
            discard(gocpp::recv(ptr(gocpp::recv(getg()->m->p))->wbBuf));
            return;
        }
        systemstack([=]() mutable -> void
        {
            wbBufFlush1(ptr(gocpp::recv(getg()->m->p)));
        });
    }

    void wbBufFlush1(p* pp)
    {
        auto start = uintptr_t(unsafe::Pointer(& pp->wbBuf.buf[0]));
        auto n = (pp->wbBuf.next - start) / gocpp::Sizeof<uintptr_t>();
        auto ptrs = pp->wbBuf.buf.make_slice(0, n);
        pp->wbBuf.next = 0;
        if(useCheckmark)
        {
            for(auto [_, ptr] : ptrs)
            {
                shade(ptr);
            }
            reset(gocpp::recv(pp->wbBuf));
            return;
        }
        auto gcw = & pp->gcw;
        auto pos = 0;
        for(auto [_, ptr] : ptrs)
        {
            if(ptr < minLegalPointer)
            {
                continue;
            }
            auto [obj, span, objIndex] = findObject(ptr, 0, 0);
            if(obj == 0)
            {
                continue;
            }
            auto mbits = markBitsForIndex(gocpp::recv(span), objIndex);
            if(isMarked(gocpp::recv(mbits)))
            {
                continue;
            }
            setMarked(gocpp::recv(mbits));
            auto [arena, pageIdx, pageMask] = pageIndexOf(base(gocpp::recv(span)));
            if(arena->pageMarks[pageIdx] & pageMask == 0)
            {
                atomic::Or8(& arena->pageMarks[pageIdx], pageMask);
            }
            if(noscan(gocpp::recv(span->spanclass)))
            {
                gcw->bytesMarked += uint64_t(span->elemsize);
                continue;
            }
            ptrs[pos] = obj;
            pos++;
        }
        putBatch(gocpp::recv(gcw), ptrs.make_slice(0, pos));
        reset(gocpp::recv(pp->wbBuf));
    }

}

