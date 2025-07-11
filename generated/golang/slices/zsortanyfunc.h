// generated by GoCpp from file '$(ImportDir)/slices/zsortanyfunc.go'
#pragma once

#include <functional>
#include <string>
#include <tuple>
#include <vector>

#include "golang/slices/zsortanyfunc.fwd.h"
#include "gocpp/support.h"

#include "golang/slices/sort.h"

namespace golang::slices
{
    
    template<typename E>
    void insertionSortCmpFunc(gocpp::slice<E> data, int a, int b, std::function<int (E a, E b)> cmp);
    
    template<typename E>
    void siftDownCmpFunc(gocpp::slice<E> data, int lo, int hi, int first, std::function<int (E a, E b)> cmp);
    
    template<typename E>
    void heapSortCmpFunc(gocpp::slice<E> data, int a, int b, std::function<int (E a, E b)> cmp);
    
    template<typename E>
    void pdqsortCmpFunc(gocpp::slice<E> data, int a, int b, int limit, std::function<int (E a, E b)> cmp);
    
    template<typename E>
    std::tuple<int, bool> partitionCmpFunc(gocpp::slice<E> data, int a, int b, int pivot, std::function<int (E a, E b)> cmp);
    
    template<typename E>
    int partitionEqualCmpFunc(gocpp::slice<E> data, int a, int b, int pivot, std::function<int (E a, E b)> cmp);
    
    template<typename E>
    bool partialInsertionSortCmpFunc(gocpp::slice<E> data, int a, int b, std::function<int (E a, E b)> cmp);
    
    template<typename E>
    void breakPatternsCmpFunc(gocpp::slice<E> data, int a, int b, std::function<int (E a, E b)> cmp);
    
    template<typename E>
    std::tuple<int, slices::sortedHint> choosePivotCmpFunc(gocpp::slice<E> data, int a, int b, std::function<int (E a, E b)> cmp);
    
    template<typename E>
    std::tuple<int, int> order2CmpFunc(gocpp::slice<E> data, int a, int b, int* swaps, std::function<int (E a, E b)> cmp);
    
    template<typename E>
    int medianCmpFunc(gocpp::slice<E> data, int a, int b, int c, int* swaps, std::function<int (E a, E b)> cmp);
    
    template<typename E>
    int medianAdjacentCmpFunc(gocpp::slice<E> data, int a, int* swaps, std::function<int (E a, E b)> cmp);
    
    template<typename E>
    void reverseRangeCmpFunc(gocpp::slice<E> data, int a, int b, std::function<int (E a, E b)> cmp);
    
    template<typename E>
    void swapRangeCmpFunc(gocpp::slice<E> data, int a, int b, int n, std::function<int (E a, E b)> cmp);
    
    template<typename E>
    void stableCmpFunc(gocpp::slice<E> data, int n, std::function<int (E a, E b)> cmp);
    
    template<typename E>
    void symMergeCmpFunc(gocpp::slice<E> data, int a, int m, int b, std::function<int (E a, E b)> cmp);
    
    template<typename E>
    void rotateCmpFunc(gocpp::slice<E> data, int a, int m, int b, std::function<int (E a, E b)> cmp);

    namespace rec
    {
    }
}

