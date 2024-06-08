#pragma once

#include <functional>
#include <string>
#include <tuple>
#include <vector>

#include "tests/TourOfGo/methods/exercise-rot-reader.fwd.h"
#include "gocpp/support.h"

// TODO: package import not implemented
// #include "io/io.fwd.h"
// #include "io/multi.fwd.h"
// #include "io/pipe.fwd.h"
// #include "os/dir.fwd.h"
// #include "os/dir_windows.fwd.h"
// #include "os/endian_little.fwd.h"
// #include "os/env.fwd.h"
// #include "os/error.fwd.h"
// #include "os/error_errno.fwd.h"
// #include "os/error_posix.fwd.h"
// #include "os/exec.fwd.h"
// #include "os/exec_posix.fwd.h"
// #include "os/exec_windows.fwd.h"
// #include "os/executable.fwd.h"
// #include "os/executable_windows.fwd.h"
// #include "os/file.fwd.h"
// #include "os/file_posix.fwd.h"
// #include "os/file_windows.fwd.h"
// #include "os/getwd.fwd.h"
// #include "os/path.fwd.h"
// #include "os/path_windows.fwd.h"
// #include "os/proc.fwd.h"
// #include "os/rawconn.fwd.h"
// #include "os/removeall_noat.fwd.h"
// #include "os/stat.fwd.h"
// #include "os/stat_windows.fwd.h"
// #include "os/sticky_notbsd.fwd.h"
// #include "os/sys.fwd.h"
// #include "os/sys_windows.fwd.h"
// #include "os/tempfile.fwd.h"
// #include "os/types.fwd.h"
// #include "os/types_windows.fwd.h"
// #include "os/zero_copy_stub.fwd.h"
// #include "strings/builder.fwd.h"
// #include "strings/clone.fwd.h"
// #include "strings/compare.fwd.h"
// #include "strings/reader.fwd.h"
// #include "strings/replace.fwd.h"
// #include "strings/search.fwd.h"
// #include "strings/strings.fwd.h"

namespace golang::main
{
    struct rot13Reader
    {
        io::Reader r;

        using isGoStruct = void;

        std::ostream& PrintTo(std::ostream& os) const;
    };

    std::ostream& operator<<(std::ostream& os, const rot13Reader& value);
    std::tuple<int, error> Read(rot13Reader r13, gocpp::slice<unsigned char> buf);
    void main();
}

