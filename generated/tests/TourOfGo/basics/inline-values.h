#pragma once

#include <functional>
#include <string>
#include <tuple>
#include <vector>

#include "tests/TourOfGo/basics/inline-values.fwd.h"
#include "gocpp/support.h"

namespace golang
{
    void main();
    using ints = gocpp::slice<int>;
    extern ints smallPrimes;
    using fakeFetcher = gocpp::map<std::string, fakeResult*>;
    struct fakeResult
    {
        std::string body;
        gocpp::slice<std::string> urls;

        using isGoStruct = void;

        std::ostream& PrintTo(std::ostream& os) const;
    };

    std::ostream& operator<<(std::ostream& os, const fakeResult& value);
    extern fakeFetcher fetcher;
}
