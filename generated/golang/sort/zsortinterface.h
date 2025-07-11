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
    void insertionSort(struct Interface data, int a, int b);
    void siftDown(struct Interface data, int lo, int hi, int first);
    void heapSort(struct Interface data, int a, int b);
    void pdqsort(struct Interface data, int a, int b, int limit);
    std::tuple<int, bool> partition(struct Interface data, int a, int b, int pivot);
    int partitionEqual(struct Interface data, int a, int b, int pivot);
    bool partialInsertionSort(struct Interface data, int a, int b);
    void breakPatterns(struct Interface data, int a, int b);
    std::tuple<int, sort::sortedHint> choosePivot(struct Interface data, int a, int b);
    std::tuple<int, int> order2(struct Interface data, int a, int b, int* swaps);
    int median(struct Interface data, int a, int b, int c, int* swaps);
    int medianAdjacent(struct Interface data, int a, int* swaps);
    void reverseRange(struct Interface data, int a, int b);
    void swapRange(struct Interface data, int a, int b, int n);
    void stable(struct Interface data, int n);
    void symMerge(struct Interface data, int a, int m, int b);
    void rotate(struct Interface data, int a, int m, int b);

    namespace rec
    {
    }
}

