// generated by GoCpp from file '$(ImportDir)/slices/zsortanyfunc.go'
#include <complex>
#include <functional>
#include <iostream>
#include <iomanip>
#include <map>
#include <string>
#include <tuple>
#include <vector>

#include "golang/slices/zsortanyfunc.h"
#include "gocpp/support.h"

#include "golang/slices/sort.h"

namespace golang::slices
{
    void insertionSortCmpFunc(gocpp::slice<E> data, int a, int b, std::function<int (E a, E b)> cmp)
    {
        for(auto i = a + 1; i < b; i++)
        {
            for(auto j = i; j > a && (cmp(data[j], data[j - 1]) < 0); j--)
            {
                std::tie(data[j], data[j - 1]) = std::tuple{data[j - 1], data[j]};
            }
        }
    }

    void siftDownCmpFunc(gocpp::slice<E> data, int lo, int hi, int first, std::function<int (E a, E b)> cmp)
    {
        auto root = lo;
        for(; ; )
        {
            auto child = 2 * root + 1;
            if(child >= hi)
            {
                break;
            }
            if(child + 1 < hi && (cmp(data[first + child], data[first + child + 1]) < 0))
            {
                child++;
            }
            if(! (cmp(data[first + root], data[first + child]) < 0))
            {
                return;
            }
            std::tie(data[first + root], data[first + child]) = std::tuple{data[first + child], data[first + root]};
            root = child;
        }
    }

    void heapSortCmpFunc(gocpp::slice<E> data, int a, int b, std::function<int (E a, E b)> cmp)
    {
        auto first = a;
        auto lo = 0;
        auto hi = b - a;
        for(auto i = (hi - 1) / 2; i >= 0; i--)
        {
            siftDownCmpFunc(data, i, hi, first, cmp);
        }
        for(auto i = hi - 1; i >= 0; i--)
        {
            std::tie(data[first], data[first + i]) = std::tuple{data[first + i], data[first]};
            siftDownCmpFunc(data, lo, i, first, cmp);
        }
    }

    void pdqsortCmpFunc(gocpp::slice<E> data, int a, int b, int limit, std::function<int (E a, E b)> cmp)
    {
        auto maxInsertion = 12;
        auto wasBalanced = true;
        auto wasPartitioned = true;
        for(; ; )
        {
            auto length = b - a;
            if(length <= maxInsertion)
            {
                insertionSortCmpFunc(data, a, b, cmp);
                return;
            }
            if(limit == 0)
            {
                heapSortCmpFunc(data, a, b, cmp);
                return;
            }
            if(! wasBalanced)
            {
                breakPatternsCmpFunc(data, a, b, cmp);
                limit--;
            }
            auto [pivot, hint] = choosePivotCmpFunc(data, a, b, cmp);
            if(hint == decreasingHint)
            {
                reverseRangeCmpFunc(data, a, b, cmp);
                pivot = (b - 1) - (pivot - a);
                hint = increasingHint;
            }
            if(wasBalanced && wasPartitioned && hint == increasingHint)
            {
                if(partialInsertionSortCmpFunc(data, a, b, cmp))
                {
                    return;
                }
            }
            if(a > 0 && ! (cmp(data[a - 1], data[pivot]) < 0))
            {
                auto mid = partitionEqualCmpFunc(data, a, b, pivot, cmp);
                a = mid;
                continue;
            }
            auto [mid, alreadyPartitioned] = partitionCmpFunc(data, a, b, pivot, cmp);
            wasPartitioned = alreadyPartitioned;
            auto [leftLen, rightLen] = std::tuple{mid - a, b - mid};
            auto balanceThreshold = length / 8;
            if(leftLen < rightLen)
            {
                wasBalanced = leftLen >= balanceThreshold;
                pdqsortCmpFunc(data, a, mid, limit, cmp);
                a = mid + 1;
            }
            else
            {
                wasBalanced = rightLen >= balanceThreshold;
                pdqsortCmpFunc(data, mid + 1, b, limit, cmp);
                b = mid;
            }
        }
    }

    std::tuple<int, bool> partitionCmpFunc(gocpp::slice<E> data, int a, int b, int pivot, std::function<int (E a, E b)> cmp)
    {
        int newpivot;
        bool alreadyPartitioned;
        std::tie(data[a], data[pivot]) = std::tuple{data[pivot], data[a]};
        auto [i, j] = std::tuple{a + 1, b - 1};
        for(; i <= j && (cmp(data[i], data[a]) < 0); )
        {
            int newpivot;
            bool alreadyPartitioned;
            i++;
        }
        for(; i <= j && ! (cmp(data[j], data[a]) < 0); )
        {
            int newpivot;
            bool alreadyPartitioned;
            j--;
        }
        if(i > j)
        {
            int newpivot;
            bool alreadyPartitioned;
            std::tie(data[j], data[a]) = std::tuple{data[a], data[j]};
            return {j, true};
        }
        std::tie(data[i], data[j]) = std::tuple{data[j], data[i]};
        i++;
        j--;
        for(; ; )
        {
            int newpivot;
            bool alreadyPartitioned;
            for(; i <= j && (cmp(data[i], data[a]) < 0); )
            {
                int newpivot;
                bool alreadyPartitioned;
                i++;
            }
            for(; i <= j && ! (cmp(data[j], data[a]) < 0); )
            {
                int newpivot;
                bool alreadyPartitioned;
                j--;
            }
            if(i > j)
            {
                int newpivot;
                bool alreadyPartitioned;
                break;
            }
            std::tie(data[i], data[j]) = std::tuple{data[j], data[i]};
            i++;
            j--;
        }
        std::tie(data[j], data[a]) = std::tuple{data[a], data[j]};
        return {j, false};
    }

    int partitionEqualCmpFunc(gocpp::slice<E> data, int a, int b, int pivot, std::function<int (E a, E b)> cmp)
    {
        int newpivot;
        std::tie(data[a], data[pivot]) = std::tuple{data[pivot], data[a]};
        auto [i, j] = std::tuple{a + 1, b - 1};
        for(; ; )
        {
            int newpivot;
            for(; i <= j && ! (cmp(data[a], data[i]) < 0); )
            {
                int newpivot;
                i++;
            }
            for(; i <= j && (cmp(data[a], data[j]) < 0); )
            {
                int newpivot;
                j--;
            }
            if(i > j)
            {
                int newpivot;
                break;
            }
            std::tie(data[i], data[j]) = std::tuple{data[j], data[i]};
            i++;
            j--;
        }
        return i;
    }

    bool partialInsertionSortCmpFunc(gocpp::slice<E> data, int a, int b, std::function<int (E a, E b)> cmp)
    {
        auto maxSteps = 5;
        auto shortestShifting = 50;
        auto i = a + 1;
        for(auto j = 0; j < maxSteps; j++)
        {
            for(; i < b && ! (cmp(data[i], data[i - 1]) < 0); )
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
            std::tie(data[i], data[i - 1]) = std::tuple{data[i - 1], data[i]};
            if(i - a >= 2)
            {
                for(auto j = i - 1; j >= 1; j--)
                {
                    if(! (cmp(data[j], data[j - 1]) < 0))
                    {
                        break;
                    }
                    std::tie(data[j], data[j - 1]) = std::tuple{data[j - 1], data[j]};
                }
            }
            if(b - i >= 2)
            {
                for(auto j = i + 1; j < b; j++)
                {
                    if(! (cmp(data[j], data[j - 1]) < 0))
                    {
                        break;
                    }
                    std::tie(data[j], data[j - 1]) = std::tuple{data[j - 1], data[j]};
                }
            }
        }
        return false;
    }

    void breakPatternsCmpFunc(gocpp::slice<E> data, int a, int b, std::function<int (E a, E b)> cmp)
    {
        auto length = b - a;
        if(length >= 8)
        {
            auto random = xorshift(length);
            auto modulus = nextPowerOfTwo(length);
            for(auto idx = a + (length / 4) * 2 - 1; idx <= a + (length / 4) * 2 + 1; idx++)
            {
                auto other = int((unsigned int)(Next(gocpp::recv(random))) & (modulus - 1));
                if(other >= length)
                {
                    other -= length;
                }
                std::tie(data[idx], data[a + other]) = std::tuple{data[a + other], data[idx]};
            }
        }
    }

    std::tuple<int, sortedHint> choosePivotCmpFunc(gocpp::slice<E> data, int a, int b, std::function<int (E a, E b)> cmp)
    {
        int pivot;
        sortedHint hint;
        auto shortestNinther = 50;
        auto maxSwaps = 4 * 3;
        auto l = b - a;
        int swaps = {};
        auto i = a + l / 4 * 1;
        auto j = a + l / 4 * 2;
        auto k = a + l / 4 * 3;
        if(l >= 8)
        {
            int pivot;
            sortedHint hint;
            if(l >= shortestNinther)
            {
                int pivot;
                sortedHint hint;
                i = medianAdjacentCmpFunc(data, i, & swaps, cmp);
                j = medianAdjacentCmpFunc(data, j, & swaps, cmp);
                k = medianAdjacentCmpFunc(data, k, & swaps, cmp);
            }
            j = medianCmpFunc(data, i, j, k, & swaps, cmp);
        }
        //Go switch emulation
        {
            auto condition = swaps;
            int conditionId = -1;
            if(condition == 0) { conditionId = 0; }
            else if(condition == maxSwaps) { conditionId = 1; }
            switch(conditionId)
            {
                int pivot;
                sortedHint hint;
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

    std::tuple<int, int> order2CmpFunc(gocpp::slice<E> data, int a, int b, int* swaps, std::function<int (E a, E b)> cmp)
    {
        if(cmp(data[b], data[a]) < 0)
        {
            *swaps++;
            return {b, a};
        }
        return {a, b};
    }

    int medianCmpFunc(gocpp::slice<E> data, int a, int b, int c, int* swaps, std::function<int (E a, E b)> cmp)
    {
        std::tie(a, b) = order2CmpFunc(data, a, b, swaps, cmp);
        std::tie(b, c) = order2CmpFunc(data, b, c, swaps, cmp);
        std::tie(a, b) = order2CmpFunc(data, a, b, swaps, cmp);
        return b;
    }

    int medianAdjacentCmpFunc(gocpp::slice<E> data, int a, int* swaps, std::function<int (E a, E b)> cmp)
    {
        return medianCmpFunc(data, a - 1, a, a + 1, swaps, cmp);
    }

    void reverseRangeCmpFunc(gocpp::slice<E> data, int a, int b, std::function<int (E a, E b)> cmp)
    {
        auto i = a;
        auto j = b - 1;
        for(; i < j; )
        {
            std::tie(data[i], data[j]) = std::tuple{data[j], data[i]};
            i++;
            j--;
        }
    }

    void swapRangeCmpFunc(gocpp::slice<E> data, int a, int b, int n, std::function<int (E a, E b)> cmp)
    {
        for(auto i = 0; i < n; i++)
        {
            std::tie(data[a + i], data[b + i]) = std::tuple{data[b + i], data[a + i]};
        }
    }

    void stableCmpFunc(gocpp::slice<E> data, int n, std::function<int (E a, E b)> cmp)
    {
        auto blockSize = 20;
        auto [a, b] = std::tuple{0, blockSize};
        for(; b <= n; )
        {
            insertionSortCmpFunc(data, a, b, cmp);
            a = b;
            b += blockSize;
        }
        insertionSortCmpFunc(data, a, n, cmp);
        for(; blockSize < n; )
        {
            std::tie(a, b) = std::tuple{0, 2 * blockSize};
            for(; b <= n; )
            {
                symMergeCmpFunc(data, a, a + blockSize, b, cmp);
                a = b;
                b += 2 * blockSize;
            }
            if(auto m = a + blockSize; m < n)
            {
                symMergeCmpFunc(data, a, m, n, cmp);
            }
            blockSize *= 2;
        }
    }

    void symMergeCmpFunc(gocpp::slice<E> data, int a, int m, int b, std::function<int (E a, E b)> cmp)
    {
        if(m - a == 1)
        {
            auto i = m;
            auto j = b;
            for(; i < j; )
            {
                auto h = int((unsigned int)(i + j) >> 1);
                if(cmp(data[h], data[a]) < 0)
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
                std::tie(data[k], data[k + 1]) = std::tuple{data[k + 1], data[k]};
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
                if(! (cmp(data[m], data[h]) < 0))
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
                std::tie(data[k], data[k - 1]) = std::tuple{data[k - 1], data[k]};
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
            if(! (cmp(data[p - c], data[c]) < 0))
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
            rotateCmpFunc(data, start, m, end, cmp);
        }
        if(a < start && start < mid)
        {
            symMergeCmpFunc(data, a, start, mid, cmp);
        }
        if(mid < end && end < b)
        {
            symMergeCmpFunc(data, mid, end, b, cmp);
        }
    }

    void rotateCmpFunc(gocpp::slice<E> data, int a, int m, int b, std::function<int (E a, E b)> cmp)
    {
        auto i = m - a;
        auto j = b - m;
        for(; i != j; )
        {
            if(i > j)
            {
                swapRangeCmpFunc(data, m - i, m, j, cmp);
                i -= j;
            }
            else
            {
                swapRangeCmpFunc(data, m - i, m + j - i, i, cmp);
                j -= i;
            }
        }
        swapRangeCmpFunc(data, m - i, m, i, cmp);
    }

}
