// generated by GoCpp from file '$(ImportDir)/sort/zsortinterface.go'
#pragma once

#include <functional>
#include <string>
#include <tuple>
#include <vector>

#include "golang/sort/zsortinterface.fwd.h"
#include "gocpp/support.h"

#include "golang/sort/sort.h"

namespace golang::sort
{
    void insertionSort(Interface data, int a, int b);
    void siftDown(Interface data, int lo, int hi, int first);
    void heapSort(Interface data, int a, int b);
    void pdqsort(Interface data, int a, int b, int limit);
    std::tuple<int, bool> partition(Interface data, int a, int b, int pivot);
    int partitionEqual(Interface data, int a, int b, int pivot);
    bool partialInsertionSort(Interface data, int a, int b);
    void breakPatterns(Interface data, int a, int b);
    std::tuple<int, sortedHint> choosePivot(Interface data, int a, int b);
    std::tuple<int, int> order2(Interface data, int a, int b, int* swaps);
    int median(Interface data, int a, int b, int c, int* swaps);
    int medianAdjacent(Interface data, int a, int* swaps);
    void reverseRange(Interface data, int a, int b);
    void swapRange(Interface data, int a, int b, int n);
    void stable(Interface data, int n);
    void symMerge(Interface data, int a, int m, int b);
    void rotate(Interface data, int a, int m, int b);
}

