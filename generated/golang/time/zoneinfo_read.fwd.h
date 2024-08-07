// generated by GoCpp from file '$(ImportDir)/time/zoneinfo_read.go'
#pragma once

#include "gocpp/support.fwd.h"


namespace golang::time
{
    const int maxFileSize = 10 << 20;
    using fileSizeError = std::string;
    const long seekStart = 0;
    const long seekCurrent = 1;
    const long seekEnd = 2;
    struct dataIO;
}
#include "golang/errors/errors.fwd.h"
#include "golang/runtime/extern.fwd.h"
#include "golang/syscall/zerrors_windows.fwd.h"
#include "golang/time/sys_windows.fwd.h"
#include "golang/time/time.fwd.h"
#include "golang/time/zoneinfo.fwd.h"
#include "golang/time/zoneinfo_goroot.fwd.h"
