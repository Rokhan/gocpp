#pragma once

#include <functional>
#include <string>
#include <tuple>
#include <vector>

#include "tests/HelloWorld.fwd.h"
#include "gocpp/support.h"

// TODO: package import not implemented
// #include "fmt/doc.fwd.h"
// #include "fmt/errors.fwd.h"
// #include "fmt/format.fwd.h"
// #include "fmt/print.fwd.h"
// #include "fmt/scan.fwd.h"

namespace golang::main
{
    void main();
    int square(int num);
    void helloFunc(std::string str1, std::string str2, std::string str3);
    void printN(std::string str1, int n);
}

