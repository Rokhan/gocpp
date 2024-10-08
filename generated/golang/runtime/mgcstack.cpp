// generated by GoCpp from file '$(ImportDir)/runtime/mgcstack.go'
#include <complex>
#include <functional>
#include <iostream>
#include <iomanip>
#include <map>
#include <string>
#include <tuple>
#include <vector>

#include "golang/runtime/mgcstack.h"
#include "gocpp/support.h"

#include "golang/internal/goarch/goarch.h"
#include "golang/runtime/internal/sys/nih.h"
#include "golang/runtime/mgcwork.h"
#include "golang/runtime/panic.h"
#include "golang/runtime/runtime2.h"
#include "golang/runtime/stack.h"
#include "golang/unsafe/unsafe.h"

namespace golang::runtime
{
    
    std::ostream& stackWorkBuf::PrintTo(std::ostream& os) const
    {
        os << '{';
        os << "" << _;
        os << " " << obj;
        os << '}';
        return os;
    }

    std::ostream& operator<<(std::ostream& os, const struct stackWorkBuf& value)
    {
        return value.PrintTo(os);
    }

    
    std::ostream& stackWorkBufHdr::PrintTo(std::ostream& os) const
    {
        os << '{';
        os << "" << _;
        os << " " << next;
        os << '}';
        return os;
    }

    std::ostream& operator<<(std::ostream& os, const struct stackWorkBufHdr& value)
    {
        return value.PrintTo(os);
    }

    
    std::ostream& stackObjectBuf::PrintTo(std::ostream& os) const
    {
        os << '{';
        os << "" << _;
        os << " " << obj;
        os << '}';
        return os;
    }

    std::ostream& operator<<(std::ostream& os, const struct stackObjectBuf& value)
    {
        return value.PrintTo(os);
    }

    
    std::ostream& stackObjectBufHdr::PrintTo(std::ostream& os) const
    {
        os << '{';
        os << "" << _;
        os << " " << next;
        os << '}';
        return os;
    }

    std::ostream& operator<<(std::ostream& os, const struct stackObjectBufHdr& value)
    {
        return value.PrintTo(os);
    }

    void init()
    {
        if(gocpp::Sizeof<stackWorkBuf>() > gocpp::Sizeof<workbuf>())
        {
            gocpp::panic("stackWorkBuf too big");
        }
        if(gocpp::Sizeof<stackObjectBuf>() > gocpp::Sizeof<workbuf>())
        {
            gocpp::panic("stackObjectBuf too big");
        }
    }

    
    std::ostream& stackObject::PrintTo(std::ostream& os) const
    {
        os << '{';
        os << "" << _;
        os << " " << off;
        os << " " << size;
        os << " " << r;
        os << " " << left;
        os << " " << right;
        os << '}';
        return os;
    }

    std::ostream& operator<<(std::ostream& os, const struct stackObject& value)
    {
        return value.PrintTo(os);
    }

    void setRecord(struct stackObject* obj, stackObjectRecord* r)
    {
        *(uintptr_t*)(unsafe::Pointer(& obj->r)) = uintptr_t(unsafe::Pointer(r));
    }

    
    std::ostream& stackScanState::PrintTo(std::ostream& os) const
    {
        os << '{';
        os << "" << stack;
        os << " " << conservative;
        os << " " << buf;
        os << " " << freeBuf;
        os << " " << cbuf;
        os << " " << head;
        os << " " << tail;
        os << " " << nobjs;
        os << " " << root;
        os << '}';
        return os;
    }

    std::ostream& operator<<(std::ostream& os, const struct stackScanState& value)
    {
        return value.PrintTo(os);
    }

    void putPtr(struct stackScanState* s, uintptr_t p, bool conservative)
    {
        if(p < s->stack.lo || p >= s->stack.hi)
        {
            go_throw("address not a stack address");
        }
        auto head = & s->buf;
        if(conservative)
        {
            head = & s->cbuf;
        }
        auto buf = *head;
        if(buf == nullptr)
        {
            buf = (stackWorkBuf*)(unsafe::Pointer(getempty()));
            buf->nobj = 0;
            buf->next = nullptr;
            *head = buf;
        }
        else
        if(buf->nobj == len(buf->obj))
        {
            if(s->freeBuf != nullptr)
            {
                buf = s->freeBuf;
                s->freeBuf = nullptr;
            }
            else
            {
                buf = (stackWorkBuf*)(unsafe::Pointer(getempty()));
            }
            buf->nobj = 0;
            buf->next = *head;
            *head = buf;
        }
        buf->obj[buf->nobj] = p;
        buf->nobj++;
    }

    std::tuple<uintptr_t, bool> getPtr(struct stackScanState* s)
    {
        uintptr_t p;
        bool conservative;
        for(auto [_, head] : gocpp::slice<stackWorkBuf**> {& s->buf, & s->cbuf})
        {
            uintptr_t p;
            bool conservative;
            auto buf = *head;
            if(buf == nullptr)
            {
                uintptr_t p;
                bool conservative;
                continue;
            }
            if(buf->nobj == 0)
            {
                uintptr_t p;
                bool conservative;
                if(s->freeBuf != nullptr)
                {
                    uintptr_t p;
                    bool conservative;
                    putempty((workbuf*)(unsafe::Pointer(s->freeBuf)));
                }
                s->freeBuf = buf;
                buf = buf->next;
                *head = buf;
                if(buf == nullptr)
                {
                    uintptr_t p;
                    bool conservative;
                    continue;
                }
            }
            buf->nobj--;
            return {buf->obj[buf->nobj], head == & s->cbuf};
        }
        if(s->freeBuf != nullptr)
        {
            uintptr_t p;
            bool conservative;
            putempty((workbuf*)(unsafe::Pointer(s->freeBuf)));
            s->freeBuf = nullptr;
        }
        return {0, false};
    }

    void addObject(struct stackScanState* s, uintptr_t addr, stackObjectRecord* r)
    {
        auto x = s->tail;
        if(x == nullptr)
        {
            x = (stackObjectBuf*)(unsafe::Pointer(getempty()));
            x->next = nullptr;
            s->head = x;
            s->tail = x;
        }
        if(x->nobj > 0 && uint32_t(addr - s->stack.lo) < x->obj[x->nobj - 1].off + x->obj[x->nobj - 1].size)
        {
            go_throw("objects added out of order or overlapping");
        }
        if(x->nobj == len(x->obj))
        {
            auto y = (stackObjectBuf*)(unsafe::Pointer(getempty()));
            y->next = nullptr;
            x->next = y;
            s->tail = y;
            x = y;
        }
        auto obj = & x->obj[x->nobj];
        x->nobj++;
        obj->off = uint32_t(addr - s->stack.lo);
        obj->size = uint32_t(r->size);
        setRecord(gocpp::recv(obj), r);
        s->nobjs++;
    }

    void buildIndex(struct stackScanState* s)
    {
        std::tie(s->root, gocpp_id_0, gocpp_id_1) = binarySearchTree(s->head, 0, s->nobjs);
    }

    std::tuple<stackObject*, stackObjectBuf*, int> binarySearchTree(stackObjectBuf* x, int idx, int n)
    {
        stackObject* root;
        stackObjectBuf* restBuf;
        int restIdx;
        if(n == 0)
        {
            stackObject* root;
            stackObjectBuf* restBuf;
            int restIdx;
            return {nullptr, x, idx};
        }
        stackObject* left = {};
        stackObject* right = {};
        std::tie(left, x, idx) = binarySearchTree(x, idx, n / 2);
        root = & x->obj[idx];
        idx++;
        if(idx == len(x->obj))
        {
            stackObject* root;
            stackObjectBuf* restBuf;
            int restIdx;
            x = x->next;
            idx = 0;
        }
        std::tie(right, x, idx) = binarySearchTree(x, idx, n - n / 2 - 1);
        root->left = left;
        root->right = right;
        return {root, x, idx};
    }

    stackObject* findObject(struct stackScanState* s, uintptr_t a)
    {
        auto off = uint32_t(a - s->stack.lo);
        auto obj = s->root;
        for(; ; )
        {
            if(obj == nullptr)
            {
                return nullptr;
            }
            if(off < obj->off)
            {
                obj = obj->left;
                continue;
            }
            if(off >= obj->off + obj->size)
            {
                obj = obj->right;
                continue;
            }
            return obj;
        }
    }

}

