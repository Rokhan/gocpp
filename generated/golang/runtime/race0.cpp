// generated by GoCpp from file '$(ImportDir)/runtime/race0.go'
#include <complex>
#include <functional>
#include <iostream>
#include <iomanip>
#include <map>
#include <string>
#include <tuple>
#include <vector>

#include "golang/runtime/race0.h"
#include "gocpp/support.h"

#include "golang/runtime/panic.h"
#include "golang/runtime/runtime2.h"
#include "golang/runtime/type.h"
#include "golang/unsafe/unsafe.h"

namespace golang::runtime
{
    void raceReadObjectPC(_type* t, unsafe::Pointer addr, uintptr_t callerpc, uintptr_t pc)
    {
        go_throw("race");
    }

    void raceWriteObjectPC(_type* t, unsafe::Pointer addr, uintptr_t callerpc, uintptr_t pc)
    {
        go_throw("race");
    }

    std::tuple<uintptr_t, uintptr_t> raceinit()
    {
        go_throw("race");
        return {0, 0};
    }

    void racefini()
    {
        go_throw("race");
    }

    uintptr_t raceproccreate()
    {
        go_throw("race");
        return 0;
    }

    void raceprocdestroy(uintptr_t ctx)
    {
        go_throw("race");
    }

    void racemapshadow(unsafe::Pointer addr, uintptr_t size)
    {
        go_throw("race");
    }

    void racewritepc(unsafe::Pointer addr, uintptr_t callerpc, uintptr_t pc)
    {
        go_throw("race");
    }

    void racereadpc(unsafe::Pointer addr, uintptr_t callerpc, uintptr_t pc)
    {
        go_throw("race");
    }

    void racereadrangepc(unsafe::Pointer addr, uintptr_t sz, uintptr_t callerpc, uintptr_t pc)
    {
        go_throw("race");
    }

    void racewriterangepc(unsafe::Pointer addr, uintptr_t sz, uintptr_t callerpc, uintptr_t pc)
    {
        go_throw("race");
    }

    void raceacquire(unsafe::Pointer addr)
    {
        go_throw("race");
    }

    void raceacquireg(g* gp, unsafe::Pointer addr)
    {
        go_throw("race");
    }

    void raceacquirectx(uintptr_t racectx, unsafe::Pointer addr)
    {
        go_throw("race");
    }

    void racerelease(unsafe::Pointer addr)
    {
        go_throw("race");
    }

    void racereleaseg(g* gp, unsafe::Pointer addr)
    {
        go_throw("race");
    }

    void racereleaseacquire(unsafe::Pointer addr)
    {
        go_throw("race");
    }

    void racereleaseacquireg(g* gp, unsafe::Pointer addr)
    {
        go_throw("race");
    }

    void racereleasemerge(unsafe::Pointer addr)
    {
        go_throw("race");
    }

    void racereleasemergeg(g* gp, unsafe::Pointer addr)
    {
        go_throw("race");
    }

    void racefingo()
    {
        go_throw("race");
    }

    void racemalloc(unsafe::Pointer p, uintptr_t sz)
    {
        go_throw("race");
    }

    void racefree(unsafe::Pointer p, uintptr_t sz)
    {
        go_throw("race");
    }

    uintptr_t racegostart(uintptr_t pc)
    {
        go_throw("race");
        return 0;
    }

    void racegoend()
    {
        go_throw("race");
    }

    void racectxend(uintptr_t racectx)
    {
        go_throw("race");
    }

}

