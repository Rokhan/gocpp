#pragma once

#include <functional>
#include <string>
#include <tuple>
#include <vector>

#include "tests/TourOfGo/concurrency/exercise-equivalent-binary-trees.fwd.h"
#include "gocpp/support.h"

// TODO: package import not implemented
// #include "fmt/doc.fwd.h"
// #include "fmt/errors.fwd.h"
// #include "fmt/format.fwd.h"
// #include "fmt/print.fwd.h"
// #include "fmt/scan.fwd.h"
// #include "golang.org/x/tour/tree/tree.fwd.h"

namespace golang::main
{
    void Walk(tree::Tree* t, gocpp::channel<int> ch);
    bool Same(tree::Tree* t1, tree::Tree* t2);
    void main();
}

