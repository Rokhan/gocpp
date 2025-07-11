// generated by GoCpp from file '$(ImportDir)/runtime/select.go'
#pragma once

#include "gocpp/support.fwd.h"


namespace golang::runtime
{
    const bool debugSelect = false;
    using selectDir = int;
    const runtime::selectDir _ = 0;
    const runtime::selectDir selectSend = 1;
    const runtime::selectDir selectRecv = 2;
    const runtime::selectDir selectDefault = 3;
}
#include "golang/runtime/chan.fwd.h"
#include "golang/unsafe/unsafe.fwd.h"

namespace golang::runtime
{
    struct scase;
    struct runtimeSelect;
}
