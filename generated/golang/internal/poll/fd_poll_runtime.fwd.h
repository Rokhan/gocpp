// generated by GoCpp from file '$(ImportDir)/internal/poll/fd_poll_runtime.go'
#pragma once

#include "gocpp/support.fwd.h"


namespace golang::poll
{
    struct pollDesc;
    const long pollNoError = 0;
    const long pollErrClosing = 1;
    const long pollErrTimeout = 2;
    const long pollErrNotPollable = 3;
}
