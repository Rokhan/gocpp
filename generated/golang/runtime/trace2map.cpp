// generated by GoCpp from file '$(ImportDir)/runtime/trace2map.go'
#include <complex>
#include <functional>
#include <iostream>
#include <iomanip>
#include <map>
#include <string>
#include <tuple>
#include <vector>

#include "golang/runtime/trace2map.h"
#include "gocpp/support.h"

// #include "golang/runtime/alg.h"  [Ignored, known errors]
#include "golang/runtime/internal/atomic/types.h"
#include "golang/runtime/internal/sys/nih.h"
// #include "golang/runtime/lock_sema.h"  [Ignored, known errors]
// #include "golang/runtime/lockrank_off.h"  [Ignored, known errors]
#include "golang/runtime/malloc.h"
#include "golang/runtime/runtime2.h"
#include "golang/runtime/slice.h"
// #include "golang/runtime/stubs.h"  [Ignored, known errors]
// #include "golang/runtime/trace2region.h"  [Ignored, known errors]
#include "golang/unsafe/unsafe.h"

namespace golang::runtime
{
    
    template<typename T> requires gocpp::GoStruct<T>
    traceMap::operator T()
    {
        T result;
        result.lock = this->lock;
        result.seq = this->seq;
        result.mem = this->mem;
        result.tab = this->tab;
        return result;
    }

    template<typename T> requires gocpp::GoStruct<T>
    bool traceMap::operator==(const T& ref) const
    {
        if (lock != ref.lock) return false;
        if (seq != ref.seq) return false;
        if (mem != ref.mem) return false;
        if (tab != ref.tab) return false;
        return true;
    }

    std::ostream& traceMap::PrintTo(std::ostream& os) const
    {
        os << '{';
        os << "" << lock;
        os << " " << seq;
        os << " " << mem;
        os << " " << tab;
        os << '}';
        return os;
    }

    std::ostream& operator<<(std::ostream& os, const struct traceMap& value)
    {
        return value.PrintTo(os);
    }

    
    template<typename T> requires gocpp::GoStruct<T>
    traceMapNode::operator T()
    {
        T result;
        result._ = this->_;
        result.link = this->link;
        result.hash = this->hash;
        result.id = this->id;
        result.data = this->data;
        return result;
    }

    template<typename T> requires gocpp::GoStruct<T>
    bool traceMapNode::operator==(const T& ref) const
    {
        if (_ != ref._) return false;
        if (link != ref.link) return false;
        if (hash != ref.hash) return false;
        if (id != ref.id) return false;
        if (data != ref.data) return false;
        return true;
    }

    std::ostream& traceMapNode::PrintTo(std::ostream& os) const
    {
        os << '{';
        os << "" << _;
        os << " " << link;
        os << " " << hash;
        os << " " << id;
        os << " " << data;
        os << '}';
        return os;
    }

    std::ostream& operator<<(std::ostream& os, const struct traceMapNode& value)
    {
        return value.PrintTo(os);
    }

    traceMapNode* next(struct traceMapNode* n)
    {
        return (traceMapNode*)(Load(gocpp::recv(n->link)));
    }

    uint64_t stealID(struct traceMap* tab)
    {
        return Add(gocpp::recv(tab->seq), 1);
    }

    std::tuple<uint64_t, bool> put(struct traceMap* tab, unsafe::Pointer data, uintptr_t size)
    {
        if(size == 0)
        {
            return {0, false};
        }
        auto hash = memhash(data, 0, size);
        if(auto id = find(gocpp::recv(tab), data, size, hash); id != 0)
        {
            return {id, false};
        }
        uint64_t id = {};
        bool added = {};
        systemstack([=]() mutable -> void
        {
            lock(& tab->lock);
            if(id = find(gocpp::recv(tab), data, size, hash); id != 0)
            {
                unlock(& tab->lock);
                return;
            }
            id = Add(gocpp::recv(tab->seq), 1);
            auto vd = newTraceMapNode(gocpp::recv(tab), data, size, hash, id);
            auto part = int(hash % uintptr_t(len(tab->tab)));
            StoreNoWB(gocpp::recv(vd->link), Load(gocpp::recv(tab->tab[part])));
            StoreNoWB(gocpp::recv(tab->tab[part]), unsafe::Pointer(vd));
            unlock(& tab->lock);
            added = true;
        });
        return {id, added};
    }

    uint64_t find(struct traceMap* tab, unsafe::Pointer data, uintptr_t size, uintptr_t hash)
    {
        auto part = int(hash % uintptr_t(len(tab->tab)));
        for(auto vd = bucket(gocpp::recv(tab), part); vd != nullptr; vd = next(gocpp::recv(vd)))
        {
            if(vd->hash == hash && uintptr_t(len(vd->data)) == size)
            {
                if(memequal(unsafe::Pointer(& vd->data[0]), data, size))
                {
                    return vd->id;
                }
            }
        }
        return 0;
    }

    traceMapNode* bucket(struct traceMap* tab, int part)
    {
        return (traceMapNode*)(Load(gocpp::recv(tab->tab[part])));
    }

    traceMapNode* newTraceMapNode(struct traceMap* tab, unsafe::Pointer data, uintptr_t size, uintptr_t hash, uint64_t id)
    {
        auto sl = gocpp::Init<notInHeapSlice>([](notInHeapSlice& x) { x.array = alloc(gocpp::recv(tab->mem), size); x.len = int(size); x.cap = int(size); });
        memmove(unsafe::Pointer(sl.array), data, size);
        auto meta = (traceMapNode*)(unsafe::Pointer(alloc(gocpp::recv(tab->mem), gocpp::Sizeof<traceMapNode>())));
        *(notInHeapSlice*)(unsafe::Pointer(& meta->data)) = sl;
        meta->id = id;
        meta->hash = hash;
        return meta;
    }

    void reset(struct traceMap* tab)
    {
        assertLockHeld(& tab->lock);
        drop(gocpp::recv(tab->mem));
        Store(gocpp::recv(tab->seq), 0);
        memclrNoHeapPointers(unsafe::Pointer(& tab->tab), gocpp::Sizeof<atomic::UnsafePointer, 8192>>());
    }

}

