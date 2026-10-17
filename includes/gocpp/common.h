#pragma once

#include "gocpp/support.fwd.h"

namespace gocpp
{
    [[noreturn]] void panic(const gocpp::string& message);
    [[noreturn]] void panic(const char* const message);
}