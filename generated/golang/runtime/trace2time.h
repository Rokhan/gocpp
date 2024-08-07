// generated by GoCpp from file '$(ImportDir)/runtime/trace2time.go'
#pragma once

#include <functional>
#include <string>
#include <tuple>
#include <vector>

#include "golang/runtime/trace2time.fwd.h"
#include "gocpp/support.h"

#include "golang/internal/goarch/zgoarch_amd64.h"
#include "golang/runtime/cputicks.h"
// #include "golang/runtime/lock_sema.h"  [Ignored, known errors]
#include "golang/runtime/proc.h"
#include "golang/runtime/runtime.h"
// #include "golang/runtime/stubs.h"  [Ignored, known errors]
#include "golang/runtime/time_nofake.h"
#include "golang/runtime/trace2buf.h"
#include "golang/runtime/trace2event.h"

namespace golang::runtime
{
    traceTime traceClockNow();
    uint64_t traceClockUnitsPerSecond();
    void traceFrequency(uintptr_t gen);
}

