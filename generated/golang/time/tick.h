// generated by GoCpp from file '$(ImportDir)/time/tick.go'
#pragma once

#include <functional>
#include <string>
#include <tuple>
#include <vector>

#include "golang/time/tick.fwd.h"
#include "gocpp/support.h"

#include "golang/time/sleep.h"
#include "golang/time/time.h"
#include "golang/time/zoneinfo.h"

namespace golang::time
{
    struct Ticker
    {
        gocpp::channel<Time> C;
        runtimeTimer r;

        using isGoStruct = void;

        std::ostream& PrintTo(std::ostream& os) const;
    };

    std::ostream& operator<<(std::ostream& os, const struct Ticker& value);
    Ticker* NewTicker(Duration d);
    void Stop(struct Ticker* t);
    void Reset(struct Ticker* t, Duration d);
    gocpp::channel<Time> Tick(Duration d);
}

