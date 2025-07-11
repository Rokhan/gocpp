// generated by GoCpp from file '$(ImportDir)/internal/poll/fd_posix.go'
#include <complex>
#include <functional>
#include <iostream>
#include <iomanip>
#include <map>
#include <string>
#include <tuple>
#include <vector>

#include "golang/internal/poll/fd_posix.h"
#include "gocpp/support.h"

#include "golang/internal/poll/fd_mutex.h"
#include "golang/internal/poll/fd_poll_runtime.h"
#include "golang/internal/poll/fd_windows.h"
#include "golang/internal/syscall/windows/syscall_windows.h"
#include "golang/sync/mutex.h"
#include "golang/syscall/syscall_windows.h"
#include "golang/syscall/types_windows.h"
#include "golang/syscall/zerrors_windows.h"

namespace golang::poll
{
    namespace rec
    {
        using namespace mocklib::rec;
    }

    // eofError returns io.EOF when fd is available for reading end of
    // file.
    struct gocpp::error rec::eofError(struct FD* fd, int n, struct gocpp::error err)
    {
        if(n == 0 && err == nullptr && fd->ZeroReadIsEOF)
        {
            return io::go_EOF;
        }
        return err;
    }

    // Shutdown wraps syscall.Shutdown.
    struct gocpp::error rec::Shutdown(struct FD* fd, int how)
    {
        gocpp::Defer defer;
        try
        {
            if(auto err = rec::incref(gocpp::recv(fd)); err != nullptr)
            {
                return err;
            }
            defer.push_back([=]{ rec::decref(gocpp::recv(fd)); });
            return syscall::Shutdown(fd->Sysfd, how);
        }
        catch(gocpp::GoPanic& gp)
        {
            defer.handlePanic(gp);
        }
    }

    // Fchown wraps syscall.Fchown.
    struct gocpp::error rec::Fchown(struct FD* fd, int uid, int gid)
    {
        gocpp::Defer defer;
        try
        {
            if(auto err = rec::incref(gocpp::recv(fd)); err != nullptr)
            {
                return err;
            }
            defer.push_back([=]{ rec::decref(gocpp::recv(fd)); });
            return ignoringEINTR([=]() mutable -> struct gocpp::error
            {
                return syscall::Fchown(fd->Sysfd, uid, gid);
            });
        }
        catch(gocpp::GoPanic& gp)
        {
            defer.handlePanic(gp);
        }
    }

    // Ftruncate wraps syscall.Ftruncate.
    struct gocpp::error rec::Ftruncate(struct FD* fd, int64_t size)
    {
        gocpp::Defer defer;
        try
        {
            if(auto err = rec::incref(gocpp::recv(fd)); err != nullptr)
            {
                return err;
            }
            defer.push_back([=]{ rec::decref(gocpp::recv(fd)); });
            return ignoringEINTR([=]() mutable -> struct gocpp::error
            {
                return syscall::Ftruncate(fd->Sysfd, size);
            });
        }
        catch(gocpp::GoPanic& gp)
        {
            defer.handlePanic(gp);
        }
    }

    // RawControl invokes the user-defined function f for a non-IO
    // operation.
    struct gocpp::error rec::RawControl(struct FD* fd, std::function<void (uintptr_t _1)> f)
    {
        gocpp::Defer defer;
        try
        {
            if(auto err = rec::incref(gocpp::recv(fd)); err != nullptr)
            {
                return err;
            }
            defer.push_back([=]{ rec::decref(gocpp::recv(fd)); });
            f(uintptr_t(fd->Sysfd));
            return nullptr;
        }
        catch(gocpp::GoPanic& gp)
        {
            defer.handlePanic(gp);
        }
    }

    // ignoringEINTR makes a function call and repeats it if it returns
    // an EINTR error. This appears to be required even though we install all
    // signal handlers with SA_RESTART: see #22838, #38033, #38836, #40846.
    // Also #20400 and #36644 are issues in which a signal handler is
    // installed without setting SA_RESTART. None of these are the common case,
    // but there are enough of them that it seems that we can't avoid
    // an EINTR loop.
    struct gocpp::error ignoringEINTR(std::function<struct gocpp::error ()> fn)
    {
        for(; ; )
        {
            auto err = fn();
            if(err != syscall::go_EINTR)
            {
                return err;
            }
        }
    }

}

