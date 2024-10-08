// generated by GoCpp from file '$(ImportDir)/runtime/symtabinl.go'
#include <complex>
#include <functional>
#include <iostream>
#include <iomanip>
#include <map>
#include <string>
#include <tuple>
#include <vector>

#include "golang/runtime/symtabinl.h"
#include "gocpp/support.h"

// #include "golang/internal/abi/symtab.h"  [Ignored, known errors]
#include "golang/internal/abi/type.h"
#include "golang/runtime/internal/sys/nih.h"
#include "golang/runtime/plugin.h"
#include "golang/runtime/proc.h"
#include "golang/runtime/runtime2.h"
#include "golang/runtime/stack.h"
// #include "golang/runtime/symtab.h"  [Ignored, known errors]

namespace golang::runtime
{
    
    std::ostream& inlinedCall::PrintTo(std::ostream& os) const
    {
        os << '{';
        os << "" << funcID;
        os << " " << _;
        os << " " << nameOff;
        os << " " << parentPc;
        os << " " << startLine;
        os << '}';
        return os;
    }

    std::ostream& operator<<(std::ostream& os, const struct inlinedCall& value)
    {
        return value.PrintTo(os);
    }

    
    std::ostream& inlineUnwinder::PrintTo(std::ostream& os) const
    {
        os << '{';
        os << "" << f;
        os << " " << inlTree;
        os << '}';
        return os;
    }

    std::ostream& operator<<(std::ostream& os, const struct inlineUnwinder& value)
    {
        return value.PrintTo(os);
    }

    
    std::ostream& inlineFrame::PrintTo(std::ostream& os) const
    {
        os << '{';
        os << "" << pc;
        os << " " << index;
        os << '}';
        return os;
    }

    std::ostream& operator<<(std::ostream& os, const struct inlineFrame& value)
    {
        return value.PrintTo(os);
    }

    std::tuple<inlineUnwinder, inlineFrame> newInlineUnwinder(funcInfo f, uintptr_t pc)
    {
        auto inldata = funcdata(f, abi::FUNCDATA_InlTree);
        if(inldata == nullptr)
        {
            return {gocpp::Init<inlineUnwinder>([](inlineUnwinder& x) { x.f = f; }), gocpp::Init<inlineFrame>([](inlineFrame& x) { x.pc = pc; x.index = - 1; })};
        }
        auto inlTree = (gocpp::array<inlinedCall, 1 << 20>*)(inldata);
        auto u = gocpp::Init<inlineUnwinder>([](inlineUnwinder& x) { x.f = f; x.inlTree = inlTree; });
        return {u, resolveInternal(gocpp::recv(u), pc)};
    }

    inlineFrame resolveInternal(struct inlineUnwinder* u, uintptr_t pc)
    {
        return gocpp::Init<inlineFrame>([](inlineFrame& x) { x.pc = pc; x.index = pcdatavalue1(u->f, abi::PCDATA_InlTreeIndex, pc, false); });
    }

    bool valid(struct inlineFrame uf)
    {
        return uf.pc != 0;
    }

    inlineFrame next(struct inlineUnwinder* u, inlineFrame uf)
    {
        if(uf.index < 0)
        {
            uf.pc = 0;
            return uf;
        }
        auto parentPc = u->inlTree[uf.index].parentPc;
        return resolveInternal(gocpp::recv(u), entry(gocpp::recv(u->f)) + uintptr_t(parentPc));
    }

    bool isInlined(struct inlineUnwinder* u, inlineFrame uf)
    {
        return uf.index >= 0;
    }

    srcFunc srcFunc(struct inlineUnwinder* u, inlineFrame uf)
    {
        if(uf.index < 0)
        {
            return srcFunc(gocpp::recv(u->f));
        }
        auto t = & u->inlTree[uf.index];
        return srcFunc {u->f.datap, t->nameOff, t->startLine, t->funcID};
    }

    std::tuple<std::string, int> fileLine(struct inlineUnwinder* u, inlineFrame uf)
    {
        std::string file;
        int line;
        auto [file, line32] = funcline1(u->f, uf.pc, false);
        return {file, int(line32)};
    }

}

