#pragma once

#include <functional>
#include <string>
#include <tuple>
#include <vector>

#include "tests/TourOfGo/methods/errors.fwd.h"
#include "gocpp/support.h"

namespace golang
{
    struct MyError
    {
        !!TYPE_EXPR_ERROR!! [*ast.SelectorExpr] When;
        std::string What;

        using isGoStruct = void;

        static MyError Init(void (init)(MyError&));

        std::ostream& PrintTo(std::ostream& os) const;
    };

    std::ostream& operator<<(std::ostream& os, const MyError& value);
    std::string Error(MyError* e);
    error run();
    void main();
}

