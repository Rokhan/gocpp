#pragma once

#include <cstdint>

// TODO: try to not need this 
#include <string>

// Temporary definitions to mock broken include files
namespace golang
{
    namespace runtime
    {
        struct g;
        struct sudog;

        struct funcval;
        struct gobuf;
        struct mcache;
        struct adjustinfo;
        struct funcInfo;
        struct itab;
        struct eface;
        struct iface;
        struct _defer;
        struct _panic;
        struct godebugInc;
    }
}

namespace gocpp
{
    template<typename T> struct slice;
    template<typename T> struct array_base;
    template<typename T, int N> struct array;
    template<typename K, typename V> struct map;
    
    struct GoPanic;
    struct complex128;
    struct go_any;
    struct Defer;

    using rune = int;
}

