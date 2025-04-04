// generated by GoCpp from file '$(ImportDir)/slices/sort.go'
#pragma once

#include <functional>
#include <string>
#include <tuple>
#include <vector>

#include "golang/slices/sort.fwd.h"
#include "gocpp/support.h"


namespace golang::slices
{

    template<typename S>
    void Sort(S x);

    template<typename S>
    void SortFunc(S x, std::function<int (E a, E b)> cmp);

    template<typename S>
    void SortStableFunc(S x, std::function<int (E a, E b)> cmp);

    template<typename S>
    bool IsSorted(S x);

    template<typename S>
    bool IsSortedFunc(S x, std::function<int (E a, E b)> cmp);

    template<typename S>
    E Min(S x);

    template<typename S>
    E MinFunc(S x, std::function<int (E a, E b)> cmp);

    template<typename S>
    E Max(S x);

    template<typename S>
    E MaxFunc(S x, std::function<int (E a, E b)> cmp);

    template<typename S, typename E>
    std::tuple<int, bool> BinarySearch(S x, E target);

    template<typename S, typename T>
    std::tuple<int, bool> BinarySearchFunc(S x, T target, std::function<int (E, T)> cmp);
    uint64_t Next(xorshift* r);
    unsigned int nextPowerOfTwo(int length);

    template<typename T>
    bool isNaN(T x);
}

