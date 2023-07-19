#pragma once

#include <functional>
#include <string>
#include <tuple>
#include <vector>

#include "tests/TourOfGo/methods/exercise-rot-reader.fwd.h"
#include "gocpp/support.h"

namespace golang
{
    struct rot13Reader
    {
        !!TYPE_EXPR_ERROR!! [*ast.SelectorExpr] r;

        using isGoStruct = void;

        static rot13Reader Init(void (init)(rot13Reader&));

        std::ostream& PrintTo(std::ostream& os) const;
    };

    std::ostream& operator<<(std::ostream& os, const rot13Reader& value);
    void main();
}

