#pragma once

#include <functional>
#include <string>
#include <tuple>
#include <vector>

#include "tests/TourOfGo/concurrency/mutex-counter.fwd.h"
#include "gocpp/support.h"

namespace golang
{
    struct SafeCounter
    {
        mocklib::Mutex mu;
        gocpp::map<std::string, int> v;

        using isGoStruct = void;

        std::ostream& PrintTo(std::ostream& os) const;
    };

    std::ostream& operator<<(std::ostream& os, const SafeCounter& value);
    void Inc(SafeCounter* c, std::string key);
    int Value(SafeCounter* c, std::string key);
    void main();
}

