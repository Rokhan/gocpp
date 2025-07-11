// generated by GoCpp from file '$(ImportDir)/internal/syscall/windows/reparse_windows.go'
#pragma once

#include <functional>
#include <string>
#include <tuple>
#include <vector>

#include "golang/internal/syscall/windows/reparse_windows.fwd.h"
#include "gocpp/support.h"


namespace golang::windows
{
    struct REPARSE_DATA_BUFFER
    {
        uint32_t ReparseTag;
        uint16_t ReparseDataLength;
        uint16_t Reserved;
        unsigned char DUMMYUNIONNAME;

        using isGoStruct = void;

        template<typename T> requires gocpp::GoStruct<T>
        operator T();

        template<typename T> requires gocpp::GoStruct<T>
        bool operator==(const T& ref) const;

        std::ostream& PrintTo(std::ostream& os) const;
    };

    std::ostream& operator<<(std::ostream& os, const struct REPARSE_DATA_BUFFER& value);
    struct REPARSE_DATA_BUFFER_HEADER
    {
        uint32_t ReparseTag;
        uint16_t ReparseDataLength;
        uint16_t Reserved;

        using isGoStruct = void;

        template<typename T> requires gocpp::GoStruct<T>
        operator T();

        template<typename T> requires gocpp::GoStruct<T>
        bool operator==(const T& ref) const;

        std::ostream& PrintTo(std::ostream& os) const;
    };

    std::ostream& operator<<(std::ostream& os, const struct REPARSE_DATA_BUFFER_HEADER& value);
    struct SymbolicLinkReparseBuffer
    {
        uint16_t SubstituteNameOffset;
        uint16_t SubstituteNameLength;
        uint16_t PrintNameOffset;
        uint16_t PrintNameLength;
        uint32_t Flags;
        gocpp::array<uint16_t, 1> PathBuffer;

        using isGoStruct = void;

        template<typename T> requires gocpp::GoStruct<T>
        operator T();

        template<typename T> requires gocpp::GoStruct<T>
        bool operator==(const T& ref) const;

        std::ostream& PrintTo(std::ostream& os) const;
    };

    std::ostream& operator<<(std::ostream& os, const struct SymbolicLinkReparseBuffer& value);
    struct MountPointReparseBuffer
    {
        uint16_t SubstituteNameOffset;
        uint16_t SubstituteNameLength;
        uint16_t PrintNameOffset;
        uint16_t PrintNameLength;
        gocpp::array<uint16_t, 1> PathBuffer;

        using isGoStruct = void;

        template<typename T> requires gocpp::GoStruct<T>
        operator T();

        template<typename T> requires gocpp::GoStruct<T>
        bool operator==(const T& ref) const;

        std::ostream& PrintTo(std::ostream& os) const;
    };

    std::ostream& operator<<(std::ostream& os, const struct MountPointReparseBuffer& value);

    namespace rec
    {
        std::string Path(struct SymbolicLinkReparseBuffer* rb);
        std::string Path(struct MountPointReparseBuffer* rb);
    }
}

