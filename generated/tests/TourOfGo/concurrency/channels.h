// generated by GoCpp from file 'tests/TourOfGo/concurrency/channels.go'
#pragma once

#include <functional>
#include <string>
#include <tuple>
#include <vector>

#include "tests/TourOfGo/concurrency/channels.fwd.h"
#include "gocpp/support.h"


namespace golang::main
{
    void sum(gocpp::slice<int> s, gocpp::channel<int> c);
    void main();

    namespace rec
    {
    }
}

