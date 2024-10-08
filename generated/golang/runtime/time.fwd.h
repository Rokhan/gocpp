// generated by GoCpp from file '$(ImportDir)/runtime/time.go'
#pragma once

#include "gocpp/support.fwd.h"


namespace golang::runtime
{
    const int timerNoStatus = 0;
    const int timerWaiting = 1;
    const int timerRunning = 2;
    const int timerDeleted = 3;
    const int timerRemoving = 4;
    const int timerRemoved = 5;
    const int timerModifying = 6;
    const int timerModifiedEarlier = 7;
    const int timerModifiedLater = 8;
    const int timerMoving = 9;
    const int maxWhen = (1 << 63) - 1;
    const bool verifyTimers = false;
}
#include "golang/runtime/internal/atomic/types.fwd.h"
#include "golang/runtime/runtime2.fwd.h"

namespace golang::runtime
{
    struct timer;
}
