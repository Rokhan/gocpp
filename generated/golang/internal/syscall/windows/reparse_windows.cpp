// generated by GoCpp from file '$(ImportDir)/internal/syscall/windows/reparse_windows.go'
#include <complex>
#include <functional>
#include <iostream>
#include <iomanip>
#include <map>
#include <string>
#include <tuple>
#include <vector>

#include "golang/internal/syscall/windows/reparse_windows.h"
#include "gocpp/support.h"

#include "golang/syscall/syscall_windows.h"
#include "golang/unsafe/unsafe.h"

namespace golang::windows
{
    namespace rec
    {
        using namespace mocklib::rec;
    }

    
    template<typename T> requires gocpp::GoStruct<T>
    REPARSE_DATA_BUFFER::operator T()
    {
        T result;
        result.ReparseTag = this->ReparseTag;
        result.ReparseDataLength = this->ReparseDataLength;
        result.Reserved = this->Reserved;
        result.DUMMYUNIONNAME = this->DUMMYUNIONNAME;
        return result;
    }

    template<typename T> requires gocpp::GoStruct<T>
    bool REPARSE_DATA_BUFFER::operator==(const T& ref) const
    {
        if (ReparseTag != ref.ReparseTag) return false;
        if (ReparseDataLength != ref.ReparseDataLength) return false;
        if (Reserved != ref.Reserved) return false;
        if (DUMMYUNIONNAME != ref.DUMMYUNIONNAME) return false;
        return true;
    }

    std::ostream& REPARSE_DATA_BUFFER::PrintTo(std::ostream& os) const
    {
        os << '{';
        os << "" << ReparseTag;
        os << " " << ReparseDataLength;
        os << " " << Reserved;
        os << " " << DUMMYUNIONNAME;
        os << '}';
        return os;
    }

    std::ostream& operator<<(std::ostream& os, const struct REPARSE_DATA_BUFFER& value)
    {
        return value.PrintTo(os);
    }

    // REPARSE_DATA_BUFFER_HEADER is a common part of REPARSE_DATA_BUFFER structure.
    
    template<typename T> requires gocpp::GoStruct<T>
    REPARSE_DATA_BUFFER_HEADER::operator T()
    {
        T result;
        result.ReparseTag = this->ReparseTag;
        result.ReparseDataLength = this->ReparseDataLength;
        result.Reserved = this->Reserved;
        return result;
    }

    template<typename T> requires gocpp::GoStruct<T>
    bool REPARSE_DATA_BUFFER_HEADER::operator==(const T& ref) const
    {
        if (ReparseTag != ref.ReparseTag) return false;
        if (ReparseDataLength != ref.ReparseDataLength) return false;
        if (Reserved != ref.Reserved) return false;
        return true;
    }

    std::ostream& REPARSE_DATA_BUFFER_HEADER::PrintTo(std::ostream& os) const
    {
        os << '{';
        os << "" << ReparseTag;
        os << " " << ReparseDataLength;
        os << " " << Reserved;
        os << '}';
        return os;
    }

    std::ostream& operator<<(std::ostream& os, const struct REPARSE_DATA_BUFFER_HEADER& value)
    {
        return value.PrintTo(os);
    }

    
    template<typename T> requires gocpp::GoStruct<T>
    SymbolicLinkReparseBuffer::operator T()
    {
        T result;
        result.SubstituteNameOffset = this->SubstituteNameOffset;
        result.SubstituteNameLength = this->SubstituteNameLength;
        result.PrintNameOffset = this->PrintNameOffset;
        result.PrintNameLength = this->PrintNameLength;
        result.Flags = this->Flags;
        result.PathBuffer = this->PathBuffer;
        return result;
    }

    template<typename T> requires gocpp::GoStruct<T>
    bool SymbolicLinkReparseBuffer::operator==(const T& ref) const
    {
        if (SubstituteNameOffset != ref.SubstituteNameOffset) return false;
        if (SubstituteNameLength != ref.SubstituteNameLength) return false;
        if (PrintNameOffset != ref.PrintNameOffset) return false;
        if (PrintNameLength != ref.PrintNameLength) return false;
        if (Flags != ref.Flags) return false;
        if (PathBuffer != ref.PathBuffer) return false;
        return true;
    }

    std::ostream& SymbolicLinkReparseBuffer::PrintTo(std::ostream& os) const
    {
        os << '{';
        os << "" << SubstituteNameOffset;
        os << " " << SubstituteNameLength;
        os << " " << PrintNameOffset;
        os << " " << PrintNameLength;
        os << " " << Flags;
        os << " " << PathBuffer;
        os << '}';
        return os;
    }

    std::ostream& operator<<(std::ostream& os, const struct SymbolicLinkReparseBuffer& value)
    {
        return value.PrintTo(os);
    }

    // Path returns path stored in rb.
    std::string rec::Path(struct SymbolicLinkReparseBuffer* rb)
    {
        auto n1 = rb->SubstituteNameOffset / 2;
        auto n2 = (rb->SubstituteNameOffset + rb->SubstituteNameLength) / 2;
        return syscall::UTF16ToString((gocpp::array<uint16_t, 0xffff>*)(unsafe::Pointer(& rb->PathBuffer[0])).make_slice(n1, n2, n2));
    }

    
    template<typename T> requires gocpp::GoStruct<T>
    MountPointReparseBuffer::operator T()
    {
        T result;
        result.SubstituteNameOffset = this->SubstituteNameOffset;
        result.SubstituteNameLength = this->SubstituteNameLength;
        result.PrintNameOffset = this->PrintNameOffset;
        result.PrintNameLength = this->PrintNameLength;
        result.PathBuffer = this->PathBuffer;
        return result;
    }

    template<typename T> requires gocpp::GoStruct<T>
    bool MountPointReparseBuffer::operator==(const T& ref) const
    {
        if (SubstituteNameOffset != ref.SubstituteNameOffset) return false;
        if (SubstituteNameLength != ref.SubstituteNameLength) return false;
        if (PrintNameOffset != ref.PrintNameOffset) return false;
        if (PrintNameLength != ref.PrintNameLength) return false;
        if (PathBuffer != ref.PathBuffer) return false;
        return true;
    }

    std::ostream& MountPointReparseBuffer::PrintTo(std::ostream& os) const
    {
        os << '{';
        os << "" << SubstituteNameOffset;
        os << " " << SubstituteNameLength;
        os << " " << PrintNameOffset;
        os << " " << PrintNameLength;
        os << " " << PathBuffer;
        os << '}';
        return os;
    }

    std::ostream& operator<<(std::ostream& os, const struct MountPointReparseBuffer& value)
    {
        return value.PrintTo(os);
    }

    // Path returns path stored in rb.
    std::string rec::Path(struct MountPointReparseBuffer* rb)
    {
        auto n1 = rb->SubstituteNameOffset / 2;
        auto n2 = (rb->SubstituteNameOffset + rb->SubstituteNameLength) / 2;
        return syscall::UTF16ToString((gocpp::array<uint16_t, 0xffff>*)(unsafe::Pointer(& rb->PathBuffer[0])).make_slice(n1, n2, n2));
    }

}

