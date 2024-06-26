// generated by GoCpp from file '$(ImportDir)/runtime/mem.go'
#include <complex>
#include <functional>
#include <iostream>
#include <iomanip>
#include <map>
#include <string>
#include <tuple>
#include <vector>

#include "golang/runtime/mem.h"
#include "gocpp/support.h"

#include "golang/runtime/internal/atomic/types.h"
#include "golang/runtime/mem_windows.h"
// #include "golang/runtime/mstats.h"  [Ignored, known errors]
#include "golang/unsafe/unsafe.h"

namespace golang::runtime
{
    unsafe::Pointer sysAlloc(uintptr_t n, sysMemStat* sysStat)
    {
        add(gocpp::recv(sysStat), int64(n));
        Add(gocpp::recv(gcController.mappedReady), int64(n));
        return sysAllocOS(n);
    }

    void sysUnused(unsafe::Pointer v, uintptr_t n)
    {
        Add(gocpp::recv(gcController.mappedReady), - int64(n));
        sysUnusedOS(v, n);
    }

    void sysUsed(unsafe::Pointer v, uintptr_t n, uintptr_t prepared)
    {
        Add(gocpp::recv(gcController.mappedReady), int64(prepared));
        sysUsedOS(v, n);
    }

    void sysHugePage(unsafe::Pointer v, uintptr_t n)
    {
        sysHugePageOS(v, n);
    }

    void sysNoHugePage(unsafe::Pointer v, uintptr_t n)
    {
        sysNoHugePageOS(v, n);
    }

    void sysHugePageCollapse(unsafe::Pointer v, uintptr_t n)
    {
        sysHugePageCollapseOS(v, n);
    }

    void sysFree(unsafe::Pointer v, uintptr_t n, sysMemStat* sysStat)
    {
        add(gocpp::recv(sysStat), - int64(n));
        Add(gocpp::recv(gcController.mappedReady), - int64(n));
        sysFreeOS(v, n);
    }

    void sysFault(unsafe::Pointer v, uintptr_t n)
    {
        Add(gocpp::recv(gcController.mappedReady), - int64(n));
        sysFaultOS(v, n);
    }

    unsafe::Pointer sysReserve(unsafe::Pointer v, uintptr_t n)
    {
        return sysReserveOS(v, n);
    }

    void sysMap(unsafe::Pointer v, uintptr_t n, sysMemStat* sysStat)
    {
        add(gocpp::recv(sysStat), int64(n));
        sysMapOS(v, n);
    }

}

