// generated by GoCpp from file '$(ImportDir)/runtime/stkframe.go'
#include <complex>
#include <functional>
#include <iostream>
#include <iomanip>
#include <map>
#include <string>
#include <tuple>
#include <vector>

#include "golang/runtime/stkframe.h"
#include "gocpp/support.h"

// #include "golang/internal/abi/abi.h"  [Ignored, known errors]
// #include "golang/internal/abi/symtab.h"  [Ignored, known errors]
// #include "golang/internal/goarch/goarch.h"  [Ignored, known errors]
#include "golang/runtime/internal/sys/consts.h"
#include "golang/runtime/extern.h"
#include "golang/runtime/panic.h"
#include "golang/runtime/print.h"
#include "golang/runtime/runtime2.h"
#include "golang/runtime/stack.h"
// #include "golang/runtime/stubs.h"  [Ignored, known errors]
// #include "golang/runtime/symtab.h"  [Ignored, known errors]
#include "golang/runtime/traceback.h"
#include "golang/runtime/typekind.h"
#include "golang/unsafe/unsafe.h"

namespace golang::runtime
{
    
    std::ostream& stkframe::PrintTo(std::ostream& os) const
    {
        os << '{';
        os << "" << fn;
        os << " " << pc;
        os << " " << continpc;
        os << " " << lr;
        os << " " << sp;
        os << " " << fp;
        os << " " << varp;
        os << " " << argp;
        os << '}';
        return os;
    }

    std::ostream& operator<<(std::ostream& os, const stkframe& value)
    {
        return value.PrintTo(os);
    }

    
    std::ostream& reflectMethodValue::PrintTo(std::ostream& os) const
    {
        os << '{';
        os << "" << fn;
        os << " " << stack;
        os << " " << argLen;
        os << '}';
        return os;
    }

    std::ostream& operator<<(std::ostream& os, const reflectMethodValue& value)
    {
        return value.PrintTo(os);
    }

    uintptr_t argBytes(stkframe* frame)
    {
        if(frame->fn.args != abi.ArgsSizeUnknown)
        {
            return uintptr(frame->fn.args);
        }
        auto [argMap, _] = argMapInternal(gocpp::recv(frame));
        return uintptr(argMap.n) * goarch.PtrSize;
    }

    std::tuple<bitvector, bool> argMapInternal(stkframe* frame)
    {
        bitvector argMap;
        bool hasReflectStackObj;
        auto f = frame->fn;
        if(f.args != abi.ArgsSizeUnknown)
        {
            bitvector argMap;
            bool hasReflectStackObj;
            argMap.n = f.args / goarch.PtrSize;
            return {argMap, hasReflectStackObj};
        }
        //Go switch emulation
        {
            auto condition = funcname(f);
            int conditionId = -1;
            if(condition == "reflect.makeFuncStub") { conditionId = 0; }
            if(condition == "reflect.methodValueCall") { conditionId = 1; }
            switch(conditionId)
            {
                bitvector argMap;
                bool hasReflectStackObj;
                case 0:
                case 1:
                    auto arg0 = frame->sp + sys.MinFrameSize;
                    auto minSP = frame->fp;
                    if(! usesLR)
                    {
                        bitvector argMap;
                        bool hasReflectStackObj;
                        minSP -= goarch.PtrSize;
                    }
                    if(arg0 >= minSP)
                    {
                        bitvector argMap;
                        bool hasReflectStackObj;
                        if(frame->pc != entry(gocpp::recv(f)))
                        {
                            bitvector argMap;
                            bool hasReflectStackObj;
                            print("runtime: confused by ", funcname(f), ": no frame (sp=", hex(frame->sp), " fp=", hex(frame->fp), ") at entry+", hex(frame->pc - entry(gocpp::recv(f))), "\n");
                            go_throw("reflect mismatch");
                        }
                        return {bitvector {}, false};
                    }
                    hasReflectStackObj = true;
                    auto mv = *(**reflectMethodValue)(Pointer(gocpp::recv(unsafe), arg0));
                    auto retValid = *(*bool)(Pointer(gocpp::recv(unsafe), arg0 + 4 * goarch.PtrSize));
                    if(mv->fn != entry(gocpp::recv(f)))
                    {
                        bitvector argMap;
                        bool hasReflectStackObj;
                        print("runtime: confused by ", funcname(f), "\n");
                        go_throw("reflect mismatch");
                    }
                    argMap = *mv->stack;
                    if(! retValid)
                    {
                        bitvector argMap;
                        bool hasReflectStackObj;
                        auto n = int32((mv->argLen &^ (goarch.PtrSize - 1)) / goarch.PtrSize);
                        if(n < argMap.n)
                        {
                            bitvector argMap;
                            bool hasReflectStackObj;
                            argMap.n = n;
                        }
                    }
                    break;
            }
        }
        return {argMap, hasReflectStackObj};
    }

    std::tuple<bitvector, bitvector, gocpp::slice<stackObjectRecord>> getStackMap(stkframe* frame, bool debug)
    {
        bitvector locals;
        bitvector args;
        gocpp::slice<stackObjectRecord> objs;
        auto targetpc = frame->continpc;
        if(targetpc == 0)
        {
            bitvector locals;
            bitvector args;
            gocpp::slice<stackObjectRecord> objs;
            return {locals, args, objs};
        }
        auto f = frame->fn;
        auto pcdata = int32(- 1);
        if(targetpc != entry(gocpp::recv(f)))
        {
            bitvector locals;
            bitvector args;
            gocpp::slice<stackObjectRecord> objs;
            targetpc--;
            pcdata = pcdatavalue(f, abi.PCDATA_StackMapIndex, targetpc);
        }
        if(pcdata == - 1)
        {
            bitvector locals;
            bitvector args;
            gocpp::slice<stackObjectRecord> objs;
            pcdata = 0;
        }
        auto size = frame->varp - frame->sp;
        uintptr_t minsize = {};
        //Go switch emulation
        {
            auto condition = goarch.ArchFamily;
            int conditionId = -1;
            if(condition == goarch.ARM64) { conditionId = 0; }
            switch(conditionId)
            {
                bitvector locals;
                bitvector args;
                gocpp::slice<stackObjectRecord> objs;
                case 0:
                    minsize = sys.StackAlign;
                    break;
                default:
                    minsize = sys.MinFrameSize;
                    break;
            }
        }
        if(size > minsize)
        {
            bitvector locals;
            bitvector args;
            gocpp::slice<stackObjectRecord> objs;
            auto stackid = pcdata;
            auto stkmap = (*stackmap)(funcdata(f, abi.FUNCDATA_LocalsPointerMaps));
            if(stkmap == nullptr || stkmap->n <= 0)
            {
                bitvector locals;
                bitvector args;
                gocpp::slice<stackObjectRecord> objs;
                print("runtime: frame ", funcname(f), " untyped locals ", hex(frame->varp - size), "+", hex(size), "\n");
                go_throw("missing stackmap");
            }
            if(stkmap->nbit > 0)
            {
                bitvector locals;
                bitvector args;
                gocpp::slice<stackObjectRecord> objs;
                if(stackid < 0 || stackid >= stkmap->n)
                {
                    bitvector locals;
                    bitvector args;
                    gocpp::slice<stackObjectRecord> objs;
                    print("runtime: pcdata is ", stackid, " and ", stkmap->n, " locals stack map entries for ", funcname(f), " (targetpc=", hex(targetpc), ")\n");
                    go_throw("bad symbol table");
                }
                locals = stackmapdata(stkmap, stackid);
                if(stackDebug >= 3 && debug)
                {
                    bitvector locals;
                    bitvector args;
                    gocpp::slice<stackObjectRecord> objs;
                    print("      locals ", stackid, "/", stkmap->n, " ", locals.n, " words ", locals.bytedata, "\n");
                }
            }
            else
            if(stackDebug >= 3 && debug)
            {
                bitvector locals;
                bitvector args;
                gocpp::slice<stackObjectRecord> objs;
                print("      no locals to adjust\n");
            }
        }
        bool isReflect = {};
        std::tie(args, isReflect) = argMapInternal(gocpp::recv(frame));
        if(args.n > 0 && args.bytedata == nullptr)
        {
            bitvector locals;
            bitvector args;
            gocpp::slice<stackObjectRecord> objs;
            auto stackmap = (*stackmap)(funcdata(f, abi.FUNCDATA_ArgsPointerMaps));
            if(stackmap == nullptr || stackmap->n <= 0)
            {
                bitvector locals;
                bitvector args;
                gocpp::slice<stackObjectRecord> objs;
                print("runtime: frame ", funcname(f), " untyped args ", hex(frame->argp), "+", hex(args.n * goarch.PtrSize), "\n");
                go_throw("missing stackmap");
            }
            if(pcdata < 0 || pcdata >= stackmap->n)
            {
                bitvector locals;
                bitvector args;
                gocpp::slice<stackObjectRecord> objs;
                print("runtime: pcdata is ", pcdata, " and ", stackmap->n, " args stack map entries for ", funcname(f), " (targetpc=", hex(targetpc), ")\n");
                go_throw("bad symbol table");
            }
            if(stackmap->nbit == 0)
            {
                bitvector locals;
                bitvector args;
                gocpp::slice<stackObjectRecord> objs;
                args.n = 0;
            }
            else
            {
                bitvector locals;
                bitvector args;
                gocpp::slice<stackObjectRecord> objs;
                args = stackmapdata(stackmap, pcdata);
            }
        }
        if((GOARCH == "amd64" || GOARCH == "arm64" || GOARCH == "loong64" || GOARCH == "ppc64" || GOARCH == "ppc64le" || GOARCH == "riscv64") && Sizeof(gocpp::recv(unsafe), abi::RegArgs {}) > 0 && isReflect)
        {
            bitvector locals;
            bitvector args;
            gocpp::slice<stackObjectRecord> objs;
            objs = methodValueCallFrameObjs.make_slice(0, );
        }
        else
        {
            bitvector locals;
            bitvector args;
            gocpp::slice<stackObjectRecord> objs;
            auto p = funcdata(f, abi.FUNCDATA_StackObjects);
            if(p != nullptr)
            {
                bitvector locals;
                bitvector args;
                gocpp::slice<stackObjectRecord> objs;
                auto n = *(*uintptr)(p);
                p = add(p, goarch.PtrSize);
                auto r0 = (*stackObjectRecord)(noescape(p));
                objs = Slice(gocpp::recv(unsafe), r0, int(n));
            }
        }
        return {locals, args, objs};
    }

    gocpp::array<stackObjectRecord, 1> methodValueCallFrameObjs;
    void stkobjinit()
    {
        any abiRegArgsEface = abi::RegArgs {};
        auto abiRegArgsType = efaceOf(& abiRegArgsEface)->_type;
        if(abiRegArgsType->Kind_ & kindGCProg != 0)
        {
            go_throw("abiRegArgsType needs GC Prog, update methodValueCallFrameObjs");
        }
        auto ptr = uintptr(Pointer(gocpp::recv(unsafe), & methodValueCallFrameObjs[0]));
        moduledata* mod = {};
        for(auto datap = & firstmoduledata; datap != nullptr; datap = datap->next)
        {
            if(datap->gofunc <= ptr && ptr < datap->end)
            {
                mod = datap;
                break;
            }
        }
        if(mod == nullptr)
        {
            go_throw("methodValueCallFrameObjs is not in a module");
        }
        methodValueCallFrameObjs[0] = gocpp::Init<stackObjectRecord>([](stackObjectRecord& x) { x.off = - int32(alignUp(abiRegArgsType->Size_, 8)); x.size = int32(abiRegArgsType->Size_); x._ptrdata = int32(abiRegArgsType->PtrBytes); x.gcdataoff = uint32_t(uintptr(Pointer(gocpp::recv(unsafe), abiRegArgsType->GCData)) - mod->rodata); });
    }

}
