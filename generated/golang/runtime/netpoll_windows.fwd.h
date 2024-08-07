// generated by GoCpp from file '$(ImportDir)/runtime/netpoll_windows.go'
#pragma once

#include "gocpp/support.fwd.h"


namespace golang::runtime
{
    const long _DWORD_MAX = 0xffffffff;
    const uintptr_t _INVALID_HANDLE_VALUE = ~ uintptr_t(0);
}
// #include "golang/runtime/defs_windows.fwd.h" [Ignored, known errors]
// #include "golang/runtime/netpoll.fwd.h" [Ignored, known errors]

namespace golang::runtime
{
    struct net_op;
    struct overlappedEntry;
}
#include "golang/runtime/internal/atomic/types.fwd.h"
// #include "golang/runtime/os_windows.fwd.h" [Ignored, known errors]
#include "golang/runtime/panic.fwd.h"
#include "golang/runtime/proc.fwd.h"
// #include "golang/runtime/stubs.fwd.h" [Ignored, known errors]
#include "golang/unsafe/unsafe.fwd.h"
