// generated by GoCpp from file '$(ImportDir)/internal/bytealg/count_native.go'
#pragma once

#include <functional>
#include <string>
#include <tuple>
#include <vector>

#include "golang/internal/bytealg/count_native.fwd.h"
#include "gocpp/support.h"

namespace golang::bytealg
{
    int Count(gocpp::slice<unsigned char> b, unsigned char c);
    int CountString(std::string s, unsigned char c);
    int countGeneric(gocpp::slice<unsigned char> b, unsigned char c);
    int countGenericString(std::string s, unsigned char c);
}
