// generated by GoCpp from file '$(ImportDir)/runtime/select.go'
#include <complex>
#include <functional>
#include <iostream>
#include <iomanip>
#include <map>
#include <string>
#include <tuple>
#include <vector>

#include "golang/runtime/select.h"
#include "gocpp/support.h"

#include "golang/internal/abi/funcpc.h"
#include "golang/internal/abi/type.h"
#include "golang/internal/chacha8rand/chacha8.h"
#include "golang/runtime/asan0.h"
// #include "golang/runtime/cgocall.h"  [Ignored, known errors]
#include "golang/runtime/chan.h"
#include "golang/runtime/coro.h"
#include "golang/runtime/cputicks.h"
#include "golang/runtime/debuglog_off.h"
#include "golang/runtime/error.h"
#include "golang/runtime/internal/atomic/types.h"
#include "golang/runtime/internal/sys/nih.h"
// #include "golang/runtime/lock_sema.h"  [Ignored, known errors]
// #include "golang/runtime/lockrank.h"  [Ignored, known errors]
// #include "golang/runtime/lockrank_off.h"  [Ignored, known errors]
#include "golang/runtime/mbarrier.h"
#include "golang/runtime/mprof.h"
#include "golang/runtime/msan0.h"
// #include "golang/runtime/os_windows.h"  [Ignored, known errors]
#include "golang/runtime/panic.h"
#include "golang/runtime/proc.h"
#include "golang/runtime/race0.h"
// #include "golang/runtime/rand.h"  [Ignored, known errors]
#include "golang/runtime/runtime2.h"
// #include "golang/runtime/signal_windows.h"  [Ignored, known errors]
// #include "golang/runtime/stubs.h"  [Ignored, known errors]
// #include "golang/runtime/symtab.h"  [Ignored, known errors]
// #include "golang/runtime/time.h"  [Ignored, known errors]
#include "golang/runtime/trace2buf.h"
// #include "golang/runtime/trace2runtime.h"  [Ignored, known errors]
#include "golang/runtime/trace2status.h"
#include "golang/runtime/trace2time.h"
#include "golang/unsafe/unsafe.h"

namespace golang::runtime
{
    
    template<typename T> requires gocpp::GoStruct<T>
    scase::operator T()
    {
        T result;
        result.c = this->c;
        result.elem = this->elem;
        return result;
    }

    template<typename T> requires gocpp::GoStruct<T>
    bool scase::operator==(const T& ref) const
    {
        if (c != ref.c) return false;
        if (elem != ref.elem) return false;
        return true;
    }

    std::ostream& scase::PrintTo(std::ostream& os) const
    {
        os << '{';
        os << "" << c;
        os << " " << elem;
        os << '}';
        return os;
    }

    std::ostream& operator<<(std::ostream& os, const struct scase& value)
    {
        return value.PrintTo(os);
    }

    uintptr_t chansendpc = abi::FuncPCABIInternal(chansend);
    uintptr_t chanrecvpc = abi::FuncPCABIInternal(chanrecv);
    void selectsetpc(uintptr_t* pc)
    {
        *pc = getcallerpc();
    }

    void sellock(gocpp::slice<scase> scases, gocpp::slice<uint16_t> lockorder)
    {
        hchan* c = {};
        for(auto [_, o] : lockorder)
        {
            auto c0 = scases[o].c;
            if(c0 != c)
            {
                c = c0;
                lock(& c->lock);
            }
        }
    }

    void selunlock(gocpp::slice<scase> scases, gocpp::slice<uint16_t> lockorder)
    {
        for(auto i = len(lockorder) - 1; i >= 0; i--)
        {
            auto c = scases[lockorder[i]].c;
            if(i > 0 && c == scases[lockorder[i - 1]].c)
            {
                continue;
            }
            unlock(& c->lock);
        }
    }

    bool selparkcommit(g* gp, unsafe::Pointer _)
    {
        gp->activeStackChans = true;
        Store(gocpp::recv(gp->parkingOnChan), false);
        hchan* lastc = {};
        for(auto sg = gp->waiting; sg != nullptr; sg = sg->waitlink)
        {
            if(sg->c != lastc && lastc != nullptr)
            {
                unlock(& lastc->lock);
            }
            lastc = sg->c;
        }
        if(lastc != nullptr)
        {
            unlock(& lastc->lock);
        }
        return true;
    }

    void block()
    {
        gopark(nullptr, nullptr, waitReasonSelectNoCases, traceBlockForever, 1);
    }

    std::tuple<int, bool> selectgo(scase* cas0, uint16_t* order0, uintptr_t* pc0, int nsends, int nrecvs, bool block)
    {
        if(debugSelect)
        {
            print("select: cas0=", cas0, "\n");
        }
        auto cas1 = (gocpp::array<scase, 1 << 16>*)(unsafe::Pointer(cas0));
        auto order1 = (gocpp::array<uint16_t, 1 << 17>*)(unsafe::Pointer(order0));
        auto ncases = nsends + nrecvs;
        auto scases = cas1.make_slice(, ncases, ncases);
        auto pollorder = order1.make_slice(, ncases, ncases);
        auto lockorder = order1.make_slice(ncases).make_slice(, ncases, ncases);
        gocpp::slice<uintptr_t> pcs = {};
        if(raceenabled && pc0 != nullptr)
        {
            auto pc1 = (gocpp::array<uintptr_t, 1 << 16>*)(unsafe::Pointer(pc0));
            pcs = pc1.make_slice(, ncases, ncases);
        }
        auto casePC = [=](int casi) mutable -> uintptr_t
        {
            if(pcs == nullptr)
            {
                return 0;
            }
            return pcs[casi];
        };
        int64_t t0 = {};
        if(blockprofilerate > 0)
        {
            t0 = cputicks();
        }
        auto norder = 0;
        for(auto [i, gocpp_ignored] : scases)
        {
            auto cas = & scases[i];
            if(cas->c == nullptr)
            {
                cas->elem = nullptr;
                continue;
            }
            auto j = cheaprandn(uint32_t(norder + 1));
            pollorder[norder] = pollorder[j];
            pollorder[j] = uint16_t(i);
            norder++;
        }
        pollorder = pollorder.make_slice(0, norder);
        lockorder = lockorder.make_slice(0, norder);
        for(auto [i, gocpp_ignored] : lockorder)
        {
            auto j = i;
            auto c = scases[pollorder[i]].c;
            for(; j > 0 && sortkey(gocpp::recv(scases[lockorder[(j - 1) / 2]].c)) < sortkey(gocpp::recv(c)); )
            {
                auto k = (j - 1) / 2;
                lockorder[j] = lockorder[k];
                j = k;
            }
            lockorder[j] = pollorder[i];
        }
        for(auto i = len(lockorder) - 1; i >= 0; i--)
        {
            auto o = lockorder[i];
            auto c = scases[o].c;
            lockorder[i] = lockorder[0];
            auto j = 0;
            for(; ; )
            {
                auto k = j * 2 + 1;
                if(k >= i)
                {
                    break;
                }
                if(k + 1 < i && sortkey(gocpp::recv(scases[lockorder[k]].c)) < sortkey(gocpp::recv(scases[lockorder[k + 1]].c)))
                {
                    k++;
                }
                if(sortkey(gocpp::recv(c)) < sortkey(gocpp::recv(scases[lockorder[k]].c)))
                {
                    lockorder[j] = lockorder[k];
                    j = k;
                    continue;
                }
                break;
            }
            lockorder[j] = o;
        }
        if(debugSelect)
        {
            for(auto i = 0; i + 1 < len(lockorder); i++)
            {
                if(sortkey(gocpp::recv(scases[lockorder[i]].c)) > sortkey(gocpp::recv(scases[lockorder[i + 1]].c)))
                {
                    print("i=", i, " x=", lockorder[i], " y=", lockorder[i + 1], "\n");
                    go_throw("select: broken sort");
                }
            }
        }
        sellock(scases, lockorder);
        g* gp = {};
        sudog* sg = {};
        hchan* c = {};
        scase* k = {};
        sudog* sglist = {};
        sudog* sgnext = {};
        unsafe::Pointer qp = {};
        sudog** nextp = {};
        int casi = {};
        scase* cas = {};
        bool caseSuccess = {};
        int64_t caseReleaseTime = - 1;
        bool recvOK = {};
        for(auto [_, casei] : pollorder)
        {
            casi = int(casei);
            cas = & scases[casi];
            c = cas->c;
            if(casi >= nsends)
            {
                sg = dequeue(gocpp::recv(c->sendq));
                if(sg != nullptr)
                {
                    goto recv;
                }
                if(c->qcount > 0)
                {
                    goto bufrecv;
                }
                if(c->closed != 0)
                {
                    goto rclose;
                }
            }
            else
            {
                if(raceenabled)
                {
                    racereadpc(raceaddr(gocpp::recv(c)), casePC(casi), chansendpc);
                }
                if(c->closed != 0)
                {
                    goto sclose;
                }
                sg = dequeue(gocpp::recv(c->recvq));
                if(sg != nullptr)
                {
                    goto send;
                }
                if(c->qcount < c->dataqsiz)
                {
                    goto bufsend;
                }
            }
        }
        if(! block)
        {
            selunlock(scases, lockorder);
            casi = - 1;
            goto retc;
        }
        gp = getg();
        if(gp->waiting != nullptr)
        {
            go_throw("gp.waiting != nil");
        }
        nextp = & gp->waiting;
        for(auto [_, casei] : lockorder)
        {
            casi = int(casei);
            cas = & scases[casi];
            c = cas->c;
            auto sg = acquireSudog();
            sg->g = gp;
            sg->isSelect = true;
            sg->elem = cas->elem;
            sg->releasetime = 0;
            if(t0 != 0)
            {
                sg->releasetime = - 1;
            }
            sg->c = c;
            *nextp = sg;
            nextp = & sg->waitlink;
            if(casi < nsends)
            {
                enqueue(gocpp::recv(c->sendq), sg);
            }
            else
            {
                enqueue(gocpp::recv(c->recvq), sg);
            }
        }
        gp->param = nullptr;
        Store(gocpp::recv(gp->parkingOnChan), true);
        gopark(selparkcommit, nullptr, waitReasonSelect, traceBlockSelect, 1);
        gp->activeStackChans = false;
        sellock(scases, lockorder);
        Store(gocpp::recv(gp->selectDone), 0);
        sg = (sudog*)(gp->param);
        gp->param = nullptr;
        casi = - 1;
        cas = nullptr;
        caseSuccess = false;
        sglist = gp->waiting;
        for(auto sg1 = gp->waiting; sg1 != nullptr; sg1 = sg1->waitlink)
        {
            sg1->isSelect = false;
            sg1->elem = nullptr;
            sg1->c = nullptr;
        }
        gp->waiting = nullptr;
        for(auto [_, casei] : lockorder)
        {
            k = & scases[casei];
            if(sg == sglist)
            {
                casi = int(casei);
                cas = k;
                caseSuccess = sglist->success;
                if(sglist->releasetime > 0)
                {
                    caseReleaseTime = sglist->releasetime;
                }
            }
            else
            {
                c = k->c;
                if(int(casei) < nsends)
                {
                    dequeueSudoG(gocpp::recv(c->sendq), sglist);
                }
                else
                {
                    dequeueSudoG(gocpp::recv(c->recvq), sglist);
                }
            }
            sgnext = sglist->waitlink;
            sglist->waitlink = nullptr;
            releaseSudog(sglist);
            sglist = sgnext;
        }
        if(cas == nullptr)
        {
            go_throw("selectgo: bad wakeup");
        }
        c = cas->c;
        if(debugSelect)
        {
            print("wait-return: cas0=", cas0, " c=", c, " cas=", cas, " send=", casi < nsends, "\n");
        }
        if(casi < nsends)
        {
            if(! caseSuccess)
            {
                goto sclose;
            }
        }
        else
        {
            recvOK = caseSuccess;
        }
        if(raceenabled)
        {
            if(casi < nsends)
            {
                raceReadObjectPC(c->elemtype, cas->elem, casePC(casi), chansendpc);
            }
            else
            if(cas->elem != nullptr)
            {
                raceWriteObjectPC(c->elemtype, cas->elem, casePC(casi), chanrecvpc);
            }
        }
        if(msanenabled)
        {
            if(casi < nsends)
            {
                msanread(cas->elem, c->elemtype->Size_);
            }
            else
            if(cas->elem != nullptr)
            {
                msanwrite(cas->elem, c->elemtype->Size_);
            }
        }
        if(asanenabled)
        {
            if(casi < nsends)
            {
                asanread(cas->elem, c->elemtype->Size_);
            }
            else
            if(cas->elem != nullptr)
            {
                asanwrite(cas->elem, c->elemtype->Size_);
            }
        }
        selunlock(scases, lockorder);
        goto retc;
        bufrecv:
        if(raceenabled)
        {
            if(cas->elem != nullptr)
            {
                raceWriteObjectPC(c->elemtype, cas->elem, casePC(casi), chanrecvpc);
            }
            racenotify(c, c->recvx, nullptr);
        }
        if(msanenabled && cas->elem != nullptr)
        {
            msanwrite(cas->elem, c->elemtype->Size_);
        }
        if(asanenabled && cas->elem != nullptr)
        {
            asanwrite(cas->elem, c->elemtype->Size_);
        }
        recvOK = true;
        qp = chanbuf(c, c->recvx);
        if(cas->elem != nullptr)
        {
            typedmemmove(c->elemtype, cas->elem, qp);
        }
        typedmemclr(c->elemtype, qp);
        c->recvx++;
        if(c->recvx == c->dataqsiz)
        {
            c->recvx = 0;
        }
        c->qcount--;
        selunlock(scases, lockorder);
        goto retc;
        bufsend:
        if(raceenabled)
        {
            racenotify(c, c->sendx, nullptr);
            raceReadObjectPC(c->elemtype, cas->elem, casePC(casi), chansendpc);
        }
        if(msanenabled)
        {
            msanread(cas->elem, c->elemtype->Size_);
        }
        if(asanenabled)
        {
            asanread(cas->elem, c->elemtype->Size_);
        }
        typedmemmove(c->elemtype, chanbuf(c, c->sendx), cas->elem);
        c->sendx++;
        if(c->sendx == c->dataqsiz)
        {
            c->sendx = 0;
        }
        c->qcount++;
        selunlock(scases, lockorder);
        goto retc;
        recv:
        recv(c, sg, cas->elem, [=]() mutable -> void
        {
            selunlock(scases, lockorder);
        }, 2);
        if(debugSelect)
        {
            print("syncrecv: cas0=", cas0, " c=", c, "\n");
        }
        recvOK = true;
        goto retc;
        rclose:
        selunlock(scases, lockorder);
        recvOK = false;
        if(cas->elem != nullptr)
        {
            typedmemclr(c->elemtype, cas->elem);
        }
        if(raceenabled)
        {
            raceacquire(raceaddr(gocpp::recv(c)));
        }
        goto retc;
        send:
        if(raceenabled)
        {
            raceReadObjectPC(c->elemtype, cas->elem, casePC(casi), chansendpc);
        }
        if(msanenabled)
        {
            msanread(cas->elem, c->elemtype->Size_);
        }
        if(asanenabled)
        {
            asanread(cas->elem, c->elemtype->Size_);
        }
        send(c, sg, cas->elem, [=]() mutable -> void
        {
            selunlock(scases, lockorder);
        }, 2);
        if(debugSelect)
        {
            print("syncsend: cas0=", cas0, " c=", c, "\n");
        }
        goto retc;
        retc:
        if(caseReleaseTime > 0)
        {
            blockevent(caseReleaseTime - t0, 1);
        }
        return {casi, recvOK};
        sclose:
        selunlock(scases, lockorder);
        gocpp::panic(plainError("send on closed channel"));
    }

    uintptr_t sortkey(struct hchan* c)
    {
        return uintptr_t(unsafe::Pointer(c));
    }

    
    template<typename T> requires gocpp::GoStruct<T>
    runtimeSelect::operator T()
    {
        T result;
        result.dir = this->dir;
        result.typ = this->typ;
        result.ch = this->ch;
        result.val = this->val;
        return result;
    }

    template<typename T> requires gocpp::GoStruct<T>
    bool runtimeSelect::operator==(const T& ref) const
    {
        if (dir != ref.dir) return false;
        if (typ != ref.typ) return false;
        if (ch != ref.ch) return false;
        if (val != ref.val) return false;
        return true;
    }

    std::ostream& runtimeSelect::PrintTo(std::ostream& os) const
    {
        os << '{';
        os << "" << dir;
        os << " " << typ;
        os << " " << ch;
        os << " " << val;
        os << '}';
        return os;
    }

    std::ostream& operator<<(std::ostream& os, const struct runtimeSelect& value)
    {
        return value.PrintTo(os);
    }

    std::tuple<int, bool> reflect_rselect(gocpp::slice<runtimeSelect> cases)
    {
        if(len(cases) == 0)
        {
            block();
        }
        auto sel = gocpp::make(gocpp::Tag<gocpp::slice<scase>>(), len(cases));
        auto orig = gocpp::make(gocpp::Tag<gocpp::slice<int>>(), len(cases));
        auto [nsends, nrecvs] = std::tuple{0, 0};
        auto dflt = - 1;
        for(auto [i, rc] : cases)
        {
            int j = {};
            //Go switch emulation
            {
                auto condition = rc.dir;
                int conditionId = -1;
                if(condition == selectDefault) { conditionId = 0; }
                else if(condition == selectSend) { conditionId = 1; }
                else if(condition == selectRecv) { conditionId = 2; }
                switch(conditionId)
                {
                    case 0:
                        dflt = i;
                        continue;
                        break;
                    case 1:
                        j = nsends;
                        nsends++;
                        break;
                    case 2:
                        nrecvs++;
                        j = len(cases) - nrecvs;
                        break;
                }
            }
            sel[j] = gocpp::Init<scase>([](scase& x) { x.c = rc.ch; x.elem = rc.val; });
            orig[j] = i;
        }
        if(nsends + nrecvs == 0)
        {
            return {dflt, false};
        }
        if(nsends + nrecvs < len(cases))
        {
            copy(sel.make_slice(nsends), sel.make_slice(len(cases) - nrecvs));
            copy(orig.make_slice(nsends), orig.make_slice(len(cases) - nrecvs));
        }
        auto order = gocpp::make(gocpp::Tag<gocpp::slice<uint16_t>>(), 2 * (nsends + nrecvs));
        uintptr_t* pc0 = {};
        if(raceenabled)
        {
            auto pcs = gocpp::make(gocpp::Tag<gocpp::slice<uintptr_t>>(), nsends + nrecvs);
            for(auto [i, gocpp_ignored] : pcs)
            {
                selectsetpc(& pcs[i]);
            }
            pc0 = & pcs[0];
        }
        auto [chosen, recvOK] = selectgo(& sel[0], & order[0], pc0, nsends, nrecvs, dflt == - 1);
        if(chosen < 0)
        {
            chosen = dflt;
        }
        else
        {
            chosen = orig[chosen];
        }
        return {chosen, recvOK};
    }

    void dequeueSudoG(struct waitq* q, sudog* sgp)
    {
        auto x = sgp->prev;
        auto y = sgp->next;
        if(x != nullptr)
        {
            if(y != nullptr)
            {
                x->next = y;
                y->prev = x;
                sgp->next = nullptr;
                sgp->prev = nullptr;
                return;
            }
            x->next = nullptr;
            q->last = x;
            sgp->prev = nullptr;
            return;
        }
        if(y != nullptr)
        {
            y->prev = nullptr;
            q->first = y;
            sgp->next = nullptr;
            return;
        }
        if(q->first == sgp)
        {
            q->first = nullptr;
            q->last = nullptr;
        }
    }

}

