#pragma once

#include <functional>
#include <string>
#include <tuple>
#include <vector>

#include "tests/TourOfGo/concurrency/mutex-counter.fwd.h"
#include "gocpp/support.h"

// TODO: package import not implemented
// #include "fmt/doc.fwd.h"
// #include "fmt/errors.fwd.h"
// #include "fmt/format.fwd.h"
// #include "fmt/print.fwd.h"
// #include "fmt/scan.fwd.h"
// #include "sync/cond.fwd.h"
// #include "sync/map.fwd.h"
// #include "sync/mutex.fwd.h"
// #include "sync/once.fwd.h"
// #include "sync/oncefunc.fwd.h"
// #include "sync/pool.fwd.h"
// #include "sync/poolqueue.fwd.h"
// #include "sync/runtime.fwd.h"
// #include "sync/runtime2.fwd.h"
// #include "sync/rwmutex.fwd.h"
// #include "sync/waitgroup.fwd.h"
// #include "time/format.fwd.h"
// #include "time/format_rfc3339.fwd.h"
// #include "time/sleep.fwd.h"
// #include "time/sys_windows.fwd.h"
// #include "time/tick.fwd.h"
// #include "time/time.fwd.h"
// #include "time/zoneinfo.fwd.h"
// #include "time/zoneinfo_abbrs_windows.fwd.h"
// #include "time/zoneinfo_goroot.fwd.h"
// #include "time/zoneinfo_read.fwd.h"
// #include "time/zoneinfo_windows.fwd.h"

namespace golang::main
{
    struct SafeCounter
    {
        mocklib::Mutex mu;
        gocpp::map<std::string, int> v;

        using isGoStruct = void;

        std::ostream& PrintTo(std::ostream& os) const;
    };

    std::ostream& operator<<(std::ostream& os, const SafeCounter& value);
    void Inc(SafeCounter* c, std::string key);
    int Value(SafeCounter* c, std::string key);
    void main();
}

