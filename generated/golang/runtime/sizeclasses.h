// generated by GoCpp from file '$(ImportDir)/runtime/sizeclasses.go'
#pragma once

#include <functional>
#include <string>
#include <tuple>
#include <vector>

#include "golang/runtime/sizeclasses.fwd.h"
#include "gocpp/support.h"

namespace golang::runtime
{
    extern gocpp::array<uint16_t, _NumSizeClasses> class_to_size;
    extern gocpp::array<uint8_t, _NumSizeClasses> class_to_allocnpages;
    extern gocpp::array<uint32_t, _NumSizeClasses> class_to_divmagic;
    extern gocpp::array<uint8_t, smallSizeMax / smallSizeDiv + 1> size_to_class8;
    extern gocpp::array<uint8_t, (_MaxSmallSize - smallSizeMax) / largeSizeDiv + 1> size_to_class128;

    namespace rec
    {
    }
}

