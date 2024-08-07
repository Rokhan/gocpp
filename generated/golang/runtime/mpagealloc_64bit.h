// generated by GoCpp from file '$(ImportDir)/runtime/mpagealloc_64bit.go'
#pragma once

#include <functional>
#include <string>
#include <tuple>
#include <vector>

#include "golang/runtime/mpagealloc_64bit.fwd.h"
#include "gocpp/support.h"

#include "golang/runtime/internal/atomic/types.h"
#include "golang/runtime/malloc.h"
#include "golang/runtime/mem.h"
// #include "golang/runtime/mgcscavenge.h"  [Ignored, known errors]
#include "golang/runtime/mpagealloc.h"
#include "golang/runtime/mranges.h"
#include "golang/runtime/mstats.h"
#include "golang/runtime/panic.h"
// #include "golang/runtime/print.h"  [Ignored, known errors]
#include "golang/runtime/slice.h"
// #include "golang/runtime/stubs.h"  [Ignored, known errors]
#include "golang/unsafe/unsafe.h"

namespace golang::runtime
{
    extern gocpp::array<unsigned int, summaryLevels> levelBits;
    extern gocpp::array<unsigned int, summaryLevels> levelShift;
    extern gocpp::array<unsigned int, summaryLevels> levelLogPages;
    void sysInit(struct pageAlloc* p, bool test);
    void sysGrow(struct pageAlloc* p, uintptr_t base, uintptr_t limit);
    uintptr_t sysGrow(struct scavengeIndex* s, uintptr_t base, uintptr_t limit, sysMemStat* sysStat);
    uintptr_t sysInit(struct scavengeIndex* s, bool test, sysMemStat* sysStat);
}

