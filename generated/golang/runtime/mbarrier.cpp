// generated by GoCpp from file '$(ImportDir)/runtime/mbarrier.go'
#include <complex>
#include <functional>
#include <iostream>
#include <iomanip>
#include <map>
#include <string>
#include <tuple>
#include <vector>

#include "golang/runtime/mbarrier.h"
#include "gocpp/support.h"

#include "golang/internal/abi/abi.h"
#include "golang/internal/abi/funcpc.h"
#include "golang/internal/abi/type.h"
#include "golang/internal/goarch/goarch.h"
#include "golang/internal/goexperiment/exp_cgocheck2_off.h"
#include "golang/runtime/asan0.h"
#include "golang/runtime/cgocheck.h"
// #include "golang/runtime/mbitmap_allocheaders.h"  [Ignored, known errors]
#include "golang/runtime/msan0.h"
#include "golang/runtime/race0.h"
#include "golang/runtime/slice.h"
// #include "golang/runtime/stubs.h"  [Ignored, known errors]
#include "golang/runtime/type.h"
#include "golang/unsafe/unsafe.h"

namespace golang::runtime
{
    void typedmemmove(abi::Type* typ, unsafe::Pointer dst, unsafe::Pointer src)
    {
        if(dst == src)
        {
            return;
        }
        if(writeBarrier.enabled && typ->PtrBytes != 0)
        {
            bulkBarrierPreWrite(uintptr_t(dst), uintptr_t(src), typ->PtrBytes, typ);
        }
        memmove(dst, src, typ->Size_);
        if(goexperiment::CgoCheck2)
        {
            cgoCheckMemmove2(typ, dst, src, 0, typ->Size_);
        }
    }

    void wbZero(_type* typ, unsafe::Pointer dst)
    {
        bulkBarrierPreWrite(uintptr_t(dst), 0, typ->PtrBytes, typ);
    }

    void wbMove(_type* typ, unsafe::Pointer dst, unsafe::Pointer src)
    {
        bulkBarrierPreWrite(uintptr_t(dst), uintptr_t(src), typ->PtrBytes, typ);
    }

    void reflect_typedmemmove(_type* typ, unsafe::Pointer dst, unsafe::Pointer src)
    {
        if(raceenabled)
        {
            raceWriteObjectPC(typ, dst, getcallerpc(), abi::FuncPCABIInternal(reflect_typedmemmove));
            raceReadObjectPC(typ, src, getcallerpc(), abi::FuncPCABIInternal(reflect_typedmemmove));
        }
        if(msanenabled)
        {
            msanwrite(dst, typ->Size_);
            msanread(src, typ->Size_);
        }
        if(asanenabled)
        {
            asanwrite(dst, typ->Size_);
            asanread(src, typ->Size_);
        }
        typedmemmove(typ, dst, src);
    }

    void reflectlite_typedmemmove(_type* typ, unsafe::Pointer dst, unsafe::Pointer src)
    {
        reflect_typedmemmove(typ, dst, src);
    }

    void reflectcallmove(_type* typ, unsafe::Pointer dst, unsafe::Pointer src, uintptr_t size, abi::RegArgs* regs)
    {
        if(writeBarrier.enabled && typ != nullptr && typ->PtrBytes != 0 && size >= goarch::PtrSize)
        {
            bulkBarrierPreWrite(uintptr_t(dst), uintptr_t(src), size, nullptr);
        }
        memmove(dst, src, size);
        for(auto [i, gocpp_ignored] : regs->Ints)
        {
            if(Get(gocpp::recv(regs->ReturnIsPtr), i))
            {
                regs->Ptrs[i] = unsafe::Pointer(regs->Ints[i]);
            }
        }
    }

    int typedslicecopy(_type* typ, unsafe::Pointer dstPtr, int dstLen, unsafe::Pointer srcPtr, int srcLen)
    {
        auto n = dstLen;
        if(n > srcLen)
        {
            n = srcLen;
        }
        if(n == 0)
        {
            return 0;
        }
        if(raceenabled)
        {
            auto callerpc = getcallerpc();
            auto pc = abi::FuncPCABIInternal(slicecopy);
            racewriterangepc(dstPtr, uintptr_t(n) * typ->Size_, callerpc, pc);
            racereadrangepc(srcPtr, uintptr_t(n) * typ->Size_, callerpc, pc);
        }
        if(msanenabled)
        {
            msanwrite(dstPtr, uintptr_t(n) * typ->Size_);
            msanread(srcPtr, uintptr_t(n) * typ->Size_);
        }
        if(asanenabled)
        {
            asanwrite(dstPtr, uintptr_t(n) * typ->Size_);
            asanread(srcPtr, uintptr_t(n) * typ->Size_);
        }
        if(goexperiment::CgoCheck2)
        {
            cgoCheckSliceCopy(typ, dstPtr, srcPtr, n);
        }
        if(dstPtr == srcPtr)
        {
            return n;
        }
        auto size = uintptr_t(n) * typ->Size_;
        if(writeBarrier.enabled)
        {
            auto pwsize = size - typ->Size_ + typ->PtrBytes;
            bulkBarrierPreWrite(uintptr_t(dstPtr), uintptr_t(srcPtr), pwsize, typ);
        }
        memmove(dstPtr, srcPtr, size);
        return n;
    }

    int reflect_typedslicecopy(_type* elemType, slice dst, slice src)
    {
        if(elemType->PtrBytes == 0)
        {
            return slicecopy(dst.array, dst.len, src.array, src.len, elemType->Size_);
        }
        return typedslicecopy(elemType, dst.array, dst.len, src.array, src.len);
    }

    void typedmemclr(_type* typ, unsafe::Pointer ptr)
    {
        if(writeBarrier.enabled && typ->PtrBytes != 0)
        {
            bulkBarrierPreWrite(uintptr_t(ptr), 0, typ->PtrBytes, typ);
        }
        memclrNoHeapPointers(ptr, typ->Size_);
    }

    void reflect_typedmemclr(_type* typ, unsafe::Pointer ptr)
    {
        typedmemclr(typ, ptr);
    }

    void reflect_typedmemclrpartial(_type* typ, unsafe::Pointer ptr, uintptr_t off, uintptr_t size)
    {
        if(writeBarrier.enabled && typ->PtrBytes != 0)
        {
            bulkBarrierPreWrite(uintptr_t(ptr), 0, size, nullptr);
        }
        memclrNoHeapPointers(ptr, size);
    }

    void reflect_typedarrayclear(_type* typ, unsafe::Pointer ptr, int len)
    {
        auto size = typ->Size_ * uintptr_t(len);
        if(writeBarrier.enabled && typ->PtrBytes != 0)
        {
            bulkBarrierPreWrite(uintptr_t(ptr), 0, size, typ);
        }
        memclrNoHeapPointers(ptr, size);
    }

    void memclrHasPointers(unsafe::Pointer ptr, uintptr_t n)
    {
        bulkBarrierPreWrite(uintptr_t(ptr), 0, n, nullptr);
        memclrNoHeapPointers(ptr, n);
    }

}

