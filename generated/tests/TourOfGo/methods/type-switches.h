#pragma once

#include <functional>
#include <string>
#include <tuple>
#include <vector>

#include "tests/TourOfGo/methods/type-switches.fwd.h"
#include "gocpp/support.h"

// TODO: package import not implemented
// #include "fmt/doc.fwd.h"
// #include "fmt/errors.fwd.h"
// #include "fmt/format.fwd.h"
// #include "fmt/print.fwd.h"
// #include "fmt/scan.fwd.h"

namespace golang::main
{
    void go_do(std::any i);
    void main();
}

