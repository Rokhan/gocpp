// generated by GoCpp from file '$(ImportDir)/syscall/asan0.go'
#pragma once

#include <functional>
#include <string>
#include <tuple>
#include <vector>

#include "golang/syscall/asan0.fwd.h"
#include "gocpp/support.h"

#include "golang/unsafe/unsafe.h"

namespace golang::syscall
{
    void asanRead(unsafe::Pointer addr, int len);
    void asanWrite(unsafe::Pointer addr, int len);
}
