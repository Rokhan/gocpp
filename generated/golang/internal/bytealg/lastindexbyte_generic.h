// generated by GoCpp from file '$(ImportDir)/internal/bytealg/lastindexbyte_generic.go'
#pragma once

#include <functional>
#include <string>
#include <tuple>
#include <vector>

#include "golang/internal/bytealg/lastindexbyte_generic.fwd.h"
#include "gocpp/support.h"

namespace golang::bytealg
{
    int LastIndexByte(gocpp::slice<unsigned char> s, unsigned char c);
    int LastIndexByteString(std::string s, unsigned char c);
}
