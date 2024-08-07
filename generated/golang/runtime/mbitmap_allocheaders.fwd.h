// generated by GoCpp from file '$(ImportDir)/runtime/mbitmap_allocheaders.go'
#pragma once

#include "gocpp/support.fwd.h"


namespace golang::runtime
{
    const long mallocHeaderSize = 8;
    struct heapArenaPtrScalar;
    struct writeUserArenaHeapBits;
    struct heapBits;
}
#include "golang/internal/goarch/goarch.fwd.h"
#include "golang/runtime/mbitmap.fwd.h"
#include "golang/runtime/type.fwd.h"

namespace golang::runtime
{
    const int minSizeForMallocHeader = goarch::PtrSize * ptrBits;
    struct typePointers;
}
#include "golang/internal/abi/type.fwd.h"
#include "golang/runtime/internal/sys/intrinsics.fwd.h"
#include "golang/runtime/malloc.fwd.h"
#include "golang/runtime/mfinal.fwd.h"
#include "golang/runtime/mheap.fwd.h"
#include "golang/runtime/mwbbuf.fwd.h"
#include "golang/runtime/panic.fwd.h"
// #include "golang/runtime/print.fwd.h" [Ignored, known errors]
// #include "golang/runtime/rand.fwd.h" [Ignored, known errors]
#include "golang/runtime/runtime2.fwd.h"
#include "golang/runtime/slice.fwd.h"
#include "golang/runtime/stack.fwd.h"
#include "golang/runtime/stkframe.fwd.h"
// #include "golang/runtime/stubs.fwd.h" [Ignored, known errors]
// #include "golang/runtime/symtab.fwd.h" [Ignored, known errors]
// #include "golang/runtime/traceback.fwd.h" [Ignored, known errors]
// #include "golang/runtime/typekind.fwd.h" [Ignored, known errors]
#include "golang/unsafe/unsafe.fwd.h"
