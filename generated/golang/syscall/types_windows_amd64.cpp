// generated by GoCpp from file '$(ImportDir)/syscall/types_windows_amd64.go'
#include <complex>
#include <functional>
#include <iostream>
#include <iomanip>
#include <map>
#include <string>
#include <tuple>
#include <vector>

#include "golang/syscall/types_windows_amd64.h"
#include "gocpp/support.h"

#include "golang/syscall/types_windows.h"

namespace golang::syscall
{
    
    std::ostream& WSAData::PrintTo(std::ostream& os) const
    {
        os << '{';
        os << "" << Version;
        os << " " << HighVersion;
        os << " " << MaxSockets;
        os << " " << MaxUdpDg;
        os << " " << VendorInfo;
        os << " " << Description;
        os << " " << SystemStatus;
        os << '}';
        return os;
    }

    std::ostream& operator<<(std::ostream& os, const struct WSAData& value)
    {
        return value.PrintTo(os);
    }

    
    std::ostream& Servent::PrintTo(std::ostream& os) const
    {
        os << '{';
        os << "" << Name;
        os << " " << Aliases;
        os << " " << Proto;
        os << " " << Port;
        os << '}';
        return os;
    }

    std::ostream& operator<<(std::ostream& os, const struct Servent& value)
    {
        return value.PrintTo(os);
    }

}
