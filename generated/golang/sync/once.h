// generated by GoCpp from file '$(ImportDir)/sync/once.go'
#pragma once

#include <functional>
#include <string>
#include <tuple>
#include <vector>

#include "golang/sync/once.fwd.h"
#include "gocpp/support.h"

#include "golang/sync/atomic/type.h"
#include "golang/sync/mutex.h"

namespace golang::sync
{
    struct Once
    {
        atomic::Uint32 done;
        Mutex m;

        using isGoStruct = void;

        std::ostream& PrintTo(std::ostream& os) const;
    };

    std::ostream& operator<<(std::ostream& os, const struct Once& value);
    void Do(struct Once* o, std::function<void ()> f);
    void doSlow(struct Once* o, std::function<void ()> f);
}

