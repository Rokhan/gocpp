// generated by GoCpp from file '$(ImportDir)/os/dir.go'
#include <complex>
#include <functional>
#include <iostream>
#include <iomanip>
#include <map>
#include <string>
#include <tuple>
#include <vector>

#include "golang/os/dir.h"
#include "gocpp/support.h"

#include "golang/internal/poll/fd_mutex.h"
#include "golang/internal/poll/fd_poll_runtime.h"
#include "golang/internal/poll/fd_windows.h"
#include "golang/internal/syscall/windows/syscall_windows.h"
#include "golang/io/fs/fs.h"
#include "golang/os/dir_windows.h"
#include "golang/os/file.h"
#include "golang/os/file_posix.h"
#include "golang/os/file_windows.h"
#include "golang/os/types.h"
#include "golang/sort/slice.h"
#include "golang/sync/mutex.h"
#include "golang/syscall/syscall_windows.h"
#include "golang/syscall/types_windows.h"
#include "golang/time/time.h"
#include "golang/time/zoneinfo.h"

namespace golang::os
{
    namespace rec
    {
        using namespace mocklib::rec;
        using fs::rec::Name;
    }

    // Readdir reads the contents of the directory associated with file and
    // returns a slice of up to n FileInfo values, as would be returned
    // by Lstat, in directory order. Subsequent calls on the same file will yield
    // further FileInfos.
    //
    // If n > 0, Readdir returns at most n FileInfo structures. In this case, if
    // Readdir returns an empty slice, it will return a non-nil error
    // explaining why. At the end of a directory, the error is io.EOF.
    //
    // If n <= 0, Readdir returns all the FileInfo from the directory in
    // a single slice. In this case, if Readdir succeeds (reads all
    // the way to the end of the directory), it returns the slice and a
    // nil error. If it encounters an error before the end of the
    // directory, Readdir returns the FileInfo read until that point
    // and a non-nil error.
    //
    // Most clients are better served by the more efficient ReadDir method.
    std::tuple<gocpp::slice<os::FileInfo>, struct gocpp::error> rec::Readdir(struct File* f, int n)
    {
        if(f == nullptr)
        {
            return {nullptr, ErrInvalid};
        }
        auto [gocpp_id_0, gocpp_id_1, infos, err] = rec::readdir(gocpp::recv(f), n, readdirFileInfo);
        if(infos == nullptr)
        {
            infos = gocpp::slice<os::FileInfo> {};
        }
        return {infos, err};
    }

    // Readdirnames reads the contents of the directory associated with file
    // and returns a slice of up to n names of files in the directory,
    // in directory order. Subsequent calls on the same file will yield
    // further names.
    //
    // If n > 0, Readdirnames returns at most n names. In this case, if
    // Readdirnames returns an empty slice, it will return a non-nil error
    // explaining why. At the end of a directory, the error is io.EOF.
    //
    // If n <= 0, Readdirnames returns all the names from the directory in
    // a single slice. In this case, if Readdirnames succeeds (reads all
    // the way to the end of the directory), it returns the slice and a
    // nil error. If it encounters an error before the end of the
    // directory, Readdirnames returns the names read until that point and
    // a non-nil error.
    std::tuple<gocpp::slice<std::string>, struct gocpp::error> rec::Readdirnames(struct File* f, int n)
    {
        gocpp::slice<std::string> names;
        struct gocpp::error err;
        if(f == nullptr)
        {
            return {nullptr, ErrInvalid};
        }
        std::tie(names, gocpp_id_2, gocpp_id_3, err) = rec::readdir(gocpp::recv(f), n, readdirName);
        if(names == nullptr)
        {
            names = gocpp::slice<std::string> {};
        }
        return {names, err};
    }

    // A DirEntry is an entry read from a directory
    // (using the ReadDir function or a File's ReadDir method).
    // ReadDir reads the contents of the directory associated with the file f
    // and returns a slice of DirEntry values in directory order.
    // Subsequent calls on the same file will yield later DirEntry records in the directory.
    //
    // If n > 0, ReadDir returns at most n DirEntry records.
    // In this case, if ReadDir returns an empty slice, it will return an error explaining why.
    // At the end of a directory, the error is io.EOF.
    //
    // If n <= 0, ReadDir returns all the DirEntry records remaining in the directory.
    // When it succeeds, it returns a nil error (not io.EOF).
    std::tuple<gocpp::slice<os::DirEntry>, struct gocpp::error> rec::ReadDir(struct File* f, int n)
    {
        if(f == nullptr)
        {
            return {nullptr, ErrInvalid};
        }
        auto [gocpp_id_4, dirents, gocpp_id_5, err] = rec::readdir(gocpp::recv(f), n, readdirDirEntry);
        if(dirents == nullptr)
        {
            dirents = gocpp::slice<os::DirEntry> {};
        }
        return {dirents, err};
    }

    // testingForceReadDirLstat forces ReadDir to call Lstat, for testing that code path.
    // This can be difficult to provoke on some Unix systems otherwise.
    bool testingForceReadDirLstat;
    // ReadDir reads the named directory,
    // returning all its directory entries sorted by filename.
    // If an error occurs reading the directory,
    // ReadDir returns the entries it was able to read before the error,
    // along with the error.
    std::tuple<gocpp::slice<os::DirEntry>, struct gocpp::error> ReadDir(std::string name)
    {
        gocpp::Defer defer;
        try
        {
            auto [f, err] = Open(name);
            if(err != nullptr)
            {
                return {nullptr, err};
            }
            defer.push_back([=]{ rec::Close(gocpp::recv(f)); });
            fs::DirEntry> dirs;
            std::tie(dirs, err) = rec::ReadDir(gocpp::recv(f), - 1);
            sort::Slice(dirs, [=](int i, int j) mutable -> bool
            {
                return rec::Name(gocpp::recv(dirs[i])) < rec::Name(gocpp::recv(dirs[j]));
            });
            return {dirs, err};
        }
        catch(gocpp::GoPanic& gp)
        {
            defer.handlePanic(gp);
        }
    }

}

