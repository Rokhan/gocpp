// generated by GoCpp from file '$(ImportDir)/reflect/makefunc.go'
#include <complex>
#include <functional>
#include <iostream>
#include <iomanip>
#include <map>
#include <string>
#include <tuple>
#include <vector>

#include "golang/reflect/makefunc.h"
#include "gocpp/support.h"

#include "golang/internal/abi/abi.h"
#include "golang/internal/abi/funcpc.h"
#include "golang/internal/abi/type.h"
#include "golang/reflect/abi.h"
#include "golang/reflect/type.h"
#include "golang/reflect/value.h"
#include "golang/sync/cond.h"
#include "golang/sync/pool.h"
#include "golang/unsafe/unsafe.h"

namespace golang::reflect
{
    namespace rec
    {
        using namespace mocklib::rec;
        using abi::rec::Common;
        using abi::rec::Get;
        using abi::rec::Kind;
    }

    // makeFuncImpl is the closure value implementing the function
    // returned by MakeFunc.
    // The first three words of this type must be kept in sync with
    // methodValue and runtime.reflectMethodValue.
    // Any changes should be reflected in all three.
    
    template<typename T> requires gocpp::GoStruct<T>
    makeFuncImpl::operator T()
    {
        T result;
        result.makeFuncCtxt = this->makeFuncCtxt;
        result.ftyp = this->ftyp;
        result.fn = this->fn;
        return result;
    }

    template<typename T> requires gocpp::GoStruct<T>
    bool makeFuncImpl::operator==(const T& ref) const
    {
        if (makeFuncCtxt != ref.makeFuncCtxt) return false;
        if (ftyp != ref.ftyp) return false;
        if (fn != ref.fn) return false;
        return true;
    }

    std::ostream& makeFuncImpl::PrintTo(std::ostream& os) const
    {
        os << '{';
        os << "" << makeFuncCtxt;
        os << " " << ftyp;
        os << " " << fn;
        os << '}';
        return os;
    }

    std::ostream& operator<<(std::ostream& os, const struct makeFuncImpl& value)
    {
        return value.PrintTo(os);
    }

    // MakeFunc returns a new function of the given Type
    // that wraps the function fn. When called, that new function
    // does the following:
    //
    //   - converts its arguments to a slice of Values.
    //   - runs results := fn(args).
    //   - returns the results as a slice of Values, one per formal result.
    //
    // The implementation fn can assume that the argument Value slice
    // has the number and type of arguments given by typ.
    // If typ describes a variadic function, the final Value is itself
    // a slice representing the variadic arguments, as in the
    // body of a variadic function. The result Value slice returned by fn
    // must have the number and type of results given by typ.
    //
    // The Value.Call method allows the caller to invoke a typed function
    // in terms of Values; in contrast, MakeFunc allows the caller to implement
    // a typed function in terms of Values.
    //
    // The Examples section of the documentation includes an illustration
    // of how to use MakeFunc to build a swap function for different types.
    struct Value MakeFunc(struct Type typ, std::function<gocpp::slice<Value> (gocpp::slice<Value> args)> fn)
    {
        if(rec::Kind(gocpp::recv(typ)) != Func)
        {
            gocpp::panic("reflect: call of MakeFunc with non-Func type"s);
        }
        auto t = rec::common(gocpp::recv(typ));
        auto ftyp = (reflect::funcType*)(unsafe::Pointer(t));
        auto code = abi::FuncPCABI0(makeFuncStub);
        auto [gocpp_id_0, gocpp_id_1, abid] = funcLayout(ftyp, nullptr);
        auto impl = gocpp::InitPtr<makeFuncImpl>([=](auto& x) {
            x.makeFuncCtxt = gocpp::Init<makeFuncCtxt>([=](auto& x) {
                x.fn = code;
                x.stack = abid.stackPtrs;
                x.argLen = abid.stackCallArgsSize;
                x.regPtrs = abid.inRegPtrs;
            });
            x.ftyp = ftyp;
            x.fn = fn;
        });
        return Value {t, unsafe::Pointer(impl), flag(Func)};
    }

    // makeFuncStub is an assembly function that is the code half of
    // the function returned from MakeFunc. It expects a *callReflectFunc
    // as its context register, and its job is to invoke callReflect(ctxt, frame)
    // where ctxt is the context register and frame is a pointer to the first
    // word in the passed-in argument frame.
    void makeFuncStub()
    /* convertBlockStmt, nil block */;

    // The first 3 words of this type must be kept in sync with
    // makeFuncImpl and runtime.reflectMethodValue.
    // Any changes should be reflected in all three.
    
    template<typename T> requires gocpp::GoStruct<T>
    methodValue::operator T()
    {
        T result;
        result.makeFuncCtxt = this->makeFuncCtxt;
        result.method = this->method;
        result.rcvr = this->rcvr;
        return result;
    }

    template<typename T> requires gocpp::GoStruct<T>
    bool methodValue::operator==(const T& ref) const
    {
        if (makeFuncCtxt != ref.makeFuncCtxt) return false;
        if (method != ref.method) return false;
        if (rcvr != ref.rcvr) return false;
        return true;
    }

    std::ostream& methodValue::PrintTo(std::ostream& os) const
    {
        os << '{';
        os << "" << makeFuncCtxt;
        os << " " << method;
        os << " " << rcvr;
        os << '}';
        return os;
    }

    std::ostream& operator<<(std::ostream& os, const struct methodValue& value)
    {
        return value.PrintTo(os);
    }

    // makeMethodValue converts v from the rcvr+method index representation
    // of a method value to an actual method func value, which is
    // basically the receiver value with a special bit set, into a true
    // func value - a value holding an actual func. The output is
    // semantically equivalent to the input as far as the user of package
    // reflect can tell, but the true func representation can be handled
    // by code like Convert and Interface and Assign.
    struct Value makeMethodValue(std::string op, struct Value v)
    {
        if(v.flag & flagMethod == 0)
        {
            gocpp::panic("reflect: internal error: invalid use of makeMethodValue"s);
        }
        auto fl = v.flag & (flagRO | flagAddr | flagIndir);
        fl |= flag(rec::Kind(gocpp::recv(rec::typ(gocpp::recv(v)))));
        auto rcvr = Value {rec::typ(gocpp::recv(v)), v.ptr, fl};
        auto ftyp = (reflect::funcType*)(unsafe::Pointer(gocpp::getValue<rtype*>(rec::Type(gocpp::recv(v)))));
        auto code = methodValueCallCodePtr();
        auto [gocpp_id_2, gocpp_id_3, abid] = funcLayout(ftyp, nullptr);
        auto fv = gocpp::InitPtr<methodValue>([=](auto& x) {
            x.makeFuncCtxt = gocpp::Init<makeFuncCtxt>([=](auto& x) {
                x.fn = code;
                x.stack = abid.stackPtrs;
                x.argLen = abid.stackCallArgsSize;
                x.regPtrs = abid.inRegPtrs;
            });
            x.method = int(v.flag) >> flagMethodShift;
            x.rcvr = rcvr;
        });
        methodReceiver(op, fv->rcvr, fv->method);
        return Value {rec::Common(gocpp::recv(ftyp)), unsafe::Pointer(fv), v.flag & flagRO | flag(Func)};
    }

    uintptr_t methodValueCallCodePtr()
    {
        return abi::FuncPCABI0(methodValueCall);
    }

    // methodValueCall is an assembly function that is the code half of
    // the function returned from makeMethodValue. It expects a *methodValue
    // as its context register, and its job is to invoke callMethod(ctxt, frame)
    // where ctxt is the context register and frame is a pointer to the first
    // word in the passed-in argument frame.
    void methodValueCall()
    /* convertBlockStmt, nil block */;

    // This structure must be kept in sync with runtime.reflectMethodValue.
    // Any changes should be reflected in all both.
    
    template<typename T> requires gocpp::GoStruct<T>
    makeFuncCtxt::operator T()
    {
        T result;
        result.fn = this->fn;
        result.stack = this->stack;
        result.argLen = this->argLen;
        result.regPtrs = this->regPtrs;
        return result;
    }

    template<typename T> requires gocpp::GoStruct<T>
    bool makeFuncCtxt::operator==(const T& ref) const
    {
        if (fn != ref.fn) return false;
        if (stack != ref.stack) return false;
        if (argLen != ref.argLen) return false;
        if (regPtrs != ref.regPtrs) return false;
        return true;
    }

    std::ostream& makeFuncCtxt::PrintTo(std::ostream& os) const
    {
        os << '{';
        os << "" << fn;
        os << " " << stack;
        os << " " << argLen;
        os << " " << regPtrs;
        os << '}';
        return os;
    }

    std::ostream& operator<<(std::ostream& os, const struct makeFuncCtxt& value)
    {
        return value.PrintTo(os);
    }

    // moveMakeFuncArgPtrs uses ctxt.regPtrs to copy integer pointer arguments
    // in args.Ints to args.Ptrs where the GC can see them.
    //
    // This is similar to what reflectcallmove does in the runtime, except
    // that happens on the return path, whereas this happens on the call path.
    //
    // nosplit because pointers are being held in uintptr slots in args, so
    // having our stack scanned now could lead to accidentally freeing
    // memory.
    //
    //go:nosplit
    void moveMakeFuncArgPtrs(struct makeFuncCtxt* ctxt, abi::RegArgs* args)
    {
        for(auto [i, arg] : args->Ints)
        {
            if(rec::Get(gocpp::recv(ctxt->regPtrs), i))
            {
                *(uintptr_t*)(unsafe::Pointer(& args->Ptrs[i])) = arg;
            }
            else
            {
                *(uintptr_t*)(unsafe::Pointer(& args->Ptrs[i])) = 0;
            }
        }
    }

}

