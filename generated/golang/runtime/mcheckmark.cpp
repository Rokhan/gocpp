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

#include "golang/internal/goarch/goarch.h"
#include "golang/runtime/internal/atomic/atomic_amd64.h"
#include "golang/runtime/internal/sys/nih.h"
// #include "golang/runtime/lockrank_off.h"  [Ignored, known errors]
#include "golang/runtime/malloc.h"
#include "golang/runtime/mbitmap.h"
#include "golang/runtime/mgc.h"
#include "golang/runtime/mgcmark.h"
#include "golang/runtime/mheap.h"
#include "golang/runtime/panic.h"
// #include "golang/runtime/print.h"  [Ignored, known errors]
// #include "golang/runtime/stubs.h"  [Ignored, known errors]

namespace golang::runtime
{
    
    std::ostream& checkmarksMap::PrintTo(std::ostream& os) const
    {
        os << '{';
        os << "" << _;
        os << " " << b;
        os << '}';
        return os;
    }

    std::ostream& operator<<(std::ostream& os, const struct checkmarksMap& value)
    {
        return value.PrintTo(os);
    }

    bool useCheckmark = false;
    void startCheckmarks()
    {
        assertWorldStopped();
        for(auto [_, ai] : mheap_.allArenas)
        {
            auto arena = mheap_.arenas[l1(gocpp::recv(ai))][l2(gocpp::recv(ai))];
            auto bitmap = arena->checkmarks;
            if(bitmap == nullptr)
            {
                bitmap = (checkmarksMap*)(persistentalloc(unsafe::Sizeof(*bitmap), 0, & memstats.gcMiscSys));
                if(bitmap == nullptr)
                {
                    go_throw("out of memory allocating checkmarks bitmap");
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

    void endCheckmarks()
    {
        if(gcMarkWorkAvailable(nullptr))
        {
            go_throw("GC work not flushed");
        }
        useCheckmark = false;
    }

    bool setCheckmark(uintptr_t obj, uintptr_t base, uintptr_t off, markBits mbits)
    {
        if(! isMarked(gocpp::recv(mbits)))
        {
            printlock();
            print("runtime: checkmarks found unexpected unmarked object obj=", hex(obj), "\n");
            print("runtime: found obj at *(", hex(base), "+", hex(off), ")\n");
            gcDumpObject("base", base, off);
            gcDumpObject("obj", obj, ~ uintptr_t(0));
            getg()->m->traceback = 2;
            go_throw("checkmark found unmarked object");
        }
        auto ai = arenaIndex(obj);
        auto arena = mheap_.arenas[l1(gocpp::recv(ai))][l2(gocpp::recv(ai))];
        auto arenaWord = (obj / heapArenaBytes / 8) % uintptr_t(len(arena->checkmarks->b));
        auto mask = unsigned char(1 << ((obj / heapArenaBytes) % 8));
        auto bytep = & arena->checkmarks->b[arenaWord];
        if(atomic::Load8(bytep) & mask != 0)
        {
            return true;
        }
        atomic::Or8(bytep, mask);
        return false;
    }

}
