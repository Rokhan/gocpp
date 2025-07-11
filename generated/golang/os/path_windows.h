// generated by GoCpp from file '$(ImportDir)/os/path_windows.go'
#pragma once

#include <functional>
#include <string>
#include <tuple>
#include <vector>

#include "golang/os/path_windows.fwd.h"
#include "gocpp/support.h"

namespace golang::os
{
    bool IsPathSeparator(uint8_t c);
    std::string basename(std::string name);
    bool isAbs(std::string path);
    std::string volumeName(std::string path);
    std::string fromSlash(std::string path);
    std::string dirname(std::string path);
    extern bool canUseLongPaths;
    std::string fixLongPath(std::string path);

    namespace rec
    {
    }
}

