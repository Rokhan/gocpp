// generated by GoCpp from file '$(ImportDir)/runtime/symtab.go'
#pragma once

#include "gocpp/support.fwd.h"

// #include "golang/internal/abi/symtab.fwd.h"  [Ignored, known errors]
// #include "golang/internal/goarch/goarch.fwd.h"  [Ignored, known errors]
#include "golang/runtime/internal/atomic/atomic_amd64.fwd.h"
#include "golang/runtime/internal/atomic/types.fwd.h"
#include "golang/runtime/internal/sys/consts.fwd.h"
#include "golang/runtime/internal/sys/nih.fwd.h"
#include "golang/runtime/atomic_pointer.fwd.h"
#include "golang/runtime/extern.fwd.h"
#include "golang/runtime/mbitmap.fwd.h"
#include "golang/runtime/mgcpacer.fwd.h"
#include "golang/runtime/panic.fwd.h"
#include "golang/runtime/plugin.fwd.h"
// #include "golang/runtime/print.fwd.h"  [Ignored, known errors]
#include "golang/runtime/proc.fwd.h"
// #include "golang/runtime/rand.fwd.h"  [Ignored, known errors]
// #include "golang/runtime/runtime1.fwd.h"  [Ignored, known errors]
#include "golang/runtime/runtime2.fwd.h"
#include "golang/runtime/stack.fwd.h"
#include "golang/runtime/string.fwd.h"
// #include "golang/runtime/stubs.fwd.h"  [Ignored, known errors]
#include "golang/runtime/symtabinl.fwd.h"
#include "golang/runtime/traceback.fwd.h"
#include "golang/runtime/type.fwd.h"
#include "golang/unsafe/unsafe.fwd.h"

namespace golang::runtime
{
    struct Frames;
    struct Frame;
    struct Func;
    struct pcHeader;
    struct moduledata;
    struct modulehash;
    struct functab;
    struct textsect;
    struct findfuncbucket;
    struct funcInfo;
    struct srcFunc;
    struct pcvalueCache;
    struct pcvalueCacheEnt;
    struct stackmap;
}

