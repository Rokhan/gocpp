// generated by GoCpp from file '$(ImportDir)/runtime/slice.go'
#include <complex>
#include <functional>
#include <iostream>
#include <iomanip>
#include <map>
#include <string>
#include <tuple>
#include <vector>

#include "golang/runtime/slice.h"
#include "gocpp/support.h"

#include "golang/internal/abi/funcpc.h"
// #include "golang/internal/goarch/goarch.h"  [Ignored, known errors]
#include "golang/runtime/internal/math/math.h"
#include "golang/runtime/internal/sys/intrinsics.h"
#include "golang/runtime/asan0.h"
#include "golang/runtime/error.h"
#include "golang/runtime/malloc.h"
#include "golang/runtime/mbitmap_allocheaders.h"
#include "golang/runtime/msan0.h"
#include "golang/runtime/msize_allocheaders.h"
#include "golang/runtime/race0.h"
// #include "golang/runtime/stubs.h"  [Ignored, known errors]
#include "golang/runtime/type.h"
#include "golang/unsafe/unsafe.h"

namespace golang::runtime
{
    
    std::ostream& slice::PrintTo(std::ostream& os) const
    {
        os << '{';
        os << "" << array;
        os << " " << len;
        os << " " << cap;
        os << '}';
        return os;
    }

    std::ostream& operator<<(std::ostream& os, const slice& value)
    {
        return value.PrintTo(os);
    }

    
    std::ostream& notInHeapSlice::PrintTo(std::ostream& os) const
    {
        os << '{';
        os << "" << array;
        os << " " << len;
        os << " " << cap;
        os << '}';
        return os;
    }

    std::ostream& operator<<(std::ostream& os, const notInHeapSlice& value)
    {
        return value.PrintTo(os);
    }

    void panicmakeslicelen()
    {
        gocpp::panic(errorString("makeslice: len out of range"));
    }

    void panicmakeslicecap()
    {
        gocpp::panic(errorString("makeslice: cap out of range"));
    }

    unsafe::Pointer makeslicecopy(_type* et, int tolen, int fromlen, unsafe::Pointer from)
    {
        uintptr_t tomem = {};
        uintptr_t copymem = {};
        if(uintptr(tolen) > uintptr(fromlen))
        {
            bool overflow = {};
            std::tie(tomem, overflow) = math::MulUintptr(et->Size_, uintptr(tolen));
            if(overflow || tomem > maxAlloc || tolen < 0)
            {
                panicmakeslicelen();
            }
            copymem = et->Size_ * uintptr(fromlen);
        }
        else
        {
            tomem = et->Size_ * uintptr(tolen);
            copymem = tomem;
        }
        unsafe::Pointer to = {};
        if(et->PtrBytes == 0)
        {
            to = mallocgc(tomem, nullptr, false);
            if(copymem < tomem)
            {
                memclrNoHeapPointers(add(to, copymem), tomem - copymem);
            }
        }
        else
        {
            to = mallocgc(tomem, et, true);
            if(copymem > 0 && writeBarrier.enabled)
            {
                bulkBarrierPreWriteSrcOnly(uintptr(to), uintptr(from), copymem, et);
            }
        }
        if(raceenabled)
        {
            auto callerpc = getcallerpc();
            auto pc = FuncPCABIInternal(gocpp::recv(abi), makeslicecopy);
            racereadrangepc(from, copymem, callerpc, pc);
        }
        if(msanenabled)
        {
            msanread(from, copymem);
        }
        if(asanenabled)
        {
            asanread(from, copymem);
        }
        memmove(to, from, copymem);
        return to;
    }

    unsafe::Pointer makeslice(_type* et, int len, int cap)
    {
        auto [mem, overflow] = math::MulUintptr(et->Size_, uintptr(cap));
        if(overflow || mem > maxAlloc || len < 0 || len > cap)
        {
            auto [mem, overflow] = math::MulUintptr(et->Size_, uintptr(len));
            if(overflow || mem > maxAlloc || len < 0)
            {
                panicmakeslicelen();
            }
            panicmakeslicecap();
        }
        return mallocgc(mem, et, true);
    }

    unsafe::Pointer makeslice64(_type* et, int64_t len64, int64_t cap64)
    {
        auto len = int(len64);
        if(int64(len) != len64)
        {
            panicmakeslicelen();
        }
        auto cap = int(cap64);
        if(int64(cap) != cap64)
        {
            panicmakeslicecap();
        }
        return makeslice(et, len, cap);
    }

    slice growslice(unsafe::Pointer oldPtr, int newLen, int oldCap, int num, _type* et)
    {
        auto oldLen = newLen - num;
        if(raceenabled)
        {
            auto callerpc = getcallerpc();
            racereadrangepc(oldPtr, uintptr(oldLen * int(et->Size_)), callerpc, FuncPCABIInternal(gocpp::recv(abi), growslice));
        }
        if(msanenabled)
        {
            msanread(oldPtr, uintptr(oldLen * int(et->Size_)));
        }
        if(asanenabled)
        {
            asanread(oldPtr, uintptr(oldLen * int(et->Size_)));
        }
        if(newLen < 0)
        {
            gocpp::panic(errorString("growslice: len out of range"));
        }
        if(et->Size_ == 0)
        {
            return slice {Pointer(gocpp::recv(unsafe), & zerobase), newLen, newLen};
        }
        auto newcap = nextslicecap(newLen, oldCap);
        bool overflow = {};
        uintptr_t lenmem = {};
        uintptr_t newlenmem = {};
        uintptr_t capmem = {};
        auto noscan = et->PtrBytes == 0;
        //Go switch emulation
        {
            int conditionId = -1;
            if(et->Size_ == 1) { conditionId = 0; }
            else if(et->Size_ == goarch.PtrSize) { conditionId = 1; }
            else if(isPowerOfTwo(et->Size_)) { conditionId = 2; }
            switch(conditionId)
            {
                case 0:
                    lenmem = uintptr(oldLen);
                    newlenmem = uintptr(newLen);
                    capmem = roundupsize(uintptr(newcap), noscan);
                    overflow = uintptr(newcap) > maxAlloc;
                    newcap = int(capmem);
                    break;
                case 1:
                    lenmem = uintptr(oldLen) * goarch.PtrSize;
                    newlenmem = uintptr(newLen) * goarch.PtrSize;
                    capmem = roundupsize(uintptr(newcap) * goarch.PtrSize, noscan);
                    overflow = uintptr(newcap) > maxAlloc / goarch.PtrSize;
                    newcap = int(capmem / goarch.PtrSize);
                    break;
                case 2:
                    uintptr_t shift = {};
                    if(goarch.PtrSize == 8)
                    {
                        shift = uintptr(TrailingZeros64(gocpp::recv(sys), uint64_t(et->Size_))) & 63;
                    }
                    else
                    {
                        shift = uintptr(TrailingZeros32(gocpp::recv(sys), uint32_t(et->Size_))) & 31;
                    }
                    lenmem = uintptr(oldLen) << shift;
                    newlenmem = uintptr(newLen) << shift;
                    capmem = roundupsize(uintptr(newcap) << shift, noscan);
                    overflow = uintptr(newcap) > (maxAlloc >> shift);
                    newcap = int(capmem >> shift);
                    capmem = uintptr(newcap) << shift;
                    break;
                default:
                    lenmem = uintptr(oldLen) * et->Size_;
                    newlenmem = uintptr(newLen) * et->Size_;
                    std::tie(capmem, overflow) = math::MulUintptr(et->Size_, uintptr(newcap));
                    capmem = roundupsize(capmem, noscan);
                    newcap = int(capmem / et->Size_);
                    capmem = uintptr(newcap) * et->Size_;
                    break;
            }
        }
        if(overflow || capmem > maxAlloc)
        {
            gocpp::panic(errorString("growslice: len out of range"));
        }
        unsafe::Pointer p = {};
        if(et->PtrBytes == 0)
        {
            p = mallocgc(capmem, nullptr, false);
            memclrNoHeapPointers(add(p, newlenmem), capmem - newlenmem);
        }
        else
        {
            p = mallocgc(capmem, et, true);
            if(lenmem > 0 && writeBarrier.enabled)
            {
                bulkBarrierPreWriteSrcOnly(uintptr(p), uintptr(oldPtr), lenmem - et->Size_ + et->PtrBytes, et);
            }
        }
        memmove(p, oldPtr, lenmem);
        return slice {p, newLen, newcap};
    }

    int nextslicecap(int newLen, int oldCap)
    {
        auto newcap = oldCap;
        auto doublecap = newcap + newcap;
        if(newLen > doublecap)
        {
            return newLen;
        }
        auto threshold = 256;
        if(oldCap < threshold)
        {
            return doublecap;
        }
        for(; ; )
        {
            newcap += (newcap + 3 * threshold) >> 2;
            if((unsigned int)(newcap) >= (unsigned int)(newLen))
            {
                break;
            }
        }
        if(newcap <= 0)
        {
            return newLen;
        }
        return newcap;
    }

    slice reflect_growslice(_type* et, slice old, int num)
    {
        num -= old.cap - old.len;
        auto go_new = growslice(old.array, old.cap + num, old.cap, num, et);
        if(et->PtrBytes == 0)
        {
            auto oldcapmem = uintptr(old.cap) * et->Size_;
            auto newlenmem = uintptr(go_new.len) * et->Size_;
            memclrNoHeapPointers(add(go_new.array, oldcapmem), newlenmem - oldcapmem);
        }
        go_new.len = old.len;
        return go_new;
    }

    bool isPowerOfTwo(uintptr_t x)
    {
        return x & (x - 1) == 0;
    }

    int slicecopy(unsafe::Pointer toPtr, int toLen, unsafe::Pointer fromPtr, int fromLen, uintptr_t width)
    {
        if(fromLen == 0 || toLen == 0)
        {
            return 0;
        }
        auto n = fromLen;
        if(toLen < n)
        {
            n = toLen;
        }
        if(width == 0)
        {
            return n;
        }
        auto size = uintptr(n) * width;
        if(raceenabled)
        {
            auto callerpc = getcallerpc();
            auto pc = FuncPCABIInternal(gocpp::recv(abi), slicecopy);
            racereadrangepc(fromPtr, size, callerpc, pc);
            racewriterangepc(toPtr, size, callerpc, pc);
        }
        if(msanenabled)
        {
            msanread(fromPtr, size);
            msanwrite(toPtr, size);
        }
        if(asanenabled)
        {
            asanread(fromPtr, size);
            asanwrite(toPtr, size);
        }
        if(size == 1)
        {
            *(*byte)(toPtr) = *(*byte)(fromPtr);
        }
        else
        {
            memmove(toPtr, fromPtr, size);
        }
        return n;
    }

    gocpp::slice<unsigned char> bytealg_MakeNoZero(int len)
    {
        if(uintptr(len) > maxAlloc)
        {
            panicmakeslicelen();
        }
        return Slice(gocpp::recv(unsafe), (*byte)(mallocgc(uintptr(len), nullptr, false)), len);
    }

}
