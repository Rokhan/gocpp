// generated by GoCpp from file '$(ImportDir)/internal/bytealg/indexbyte_native.go'
#pragma once

#include <functional>
#include <string>
#include <tuple>
#include <vector>

#include "golang/internal/bytealg/indexbyte_native.fwd.h"
#include "gocpp/support.h"

namespace golang::bytealg
{
    int IndexByte(gocpp::slice<unsigned char> b, unsigned char c);
    int IndexByteString(std::string s, unsigned char c);

    namespace rec
    {
    }
}

