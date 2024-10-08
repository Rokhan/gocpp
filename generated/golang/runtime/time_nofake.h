// generated by GoCpp from file '$(ImportDir)/runtime/time_nofake.go'
#pragma once

#include <functional>
#include <string>
#include <tuple>
#include <vector>

#include "golang/runtime/time_nofake.fwd.h"
#include "gocpp/support.h"


namespace golang::runtime
{
    int64_t nanotime();
    int32_t write(uintptr_t fd, unsafe::Pointer p, int32_t n);
}

