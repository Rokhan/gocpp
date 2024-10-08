// generated by GoCpp from file '$(ImportDir)/runtime/mem_windows.go'
#pragma once

#include "gocpp/support.fwd.h"


namespace golang::runtime
{
    const long _MEM_COMMIT = 0x1000;
    const long _MEM_RESERVE = 0x2000;
    const long _MEM_DECOMMIT = 0x4000;
    const long _MEM_RELEASE = 0x8000;
    const long _PAGE_READWRITE = 0x0004;
    const long _PAGE_NOACCESS = 0x0001;
    const long _ERROR_NOT_ENOUGH_MEMORY = 8;
    const long _ERROR_COMMITMENT_LIMIT = 1455;
}
