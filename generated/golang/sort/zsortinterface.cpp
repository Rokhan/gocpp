// generated by GoCpp from file '$(ImportDir)/sort/zsortinterface.go'
#include <complex>
#include <functional>
#include <iostream>
#include <iomanip>
#include <map>
#include <string>
#include <tuple>
#include <vector>

#include "golang/sort/zsortinterface.h"
#include "gocpp/support.h"

#include "golang/sort/sort.h"

namespace golang::sort
{
    namespace rec
    {
        using namespace mocklib::rec;
    }

    // insertionSort sorts data[a:b] using insertion sort.
    void insertionSort(struct Interface data, int a, int b)
    {
        for(auto i = a + 1; i < b; i++)
        {
            for(auto j = i; j > a && rec::Less(gocpp::recv(data), j, j - 1); j--)
            {
                rec::Swap(gocpp::recv(data), j, j - 1);
            }
        }
    }

    // siftDown implements the heap property on data[lo:hi].
    // first is an offset into the array where the root of the heap lies.
    void siftDown(struct Interface data, int lo, int hi, int first)
    {
        auto root = lo;
        for(; ; )
        {
            auto child = 2 * root + 1;
            if(child >= hi)
            {
                break;
            }
            if(child + 1 < hi && rec::Less(gocpp::recv(data), first + child, first + child + 1))
            {
                child++;
            }
            if(! rec::Less(gocpp::recv(data), first + root, first + child))
            {
                return;
            }
            rec::Swap(gocpp::recv(data), first + root, first + child);
            root = child;
        }
    }

    void heapSort(struct Interface data, int a, int b)
    {
        auto first = a;
        auto lo = 0;
        auto hi = b - a;
        for(auto i = (hi - 1) / 2; i >= 0; i--)
        {
            siftDown(data, i, hi, first);
        }
        for(auto i = hi - 1; i >= 0; i--)
        {
            rec::Swap(gocpp::recv(data), first, first + i);
            siftDown(data, lo, i, first);
        }
    }

    // pdqsort sorts data[a:b].
    // The algorithm based on pattern-defeating quicksort(pdqsort), but without the optimizations from BlockQuicksort.
    // pdqsort paper: https://arxiv.org/pdf/2106.05123.pdf
    // C++ implementation: https://github.com/orlp/pdqsort
    // Rust implementation: https://docs.rs/pdqsort/latest/pdqsort/
    // limit is the number of allowed bad (very unbalanced) pivots before falling back to heapsort.
    void pdqsort(struct Interface data, int a, int b, int limit)
    {
        auto maxInsertion = 12;
        auto wasBalanced = true;
        auto wasPartitioned = true;
        for(; ; )
        {
            auto length = b - a;
            if(length <= maxInsertion)
            {
                insertionSort(data, a, b);
                return;
            }
            if(limit == 0)
            {
                heapSort(data, a, b);
                return;
            }
            if(! wasBalanced)
            {
                breakPatterns(data, a, b);
                limit--;
            }
            auto [pivot, hint] = choosePivot(data, a, b);
            if(hint == decreasingHint)
            {
                reverseRange(data, a, b);
                pivot = (b - 1) - (pivot - a);
                hint = increasingHint;
            }
            if(wasBalanced && wasPartitioned && hint == increasingHint)
            {
                if(partialInsertionSort(data, a, b))
                {
                    return;
                }
            }
            if(a > 0 && ! rec::Less(gocpp::recv(data), a - 1, pivot))
            {
                auto mid = partitionEqual(data, a, b, pivot);
                a = mid;
                continue;
            }
            auto [mid, alreadyPartitioned] = partition(data, a, b, pivot);
            wasPartitioned = alreadyPartitioned;
            auto [leftLen, rightLen] = std::tuple{mid - a, b - mid};
            auto balanceThreshold = length / 8;
            if(leftLen < rightLen)
            {
                wasBalanced = leftLen >= balanceThreshold;
                pdqsort(data, a, mid, limit);
                a = mid + 1;
            }
            else
            {
                wasBalanced = rightLen >= balanceThreshold;
                pdqsort(data, mid + 1, b, limit);
                b = mid;
            }
        }
    }

    // partition does one quicksort partition.
    // Let p = data[pivot]
    // Moves elements in data[a:b] around, so that data[i]<p and data[j]>=p for i<newpivot and j>newpivot.
    // On return, data[newpivot] = p
    std::tuple<int, bool> partition(struct Interface data, int a, int b, int pivot)
    {
        int newpivot;
        bool alreadyPartitioned;
        rec::Swap(gocpp::recv(data), a, pivot);
        auto [i, j] = std::tuple{a + 1, b - 1};
        for(; i <= j && rec::Less(gocpp::recv(data), i, a); )
        {
            i++;
        }
        for(; i <= j && ! rec::Less(gocpp::recv(data), j, a); )
        {
            j--;
        }
        if(i > j)
        {
            rec::Swap(gocpp::recv(data), j, a);
            return {j, true};
        }
        rec::Swap(gocpp::recv(data), i, j);
        i++;
        j--;
        for(; ; )
        {
            for(; i <= j && rec::Less(gocpp::recv(data), i, a); )
            {
                i++;
            }
            for(; i <= j && ! rec::Less(gocpp::recv(data), j, a); )
            {
                j--;
            }
            if(i > j)
            {
                break;
            }
            rec::Swap(gocpp::recv(data), i, j);
            i++;
            j--;
        }
        rec::Swap(gocpp::recv(data), j, a);
        return {j, false};
    }

    // partitionEqual partitions data[a:b] into elements equal to data[pivot] followed by elements greater than data[pivot].
    // It assumed that data[a:b] does not contain elements smaller than the data[pivot].
    int partitionEqual(struct Interface data, int a, int b, int pivot)
    {
        int newpivot;
        rec::Swap(gocpp::recv(data), a, pivot);
        auto [i, j] = std::tuple{a + 1, b - 1};
        for(; ; )
        {
            for(; i <= j && ! rec::Less(gocpp::recv(data), a, i); )
            {
                i++;
            }
            for(; i <= j && rec::Less(gocpp::recv(data), a, j); )
            {
                j--;
            }
            if(i > j)
            {
                break;
            }
            rec::Swap(gocpp::recv(data), i, j);
            i++;
            j--;
        }
        return i;
    }

    // partialInsertionSort partially sorts a slice, returns true if the slice is sorted at the end.
    bool partialInsertionSort(struct Interface data, int a, int b)
    {
        auto maxSteps = 5;
        auto shortestShifting = 50;
        auto i = a + 1;
        for(auto j = 0; j < maxSteps; j++)
        {
            for(; i < b && ! rec::Less(gocpp::recv(data), i, i - 1); )
            {
                i++;
            }
            if(i == b)
            {
                return true;
            }
            if(b - a < shortestShifting)
            {
                return false;
            }
            rec::Swap(gocpp::recv(data), i, i - 1);
            if(i - a >= 2)
            {
                for(auto j = i - 1; j >= 1; j--)
                {
                    if(! rec::Less(gocpp::recv(data), j, j - 1))
                    {
                        break;
                    }
                    rec::Swap(gocpp::recv(data), j, j - 1);
                }
            }
            if(b - i >= 2)
            {
                for(auto j = i + 1; j < b; j++)
                {
                    if(! rec::Less(gocpp::recv(data), j, j - 1))
                    {
                        break;
                    }
                    rec::Swap(gocpp::recv(data), j, j - 1);
                }
            }
        }
        return false;
    }

    // breakPatterns scatters some elements around in an attempt to break some patterns
    // that might cause imbalanced partitions in quicksort.
    void breakPatterns(struct Interface data, int a, int b)
    {
        auto length = b - a;
        if(length >= 8)
        {
            auto random = xorshift(length);
            auto modulus = nextPowerOfTwo(length);
            for(auto idx = a + (length / 4) * 2 - 1; idx <= a + (length / 4) * 2 + 1; idx++)
            {
                auto other = int((unsigned int)(rec::Next(gocpp::recv(random))) & (modulus - 1));
                if(other >= length)
                {
                    other -= length;
                }
                rec::Swap(gocpp::recv(data), idx, a + other);
            }
        }
    }

    // choosePivot chooses a pivot in data[a:b].
    //
    // [0,8): chooses a static pivot.
    // [8,shortestNinther): uses the simple median-of-three method.
    // [shortestNinther,∞): uses the Tukey ninther method.
    std::tuple<int, sort::sortedHint> choosePivot(struct Interface data, int a, int b)
    {
        int pivot;
        sort::sortedHint hint;
        auto shortestNinther = 50;
        auto maxSwaps = 4 * 3;
        auto l = b - a;
        int swaps = {};
        auto i = a + l / 4 * 1;
        auto j = a + l / 4 * 2;
        auto k = a + l / 4 * 3;
        if(l >= 8)
        {
            if(l >= shortestNinther)
            {
                i = medianAdjacent(data, i, & swaps);
                j = medianAdjacent(data, j, & swaps);
                k = medianAdjacent(data, k, & swaps);
            }
            j = median(data, i, j, k, & swaps);
        }
        //Go switch emulation
        {
            auto condition = swaps;
            int conditionId = -1;
            if(condition == 0) { conditionId = 0; }
            else if(condition == maxSwaps) { conditionId = 1; }
            switch(conditionId)
            {
                case 0:
                    return {j, increasingHint};
                    break;
                case 1:
                    return {j, decreasingHint};
                    break;
                default:
                    return {j, unknownHint};
                    break;
            }
        }
    }

    // order2 returns x,y where data[x] <= data[y], where x,y=a,b or x,y=b,a.
    std::tuple<int, int> order2(struct Interface data, int a, int b, int* swaps)
    {
        if(rec::Less(gocpp::recv(data), b, a))
        {
            *swaps++;
            return {b, a};
        }
        return {a, b};
    }

    // median returns x where data[x] is the median of data[a],data[b],data[c], where x is a, b, or c.
    int median(struct Interface data, int a, int b, int c, int* swaps)
    {
        std::tie(a, b) = order2(data, a, b, swaps);
        std::tie(b, c) = order2(data, b, c, swaps);
        std::tie(a, b) = order2(data, a, b, swaps);
        return b;
    }

    // medianAdjacent finds the median of data[a - 1], data[a], data[a + 1] and stores the index into a.
    int medianAdjacent(struct Interface data, int a, int* swaps)
    {
        return median(data, a - 1, a, a + 1, swaps);
    }

    void reverseRange(struct Interface data, int a, int b)
    {
        auto i = a;
        auto j = b - 1;
        for(; i < j; )
        {
            rec::Swap(gocpp::recv(data), i, j);
            i++;
            j--;
        }
    }

    void swapRange(struct Interface data, int a, int b, int n)
    {
        for(auto i = 0; i < n; i++)
        {
            rec::Swap(gocpp::recv(data), a + i, b + i);
        }
    }

    void stable(struct Interface data, int n)
    {
        auto blockSize = 20;
        auto [a, b] = std::tuple{0, blockSize};
        for(; b <= n; )
        {
            insertionSort(data, a, b);
            a = b;
            b += blockSize;
        }
        insertionSort(data, a, n);
        for(; blockSize < n; )
        {
            std::tie(a, b) = std::tuple{0, 2 * blockSize};
            for(; b <= n; )
            {
                symMerge(data, a, a + blockSize, b);
                a = b;
                b += 2 * blockSize;
            }
            if(auto m = a + blockSize; m < n)
            {
                symMerge(data, a, m, n);
            }
            blockSize *= 2;
        }
    }

    // symMerge merges the two sorted subsequences data[a:m] and data[m:b] using
    // the SymMerge algorithm from Pok-Son Kim and Arne Kutzner, "Stable Minimum
    // Storage Merging by Symmetric Comparisons", in Susanne Albers and Tomasz
    // Radzik, editors, Algorithms - ESA 2004, volume 3221 of Lecture Notes in
    // Computer Science, pages 714-723. Springer, 2004.
    //
    // Let M = m-a and N = b-n. Wolog M < N.
    // The recursion depth is bound by ceil(log(N+M)).
    // The algorithm needs O(M*log(N/M + 1)) calls to data.Less.
    // The algorithm needs O((M+N)*log(M)) calls to data.Swap.
    //
    // The paper gives O((M+N)*log(M)) as the number of assignments assuming a
    // rotation algorithm which uses O(M+N+gcd(M+N)) assignments. The argumentation
    // in the paper carries through for Swap operations, especially as the block
    // swapping rotate uses only O(M+N) Swaps.
    //
    // symMerge assumes non-degenerate arguments: a < m && m < b.
    // Having the caller check this condition eliminates many leaf recursion calls,
    // which improves performance.
    void symMerge(struct Interface data, int a, int m, int b)
    {
        if(m - a == 1)
        {
            auto i = m;
            auto j = b;
            for(; i < j; )
            {
                auto h = int((unsigned int)(i + j) >> 1);
                if(rec::Less(gocpp::recv(data), h, a))
                {
                    i = h + 1;
                }
                else
                {
                    j = h;
                }
            }
            for(auto k = a; k < i - 1; k++)
            {
                rec::Swap(gocpp::recv(data), k, k + 1);
            }
            return;
        }
        if(b - m == 1)
        {
            auto i = a;
            auto j = m;
            for(; i < j; )
            {
                auto h = int((unsigned int)(i + j) >> 1);
                if(! rec::Less(gocpp::recv(data), m, h))
                {
                    i = h + 1;
                }
                else
                {
                    j = h;
                }
            }
            for(auto k = m; k > i; k--)
            {
                rec::Swap(gocpp::recv(data), k, k - 1);
            }
            return;
        }
        auto mid = int((unsigned int)(a + b) >> 1);
        auto n = mid + m;
        int start = {};
        int r = {};
        if(m > mid)
        {
            start = n - b;
            r = mid;
        }
        else
        {
            start = a;
            r = m;
        }
        auto p = n - 1;
        for(; start < r; )
        {
            auto c = int((unsigned int)(start + r) >> 1);
            if(! rec::Less(gocpp::recv(data), p - c, c))
            {
                start = c + 1;
            }
            else
            {
                r = c;
            }
        }
        auto end = n - start;
        if(start < m && m < end)
        {
            rotate(data, start, m, end);
        }
        if(a < start && start < mid)
        {
            symMerge(data, a, start, mid);
        }
        if(mid < end && end < b)
        {
            symMerge(data, mid, end, b);
        }
    }

    // rotate rotates two consecutive blocks u = data[a:m] and v = data[m:b] in data:
    // Data of the form 'x u v y' is changed to 'x v u y'.
    // rotate performs at most b-a many calls to data.Swap,
    // and it assumes non-degenerate arguments: a < m && m < b.
    void rotate(struct Interface data, int a, int m, int b)
    {
        auto i = m - a;
        auto j = b - m;
        for(; i != j; )
        {
            if(i > j)
            {
                swapRange(data, m - i, m, j);
                i -= j;
            }
            else
            {
                swapRange(data, m - i, m + j - i, i);
                j -= i;
            }
        }
        swapRange(data, m - i, m, i);
    }

}

