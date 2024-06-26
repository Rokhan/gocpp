#pragma once

namespace gocpp
{
    template<typename T> struct slice;
    template<typename T> struct array_base;
    template<typename T, int N> struct array;
    template<typename K, typename V> struct map;
    
    struct complex128;
    struct Defer;
    using rune = int;
}
