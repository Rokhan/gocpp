// generated by GoCpp from file '$(ImportDir)/encoding/binary/native_endian_little.go'
#include <complex>
#include <functional>
#include <iostream>
#include <iomanip>
#include <map>
#include <string>
#include <tuple>
#include <vector>

#include "golang/encoding/binary/native_endian_little.h"
#include "gocpp/support.h"

#include "golang/encoding/binary/binary.h"

namespace golang::binary
{
    
    std::ostream& nativeEndian::PrintTo(std::ostream& os) const
    {
        os << '{';
        os << '}';
        return os;
    }

    std::ostream& operator<<(std::ostream& os, const nativeEndian& value)
    {
        return value.PrintTo(os);
    }

    nativeEndian NativeEndian;
}
