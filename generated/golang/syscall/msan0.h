// generated by GoCpp from file '$(ImportDir)/syscall/msan0.go'
#pragma once

#include <functional>
#include <string>
#include <tuple>
#include <vector>

#include "golang/syscall/msan0.fwd.h"
#include "gocpp/support.h"


namespace golang::syscall
{
    void msanRead(unsafe::Pointer addr, int len);
    void msanWrite(unsafe::Pointer addr, int len);

    namespace rec
    {
    }
}

