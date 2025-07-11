// generated by GoCpp from file '$(ImportDir)/runtime/mgcsweep.go'
#pragma once

#include "gocpp/support.fwd.h"


namespace golang::runtime
{
    using sweepClass = uint32_t;
    const int sweepDrainedMask = 1 << 31;
    struct sweepLocker;
    const runtime::sweepClass sweepClassDone = sweepClass(~ uint32_t(0));
}
#include "golang/runtime/internal/atomic/types.fwd.h"
#include "golang/runtime/mheap.fwd.h"
#include "golang/runtime/runtime2.fwd.h"

namespace golang::runtime
{
    struct sweepdata;
    const int numSweepClasses = numSpanClasses * 2;
    struct activeSweep;
    struct sweepLocked;
}
