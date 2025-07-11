// generated by GoCpp from file '$(ImportDir)/runtime/defs_windows.go'
#include <complex>
#include <functional>
#include <iostream>
#include <iomanip>
#include <map>
#include <string>
#include <tuple>
#include <vector>

#include "golang/runtime/defs_windows.h"
#include "gocpp/support.h"

#include "golang/runtime/defs_windows_amd64.h"

namespace golang::runtime
{
    namespace rec
    {
        using namespace mocklib::rec;
    }

    
    template<typename T> requires gocpp::GoStruct<T>
    systeminfo::operator T()
    {
        T result;
        result.anon0 = this->anon0;
        result.dwpagesize = this->dwpagesize;
        result.lpminimumapplicationaddress = this->lpminimumapplicationaddress;
        result.lpmaximumapplicationaddress = this->lpmaximumapplicationaddress;
        result.dwactiveprocessormask = this->dwactiveprocessormask;
        result.dwnumberofprocessors = this->dwnumberofprocessors;
        result.dwprocessortype = this->dwprocessortype;
        result.dwallocationgranularity = this->dwallocationgranularity;
        result.wprocessorlevel = this->wprocessorlevel;
        result.wprocessorrevision = this->wprocessorrevision;
        return result;
    }

    template<typename T> requires gocpp::GoStruct<T>
    bool systeminfo::operator==(const T& ref) const
    {
        if (anon0 != ref.anon0) return false;
        if (dwpagesize != ref.dwpagesize) return false;
        if (lpminimumapplicationaddress != ref.lpminimumapplicationaddress) return false;
        if (lpmaximumapplicationaddress != ref.lpmaximumapplicationaddress) return false;
        if (dwactiveprocessormask != ref.dwactiveprocessormask) return false;
        if (dwnumberofprocessors != ref.dwnumberofprocessors) return false;
        if (dwprocessortype != ref.dwprocessortype) return false;
        if (dwallocationgranularity != ref.dwallocationgranularity) return false;
        if (wprocessorlevel != ref.wprocessorlevel) return false;
        if (wprocessorrevision != ref.wprocessorrevision) return false;
        return true;
    }

    std::ostream& systeminfo::PrintTo(std::ostream& os) const
    {
        os << '{';
        os << "" << anon0;
        os << " " << dwpagesize;
        os << " " << lpminimumapplicationaddress;
        os << " " << lpmaximumapplicationaddress;
        os << " " << dwactiveprocessormask;
        os << " " << dwnumberofprocessors;
        os << " " << dwprocessortype;
        os << " " << dwallocationgranularity;
        os << " " << wprocessorlevel;
        os << " " << wprocessorrevision;
        os << '}';
        return os;
    }

    std::ostream& operator<<(std::ostream& os, const struct systeminfo& value)
    {
        return value.PrintTo(os);
    }

    
    template<typename T> requires gocpp::GoStruct<T>
    exceptionpointers::operator T()
    {
        T result;
        result.record = this->record;
        result.context = this->context;
        return result;
    }

    template<typename T> requires gocpp::GoStruct<T>
    bool exceptionpointers::operator==(const T& ref) const
    {
        if (record != ref.record) return false;
        if (context != ref.context) return false;
        return true;
    }

    std::ostream& exceptionpointers::PrintTo(std::ostream& os) const
    {
        os << '{';
        os << "" << record;
        os << " " << context;
        os << '}';
        return os;
    }

    std::ostream& operator<<(std::ostream& os, const struct exceptionpointers& value)
    {
        return value.PrintTo(os);
    }

    
    template<typename T> requires gocpp::GoStruct<T>
    exceptionrecord::operator T()
    {
        T result;
        result.exceptioncode = this->exceptioncode;
        result.exceptionflags = this->exceptionflags;
        result.exceptionrecord = this->exceptionrecord;
        result.exceptionaddress = this->exceptionaddress;
        result.numberparameters = this->numberparameters;
        result.exceptioninformation = this->exceptioninformation;
        return result;
    }

    template<typename T> requires gocpp::GoStruct<T>
    bool exceptionrecord::operator==(const T& ref) const
    {
        if (exceptioncode != ref.exceptioncode) return false;
        if (exceptionflags != ref.exceptionflags) return false;
        if (exceptionrecord != ref.exceptionrecord) return false;
        if (exceptionaddress != ref.exceptionaddress) return false;
        if (numberparameters != ref.numberparameters) return false;
        if (exceptioninformation != ref.exceptioninformation) return false;
        return true;
    }

    std::ostream& exceptionrecord::PrintTo(std::ostream& os) const
    {
        os << '{';
        os << "" << exceptioncode;
        os << " " << exceptionflags;
        os << " " << exceptionrecord;
        os << " " << exceptionaddress;
        os << " " << numberparameters;
        os << " " << exceptioninformation;
        os << '}';
        return os;
    }

    std::ostream& operator<<(std::ostream& os, const struct exceptionrecord& value)
    {
        return value.PrintTo(os);
    }

    
    template<typename T> requires gocpp::GoStruct<T>
    overlapped::operator T()
    {
        T result;
        result.internal = this->internal;
        result.internalhigh = this->internalhigh;
        result.anon0 = this->anon0;
        result.hevent = this->hevent;
        return result;
    }

    template<typename T> requires gocpp::GoStruct<T>
    bool overlapped::operator==(const T& ref) const
    {
        if (internal != ref.internal) return false;
        if (internalhigh != ref.internalhigh) return false;
        if (anon0 != ref.anon0) return false;
        if (hevent != ref.hevent) return false;
        return true;
    }

    std::ostream& overlapped::PrintTo(std::ostream& os) const
    {
        os << '{';
        os << "" << internal;
        os << " " << internalhigh;
        os << " " << anon0;
        os << " " << hevent;
        os << '}';
        return os;
    }

    std::ostream& operator<<(std::ostream& os, const struct overlapped& value)
    {
        return value.PrintTo(os);
    }

    
    template<typename T> requires gocpp::GoStruct<T>
    memoryBasicInformation::operator T()
    {
        T result;
        result.baseAddress = this->baseAddress;
        result.allocationBase = this->allocationBase;
        result.allocationProtect = this->allocationProtect;
        result.regionSize = this->regionSize;
        result.state = this->state;
        result.protect = this->protect;
        result.type_ = this->type_;
        return result;
    }

    template<typename T> requires gocpp::GoStruct<T>
    bool memoryBasicInformation::operator==(const T& ref) const
    {
        if (baseAddress != ref.baseAddress) return false;
        if (allocationBase != ref.allocationBase) return false;
        if (allocationProtect != ref.allocationProtect) return false;
        if (regionSize != ref.regionSize) return false;
        if (state != ref.state) return false;
        if (protect != ref.protect) return false;
        if (type_ != ref.type_) return false;
        return true;
    }

    std::ostream& memoryBasicInformation::PrintTo(std::ostream& os) const
    {
        os << '{';
        os << "" << baseAddress;
        os << " " << allocationBase;
        os << " " << allocationProtect;
        os << " " << regionSize;
        os << " " << state;
        os << " " << protect;
        os << " " << type_;
        os << '}';
        return os;
    }

    std::ostream& operator<<(std::ostream& os, const struct memoryBasicInformation& value)
    {
        return value.PrintTo(os);
    }

}

