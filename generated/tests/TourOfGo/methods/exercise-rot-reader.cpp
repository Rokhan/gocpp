#include <complex>
#include <functional>
#include <iostream>
#include <iomanip>
#include <map>
#include <string>
#include <tuple>
#include <vector>

#include "tests/TourOfGo/methods/exercise-rot-reader.h"
#include "gocpp/support.h"

// TODO: package import not implemented
// #include "io/io.h"
// #include "io/multi.h"
// #include "io/pipe.h"
// #include "os/dir.h"
// #include "os/dir_windows.h"
// #include "os/endian_little.h"
// #include "os/env.h"
// #include "os/error.h"
// #include "os/error_errno.h"
// #include "os/error_posix.h"
// #include "os/exec.h"
// #include "os/exec_posix.h"
// #include "os/exec_windows.h"
// #include "os/executable.h"
// #include "os/executable_windows.h"
// #include "os/file.h"
// #include "os/file_posix.h"
// #include "os/file_windows.h"
// #include "os/getwd.h"
// #include "os/path.h"
// #include "os/path_windows.h"
// #include "os/proc.h"
// #include "os/rawconn.h"
// #include "os/removeall_noat.h"
// #include "os/stat.h"
// #include "os/stat_windows.h"
// #include "os/sticky_notbsd.h"
// #include "os/sys.h"
// #include "os/sys_windows.h"
// #include "os/tempfile.h"
// #include "os/types.h"
// #include "os/types_windows.h"
// #include "os/zero_copy_stub.h"
// #include "strings/builder.h"
// #include "strings/clone.h"
// #include "strings/compare.h"
// #include "strings/reader.h"
// #include "strings/replace.h"
// #include "strings/search.h"
// #include "strings/strings.h"

namespace golang::main
{
    
    std::ostream& rot13Reader::PrintTo(std::ostream& os) const
    {
        os << '{';
        os << "" << r;
        os << '}';
        return os;
    }

    std::ostream& operator<<(std::ostream& os, const rot13Reader& value)
    {
        return value.PrintTo(os);
    }

    std::tuple<int, error> Read(rot13Reader r13, gocpp::slice<unsigned char> buf)
    {
        auto [n, err] = Read(gocpp::recv(r13.r), buf);
        if(err != nullptr)
        {
            return {n, err};
        }
        for(auto i = 0; i < n; i++)
        {
            buf[i] += 13;
        }
        return {n, nullptr};
    }

    void main()
    {
        auto s = strings::NewReader("Lbh penpxrq gur pbqr!");
        auto r = rot13Reader {s};
        Copy(gocpp::recv(io), os.Stdout, & r);
    }

}

int main()
{
    try
    {
        std::cout << std::boolalpha << std::fixed << std::setprecision(5);
        golang::main::main();
        return 0;
    }
    catch(const gocpp::GoPanic& ex)
    {
        std::cout << "Panic: " << ex.what() << std::endl;
        return -1;
    }
}
