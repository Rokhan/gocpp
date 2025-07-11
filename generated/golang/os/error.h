// generated by GoCpp from file '$(ImportDir)/os/error.go'
#pragma once

#include <functional>
#include <string>
#include <tuple>
#include <vector>

#include "golang/os/error.fwd.h"
#include "gocpp/support.h"

#include "golang/io/fs/fs.h"

namespace golang::os
{
    extern gocpp::error ErrInvalid;
    extern gocpp::error ErrPermission;
    extern gocpp::error ErrExist;
    extern gocpp::error ErrNotExist;
    extern gocpp::error ErrClosed;
    extern gocpp::error ErrNoDeadline;
    extern gocpp::error ErrDeadlineExceeded;
    struct gocpp::error errNoDeadline();
    struct gocpp::error errDeadlineExceeded();
    struct timeout : gocpp::Interface
    {
        using gocpp::Interface::operator==;
        using gocpp::Interface::operator!=;

        timeout(){}
        timeout(timeout& i) = default;
        timeout(const timeout& i) = default;
        timeout& operator=(timeout& i) = default;
        timeout& operator=(const timeout& i) = default;

        template<typename T>
        timeout(T& ref);

        template<typename T>
        timeout(const T& ref);

        template<typename T>
        timeout(T* ptr);

        using isGoInterface = void;

        std::ostream& PrintTo(std::ostream& os) const;

        struct Itimeout
        {
            virtual bool vTimeout() = 0;
        };

        template<typename T, typename StoreT>
        struct timeoutImpl : Itimeout
        {
            explicit timeoutImpl(T* ptr)
            {
                value.reset(ptr);
            }

            bool vTimeout() override;

            StoreT value;
        };

        std::shared_ptr<Itimeout> value;
    };

    namespace rec
    {
        bool Timeout(const gocpp::PtrRecv<struct timeout, false>& self);
        bool Timeout(const gocpp::ObjRecv<struct timeout>& self);
    }

    std::ostream& operator<<(std::ostream& os, const struct timeout& value);
    struct SyscallError
    {
        std::string Syscall;
        gocpp::error Err;

        using isGoStruct = void;

        template<typename T> requires gocpp::GoStruct<T>
        operator T();

        template<typename T> requires gocpp::GoStruct<T>
        bool operator==(const T& ref) const;

        std::ostream& PrintTo(std::ostream& os) const;
    };

    std::ostream& operator<<(std::ostream& os, const struct SyscallError& value);
    struct gocpp::error NewSyscallError(std::string syscall, struct gocpp::error err);
    bool IsExist(struct gocpp::error err);
    bool IsNotExist(struct gocpp::error err);
    bool IsPermission(struct gocpp::error err);
    bool IsTimeout(struct gocpp::error err);
    bool underlyingErrorIs(struct gocpp::error err, struct gocpp::error target);
    struct gocpp::error underlyingError(struct gocpp::error err);

    namespace rec
    {
        std::string Error(struct SyscallError* e);
        struct gocpp::error Unwrap(struct SyscallError* e);
        bool Timeout(struct SyscallError* e);
    }
}

