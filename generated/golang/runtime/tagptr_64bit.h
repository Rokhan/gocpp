// generated by GoCpp from file '$(ImportDir)/runtime/tagptr_64bit.go'
#pragma once

#include <functional>
#include <string>
#include <tuple>
#include <vector>

#include "golang/runtime/tagptr_64bit.fwd.h"
#include "gocpp/support.h"

#include "golang/internal/goarch/zgoarch_amd64.h"
#include "golang/internal/goos/zgoos_windows.h"
#include "golang/runtime/extern.h"
#include "golang/runtime/panic.h"
#include "golang/runtime/tagptr.h"
#include "golang/unsafe/unsafe.h"

namespace golang::runtime
{
    extern int addrBits;
    extern int tagBits;
    extern int aixAddrBits;
    extern int aixTagBits;
    extern int riscv64AddrBits;
    extern int riscv64TagBits;
    extern int taggedPointerBits;
    taggedPointer taggedPointerPack(unsafe::Pointer ptr, uintptr_t tag);
    unsafe::Pointer pointer(taggedPointer tp);
    uintptr_t tag(taggedPointer tp);
}

