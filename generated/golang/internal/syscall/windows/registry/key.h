// generated by GoCpp from file '$(ImportDir)/internal/syscall/windows/registry/key.go'
#pragma once

#include <functional>
#include <string>
#include <tuple>
#include <vector>

#include "golang/internal/syscall/windows/registry/key.fwd.h"
#include "gocpp/support.h"

#include "golang/internal/syscall/windows/registry/syscall.h"
#include "golang/internal/syscall/windows/registry/zsyscall_windows.h"
#include "golang/runtime/proc.h"
#include "golang/syscall/syscall_windows.h"
#include "golang/syscall/types_windows.h"
#include "golang/syscall/zsyscall_windows.h"

namespace golang::registry
{
    std::string Close(Key k);
    std::tuple<Key, std::string> OpenKey(Key k, std::string path, uint32_t access);
    std::tuple<gocpp::slice<std::string>, std::string> ReadSubKeyNames(Key k);
    std::tuple<Key, bool, std::string> CreateKey(Key k, std::string path, uint32_t access);
    std::string DeleteKey(Key k, std::string path);
    struct KeyInfo
    {
        uint32_t SubKeyCount;
        uint32_t MaxSubKeyLen;
        uint32_t ValueCount;
        uint32_t MaxValueNameLen;
        uint32_t MaxValueLen;
        syscall::Filetime lastWriteTime;

        using isGoStruct = void;

        std::ostream& PrintTo(std::ostream& os) const;
    };

    std::ostream& operator<<(std::ostream& os, const struct KeyInfo& value);
    std::tuple<KeyInfo*, std::string> Stat(Key k);
}
