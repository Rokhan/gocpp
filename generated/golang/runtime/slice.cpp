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
#include "golang/internal/abi/type.h"
#include "golang/internal/goarch/goarch.h"
#include "golang/runtime/asan0.h"
#include "golang/runtime/error.h"
#include "golang/runtime/internal/math/math.h"
#include "golang/runtime/internal/sys/intrinsics.h"
#include "golang/runtime/internal/sys/nih.h"
#include "golang/runtime/malloc.h"
#include "golang/runtime/mbitmap_allocheaders.h"
#include "golang/runtime/mgc.h"
#include "golang/runtime/msan0.h"
#include "golang/runtime/msize_allocheaders.h"
#include "golang/runtime/race0.h"
#include "golang/runtime/stubs.h"
#include "golang/runtime/type.h"
#include "golang/unsafe/unsafe.h"

namespace golang::runtime
{
    namespace rec
    {
        using namespace mocklib::rec;
    }

    
    template<typename T> requires gocpp::GoStruct<T>
    slice::operator T()
    {
        T result;
        result.array = this->array;
        result.len = this->len;
        result.cap = this->cap;
        return result;
    }

    template<typename T> requires gocpp::GoStruct<T>
    bool slice::operator==(const T& ref) const
    {
        if (array != ref.array) return false;
        if (len != ref.len) return false;
        if (cap != ref.cap) return false;
        return true;
    }

    std::ostream& slice::PrintTo(std::ostream& os) const
    {
        os << '{';
        os << "" << array;
        os << " " << len;
        os << " " << cap;
        os << '}';
        return os;
    }

    std::ostream& operator<<(std::ostream& os, const struct slice& value)
    {
        return value.PrintTo(os);
    }

    // A notInHeapSlice is a slice backed by runtime/internal/sys.NotInHeap memory.
    
    template<typename T> requires gocpp::GoStruct<T>
    notInHeapSlice::operator T()
    {
        T result;
        result.array = this->array;
        result.len = this->len;
        result.cap = this->cap;
        return result;
    }

    template<typename T> requires gocpp::GoStruct<T>
    bool notInHeapSlice::operator==(const T& ref) const
    {
        if (array != ref.array) return false;
        if (len != ref.len) return false;
        if (cap != ref.cap) return false;
        return true;
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

    std::ostream& operator<<(std::ostream& os, const struct notInHeapSlice& value)
    {
        return value.PrintTo(os);
    }

    void panicmakeslicelen()
    {
        gocpp::panic(errorString("makeslice: len out of range"s));
    }

    void panicmakeslicecap()
    {
        gocpp::panic(errorString("makeslice: cap out of range"s));
    }

    // makeslicecopy allocates a slice of "tolen" elements of type "et",
    // then copies "fromlen" elements of type "et" into that new allocation from "from".
    unsafe::Pointer makeslicecopy(golang::runtime::_type* et, int tolen, int fromlen, unsafe::Pointer from)
    {
        uintptr_t tomem = {};
        uintptr_t copymem = {};
        if(uintptr_t(tolen) > uintptr_t(fromlen))
        {
            bool overflow = {};
            std::tie(tomem, overflow) = math::MulUintptr(et->Size_, uintptr_t(tolen));
            if(overflow || tomem > maxAlloc || tolen < 0)
            {
                panicmakeslicelen();
            }
            copymem = et->Size_ * uintptr_t(fromlen);
        }
        else
        {
            tomem = et->Size_ * uintptr_t(tolen);
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
                bulkBarrierPreWriteSrcOnly(uintptr_t(to), uintptr_t(from), copymem, et);
            }
        }
        if(raceenabled)
        {
            auto callerpc = getcallerpc();
            auto pc = abi::FuncPCABIInternal(makeslicecopy);
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

    unsafe::Pointer makeslice(golang::runtime::_type* et, int len, int cap)
    {
        auto [mem, overflow] = math::MulUintptr(et->Size_, uintptr_t(cap));
        if(overflow || mem > maxAlloc || len < 0 || len > cap)
        {
            auto [mem, overflow] = math::MulUintptr(et->Size_, uintptr_t(len));
            if(overflow || mem > maxAlloc || len < 0)
            {
                panicmakeslicelen();
            }
            panicmakeslicecap();
        }
        return mallocgc(mem, et, true);
    }

    unsafe::Pointer makeslice64(golang::runtime::_type* et, int64_t len64, int64_t cap64)
    {
        auto len = int(len64);
        if(int64_t(len) != len64)
        {
            panicmakeslicelen();
        }
        auto cap = int(cap64);
        if(int64_t(cap) != cap64)
        {
            panicmakeslicecap();
        }
        return makeslice(et, len, cap);
    }

    // growslice allocates new backing store for a slice.
    //
    // arguments:
    //
    //	oldPtr = pointer to the slice's backing array
    //	newLen = new length (= oldLen + num)
    //	oldCap = original slice's capacity.
    //	   num = number of elements being added
    //	    et = element type
    //
    // return values:
    //
    //	newPtr = pointer to the new backing store
    //	newLen = same value as the argument
    //	newCap = capacity of the new backing store
    //
    // Requires that uint(newLen) > uint(oldCap).
    // Assumes the original slice length is newLen - num
    //
    // A new backing store is allocated with space for at least newLen elements.
    // Existing entries [0, oldLen) are copied over to the new backing store.
    // Added entries [oldLen, newLen) are not initialized by growslice
    // (although for pointer-containing element types, they are zeroed). They
    // must be initialized by the caller.
    // Trailing entries [newLen, newCap) are zeroed.
    //
    // growslice's odd calling convention makes the generated code that calls
    // this function simpler. In particular, it accepts and returns the
    // new length so that the old length is not live (does not need to be
    // spilled/restored) and the new length is returned (also does not need
    // to be spilled/restored).
    struct slice growslice(unsafe::Pointer oldPtr, int newLen, int oldCap, int num, golang::runtime::_type* et)
    {
        auto oldLen = newLen - num;
        if(raceenabled)
        {
            auto callerpc = getcallerpc();
            racereadrangepc(oldPtr, uintptr_t(oldLen * int(et->Size_)), callerpc, abi::FuncPCABIInternal(growslice));
        }
        if(msanenabled)
        {
            msanread(oldPtr, uintptr_t(oldLen * int(et->Size_)));
        }
        if(asanenabled)
        {
            asanread(oldPtr, uintptr_t(oldLen * int(et->Size_)));
        }
        if(newLen < 0)
        {
            gocpp::panic(errorString("growslice: len out of range"s));
        }
        if(et->Size_ == 0)
        {
            return slice {unsafe::Pointer(& zerobase), newLen, newLen};
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
            else if(et->Size_ == goarch::PtrSize) { conditionId = 1; }
            else if(isPowerOfTwo(et->Size_)) { conditionId = 2; }
            switch(conditionId)
            {
                case 0:
                    lenmem = uintptr_t(oldLen);
                    newlenmem = uintptr_t(newLen);
                    capmem = roundupsize(uintptr_t(newcap), noscan);
                    overflow = uintptr_t(newcap) > maxAlloc;
                    newcap = int(capmem);
                    break;
                case 1:
                    lenmem = uintptr_t(oldLen) * goarch::PtrSize;
                    newlenmem = uintptr_t(newLen) * goarch::PtrSize;
                    capmem = roundupsize(uintptr_t(newcap) * goarch::PtrSize, noscan);
                    overflow = uintptr_t(newcap) > maxAlloc / goarch::PtrSize;
                    newcap = int(capmem / goarch::PtrSize);
                    break;
                case 2:
                    uintptr_t shift = {};
                    if(goarch::PtrSize == 8)
                    {
                        shift = uintptr_t(sys::TrailingZeros64(uint64_t(et->Size_))) & 63;
                    }
                    else
                    {
                        shift = uintptr_t(sys::TrailingZeros32(uint32_t(et->Size_))) & 31;
                    }
                    lenmem = uintptr_t(oldLen) << shift;
                    newlenmem = uintptr_t(newLen) << shift;
                    capmem = roundupsize(uintptr_t(newcap) << shift, noscan);
                    overflow = uintptr_t(newcap) > (maxAlloc >> shift);
                    newcap = int(capmem >> shift);
                    capmem = uintptr_t(newcap) << shift;
                    break;
                default:
                    lenmem = uintptr_t(oldLen) * et->Size_;
                    newlenmem = uintptr_t(newLen) * et->Size_;
                    std::tie(capmem, overflow) = math::MulUintptr(et->Size_, uintptr_t(newcap));
                    capmem = roundupsize(capmem, noscan);
                    newcap = int(capmem / et->Size_);
                    capmem = uintptr_t(newcap) * et->Size_;
                    break;
            }
        }
        if(overflow || capmem > maxAlloc)
        {
            gocpp::panic(errorString("growslice: len out of range"s));
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
                bulkBarrierPreWriteSrcOnly(uintptr_t(p), uintptr_t(oldPtr), lenmem - et->Size_ + et->PtrBytes, et);
            }
        }
        memmove(p, oldPtr, lenmem);
        return slice {p, newLen, newcap};
    }

    // nextslicecap computes the next appropriate slice length.
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

    //go:linkname reflect_growslice reflect.growslice
    struct slice reflect_growslice(golang::runtime::_type* et, struct slice old, int num)
    {
        num -= old.cap - old.len;
        auto go_new = growslice(old.array, old.cap + num, old.cap, num, et);
        if(et->PtrBytes == 0)
        {
            auto oldcapmem = uintptr_t(old.cap) * et->Size_;
            auto newlenmem = uintptr_t(go_new.len) * et->Size_;
            memclrNoHeapPointers(add(go_new.array, oldcapmem), newlenmem - oldcapmem);
        }
        go_new.len = old.len;
        return go_new;
    }

    bool isPowerOfTwo(uintptr_t x)
    {
        return x & (x - 1) == 0;
    }

    // slicecopy is used to copy from a string or slice of pointerless elements into a slice.
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
        auto size = uintptr_t(n) * width;
        if(raceenabled)
        {
            auto callerpc = getcallerpc();
            auto pc = abi::FuncPCABIInternal(slicecopy);
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
            *(unsigned char*)(toPtr) = *(unsigned char*)(fromPtr);
        }
        else
        {
            memmove(toPtr, fromPtr, size);
        }
        return n;
    }

    //go:linkname bytealg_MakeNoZero internal/bytealg.MakeNoZero
    gocpp::slice<unsigned char> bytealg_MakeNoZero(int len)
    {
        if(uintptr_t(len) > maxAlloc)
        {
            panicmakeslicelen();
        }
        return unsafe::Slice((unsigned char*)(mallocgc(uintptr_t(len), nullptr, false)), len);
    }

}

