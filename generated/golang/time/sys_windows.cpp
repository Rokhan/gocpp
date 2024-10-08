// generated by GoCpp from file '$(ImportDir)/time/sys_windows.go'
#include <complex>
#include <functional>
#include <iostream>
#include <iomanip>
#include <map>
#include <string>
#include <tuple>
#include <vector>

#include "golang/time/sys_windows.h"
#include "gocpp/support.h"

#include "golang/errors/errors.h"
#include "golang/syscall/syscall_windows.h"
#include "golang/syscall/types_windows.h"
#include "golang/syscall/zerrors_windows.h"
#include "golang/time/zoneinfo_read.h"

namespace golang::time
{
    void interrupt()
    {
    }

    std::tuple<uintptr_t, std::string> open(std::string name)
    {
        auto [fd, err] = syscall::Open(name, syscall::O_RDONLY, 0);
        if(err != nullptr)
        {
            if(err == syscall::ERROR_PATH_NOT_FOUND)
            {
                err = syscall::ENOENT;
            }
            return {0, err};
        }
        return {uintptr_t(fd), nullptr};
    }

    std::tuple<int, std::string> read(uintptr_t fd, gocpp::slice<unsigned char> buf)
    {
        return syscall::Read(syscall::Handle(fd), buf);
    }

    void closefd(uintptr_t fd)
    {
        syscall::Close(syscall::Handle(fd));
    }

    std::string preadn(uintptr_t fd, gocpp::slice<unsigned char> buf, int off)
    {
        auto whence = seekStart;
        if(off < 0)
        {
            whence = seekEnd;
        }
        if(auto [gocpp_id_1, err] = syscall::Seek(syscall::Handle(fd), int64_t(off), whence); err != nullptr)
        {
            return err;
        }
        for(; len(buf) > 0; )
        {
            auto [m, err] = syscall::Read(syscall::Handle(fd), buf);
            if(m <= 0)
            {
                if(err == nullptr)
                {
                    return errors::New("short read");
                }
                return err;
            }
            buf = buf.make_slice(m);
        }
        return nullptr;
    }

}

