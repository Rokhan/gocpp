#pragma once

#include <functional>
#include <string>
#include <tuple>
#include <vector>

#include "tests/TourOfGo/methods/errors.fwd.h"
#include "gocpp/support.h"

// TODO: package import not implemented
// #include "fmt/doc.fwd.h"
// #include "fmt/errors.fwd.h"
// #include "fmt/format.fwd.h"
// #include "fmt/print.fwd.h"
// #include "fmt/scan.fwd.h"
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
    struct MyError
    {
        time::Time When;
        std::string What;

        using isGoStruct = void;

        std::ostream& PrintTo(std::ostream& os) const;
    };

    std::ostream& operator<<(std::ostream& os, const MyError& value);
    std::string Error(MyError* e);
    error run();
    void main();
}

