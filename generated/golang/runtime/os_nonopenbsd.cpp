// generated by GoCpp from file '$(ImportDir)/runtime/os_nonopenbsd.go'
#include <complex>
#include <functional>
#include <iostream>
#include <iomanip>
#include <map>
#include <string>
#include <tuple>
#include <vector>

#include "golang/runtime/os_nonopenbsd.h"
#include "gocpp/support.h"

#include "golang/internal/abi/type.h"
#include "golang/runtime/internal/atomic/types.h"
#include "golang/runtime/internal/sys/nih.h"
#include "golang/runtime/lockrank_off.h"
#include "golang/runtime/mcache.h"
#include "golang/runtime/mheap.h"
#include "golang/runtime/mranges.h"
#include "golang/runtime/runtime2.h"

namespace golang::runtime
{
    namespace rec
    {
        using namespace mocklib::rec;
    }

    // osStackAlloc performs OS-specific initialization before s is used
    // as stack memory.
    void osStackAlloc(struct mspan* s)
    {
    }

    // osStackFree undoes the effect of osStackAlloc before s is returned
    // to the heap.
    void osStackFree(struct mspan* s)
    {
    }

}

