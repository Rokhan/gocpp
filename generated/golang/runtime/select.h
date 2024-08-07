// generated by GoCpp from file '$(ImportDir)/runtime/select.go'
#pragma once

#include <functional>
#include <string>
#include <tuple>
#include <vector>

#include "golang/runtime/select.fwd.h"
#include "gocpp/support.h"

#include "golang/internal/abi/funcpc.h"
#include "golang/runtime/asan0.h"
#include "golang/runtime/chan.h"
#include "golang/runtime/cputicks.h"
#include "golang/runtime/error.h"
#include "golang/runtime/internal/atomic/types.h"
// #include "golang/runtime/lock_sema.h"  [Ignored, known errors]
#include "golang/runtime/mbarrier.h"
#include "golang/runtime/mprof.h"
#include "golang/runtime/msan0.h"
#include "golang/runtime/panic.h"
#include "golang/runtime/proc.h"
// #include "golang/runtime/race0.h"  [Ignored, known errors]
// #include "golang/runtime/rand.h"  [Ignored, known errors]
#include "golang/runtime/runtime2.h"
// #include "golang/runtime/stubs.h"  [Ignored, known errors]
// #include "golang/runtime/trace2runtime.h"  [Ignored, known errors]
#include "golang/unsafe/unsafe.h"

namespace golang::runtime
{
    struct scase
    {
        hchan* c;
        unsafe::Pointer elem;

        using isGoStruct = void;

        std::ostream& PrintTo(std::ostream& os) const;
    };

    std::ostream& operator<<(std::ostream& os, const struct scase& value);
    extern uintptr_t chansendpc;
    extern uintptr_t chanrecvpc;
    void selectsetpc(uintptr_t* pc);
    void sellock(gocpp::slice<scase> scases, gocpp::slice<uint16_t> lockorder);
    void selunlock(gocpp::slice<scase> scases, gocpp::slice<uint16_t> lockorder);
    bool selparkcommit(g* gp, unsafe::Pointer _);
    void block();
    std::tuple<int, bool> selectgo(scase* cas0, uint16_t* order0, uintptr_t* pc0, int nsends, int nrecvs, bool block);
    uintptr_t sortkey(struct hchan* c);
    struct runtimeSelect
    {
        selectDir dir;
        unsafe::Pointer typ;
        hchan* ch;
        unsafe::Pointer val;

        using isGoStruct = void;

        std::ostream& PrintTo(std::ostream& os) const;
    };

    std::ostream& operator<<(std::ostream& os, const struct runtimeSelect& value);
    std::tuple<int, bool> reflect_rselect(gocpp::slice<runtimeSelect> cases);
    void dequeueSudoG(struct waitq* q, sudog* sgp);
}

