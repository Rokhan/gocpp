// generated by GoCpp from file '$(ImportDir)/runtime/mem_windows.go'
#include <complex>
#include <functional>
#include <iostream>
#include <iomanip>
#include <map>
#include <string>
#include <tuple>
#include <vector>

#include "golang/runtime/mem_windows.h"
#include "gocpp/support.h"

// #include "golang/runtime/os_windows.h"  [Ignored, known errors]
#include "golang/runtime/panic.h"
// #include "golang/runtime/stubs.h"  [Ignored, known errors]
#include "golang/unsafe/unsafe.h"

namespace golang::runtime
{
    unsafe::Pointer sysAllocOS(uintptr_t n)
    {
        return unsafe::Pointer(stdcall4(_VirtualAlloc, 0, n, _MEM_COMMIT | _MEM_RESERVE, _PAGE_READWRITE));
    }

    void sysUnusedOS(unsafe::Pointer v, uintptr_t n)
    {
        auto r = stdcall3(_VirtualFree, uintptr_t(v), n, _MEM_DECOMMIT);
        if(r != 0)
        {
            return;
        }
        for(; n > 0; )
        {
            auto small = n;
            for(; small >= 4096 && stdcall3(_VirtualFree, uintptr_t(v), small, _MEM_DECOMMIT) == 0; )
            {
                small /= 2;
                small &^= 4096 - 1;
            }
            if(small < 4096)
            {
                print("runtime: VirtualFree of ", small, " bytes failed with errno=", getlasterror(), "\n");
                go_throw("runtime: failed to decommit pages");
            }
            v = add(v, small);
            n -= small;
        }
    }

    void sysUsedOS(unsafe::Pointer v, uintptr_t n)
    {
        auto p = stdcall4(_VirtualAlloc, uintptr_t(v), n, _MEM_COMMIT, _PAGE_READWRITE);
        if(p == uintptr_t(v))
        {
            return;
        }
        auto k = n;
        for(; k > 0; )
        {
            auto small = k;
            for(; small >= 4096 && stdcall4(_VirtualAlloc, uintptr_t(v), small, _MEM_COMMIT, _PAGE_READWRITE) == 0; )
            {
                small /= 2;
                small &^= 4096 - 1;
            }
            if(small < 4096)
            {
                auto errno = getlasterror();
                //Go switch emulation
                {
                    auto condition = errno;
                    int conditionId = -1;
                    if(condition == _ERROR_NOT_ENOUGH_MEMORY) { conditionId = 0; }
                    if(condition == _ERROR_COMMITMENT_LIMIT) { conditionId = 1; }
                    switch(conditionId)
                    {
                        case 0:
                        case 1:
                            print("runtime: VirtualAlloc of ", n, " bytes failed with errno=", errno, "\n");
                            go_throw("out of memory");
                            break;
                        default:
                            print("runtime: VirtualAlloc of ", small, " bytes failed with errno=", errno, "\n");
                            go_throw("runtime: failed to commit pages");
                            break;
                    }
                }
            }
            v = add(v, small);
            k -= small;
        }
    }

    void sysHugePageOS(unsafe::Pointer v, uintptr_t n)
    {
    }

    void sysNoHugePageOS(unsafe::Pointer v, uintptr_t n)
    {
    }

    void sysHugePageCollapseOS(unsafe::Pointer v, uintptr_t n)
    {
    }

    void sysFreeOS(unsafe::Pointer v, uintptr_t n)
    {
        auto r = stdcall3(_VirtualFree, uintptr_t(v), 0, _MEM_RELEASE);
        if(r == 0)
        {
            print("runtime: VirtualFree of ", n, " bytes failed with errno=", getlasterror(), "\n");
            go_throw("runtime: failed to release pages");
        }
    }

    void sysFaultOS(unsafe::Pointer v, uintptr_t n)
    {
        sysUnusedOS(v, n);
    }

    unsafe::Pointer sysReserveOS(unsafe::Pointer v, uintptr_t n)
    {
        v = unsafe::Pointer(stdcall4(_VirtualAlloc, uintptr_t(v), n, _MEM_RESERVE, _PAGE_READWRITE));
        if(v != nullptr)
        {
            return v;
        }
        return unsafe::Pointer(stdcall4(_VirtualAlloc, 0, n, _MEM_RESERVE, _PAGE_READWRITE));
    }

    void sysMapOS(unsafe::Pointer v, uintptr_t n)
    {
    }

}

