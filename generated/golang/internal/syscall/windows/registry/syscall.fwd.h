// generated by GoCpp from file '$(ImportDir)/internal/syscall/windows/registry/syscall.go'
#pragma once

#include "gocpp/support.fwd.h"


namespace golang::registry
{
    const long _REG_OPTION_NON_VOLATILE = 0;
    const long _REG_CREATED_NEW_KEY = 1;
    const long _REG_OPENED_EXISTING_KEY = 2;
    const syscall::Errno _ERROR_NO_MORE_ITEMS = 259;
}
#include "golang/syscall/syscall_windows.fwd.h"