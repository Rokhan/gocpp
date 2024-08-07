// generated by GoCpp from file '$(ImportDir)/runtime/stack.go'
#pragma once

#include "gocpp/support.fwd.h"


namespace golang::runtime
{
    const long stackMin = 2048;
    const long stackDebug = 0;
    const long stackFromSystem = 0;
    const long stackFaultOnFree = 0;
    const long stackNoCache = 0;
    const bool debugCheckBP = false;
    struct gocpp_id_0;
    struct gocpp_id_1;
    struct bitvector;
    struct stackObjectRecord;
}
#include "golang/internal/abi/stack.fwd.h"
#include "golang/internal/goarch/goarch.fwd.h"
#include "golang/internal/goarch/zgoarch_amd64.fwd.h"
#include "golang/internal/goos/zgoos_windows.fwd.h"
#include "golang/runtime/internal/sys/consts.fwd.h"
#include "golang/runtime/internal/sys/nih.fwd.h"
#include "golang/runtime/mheap.fwd.h"
#include "golang/runtime/runtime2.fwd.h"

namespace golang::runtime
{
    const int stackSystem = goos::IsWindows * 512 * goarch::PtrSize + goos::IsPlan9 * 512 + goos::IsIos * goarch::IsArm64 * 1024;
    const int stackNosplit = abi::StackNosplitBase * sys::StackGuardMultiplier;
    const int uintptrMask = (1 << (8 * goarch::PtrSize)) - 1;
    struct stackpoolItem;
    struct adjustinfo;
    const int fixedStack0 = stackMin + stackSystem;
    const int stackGuard = stackNosplit + stackSystem + abi::StackSmall;
    const int stackPreempt = uintptrMask & - 1314;
    const int stackFork = uintptrMask & - 1234;
    const int stackForceMove = uintptrMask & - 275;
    const int stackPoisonMin = uintptrMask & - 4096;
    const int fixedStack1 = fixedStack0 - 1;
    const int fixedStack2 = fixedStack1 | (fixedStack1 >> 1);
    const int fixedStack3 = fixedStack2 | (fixedStack2 >> 2);
    const int fixedStack4 = fixedStack3 | (fixedStack3 >> 4);
    const int fixedStack5 = fixedStack4 | (fixedStack4 >> 8);
    const int fixedStack6 = fixedStack5 | (fixedStack5 >> 16);
    const int fixedStack = fixedStack6 + 1;
}
#include "golang/internal/abi/funcpc.fwd.h"
// #include "golang/internal/abi/symtab.fwd.h" [Ignored, known errors]
#include "golang/internal/cpu/cpu_x86.fwd.h"
#include "golang/runtime/asan0.fwd.h"
#include "golang/runtime/chan.fwd.h"
#include "golang/runtime/extern.fwd.h"
#include "golang/runtime/internal/atomic/stubs.fwd.h"
#include "golang/runtime/internal/atomic/types.fwd.h"
#include "golang/runtime/internal/sys/intrinsics.fwd.h"
// #include "golang/runtime/lock_sema.fwd.h" [Ignored, known errors]
// #include "golang/runtime/lockrank.fwd.h" [Ignored, known errors]
// #include "golang/runtime/lockrank_off.fwd.h" [Ignored, known errors]
#include "golang/runtime/malloc.fwd.h"
#include "golang/runtime/mbitmap.fwd.h"
// #include "golang/runtime/mcache.fwd.h" [Ignored, known errors]
#include "golang/runtime/mem.fwd.h"
#include "golang/runtime/mgc.fwd.h"
// #include "golang/runtime/mgcpacer.fwd.h" [Ignored, known errors]
#include "golang/runtime/msan0.fwd.h"
#include "golang/runtime/os_nonopenbsd.fwd.h"
#include "golang/runtime/panic.fwd.h"
// #include "golang/runtime/preempt.fwd.h" [Ignored, known errors]
// #include "golang/runtime/print.fwd.h" [Ignored, known errors]
#include "golang/runtime/proc.fwd.h"
// #include "golang/runtime/race0.fwd.h" [Ignored, known errors]
#include "golang/runtime/sizeclasses.fwd.h"
#include "golang/runtime/stkframe.fwd.h"
// #include "golang/runtime/stubs.fwd.h" [Ignored, known errors]
// #include "golang/runtime/symtab.fwd.h" [Ignored, known errors]
#include "golang/runtime/sys_x86.fwd.h"
// #include "golang/runtime/traceback.fwd.h" [Ignored, known errors]
#include "golang/unsafe/unsafe.fwd.h"
