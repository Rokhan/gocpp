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

namespace golang::time
{
    struct Ticker
    {
        gocpp::channel<Time> C;
        runtimeTimer r;

        using isGoStruct = void;

        std::ostream& PrintTo(std::ostream& os) const;
    };

    std::ostream& operator<<(std::ostream& os, const Ticker& value);
    Ticker* NewTicker(Duration d);
    void Stop(Ticker* t);
    void Reset(Ticker* t, Duration d);
    gocpp::channel<Time> Tick(Duration d);
}
