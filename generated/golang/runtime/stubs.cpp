// generated by GoCpp from file '$(ImportDir)/runtime/stubs.go'
#include <complex>
#include <functional>
#include <iostream>
#include <iomanip>
#include <map>
#include <string>
#include <tuple>
#include <vector>

#include "golang/runtime/stubs.h"
#include "gocpp/support.h"

// #include "golang/internal/abi/abi.h"  [Ignored, known errors]
#include "golang/internal/abi/abi_amd64.h"
#include "golang/runtime/map.h"
#include "golang/runtime/runtime.h"
#include "golang/runtime/runtime2.h"
#include "golang/runtime/type.h"
#include "golang/unsafe/unsafe.h"

namespace golang::runtime
{
    unsafe::Pointer add(unsafe::Pointer p, uintptr_t x)
    {
        return Pointer(gocpp::recv(unsafe), uintptr(p) + x);
    }

    g* getg()
    /* convertBlockStmt, nil block */;

    void mcall(std::function<void (g*)> fn)
    /* convertBlockStmt, nil block */;

    void systemstack(std::function<void ()> fn)
    /* convertBlockStmt, nil block */;

    void badsystemstack()
    {
        writeErrStr("fatal: systemstack called from unexpected goroutine");
    }

    void memclrNoHeapPointers(unsafe::Pointer ptr, uintptr_t n)
    /* convertBlockStmt, nil block */;

    void reflect_memclrNoHeapPointers(unsafe::Pointer ptr, uintptr_t n)
    {
        memclrNoHeapPointers(ptr, n);
    }

    void memmove(unsafe::Pointer to, unsafe::Pointer from, uintptr_t n)
    /* convertBlockStmt, nil block */;

    void reflect_memmove(unsafe::Pointer to, unsafe::Pointer from, uintptr_t n)
    {
        memmove(to, from, n);
    }

    float hashLoad = float(loadFactorNum) / float(loadFactorDen);
    bool memequal(unsafe::Pointer a, unsafe::Pointer b, uintptr_t size)
    /* convertBlockStmt, nil block */;

    unsafe::Pointer noescape(unsafe::Pointer p)
    {
        auto x = uintptr(p);
        return Pointer(gocpp::recv(unsafe), x ^ 0);
    }

    T* noEscapePtr(T* p)
    {
        auto x = uintptr(Pointer(gocpp::recv(unsafe), p));
        return (*T)(Pointer(gocpp::recv(unsafe), x ^ 0));
    }

    void cgocallback(uintptr_t fn, uintptr_t frame, uintptr_t ctxt)
    /* convertBlockStmt, nil block */;

    void gogo(gobuf* buf)
    /* convertBlockStmt, nil block */;

    void asminit()
    /* convertBlockStmt, nil block */;

    void setg(g* gg)
    /* convertBlockStmt, nil block */;

    void breakpoint()
    /* convertBlockStmt, nil block */;

    void reflectcall(_type* stackArgsType, unsafe::Pointer fn, unsafe::Pointer stackArgs, uint32_t stackArgsSize, uint32_t stackRetOffset, uint32_t frameSize, abi::RegArgs* regArgs)
    /* convertBlockStmt, nil block */;

    void procyield(uint32_t cycles)
    /* convertBlockStmt, nil block */;

    
    std::ostream& neverCallThisFunction::PrintTo(std::ostream& os) const
    {
        os << '{';
        os << '}';
        return os;
    }

    std::ostream& operator<<(std::ostream& os, const neverCallThisFunction& value)
    {
        return value.PrintTo(os);
    }

    void goexit(neverCallThisFunction)
    /* convertBlockStmt, nil block */;

    void publicationBarrier()
    /* convertBlockStmt, nil block */;

    uintptr_t getcallerpc()
    /* convertBlockStmt, nil block */;

    uintptr_t getcallersp()
    /* convertBlockStmt, nil block */;

    uintptr_t getclosureptr()
    /* convertBlockStmt, nil block */;

    int32_t asmcgocall(unsafe::Pointer fn, unsafe::Pointer arg)
    /* convertBlockStmt, nil block */;

    void morestack()
    /* convertBlockStmt, nil block */;

    void morestack_noctxt()
    /* convertBlockStmt, nil block */;

    void rt0_go()
    /* convertBlockStmt, nil block */;

    void return0()
    /* convertBlockStmt, nil block */;

    void call16(unsafe::Pointer typ, unsafe::Pointer fn, unsafe::Pointer stackArgs, uint32_t stackArgsSize, uint32_t stackRetOffset, uint32_t frameSize, abi::RegArgs* regArgs)
    /* convertBlockStmt, nil block */;

    void call32(unsafe::Pointer typ, unsafe::Pointer fn, unsafe::Pointer stackArgs, uint32_t stackArgsSize, uint32_t stackRetOffset, uint32_t frameSize, abi::RegArgs* regArgs)
    /* convertBlockStmt, nil block */;

    void call64(unsafe::Pointer typ, unsafe::Pointer fn, unsafe::Pointer stackArgs, uint32_t stackArgsSize, uint32_t stackRetOffset, uint32_t frameSize, abi::RegArgs* regArgs)
    /* convertBlockStmt, nil block */;

    void call128(unsafe::Pointer typ, unsafe::Pointer fn, unsafe::Pointer stackArgs, uint32_t stackArgsSize, uint32_t stackRetOffset, uint32_t frameSize, abi::RegArgs* regArgs)
    /* convertBlockStmt, nil block */;

    void call256(unsafe::Pointer typ, unsafe::Pointer fn, unsafe::Pointer stackArgs, uint32_t stackArgsSize, uint32_t stackRetOffset, uint32_t frameSize, abi::RegArgs* regArgs)
    /* convertBlockStmt, nil block */;

    void call512(unsafe::Pointer typ, unsafe::Pointer fn, unsafe::Pointer stackArgs, uint32_t stackArgsSize, uint32_t stackRetOffset, uint32_t frameSize, abi::RegArgs* regArgs)
    /* convertBlockStmt, nil block */;

    void call1024(unsafe::Pointer typ, unsafe::Pointer fn, unsafe::Pointer stackArgs, uint32_t stackArgsSize, uint32_t stackRetOffset, uint32_t frameSize, abi::RegArgs* regArgs)
    /* convertBlockStmt, nil block */;

    void call2048(unsafe::Pointer typ, unsafe::Pointer fn, unsafe::Pointer stackArgs, uint32_t stackArgsSize, uint32_t stackRetOffset, uint32_t frameSize, abi::RegArgs* regArgs)
    /* convertBlockStmt, nil block */;

    void call4096(unsafe::Pointer typ, unsafe::Pointer fn, unsafe::Pointer stackArgs, uint32_t stackArgsSize, uint32_t stackRetOffset, uint32_t frameSize, abi::RegArgs* regArgs)
    /* convertBlockStmt, nil block */;

    void call8192(unsafe::Pointer typ, unsafe::Pointer fn, unsafe::Pointer stackArgs, uint32_t stackArgsSize, uint32_t stackRetOffset, uint32_t frameSize, abi::RegArgs* regArgs)
    /* convertBlockStmt, nil block */;

    void call16384(unsafe::Pointer typ, unsafe::Pointer fn, unsafe::Pointer stackArgs, uint32_t stackArgsSize, uint32_t stackRetOffset, uint32_t frameSize, abi::RegArgs* regArgs)
    /* convertBlockStmt, nil block */;

    void call32768(unsafe::Pointer typ, unsafe::Pointer fn, unsafe::Pointer stackArgs, uint32_t stackArgsSize, uint32_t stackRetOffset, uint32_t frameSize, abi::RegArgs* regArgs)
    /* convertBlockStmt, nil block */;

    void call65536(unsafe::Pointer typ, unsafe::Pointer fn, unsafe::Pointer stackArgs, uint32_t stackArgsSize, uint32_t stackRetOffset, uint32_t frameSize, abi::RegArgs* regArgs)
    /* convertBlockStmt, nil block */;

    void call131072(unsafe::Pointer typ, unsafe::Pointer fn, unsafe::Pointer stackArgs, uint32_t stackArgsSize, uint32_t stackRetOffset, uint32_t frameSize, abi::RegArgs* regArgs)
    /* convertBlockStmt, nil block */;

    void call262144(unsafe::Pointer typ, unsafe::Pointer fn, unsafe::Pointer stackArgs, uint32_t stackArgsSize, uint32_t stackRetOffset, uint32_t frameSize, abi::RegArgs* regArgs)
    /* convertBlockStmt, nil block */;

    void call524288(unsafe::Pointer typ, unsafe::Pointer fn, unsafe::Pointer stackArgs, uint32_t stackArgsSize, uint32_t stackRetOffset, uint32_t frameSize, abi::RegArgs* regArgs)
    /* convertBlockStmt, nil block */;

    void call1048576(unsafe::Pointer typ, unsafe::Pointer fn, unsafe::Pointer stackArgs, uint32_t stackArgsSize, uint32_t stackRetOffset, uint32_t frameSize, abi::RegArgs* regArgs)
    /* convertBlockStmt, nil block */;

    void call2097152(unsafe::Pointer typ, unsafe::Pointer fn, unsafe::Pointer stackArgs, uint32_t stackArgsSize, uint32_t stackRetOffset, uint32_t frameSize, abi::RegArgs* regArgs)
    /* convertBlockStmt, nil block */;

    void call4194304(unsafe::Pointer typ, unsafe::Pointer fn, unsafe::Pointer stackArgs, uint32_t stackArgsSize, uint32_t stackRetOffset, uint32_t frameSize, abi::RegArgs* regArgs)
    /* convertBlockStmt, nil block */;

    void call8388608(unsafe::Pointer typ, unsafe::Pointer fn, unsafe::Pointer stackArgs, uint32_t stackArgsSize, uint32_t stackRetOffset, uint32_t frameSize, abi::RegArgs* regArgs)
    /* convertBlockStmt, nil block */;

    void call16777216(unsafe::Pointer typ, unsafe::Pointer fn, unsafe::Pointer stackArgs, uint32_t stackArgsSize, uint32_t stackRetOffset, uint32_t frameSize, abi::RegArgs* regArgs)
    /* convertBlockStmt, nil block */;

    void call33554432(unsafe::Pointer typ, unsafe::Pointer fn, unsafe::Pointer stackArgs, uint32_t stackArgsSize, uint32_t stackRetOffset, uint32_t frameSize, abi::RegArgs* regArgs)
    /* convertBlockStmt, nil block */;

    void call67108864(unsafe::Pointer typ, unsafe::Pointer fn, unsafe::Pointer stackArgs, uint32_t stackArgsSize, uint32_t stackRetOffset, uint32_t frameSize, abi::RegArgs* regArgs)
    /* convertBlockStmt, nil block */;

    void call134217728(unsafe::Pointer typ, unsafe::Pointer fn, unsafe::Pointer stackArgs, uint32_t stackArgsSize, uint32_t stackRetOffset, uint32_t frameSize, abi::RegArgs* regArgs)
    /* convertBlockStmt, nil block */;

    void call268435456(unsafe::Pointer typ, unsafe::Pointer fn, unsafe::Pointer stackArgs, uint32_t stackArgsSize, uint32_t stackRetOffset, uint32_t frameSize, abi::RegArgs* regArgs)
    /* convertBlockStmt, nil block */;

    void call536870912(unsafe::Pointer typ, unsafe::Pointer fn, unsafe::Pointer stackArgs, uint32_t stackArgsSize, uint32_t stackRetOffset, uint32_t frameSize, abi::RegArgs* regArgs)
    /* convertBlockStmt, nil block */;

    void call1073741824(unsafe::Pointer typ, unsafe::Pointer fn, unsafe::Pointer stackArgs, uint32_t stackArgsSize, uint32_t stackRetOffset, uint32_t frameSize, abi::RegArgs* regArgs)
    /* convertBlockStmt, nil block */;

    void systemstack_switch()
    /* convertBlockStmt, nil block */;

    uintptr_t alignUp(uintptr_t n, uintptr_t a)
    {
        return (n + a - 1) &^ (a - 1);
    }

    uintptr_t alignDown(uintptr_t n, uintptr_t a)
    {
        return n &^ (a - 1);
    }

    uintptr_t divRoundUp(uintptr_t n, uintptr_t a)
    {
        return (n + a - 1) / a;
    }

    bool checkASM()
    /* convertBlockStmt, nil block */;

    bool memequal_varlen(unsafe::Pointer a, unsafe::Pointer b)
    /* convertBlockStmt, nil block */;

    int bool2int(bool x)
    {
        return int(*(*uint8_t)(Pointer(gocpp::recv(unsafe), & x)));
    }

    void abort()
    /* convertBlockStmt, nil block */;

    void gcWriteBarrier1()
    /* convertBlockStmt, nil block */;

    void gcWriteBarrier2()
    /* convertBlockStmt, nil block */;

    void gcWriteBarrier3()
    /* convertBlockStmt, nil block */;

    void gcWriteBarrier4()
    /* convertBlockStmt, nil block */;

    void gcWriteBarrier5()
    /* convertBlockStmt, nil block */;

    void gcWriteBarrier6()
    /* convertBlockStmt, nil block */;

    void gcWriteBarrier7()
    /* convertBlockStmt, nil block */;

    void gcWriteBarrier8()
    /* convertBlockStmt, nil block */;

    void duffzero()
    /* convertBlockStmt, nil block */;

    void duffcopy()
    /* convertBlockStmt, nil block */;

    void addmoduledata()
    /* convertBlockStmt, nil block */;

    void sigpanic0()
    /* convertBlockStmt, nil block */;

    int intArgRegs = abi.IntArgRegs;
}
