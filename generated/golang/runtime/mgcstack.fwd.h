// generated by GoCpp from file '$(ImportDir)/runtime/mgcstack.go'
#pragma once

#include "gocpp/support.fwd.h"


namespace golang::runtime
{
    const bool stackTraceDebug = false;
}
#include "golang/internal/goarch/goarch.fwd.h"
#include "golang/runtime/internal/sys/nih.fwd.h"
#include "golang/runtime/mgcwork.fwd.h"
#include "golang/runtime/runtime2.fwd.h"
#include "golang/runtime/stack.fwd.h"
#include "golang/unsafe/unsafe.fwd.h"

namespace golang::runtime
{
    struct stackWorkBuf;
    struct stackWorkBufHdr;
    struct stackObjectBuf;
    struct stackObjectBufHdr;
    struct stackObject;
    struct stackScanState;
}
#include "golang/runtime/panic.fwd.h"