// generated by GoCpp from file '$(ImportDir)/internal/syscall/windows/sysdll/sysdll.go'
#pragma once

#include <functional>
#include <string>
#include <tuple>
#include <vector>

#include "golang/internal/syscall/windows/sysdll/sysdll.fwd.h"
#include "gocpp/support.h"

namespace golang::sysdll
{
    extern gocpp::map<std::string, bool> IsSystemDLL;
    std::string Add(std::string dll);
}
