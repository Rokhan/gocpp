// generated by GoCpp from file '$(ImportDir)/runtime/asan0.go'
#pragma once

#include <functional>
#include <string>
#include <tuple>
#include <vector>

#include "golang/runtime/asan0.fwd.h"
#include "gocpp/support.h"

#include "golang/runtime/panic.h"
#include "golang/unsafe/unsafe.h"

namespace golang::runtime
{
    extern bool asanenabled;
    void asanread(unsafe::Pointer addr, uintptr_t sz);
    void asanwrite(unsafe::Pointer addr, uintptr_t sz);
    void asanunpoison(unsafe::Pointer addr, uintptr_t sz);
    void asanpoison(unsafe::Pointer addr, uintptr_t sz);
    void asanregisterglobals(unsafe::Pointer addr, uintptr_t sz);
}
