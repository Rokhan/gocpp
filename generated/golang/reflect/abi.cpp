// generated by GoCpp from file '$(ImportDir)/reflect/abi.go'
#include <complex>
#include <functional>
#include <iostream>
#include <iomanip>
#include <map>
#include <string>
#include <tuple>
#include <vector>

#include "golang/reflect/abi.h"
#include "gocpp/support.h"

#include "golang/internal/abi/abi.h"
#include "golang/internal/abi/abi_amd64.h"
#include "golang/internal/abi/type.h"
#include "golang/internal/goarch/goarch.h"
#include "golang/reflect/float32reg_generic.h"
#include "golang/reflect/type.h"
// #include "golang/reflect/value.h"  [Ignored, known errors]
#include "golang/unsafe/unsafe.h"

namespace golang::reflect
{
    int intArgRegs = abi::IntArgRegs;
    int floatArgRegs = abi::FloatArgRegs;
    uintptr_t floatRegSize = uintptr_t(abi::EffectiveFloatRegSize);
    
    template<typename T> requires gocpp::GoStruct<T>
    abiStep::operator T()
    {
        T result;
        result.kind = this->kind;
        result.offset = this->offset;
        result.size = this->size;
        result.stkOff = this->stkOff;
        result.ireg = this->ireg;
        result.freg = this->freg;
        return result;
    }

    template<typename T> requires gocpp::GoStruct<T>
    bool abiStep::operator==(const T& ref) const
    {
        if (kind != ref.kind) return false;
        if (offset != ref.offset) return false;
        if (size != ref.size) return false;
        if (stkOff != ref.stkOff) return false;
        if (ireg != ref.ireg) return false;
        if (freg != ref.freg) return false;
        return true;
    }

    std::ostream& abiStep::PrintTo(std::ostream& os) const
    {
        os << '{';
        os << "" << kind;
        os << " " << offset;
        os << " " << size;
        os << " " << stkOff;
        os << " " << ireg;
        os << " " << freg;
        os << '}';
        return os;
    }

    std::ostream& operator<<(std::ostream& os, const struct abiStep& value)
    {
        return value.PrintTo(os);
    }

    
    template<typename T> requires gocpp::GoStruct<T>
    abiSeq::operator T()
    {
        T result;
        result.steps = this->steps;
        result.valueStart = this->valueStart;
        result.stackBytes = this->stackBytes;
        result.iregs = this->iregs;
        result.fregs = this->fregs;
        return result;
    }

    template<typename T> requires gocpp::GoStruct<T>
    bool abiSeq::operator==(const T& ref) const
    {
        if (steps != ref.steps) return false;
        if (valueStart != ref.valueStart) return false;
        if (stackBytes != ref.stackBytes) return false;
        if (iregs != ref.iregs) return false;
        if (fregs != ref.fregs) return false;
        return true;
    }

    std::ostream& abiSeq::PrintTo(std::ostream& os) const
    {
        os << '{';
        os << "" << steps;
        os << " " << valueStart;
        os << " " << stackBytes;
        os << " " << iregs;
        os << " " << fregs;
        os << '}';
        return os;
    }

    std::ostream& operator<<(std::ostream& os, const struct abiSeq& value)
    {
        return value.PrintTo(os);
    }

    void dump(struct abiSeq* a)
    {
        for(auto [i, p] : a->steps)
        {
            println("part", i, p.kind, p.offset, p.size, p.stkOff, p.ireg, p.freg);
        }
        print("values ");
        for(auto [_, i] : a->valueStart)
        {
            print(i, " ");
        }
        println();
        println("stack", a->stackBytes);
        println("iregs", a->iregs);
        println("fregs", a->fregs);
    }

    gocpp::slice<abiStep> stepsForValue(struct abiSeq* a, int i)
    {
        auto s = a->valueStart[i];
        int e = {};
        if(i == len(a->valueStart) - 1)
        {
            e = len(a->steps);
        }
        else
        {
            e = a->valueStart[i + 1];
        }
        return a->steps.make_slice(s, e);
    }

    abiStep* addArg(struct abiSeq* a, abi::Type* t)
    {
        auto pStart = len(a->steps);
        a->valueStart = append(a->valueStart, pStart);
        if(Size(gocpp::recv(t)) == 0)
        {
            a->stackBytes = align(a->stackBytes, uintptr_t(Align(gocpp::recv(t))));
            return nullptr;
        }
        auto aOld = *a;
        if(! regAssign(gocpp::recv(a), t, 0))
        {
            *a = aOld;
            stackAssign(gocpp::recv(a), Size(gocpp::recv(t)), uintptr_t(Align(gocpp::recv(t))));
            return & a->steps[len(a->steps) - 1];
        }
        return nullptr;
    }

    std::tuple<abiStep*, bool> addRcvr(struct abiSeq* a, abi::Type* rcvr)
    {
        a->valueStart = append(a->valueStart, len(a->steps));
        bool ok = {};
        bool ptr = {};
        if(ifaceIndir(rcvr) || Pointers(gocpp::recv(rcvr)))
        {
            ok = assignIntN(gocpp::recv(a), 0, goarch::PtrSize, 1, 0b1);
            ptr = true;
        }
        else
        {
            ok = assignIntN(gocpp::recv(a), 0, goarch::PtrSize, 1, 0b0);
            ptr = false;
        }
        if(! ok)
        {
            stackAssign(gocpp::recv(a), goarch::PtrSize, goarch::PtrSize);
            return {& a->steps[len(a->steps) - 1], ptr};
        }
        return {nullptr, ptr};
    }

    bool regAssign(struct abiSeq* a, abi::Type* t, uintptr_t offset)
    {
        //Go switch emulation
        {
            auto condition = Kind(Kind(gocpp::recv(t)));
            int conditionId = -1;
            if(condition == UnsafePointer) { conditionId = 0; }
            if(condition == Pointer) { conditionId = 1; }
            if(condition == Chan) { conditionId = 2; }
            if(condition == Map) { conditionId = 3; }
            if(condition == Func) { conditionId = 4; }
            else if(condition == Bool) { conditionId = 5; }
            else if(condition == Int) { conditionId = 6; }
            else if(condition == Uint) { conditionId = 7; }
            else if(condition == Int8) { conditionId = 8; }
            else if(condition == Uint8) { conditionId = 9; }
            else if(condition == Int16) { conditionId = 10; }
            else if(condition == Uint16) { conditionId = 11; }
            else if(condition == Int32) { conditionId = 12; }
            else if(condition == Uint32) { conditionId = 13; }
            else if(condition == Uintptr) { conditionId = 14; }
            else if(condition == Int64) { conditionId = 15; }
            else if(condition == Uint64) { conditionId = 16; }
            else if(condition == Float32) { conditionId = 17; }
            else if(condition == Float64) { conditionId = 18; }
            else if(condition == Complex64) { conditionId = 19; }
            else if(condition == Complex128) { conditionId = 20; }
            else if(condition == String) { conditionId = 21; }
            else if(condition == Interface) { conditionId = 22; }
            else if(condition == Slice) { conditionId = 23; }
            else if(condition == Array) { conditionId = 24; }
            else if(condition == Struct) { conditionId = 25; }
            switch(conditionId)
            {
                case 0:
                case 1:
                case 2:
                case 3:
                case 4:
                    return assignIntN(gocpp::recv(a), offset, Size(gocpp::recv(t)), 1, 0b1);
                    break;
                case 5:
                case 6:
                case 7:
                case 8:
                case 9:
                case 10:
                case 11:
                case 12:
                case 13:
                case 14:
                    return assignIntN(gocpp::recv(a), offset, Size(gocpp::recv(t)), 1, 0b0);
                    break;
                case 15:
                case 16:
                    //Go switch emulation
                    {
                        auto condition = goarch::PtrSize;
                        int conditionId = -1;
                        if(condition == 4) { conditionId = 0; }
                        else if(condition == 8) { conditionId = 1; }
                        switch(conditionId)
                        {
                            case 0:
                                return assignIntN(gocpp::recv(a), offset, 4, 2, 0b0);
                                break;
                            case 1:
                                return assignIntN(gocpp::recv(a), offset, 8, 1, 0b0);
                                break;
                        }
                    }
                    break;
                case 17:
                case 18:
                    return assignFloatN(gocpp::recv(a), offset, Size(gocpp::recv(t)), 1);
                    break;
                case 19:
                    return assignFloatN(gocpp::recv(a), offset, 4, 2);
                    break;
                case 20:
                    return assignFloatN(gocpp::recv(a), offset, 8, 2);
                    break;
                case 21:
                    return assignIntN(gocpp::recv(a), offset, goarch::PtrSize, 2, 0b01);
                    break;
                case 22:
                    return assignIntN(gocpp::recv(a), offset, goarch::PtrSize, 2, 0b10);
                    break;
                case 23:
                    return assignIntN(gocpp::recv(a), offset, goarch::PtrSize, 3, 0b001);
                    break;
                case 24:
                    auto tt = (arrayType*)(unsafe::Pointer(t));
                    //Go switch emulation
                    {
                        auto condition = tt->Len;
                        int conditionId = -1;
                        if(condition == 0) { conditionId = 0; }
                        else if(condition == 1) { conditionId = 1; }
                        switch(conditionId)
                        {
                            case 0:
                                return true;
                                break;
                            case 1:
                                return regAssign(gocpp::recv(a), tt->Elem, offset);
                                break;
                            default:
                                return false;
                                break;
                        }
                    }
                    break;
                case 25:
                    auto st = (structType*)(unsafe::Pointer(t));
                    for(auto [i, gocpp_ignored] : st->Fields)
                    {
                        auto f = & st->Fields[i];
                        if(! regAssign(gocpp::recv(a), f->Typ, offset + f->Offset))
                        {
                            return false;
                        }
                    }
                    return true;
                    break;
                default:
                    print("t.Kind == ", Kind(gocpp::recv(t)), "\n");
                    gocpp::panic("unknown type kind");
                    break;
            }
        }
        gocpp::panic("unhandled register assignment path");
    }

    bool assignIntN(struct abiSeq* a, uintptr_t offset, uintptr_t size, int n, uint8_t ptrMap)
    {
        if(n > 8 || n < 0)
        {
            gocpp::panic("invalid n");
        }
        if(ptrMap != 0 && size != goarch::PtrSize)
        {
            gocpp::panic("non-empty pointer map passed for non-pointer-size values");
        }
        if(a->iregs + n > intArgRegs)
        {
            return false;
        }
        for(auto i = 0; i < n; i++)
        {
            auto kind = abiStepIntReg;
            if(ptrMap & (uint8_t(1) << i) != 0)
            {
                kind = abiStepPointer;
            }
            a->steps = append(a->steps, gocpp::Init<abiStep>([](abiStep& x) { x.kind = kind; x.offset = offset + uintptr_t(i) * size; x.size = size; x.ireg = a->iregs; }));
            a->iregs++;
        }
        return true;
    }

    bool assignFloatN(struct abiSeq* a, uintptr_t offset, uintptr_t size, int n)
    {
        if(n < 0)
        {
            gocpp::panic("invalid n");
        }
        if(a->fregs + n > floatArgRegs || floatRegSize < size)
        {
            return false;
        }
        for(auto i = 0; i < n; i++)
        {
            a->steps = append(a->steps, gocpp::Init<abiStep>([](abiStep& x) { x.kind = abiStepFloatReg; x.offset = offset + uintptr_t(i) * size; x.size = size; x.freg = a->fregs; }));
            a->fregs++;
        }
        return true;
    }

    void stackAssign(struct abiSeq* a, uintptr_t size, uintptr_t alignment)
    {
        a->stackBytes = align(a->stackBytes, alignment);
        a->steps = append(a->steps, gocpp::Init<abiStep>([](abiStep& x) { x.kind = abiStepStack; x.offset = 0; x.size = size; x.stkOff = a->stackBytes; }));
        a->stackBytes += size;
    }

    
    template<typename T> requires gocpp::GoStruct<T>
    abiDesc::operator T()
    {
        T result;
        result.call = this->call;
        result.ret = this->ret;
        result.stackCallArgsSize = this->stackCallArgsSize;
        result.retOffset = this->retOffset;
        result.spill = this->spill;
        result.stackPtrs = this->stackPtrs;
        result.inRegPtrs = this->inRegPtrs;
        result.outRegPtrs = this->outRegPtrs;
        return result;
    }

    template<typename T> requires gocpp::GoStruct<T>
    bool abiDesc::operator==(const T& ref) const
    {
        if (call != ref.call) return false;
        if (ret != ref.ret) return false;
        if (stackCallArgsSize != ref.stackCallArgsSize) return false;
        if (retOffset != ref.retOffset) return false;
        if (spill != ref.spill) return false;
        if (stackPtrs != ref.stackPtrs) return false;
        if (inRegPtrs != ref.inRegPtrs) return false;
        if (outRegPtrs != ref.outRegPtrs) return false;
        return true;
    }

    std::ostream& abiDesc::PrintTo(std::ostream& os) const
    {
        os << '{';
        os << "" << call;
        os << " " << ret;
        os << " " << stackCallArgsSize;
        os << " " << retOffset;
        os << " " << spill;
        os << " " << stackPtrs;
        os << " " << inRegPtrs;
        os << " " << outRegPtrs;
        os << '}';
        return os;
    }

    std::ostream& operator<<(std::ostream& os, const struct abiDesc& value)
    {
        return value.PrintTo(os);
    }

    void dump(struct abiDesc* a)
    {
        println("ABI");
        println("call");
        dump(gocpp::recv(a->call));
        println("ret");
        dump(gocpp::recv(a->ret));
        println("stackCallArgsSize", a->stackCallArgsSize);
        println("retOffset", a->retOffset);
        println("spill", a->spill);
        print("inRegPtrs:");
        dumpPtrBitMap(a->inRegPtrs);
        println();
        print("outRegPtrs:");
        dumpPtrBitMap(a->outRegPtrs);
        println();
    }

    void dumpPtrBitMap(abi::IntArgRegBitmap b)
    {
        for(auto i = 0; i < intArgRegs; i++)
        {
            auto x = 0;
            if(Get(gocpp::recv(b), i))
            {
                x = 1;
            }
            print(" ", x);
        }
    }

    abiDesc newAbiDesc(funcType* t, abi::Type* rcvr)
    {
        auto spill = uintptr_t(0);
        auto stackPtrs = go_new(bitVector);
        auto inRegPtrs = abi::IntArgRegBitmap {};
        abiSeq in = {};
        if(rcvr != nullptr)
        {
            auto [stkStep, isPtr] = addRcvr(gocpp::recv(in), rcvr);
            if(stkStep != nullptr)
            {
                if(isPtr)
                {
                    append(gocpp::recv(stackPtrs), 1);
                }
                else
                {
                    append(gocpp::recv(stackPtrs), 0);
                }
            }
            else
            {
                spill += goarch::PtrSize;
            }
        }
        for(auto [i, arg] : InSlice(gocpp::recv(t)))
        {
            auto stkStep = addArg(gocpp::recv(in), arg);
            if(stkStep != nullptr)
            {
                addTypeBits(stackPtrs, stkStep->stkOff, arg);
            }
            else
            {
                spill = align(spill, uintptr_t(Align(gocpp::recv(arg))));
                spill += Size(gocpp::recv(arg));
                for(auto [_, st] : stepsForValue(gocpp::recv(in), i))
                {
                    if(st.kind == abiStepPointer)
                    {
                        Set(gocpp::recv(inRegPtrs), st.ireg);
                    }
                }
            }
        }
        spill = align(spill, goarch::PtrSize);
        auto stackCallArgsSize = in.stackBytes;
        auto retOffset = align(in.stackBytes, goarch::PtrSize);
        auto outRegPtrs = abi::IntArgRegBitmap {};
        abiSeq out = {};
        out.stackBytes = retOffset;
        for(auto [i, res] : OutSlice(gocpp::recv(t)))
        {
            auto stkStep = addArg(gocpp::recv(out), res);
            if(stkStep != nullptr)
            {
                addTypeBits(stackPtrs, stkStep->stkOff, res);
            }
            else
            {
                for(auto [_, st] : stepsForValue(gocpp::recv(out), i))
                {
                    if(st.kind == abiStepPointer)
                    {
                        Set(gocpp::recv(outRegPtrs), st.ireg);
                    }
                }
            }
        }
        out.stackBytes -= retOffset;
        return abiDesc {in, out, stackCallArgsSize, retOffset, spill, stackPtrs, inRegPtrs, outRegPtrs};
    }

    void intFromReg(abi::RegArgs* r, int reg, uintptr_t argSize, unsafe::Pointer to)
    {
        memmove(to, IntRegArgAddr(gocpp::recv(r), reg, argSize), argSize);
    }

    void intToReg(abi::RegArgs* r, int reg, uintptr_t argSize, unsafe::Pointer from)
    {
        memmove(IntRegArgAddr(gocpp::recv(r), reg, argSize), from, argSize);
    }

    void floatFromReg(abi::RegArgs* r, int reg, uintptr_t argSize, unsafe::Pointer to)
    {
        //Go switch emulation
        {
            auto condition = argSize;
            int conditionId = -1;
            if(condition == 4) { conditionId = 0; }
            else if(condition == 8) { conditionId = 1; }
            switch(conditionId)
            {
                case 0:
                    *(float*)(to) = archFloat32FromReg(r->Floats[reg]);
                    break;
                case 1:
                    *(double*)(to) = *(double*)(unsafe::Pointer(& r->Floats[reg]));
                    break;
                default:
                    gocpp::panic("bad argSize");
                    break;
            }
        }
    }

    void floatToReg(abi::RegArgs* r, int reg, uintptr_t argSize, unsafe::Pointer from)
    {
        //Go switch emulation
        {
            auto condition = argSize;
            int conditionId = -1;
            if(condition == 4) { conditionId = 0; }
            else if(condition == 8) { conditionId = 1; }
            switch(conditionId)
            {
                case 0:
                    r->Floats[reg] = archFloat32ToReg(*(float*)(from));
                    break;
                case 1:
                    r->Floats[reg] = *(uint64_t*)(from);
                    break;
                default:
                    gocpp::panic("bad argSize");
                    break;
            }
        }
    }

}

