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
