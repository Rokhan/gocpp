// generated by GoCpp from file '$(ImportDir)/runtime/mem_windows.go'
#pragma once

#include <functional>
#include <string>
#include <tuple>
#include <vector>

#include "golang/runtime/mem_windows.fwd.h"
#include "gocpp/support.h"

// #include "golang/runtime/os_windows.h"  [Ignored, known errors]
#include "golang/runtime/panic.h"
// #include "golang/runtime/stubs.h"  [Ignored, known errors]
#include "golang/unsafe/unsafe.h"

namespace golang::runtime
{
    unsafe::Pointer sysAllocOS(uintptr_t n);
    void sysUnusedOS(unsafe::Pointer v, uintptr_t n);
    void sysUsedOS(unsafe::Pointer v, uintptr_t n);
    void sysHugePageOS(unsafe::Pointer v, uintptr_t n);
    void sysNoHugePageOS(unsafe::Pointer v, uintptr_t n);
    void sysHugePageCollapseOS(unsafe::Pointer v, uintptr_t n);
    void sysFreeOS(unsafe::Pointer v, uintptr_t n);
    void sysFaultOS(unsafe::Pointer v, uintptr_t n);
    unsafe::Pointer sysReserveOS(unsafe::Pointer v, uintptr_t n);
    void sysMapOS(unsafe::Pointer v, uintptr_t n);
}

