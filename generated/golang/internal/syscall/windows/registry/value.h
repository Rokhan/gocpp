// generated by GoCpp from file '$(ImportDir)/internal/syscall/windows/registry/value.go'
#pragma once

#include <functional>
#include <string>
#include <tuple>
#include <vector>

#include "golang/internal/syscall/windows/registry/value.fwd.h"
#include "gocpp/support.h"

#include "golang/errors/errors.h"
#include "golang/internal/syscall/windows/registry/key.h"
#include "golang/internal/syscall/windows/registry/syscall.h"
#include "golang/internal/syscall/windows/registry/zsyscall_windows.h"
#include "golang/syscall/syscall_windows.h"
#include "golang/syscall/types_windows.h"
#include "golang/syscall/zsyscall_windows.h"
#include "golang/unicode/utf16/utf16.h"
#include "golang/unsafe/unsafe.h"

namespace golang::registry
{
    extern syscall::Errno ErrShortBuffer;
    extern syscall::Errno ErrNotExist;
    extern std::string ErrUnexpectedType;
    std::tuple<int, uint32_t, std::string> GetValue(Key k, std::string name, gocpp::slice<unsigned char> buf);
    std::tuple<gocpp::slice<unsigned char>, uint32_t, std::string> getValue(Key k, std::string name, gocpp::slice<unsigned char> buf);
    std::tuple<std::string, uint32_t, std::string> GetStringValue(Key k, std::string name);
    std::tuple<std::string, std::string> GetMUIStringValue(Key k, std::string name);
    std::tuple<std::string, std::string> ExpandString(std::string value);
    std::tuple<gocpp::slice<std::string>, uint32_t, std::string> GetStringsValue(Key k, std::string name);
    std::tuple<uint64_t, uint32_t, std::string> GetIntegerValue(Key k, std::string name);
    std::tuple<gocpp::slice<unsigned char>, uint32_t, std::string> GetBinaryValue(Key k, std::string name);
    std::string setValue(Key k, std::string name, uint32_t valtype, gocpp::slice<unsigned char> data);
    std::string SetDWordValue(Key k, std::string name, uint32_t value);
    std::string SetQWordValue(Key k, std::string name, uint64_t value);
    std::string setStringValue(Key k, std::string name, uint32_t valtype, std::string value);
    std::string SetStringValue(Key k, std::string name, std::string value);
    std::string SetExpandStringValue(Key k, std::string name, std::string value);
    std::string SetStringsValue(Key k, std::string name, gocpp::slice<std::string> value);
    std::string SetBinaryValue(Key k, std::string name, gocpp::slice<unsigned char> value);
    std::string DeleteValue(Key k, std::string name);
    std::tuple<gocpp::slice<std::string>, std::string> ReadValueNames(Key k);
}
