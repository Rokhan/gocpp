// generated by GoCpp from file 'tests/TourOfGo/basics/name-conflicts.go'
#pragma once

#include <functional>
#include <string>
#include <tuple>
#include <vector>

#include "tests/TourOfGo/basics/name-conflicts.fwd.h"
#include "gocpp/support.h"


namespace golang::main
{
    struct toto
    {

        using isGoStruct = void;

        template<typename T> requires gocpp::GoStruct<T>
        operator T();

        template<typename T> requires gocpp::GoStruct<T>
        bool operator==(const T& ref) const;

        std::ostream& PrintTo(std::ostream& os) const;
    };

    std::ostream& operator<<(std::ostream& os, const struct toto& value);
    void main();
    void newFunction();

    namespace rec
    {
        double Pi(struct toto t);
        double toto(struct toto t);
        main::titi titi(struct toto t, golang::main::titi d);
    }
}

