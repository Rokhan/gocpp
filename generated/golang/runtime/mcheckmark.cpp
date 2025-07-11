// generated by GoCpp from file '$(ImportDir)/runtime/mcheckmark.go'
#include <complex>
#include <functional>
#include <iostream>
#include <iomanip>
#include <map>
#include <string>
#include <tuple>
#include <vector>

#include "golang/runtime/mcheckmark.h"
#include "gocpp/support.h"

#include "golang/internal/abi/type.h"
#include "golang/internal/chacha8rand/chacha8.h"
#include "golang/internal/cpu/cpu.h"
#include "golang/internal/goarch/goarch.h"
#include "golang/runtime/cgocall.h"
#include "golang/runtime/chan.h"
#include "golang/runtime/coro.h"
#include "golang/runtime/debuglog_off.h"
#include "golang/runtime/internal/atomic/atomic_amd64.h"
#include "golang/runtime/internal/atomic/types.h"
#include "golang/runtime/internal/sys/nih.h"
#include "golang/runtime/lockrank.h"
#include "golang/runtime/lockrank_off.h"
#include "golang/runtime/malloc.h"
#include "golang/runtime/mbitmap.h"
#include "golang/runtime/mbitmap_allocheaders.h"
#include "golang/runtime/mcache.h"
#include "golang/runtime/mcentral.h"
#include "golang/runtime/mfixalloc.h"
#include "golang/runtime/mgc.h"
#include "golang/runtime/mgclimit.h"
#include "golang/runtime/mgcmark.h"
#include "golang/runtime/mgcscavenge.h"
#include "golang/runtime/mgcwork.h"
#include "golang/runtime/mheap.h"
#include "golang/runtime/mpagealloc.h"
#include "golang/runtime/mpagecache.h"
#include "golang/runtime/mpallocbits.h"
#include "golang/runtime/mprof.h"
#include "golang/runtime/mranges.h"
#include "golang/runtime/mspanset.h"
#include "golang/runtime/mstats.h"
#include "golang/runtime/mwbbuf.h"
#include "golang/runtime/os_windows.h"
#include "golang/runtime/pagetrace_off.h"
#include "golang/runtime/panic.h"
#include "golang/runtime/pinner.h"
#include "golang/runtime/print.h"
#include "golang/runtime/proc.h"
#include "golang/runtime/runtime2.h"
#include "golang/runtime/signal_windows.h"
#include "golang/runtime/stubs.h"
#include "golang/runtime/symtab.h"
#include "golang/runtime/time.h"
#include "golang/runtime/trace2buf.h"
#include "golang/runtime/trace2runtime.h"
#include "golang/runtime/trace2status.h"
#include "golang/runtime/trace2time.h"

namespace golang::runtime
{
    namespace rec
    {
        using namespace mocklib::rec;
    }

    // A checkmarksMap stores the GC marks in "checkmarks" mode. It is a
    // per-arena bitmap with a bit for every word in the arena. The mark
    // is stored on the bit corresponding to the first word of the marked
    // allocation.
    
    template<typename T> requires gocpp::GoStruct<T>
    checkmarksMap::operator T()
    {
        T result;
        result._1 = this->_1;
        result.b = this->b;
        return result;
    }

    template<typename T> requires gocpp::GoStruct<T>
    bool checkmarksMap::operator==(const T& ref) const
    {
        if (_1 != ref._1) return false;
        if (b != ref.b) return false;
        return true;
    }

    std::ostream& checkmarksMap::PrintTo(std::ostream& os) const
    {
        os << '{';
        os << "" << _1;
        os << " " << b;
        os << '}';
        return os;
    }

    std::ostream& operator<<(std::ostream& os, const struct checkmarksMap& value)
    {
        return value.PrintTo(os);
    }

    // If useCheckmark is true, marking of an object uses the checkmark
    // bits instead of the standard mark bits.
    bool useCheckmark = false;
    // startCheckmarks prepares for the checkmarks phase.
    //
    // The world must be stopped.
    void startCheckmarks()
    {
        assertWorldStopped();
        for(auto [gocpp_ignored, ai] : mheap_.allArenas)
        {
            auto arena = mheap_.arenas[rec::l1(gocpp::recv(ai))][rec::l2(gocpp::recv(ai))];
            auto bitmap = arena->checkmarks;
            if(bitmap == nullptr)
            {
                bitmap = (checkmarksMap*)(persistentalloc(gocpp::Sizeof<checkmarksMap>(), 0, & memstats.gcMiscSys));
                if(bitmap == nullptr)
                {
                    go_throw("out of memory allocating checkmarks bitmap"s);
                }
                arena->checkmarks = bitmap;
            }
            else
            {
                for(auto [i, gocpp_ignored] : bitmap->b)
                {
                    bitmap->b[i] = 0;
                }
            }
        }
        useCheckmark = true;
    }

    // endCheckmarks ends the checkmarks phase.
    void endCheckmarks()
    {
        if(gcMarkWorkAvailable(nullptr))
        {
            go_throw("GC work not flushed"s);
        }
        useCheckmark = false;
    }

    // setCheckmark throws if marking object is a checkmarks violation,
    // and otherwise sets obj's checkmark. It returns true if obj was
    // already checkmarked.
    bool setCheckmark(uintptr_t obj, uintptr_t base, uintptr_t off, struct markBits mbits)
    {
        if(! rec::isMarked(gocpp::recv(mbits)))
        {
            printlock();
            print("runtime: checkmarks found unexpected unmarked object obj="s, hex(obj), "\n"s);
            print("runtime: found obj at *("s, hex(base), "+"s, hex(off), ")\n"s);
            gcDumpObject("base"s, base, off);
            gcDumpObject("obj"s, obj, ~ uintptr_t(0));
            getg()->m->traceback = 2;
            go_throw("checkmark found unmarked object"s);
        }
        auto ai = arenaIndex(obj);
        auto arena = mheap_.arenas[rec::l1(gocpp::recv(ai))][rec::l2(gocpp::recv(ai))];
        auto arenaWord = (obj / heapArenaBytes / 8) % uintptr_t(len(arena->checkmarks->b));
        auto mask = (unsigned char)(1 << ((obj / heapArenaBytes) % 8));
        auto bytep = & arena->checkmarks->b[arenaWord];
        if(atomic::Load8(bytep) & mask != 0)
        {
            return true;
        }
        atomic::Or8(bytep, mask);
        return false;
    }

}

