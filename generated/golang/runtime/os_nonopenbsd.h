// generated by GoCpp from file '$(ImportDir)/runtime/os_nonopenbsd.go'
#pragma once

#include <functional>
#include <string>
#include <tuple>
#include <vector>

#include "golang/runtime/os_nonopenbsd.fwd.h"
#include "gocpp/support.h"

#include "golang/runtime/mheap.h"

namespace golang::runtime
{
    void osStackAlloc(mspan* s);
    void osStackFree(mspan* s);
}
