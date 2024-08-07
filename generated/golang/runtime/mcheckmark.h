// generated by GoCpp from file '$(ImportDir)/runtime/mcheckmark.go'
#pragma once

#include <functional>
#include <string>
#include <tuple>
#include <vector>

#include "golang/runtime/mcheckmark.fwd.h"
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
    struct checkmarksMap
    {
        sys::NotInHeap _;
        gocpp::array<uint8_t, heapArenaBytes / goarch::PtrSize / 8> b;

        using isGoStruct = void;

        std::ostream& PrintTo(std::ostream& os) const;
    };

    std::ostream& operator<<(std::ostream& os, const struct checkmarksMap& value);
    extern bool useCheckmark;
    void startCheckmarks();
    void endCheckmarks();
    bool setCheckmark(uintptr_t obj, uintptr_t base, uintptr_t off, markBits mbits);
}

