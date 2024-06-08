#pragma once

#include <functional>
#include <string>
#include <tuple>
#include <vector>

#include "tests/TourOfGo/moretypes/exercise-maps.fwd.h"
#include "gocpp/support.h"

// TODO: package import not implemented
// #include "strings/builder.fwd.h"
// #include "strings/clone.fwd.h"
// #include "strings/compare.fwd.h"
// #include "strings/reader.fwd.h"
// #include "strings/replace.fwd.h"
// #include "strings/search.fwd.h"
// #include "strings/strings.fwd.h"
// #include "golang.org/x/tour/wc/wc.fwd.h"

namespace golang::main
{
    gocpp::map<std::string, int> WordCount(std::string s);
    void main();
}

