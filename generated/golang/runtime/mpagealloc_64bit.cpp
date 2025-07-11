// generated by GoCpp from file '$(ImportDir)/runtime/mpagealloc_64bit.go'
#include <complex>
#include <functional>
#include <iostream>
#include <iomanip>
#include <map>
#include <string>
#include <tuple>
#include <vector>

#include "golang/runtime/mpagealloc_64bit.h"
#include "gocpp/support.h"

#include "golang/runtime/internal/atomic/types.h"
#include "golang/runtime/internal/sys/nih.h"
#include "golang/runtime/lockrank_off.h"
#include "golang/runtime/malloc.h"
#include "golang/runtime/mem.h"
#include "golang/runtime/mgcscavenge.h"
#include "golang/runtime/mpagealloc.h"
#include "golang/runtime/mpallocbits.h"
#include "golang/runtime/mranges.h"
#include "golang/runtime/mstats.h"
#include "golang/runtime/panic.h"
#include "golang/runtime/print.h"
#include "golang/runtime/runtime2.h"
#include "golang/runtime/slice.h"
#include "golang/runtime/stubs.h"
#include "golang/unsafe/unsafe.h"

namespace golang::runtime
{
    namespace rec
    {
        using namespace mocklib::rec;
        using atomic::rec::Load;
        using atomic::rec::Store;
    }

    // The number of levels in the radix tree.
    // Constants for testing.
    // Number of bits needed to represent all indices into the L1 of the
    // chunks map.
    //
    // See (*pageAlloc).chunks for more details. Update the documentation
    // there should this number change.
    // levelBits is the number of bits in the radix for a given level in the super summary
    // structure.
    //
    // The sum of all the entries of levelBits should equal heapAddrBits.
    gocpp::array<unsigned int, summaryLevels> levelBits = gocpp::array<unsigned int, summaryLevels> {summaryL0Bits, summaryLevelBits, summaryLevelBits, summaryLevelBits, summaryLevelBits};
    // levelShift is the number of bits to shift to acquire the radix for a given level
    // in the super summary structure.
    //
    // With levelShift, one can compute the index of the summary at level l related to a
    // pointer p by doing:
    //
    //	p >> levelShift[l]
    gocpp::array<unsigned int, summaryLevels> levelShift = gocpp::array<unsigned int, summaryLevels> {heapAddrBits - summaryL0Bits, heapAddrBits - summaryL0Bits - 1 * summaryLevelBits, heapAddrBits - summaryL0Bits - 2 * summaryLevelBits, heapAddrBits - summaryL0Bits - 3 * summaryLevelBits, heapAddrBits - summaryL0Bits - 4 * summaryLevelBits};
    // levelLogPages is log2 the maximum number of runtime pages in the address space
    // a summary in the given level represents.
    //
    // The leaf level always represents exactly log2 of 1 chunk's worth of pages.
    gocpp::array<unsigned int, summaryLevels> levelLogPages = gocpp::array<unsigned int, summaryLevels> {logPallocChunkPages + 4 * summaryLevelBits, logPallocChunkPages + 3 * summaryLevelBits, logPallocChunkPages + 2 * summaryLevelBits, logPallocChunkPages + 1 * summaryLevelBits, logPallocChunkPages};
    // sysInit performs architecture-dependent initialization of fields
    // in pageAlloc. pageAlloc should be uninitialized except for sysStat
    // if any runtime statistic should be updated.
    void rec::sysInit(struct pageAlloc* p, bool test)
    {
        for(auto [l, shift] : levelShift)
        {
            auto entries = 1 << (heapAddrBits - shift);
            auto b = alignUp(uintptr_t(entries) * pallocSumBytes, physPageSize);
            auto r = sysReserve(nullptr, b);
            if(r == nullptr)
            {
                go_throw("failed to reserve page summary memory"s);
            }
            auto sl = notInHeapSlice {(notInHeap*)(r), 0, entries};
            p->summary[l] = *(gocpp::slice<runtime::pallocSum>*)(unsafe::Pointer(& sl));
        }
    }

    // sysGrow performs architecture-dependent operations on heap
    // growth for the page allocator, such as mapping in new memory
    // for summaries. It also updates the length of the slices in
    // p.summary.
    //
    // base is the base of the newly-added heap memory and limit is
    // the first address past the end of the newly-added heap memory.
    // Both must be aligned to pallocChunkBytes.
    //
    // The caller must update p.start and p.end after calling sysGrow.
    void rec::sysGrow(struct pageAlloc* p, uintptr_t base, uintptr_t limit)
    {
        if(base % pallocChunkBytes != 0 || limit % pallocChunkBytes != 0)
        {
            print("runtime: base = "s, hex(base), ", limit = "s, hex(limit), "\n"s);
            go_throw("sysGrow bounds not aligned to pallocChunkBytes"s);
        }
        auto addrRangeToSummaryRange = [=](int level, struct addrRange r) mutable -> std::tuple<int, int>
        {
            auto [sumIdxBase, sumIdxLimit] = addrsToSummaryRange(level, rec::addr(gocpp::recv(r.base)), rec::addr(gocpp::recv(r.limit)));
            return blockAlignSummaryRange(level, sumIdxBase, sumIdxLimit);
        };
        auto summaryRangeToSumAddrRange = [=](int level, int sumIdxBase, int sumIdxLimit) mutable -> struct addrRange
        {
            auto baseOffset = alignDown(uintptr_t(sumIdxBase) * pallocSumBytes, physPageSize);
            auto limitOffset = alignUp(uintptr_t(sumIdxLimit) * pallocSumBytes, physPageSize);
            auto base = unsafe::Pointer(& p->summary[level][0]);
            return addrRange {offAddr {uintptr_t(add(base, baseOffset))}, offAddr {uintptr_t(add(base, limitOffset))}};
        };
        auto addrRangeToSumAddrRange = [=](int level, struct addrRange r) mutable -> struct addrRange
        {
            auto [sumIdxBase, sumIdxLimit] = addrRangeToSummaryRange(level, r);
            return summaryRangeToSumAddrRange(level, sumIdxBase, sumIdxLimit);
        };
        auto inUseIndex = rec::findSucc(gocpp::recv(p->inUse), base);
        for(auto [l, gocpp_ignored] : p->summary)
        {
            auto [needIdxBase, needIdxLimit] = addrRangeToSummaryRange(l, makeAddrRange(base, limit));
            if(needIdxLimit > len(p->summary[l]))
            {
                p->summary[l] = p->summary[l].make_slice(0, needIdxLimit);
            }
            auto need = summaryRangeToSumAddrRange(l, needIdxBase, needIdxLimit);
            if(inUseIndex > 0)
            {
                need = rec::subtract(gocpp::recv(need), addrRangeToSumAddrRange(l, p->inUse.ranges[inUseIndex - 1]));
            }
            if(inUseIndex < len(p->inUse.ranges))
            {
                need = rec::subtract(gocpp::recv(need), addrRangeToSumAddrRange(l, p->inUse.ranges[inUseIndex]));
            }
            if(rec::size(gocpp::recv(need)) == 0)
            {
                continue;
            }
            sysMap(unsafe::Pointer(rec::addr(gocpp::recv(need.base))), rec::size(gocpp::recv(need)), p->sysStat);
            sysUsed(unsafe::Pointer(rec::addr(gocpp::recv(need.base))), rec::size(gocpp::recv(need)), rec::size(gocpp::recv(need)));
            p->summaryMappedReady += rec::size(gocpp::recv(need));
        }
        p->summaryMappedReady += rec::sysGrow(gocpp::recv(p->scav.index), base, limit, p->sysStat);
    }

    // sysGrow increases the index's backing store in response to a heap growth.
    //
    // Returns the amount of memory added to sysStat.
    uintptr_t rec::sysGrow(struct scavengeIndex* s, uintptr_t base, uintptr_t limit, golang::runtime::sysMemStat* sysStat)
    {
        if(base % pallocChunkBytes != 0 || limit % pallocChunkBytes != 0)
        {
            print("runtime: base = "s, hex(base), ", limit = "s, hex(limit), "\n"s);
            go_throw("sysGrow bounds not aligned to pallocChunkBytes"s);
        }
        auto scSize = gocpp::Sizeof<atomicScavChunkData>();
        auto haveMin = rec::Load(gocpp::recv(s->min));
        auto haveMax = rec::Load(gocpp::recv(s->max));
        auto needMin = alignDown(uintptr_t(chunkIndex(base)), physPageSize / scSize);
        auto needMax = alignUp(uintptr_t(chunkIndex(limit)), physPageSize / scSize);
        if(needMax < haveMin)
        {
            needMax = haveMin;
        }
        if(haveMax != 0 && needMin > haveMax)
        {
            needMin = haveMax;
        }
        auto chunksBase = uintptr_t(unsafe::Pointer(& s->chunks[0]));
        auto have = makeAddrRange(chunksBase + haveMin * scSize, chunksBase + haveMax * scSize);
        auto need = makeAddrRange(chunksBase + needMin * scSize, chunksBase + needMax * scSize);
        need = rec::subtract(gocpp::recv(need), have);
        if(rec::size(gocpp::recv(need)) != 0)
        {
            sysMap(unsafe::Pointer(rec::addr(gocpp::recv(need.base))), rec::size(gocpp::recv(need)), sysStat);
            sysUsed(unsafe::Pointer(rec::addr(gocpp::recv(need.base))), rec::size(gocpp::recv(need)), rec::size(gocpp::recv(need)));
            if(haveMax == 0 || needMin < haveMin)
            {
                rec::Store(gocpp::recv(s->min), needMin);
            }
            if(needMax > haveMax)
            {
                rec::Store(gocpp::recv(s->max), needMax);
            }
        }
        return rec::size(gocpp::recv(need));
    }

    // sysInit initializes the scavengeIndex' chunks array.
    //
    // Returns the amount of memory added to sysStat.
    uintptr_t rec::sysInit(struct scavengeIndex* s, bool test, golang::runtime::sysMemStat* sysStat)
    {
        auto n = uintptr_t(1 << heapAddrBits) / pallocChunkBytes;
        auto nbytes = n * gocpp::Sizeof<atomicScavChunkData>();
        auto r = sysReserve(nullptr, nbytes);
        auto sl = notInHeapSlice {(notInHeap*)(r), int(n), int(n)};
        s->chunks = *(gocpp::slice<atomicScavChunkData>*)(unsafe::Pointer(& sl));
        return 0;
    }

}

