// generated by GoCpp from file '$(ImportDir)/runtime/cgocall.go'
#pragma once

#include "gocpp/support.fwd.h"


namespace golang::runtime
{
    using cgoCallers = gocpp::array<uintptr_t, 32>;
}
#include "golang/unsafe/unsafe.fwd.h"

namespace golang::runtime
{
    struct argset;
}
#include "golang/internal/goarch/goarch.fwd.h"
#include "golang/internal/goexperiment/exp_allocheaders_on.fwd.h"
#include "golang/internal/goexperiment/exp_cgocheck2_off.fwd.h"
#include "golang/runtime/atomic_pointer.fwd.h"
#include "golang/runtime/error.fwd.h"
#include "golang/runtime/extern.fwd.h"
#include "golang/runtime/internal/atomic/types.fwd.h"
#include "golang/runtime/internal/sys/consts.fwd.h"
#include "golang/runtime/mbitmap.fwd.h"
// #include "golang/runtime/mbitmap_allocheaders.fwd.h" [Ignored, known errors]
#include "golang/runtime/mfinal.fwd.h"
#include "golang/runtime/mheap.fwd.h"
// #include "golang/runtime/os_windows.fwd.h" [Ignored, known errors]
#include "golang/runtime/panic.fwd.h"
#include "golang/runtime/pinner.fwd.h"
// #include "golang/runtime/print.fwd.h" [Ignored, known errors]
#include "golang/runtime/proc.fwd.h"
// #include "golang/runtime/race0.fwd.h" [Ignored, known errors]
// #include "golang/runtime/runtime1.fwd.h" [Ignored, known errors]
#include "golang/runtime/runtime2.fwd.h"
#include "golang/runtime/slice.fwd.h"
#include "golang/runtime/stack.fwd.h"
#include "golang/runtime/string.fwd.h"
// #include "golang/runtime/stubs.fwd.h" [Ignored, known errors]
// #include "golang/runtime/symtab.fwd.h" [Ignored, known errors]
#include "golang/runtime/type.fwd.h"
// #include "golang/runtime/typekind.fwd.h" [Ignored, known errors]
