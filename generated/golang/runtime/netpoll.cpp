// generated by GoCpp from file '$(ImportDir)/runtime/netpoll.go'
#include <complex>
#include <functional>
#include <iostream>
#include <iomanip>
#include <map>
#include <string>
#include <tuple>
#include <vector>

#include "golang/runtime/netpoll.h"
#include "gocpp/support.h"

#include "golang/runtime/internal/atomic/stubs.h"
#include "golang/runtime/internal/atomic/types.h"
#include "golang/runtime/internal/sys/nih.h"
#include "golang/runtime/extern.h"
// #include "golang/runtime/lock_sema.h"  [Ignored, known errors]
// #include "golang/runtime/lockrank.h"  [Ignored, known errors]
// #include "golang/runtime/lockrank_off.h"  [Ignored, known errors]
#include "golang/runtime/malloc.h"
#include "golang/runtime/netpoll_windows.h"
#include "golang/runtime/panic.h"
#include "golang/runtime/proc.h"
#include "golang/runtime/runtime2.h"
// #include "golang/runtime/stubs.h"  [Ignored, known errors]
#include "golang/runtime/tagptr_64bit.h"
#include "golang/runtime/time.h"
#include "golang/runtime/time_nofake.h"
#include "golang/runtime/trace2runtime.h"
#include "golang/runtime/type.h"
#include "golang/unsafe/unsafe.h"

namespace golang::runtime
{
    int pollNoError = 0;
    int pollErrClosing = 1;
    int pollErrTimeout = 2;
    int pollErrNotPollable = 3;
    uintptr_t pdNil = 0;
    uintptr_t pdReady = 1;
    uintptr_t pdWait = 2;
    int pollBlockSize = 4 * 1024;
    
    std::ostream& pollDesc::PrintTo(std::ostream& os) const
    {
        os << '{';
        os << "" << _;
        os << " " << link;
        os << " " << fd;
        os << " " << fdseq;
        os << " " << atomicInfo;
        os << " " << rg;
        os << " " << wg;
        os << " " << lock;
        os << " " << closing;
        os << " " << user;
        os << " " << rseq;
        os << " " << rt;
        os << " " << rd;
        os << " " << wseq;
        os << " " << wt;
        os << " " << wd;
        os << " " << self;
        os << '}';
        return os;
    }

    std::ostream& operator<<(std::ostream& os, const struct pollDesc& value)
    {
        return value.PrintTo(os);
    }

    int pollClosing = 1 << 0;
    int pollEventErr = 1 << 1;
    int pollExpiredReadDeadline = 1 << 2;
    int pollExpiredWriteDeadline = 1 << 3;
    int pollFDSeq = 1 << 4;
    int pollFDSeqBits = 20;
    int pollFDSeqMask = (1 << pollFDSeqBits) - 1;
    bool closing(pollInfo i)
    {
        return i & pollClosing != 0;
    }

    bool eventErr(pollInfo i)
    {
        return i & pollEventErr != 0;
    }

    bool expiredReadDeadline(pollInfo i)
    {
        return i & pollExpiredReadDeadline != 0;
    }

    bool expiredWriteDeadline(pollInfo i)
    {
        return i & pollExpiredWriteDeadline != 0;
    }

    pollInfo info(struct pollDesc* pd)
    {
        return pollInfo(Load(gocpp::recv(pd->atomicInfo)));
    }

    void publishInfo(struct pollDesc* pd)
    {
        uint32_t info = {};
        if(pd->closing)
        {
            info |= pollClosing;
        }
        if(pd->rd < 0)
        {
            info |= pollExpiredReadDeadline;
        }
        if(pd->wd < 0)
        {
            info |= pollExpiredWriteDeadline;
        }
        info |= uint32_t(Load(gocpp::recv(pd->fdseq)) & pollFDSeqMask) << pollFDSeq;
        auto x = Load(gocpp::recv(pd->atomicInfo));
        for(; ! CompareAndSwap(gocpp::recv(pd->atomicInfo), x, (x & pollEventErr) | info); )
        {
            x = Load(gocpp::recv(pd->atomicInfo));
        }
    }

    void setEventErr(struct pollDesc* pd, bool b, uintptr_t seq)
    {
        auto mSeq = uint32_t(seq & pollFDSeqMask);
        auto x = Load(gocpp::recv(pd->atomicInfo));
        auto xSeq = (x >> pollFDSeq) & pollFDSeqMask;
        if(seq != 0 && xSeq != mSeq)
        {
            return;
        }
        for(; (x & pollEventErr != 0) != b && ! CompareAndSwap(gocpp::recv(pd->atomicInfo), x, x ^ pollEventErr); )
        {
            x = Load(gocpp::recv(pd->atomicInfo));
            auto xSeq = (x >> pollFDSeq) & pollFDSeqMask;
            if(seq != 0 && xSeq != mSeq)
            {
                return;
            }
        }
    }

    
    std::ostream& pollCache::PrintTo(std::ostream& os) const
    {
        os << '{';
        os << "" << lock;
        os << " " << first;
        os << '}';
        return os;
    }

    std::ostream& operator<<(std::ostream& os, const struct pollCache& value)
    {
        return value.PrintTo(os);
    }

    mutex netpollInitLock;
    atomic::Uint32 netpollInited;
    pollCache pollcache;
    atomic::Uint32 netpollWaiters;
    void poll_runtime_pollServerInit()
    {
        netpollGenericInit();
    }

    void netpollGenericInit()
    {
        if(Load(gocpp::recv(netpollInited)) == 0)
        {
            lockInit(& netpollInitLock, lockRankNetpollInit);
            lock(& netpollInitLock);
            if(Load(gocpp::recv(netpollInited)) == 0)
            {
                netpollinit();
                Store(gocpp::recv(netpollInited), 1);
            }
            unlock(& netpollInitLock);
        }
    }

    bool netpollinited()
    {
        return Load(gocpp::recv(netpollInited)) != 0;
    }

    bool poll_runtime_isPollServerDescriptor(uintptr_t fd)
    {
        return netpollIsPollDescriptor(fd);
    }

    std::tuple<pollDesc*, int> poll_runtime_pollOpen(uintptr_t fd)
    {
        auto pd = alloc(gocpp::recv(pollcache));
        lock(& pd->lock);
        auto wg = Load(gocpp::recv(pd->wg));
        if(wg != pdNil && wg != pdReady)
        {
            go_throw("runtime: blocked write on free polldesc");
        }
        auto rg = Load(gocpp::recv(pd->rg));
        if(rg != pdNil && rg != pdReady)
        {
            go_throw("runtime: blocked read on free polldesc");
        }
        pd->fd = fd;
        if(Load(gocpp::recv(pd->fdseq)) == 0)
        {
            Store(gocpp::recv(pd->fdseq), 1);
        }
        pd->closing = false;
        setEventErr(gocpp::recv(pd), false, 0);
        pd->rseq++;
        Store(gocpp::recv(pd->rg), pdNil);
        pd->rd = 0;
        pd->wseq++;
        Store(gocpp::recv(pd->wg), pdNil);
        pd->wd = 0;
        pd->self = pd;
        publishInfo(gocpp::recv(pd));
        unlock(& pd->lock);
        auto errno = netpollopen(fd, pd);
        if(errno != 0)
        {
            free(gocpp::recv(pollcache), pd);
            return {nullptr, int(errno)};
        }
        return {pd, 0};
    }

    void poll_runtime_pollClose(pollDesc* pd)
    {
        if(! pd->closing)
        {
            go_throw("runtime: close polldesc w/o unblock");
        }
        auto wg = Load(gocpp::recv(pd->wg));
        if(wg != pdNil && wg != pdReady)
        {
            go_throw("runtime: blocked write on closing polldesc");
        }
        auto rg = Load(gocpp::recv(pd->rg));
        if(rg != pdNil && rg != pdReady)
        {
            go_throw("runtime: blocked read on closing polldesc");
        }
        netpollclose(pd->fd);
        free(gocpp::recv(pollcache), pd);
    }

    void free(struct pollCache* c, pollDesc* pd)
    {
        lock(& pd->lock);
        auto fdseq = Load(gocpp::recv(pd->fdseq));
        fdseq = (fdseq + 1) & ((1 << taggedPointerBits) - 1);
        Store(gocpp::recv(pd->fdseq), fdseq);
        publishInfo(gocpp::recv(pd));
        unlock(& pd->lock);
        lock(& c->lock);
        pd->link = c->first;
        c->first = pd;
        unlock(& c->lock);
    }

    int poll_runtime_pollReset(pollDesc* pd, int mode)
    {
        auto errcode = netpollcheckerr(pd, int32(mode));
        if(errcode != pollNoError)
        {
            return errcode;
        }
        if(mode == 'r')
        {
            Store(gocpp::recv(pd->rg), pdNil);
        }
        else
        if(mode == 'w')
        {
            Store(gocpp::recv(pd->wg), pdNil);
        }
        return pollNoError;
    }

    int poll_runtime_pollWait(pollDesc* pd, int mode)
    {
        auto errcode = netpollcheckerr(pd, int32(mode));
        if(errcode != pollNoError)
        {
            return errcode;
        }
        if(GOOS == "solaris" || GOOS == "illumos" || GOOS == "aix" || GOOS == "wasip1")
        {
            netpollarm(pd, mode);
        }
        for(; ! netpollblock(pd, int32(mode), false); )
        {
            errcode = netpollcheckerr(pd, int32(mode));
            if(errcode != pollNoError)
            {
                return errcode;
            }
        }
        return pollNoError;
    }

    void poll_runtime_pollWaitCanceled(pollDesc* pd, int mode)
    {
        for(; ! netpollblock(pd, int32(mode), true); )
        {
        }
    }

    void poll_runtime_pollSetDeadline(pollDesc* pd, int64_t d, int mode)
    {
        lock(& pd->lock);
        if(pd->closing)
        {
            unlock(& pd->lock);
            return;
        }
        auto [rd0, wd0] = std::tuple{pd->rd, pd->wd};
        auto combo0 = rd0 > 0 && rd0 == wd0;
        if(d > 0)
        {
            d += nanotime();
            if(d <= 0)
            {
                d = (1 << 63) - 1;
            }
        }
        if(mode == 'r' || mode == 'r' + 'w')
        {
            pd->rd = d;
        }
        if(mode == 'w' || mode == 'r' + 'w')
        {
            pd->wd = d;
        }
        publishInfo(gocpp::recv(pd));
        auto combo = pd->rd > 0 && pd->rd == pd->wd;
        auto rtf = netpollReadDeadline;
        if(combo)
        {
            rtf = netpollDeadline;
        }
        if(pd->rt.f == nullptr)
        {
            if(pd->rd > 0)
            {
                pd->rt.f = rtf;
                pd->rt.arg = makeArg(gocpp::recv(pd));
                pd->rt.seq = pd->rseq;
                resettimer(& pd->rt, pd->rd);
            }
        }
        else
        if(pd->rd != rd0 || combo != combo0)
        {
            pd->rseq++;
            if(pd->rd > 0)
            {
                modtimer(& pd->rt, pd->rd, 0, rtf, makeArg(gocpp::recv(pd)), pd->rseq);
            }
            else
            {
                deltimer(& pd->rt);
                pd->rt.f = nullptr;
            }
        }
        if(pd->wt.f == nullptr)
        {
            if(pd->wd > 0 && ! combo)
            {
                pd->wt.f = netpollWriteDeadline;
                pd->wt.arg = makeArg(gocpp::recv(pd));
                pd->wt.seq = pd->wseq;
                resettimer(& pd->wt, pd->wd);
            }
        }
        else
        if(pd->wd != wd0 || combo != combo0)
        {
            pd->wseq++;
            if(pd->wd > 0 && ! combo)
            {
                modtimer(& pd->wt, pd->wd, 0, netpollWriteDeadline, makeArg(gocpp::recv(pd)), pd->wseq);
            }
            else
            {
                deltimer(& pd->wt);
                pd->wt.f = nullptr;
            }
        }
        auto delta = int32(0);
        g* rg = {};
        g* wg = {};
        if(pd->rd < 0)
        {
            rg = netpollunblock(pd, 'r', false, & delta);
        }
        if(pd->wd < 0)
        {
            wg = netpollunblock(pd, 'w', false, & delta);
        }
        unlock(& pd->lock);
        if(rg != nullptr)
        {
            netpollgoready(rg, 3);
        }
        if(wg != nullptr)
        {
            netpollgoready(wg, 3);
        }
        netpollAdjustWaiters(delta);
    }

    void poll_runtime_pollUnblock(pollDesc* pd)
    {
        lock(& pd->lock);
        if(pd->closing)
        {
            go_throw("runtime: unblock on closing polldesc");
        }
        pd->closing = true;
        pd->rseq++;
        pd->wseq++;
        g* rg = {};
        g* wg = {};
        publishInfo(gocpp::recv(pd));
        auto delta = int32(0);
        rg = netpollunblock(pd, 'r', false, & delta);
        wg = netpollunblock(pd, 'w', false, & delta);
        if(pd->rt.f != nullptr)
        {
            deltimer(& pd->rt);
            pd->rt.f = nullptr;
        }
        if(pd->wt.f != nullptr)
        {
            deltimer(& pd->wt);
            pd->wt.f = nullptr;
        }
        unlock(& pd->lock);
        if(rg != nullptr)
        {
            netpollgoready(rg, 3);
        }
        if(wg != nullptr)
        {
            netpollgoready(wg, 3);
        }
        netpollAdjustWaiters(delta);
    }

    int32_t netpollready(gList* toRun, pollDesc* pd, int32_t mode)
    {
        auto delta = int32(0);
        g* rg = {};
        g* wg = {};
        if(mode == 'r' || mode == 'r' + 'w')
        {
            rg = netpollunblock(pd, 'r', true, & delta);
        }
        if(mode == 'w' || mode == 'r' + 'w')
        {
            wg = netpollunblock(pd, 'w', true, & delta);
        }
        if(rg != nullptr)
        {
            push(gocpp::recv(toRun), rg);
        }
        if(wg != nullptr)
        {
            push(gocpp::recv(toRun), wg);
        }
        return delta;
    }

    int netpollcheckerr(pollDesc* pd, int32_t mode)
    {
        auto info = info(gocpp::recv(pd));
        if(closing(gocpp::recv(info)))
        {
            return pollErrClosing;
        }
        if((mode == 'r' && expiredReadDeadline(gocpp::recv(info))) || (mode == 'w' && expiredWriteDeadline(gocpp::recv(info))))
        {
            return pollErrTimeout;
        }
        if(mode == 'r' && eventErr(gocpp::recv(info)))
        {
            return pollErrNotPollable;
        }
        return pollNoError;
    }

    bool netpollblockcommit(g* gp, unsafe::Pointer gpp)
    {
        auto r = Casuintptr(gocpp::recv(atomic), (*uintptr)(gpp), pdWait, uintptr(Pointer(gocpp::recv(unsafe), gp)));
        if(r)
        {
            netpollAdjustWaiters(1);
        }
        return r;
    }

    void netpollgoready(g* gp, int traceskip)
    {
        goready(gp, traceskip + 1);
    }

    bool netpollblock(pollDesc* pd, int32_t mode, bool waitio)
    {
        auto gpp = & pd->rg;
        if(mode == 'w')
        {
            gpp = & pd->wg;
        }
        for(; ; )
        {
            if(CompareAndSwap(gocpp::recv(gpp), pdReady, pdNil))
            {
                return true;
            }
            if(CompareAndSwap(gocpp::recv(gpp), pdNil, pdWait))
            {
                break;
            }
            if(auto v = Load(gocpp::recv(gpp)); v != pdReady && v != pdNil)
            {
                go_throw("runtime: double wait");
            }
        }
        if(waitio || netpollcheckerr(pd, mode) == pollNoError)
        {
            gopark(netpollblockcommit, Pointer(gocpp::recv(unsafe), gpp), waitReasonIOWait, traceBlockNet, 5);
        }
        auto old = Swap(gocpp::recv(gpp), pdNil);
        if(old > pdWait)
        {
            go_throw("runtime: corrupted polldesc");
        }
        return old == pdReady;
    }

    g* netpollunblock(pollDesc* pd, int32_t mode, bool ioready, int32_t* delta)
    {
        auto gpp = & pd->rg;
        if(mode == 'w')
        {
            gpp = & pd->wg;
        }
        for(; ; )
        {
            auto old = Load(gocpp::recv(gpp));
            if(old == pdReady)
            {
                return nullptr;
            }
            if(old == pdNil && ! ioready)
            {
                return nullptr;
            }
            auto go_new = pdNil;
            if(ioready)
            {
                go_new = pdReady;
            }
            if(CompareAndSwap(gocpp::recv(gpp), old, go_new))
            {
                if(old == pdWait)
                {
                    old = pdNil;
                }
                else
                if(old != pdNil)
                {
                    *delta -= 1;
                }
                return (*g)(Pointer(gocpp::recv(unsafe), old));
            }
        }
    }

    void netpolldeadlineimpl(pollDesc* pd, uintptr_t seq, bool read, bool write)
    {
        lock(& pd->lock);
        auto currentSeq = pd->rseq;
        if(! read)
        {
            currentSeq = pd->wseq;
        }
        if(seq != currentSeq)
        {
            unlock(& pd->lock);
            return;
        }
        auto delta = int32(0);
        g* rg = {};
        if(read)
        {
            if(pd->rd <= 0 || pd->rt.f == nullptr)
            {
                go_throw("runtime: inconsistent read deadline");
            }
            pd->rd = - 1;
            publishInfo(gocpp::recv(pd));
            rg = netpollunblock(pd, 'r', false, & delta);
        }
        g* wg = {};
        if(write)
        {
            if(pd->wd <= 0 || pd->wt.f == nullptr && ! read)
            {
                go_throw("runtime: inconsistent write deadline");
            }
            pd->wd = - 1;
            publishInfo(gocpp::recv(pd));
            wg = netpollunblock(pd, 'w', false, & delta);
        }
        unlock(& pd->lock);
        if(rg != nullptr)
        {
            netpollgoready(rg, 0);
        }
        if(wg != nullptr)
        {
            netpollgoready(wg, 0);
        }
        netpollAdjustWaiters(delta);
    }

    void netpollDeadline(go_any arg, uintptr_t seq)
    {
        netpolldeadlineimpl(gocpp::getValue<runtime.pollDesc*>(arg), seq, true, true);
    }

    void netpollReadDeadline(go_any arg, uintptr_t seq)
    {
        netpolldeadlineimpl(gocpp::getValue<runtime.pollDesc*>(arg), seq, true, false);
    }

    void netpollWriteDeadline(go_any arg, uintptr_t seq)
    {
        netpolldeadlineimpl(gocpp::getValue<runtime.pollDesc*>(arg), seq, false, true);
    }

    bool netpollAnyWaiters()
    {
        return Load(gocpp::recv(netpollWaiters)) > 0;
    }

    void netpollAdjustWaiters(int32_t delta)
    {
        if(delta != 0)
        {
            Add(gocpp::recv(netpollWaiters), delta);
        }
    }

    pollDesc* alloc(struct pollCache* c)
    {
        lock(& c->lock);
        if(c->first == nullptr)
        {
            auto pdSize = Sizeof(gocpp::recv(unsafe), pollDesc {});
            auto n = pollBlockSize / pdSize;
            if(n == 0)
            {
                n = 1;
            }
            auto mem = persistentalloc(n * pdSize, 0, & memstats.other_sys);
            for(auto i = uintptr(0); i < n; i++)
            {
                auto pd = (*pollDesc)(add(mem, i * pdSize));
                pd->link = c->first;
                c->first = pd;
            }
        }
        auto pd = c->first;
        c->first = pd->link;
        lockInit(& pd->lock, lockRankPollDesc);
        unlock(& c->lock);
        return pd;
    }

    go_any makeArg(struct pollDesc* pd)
    {
        go_any i;
        auto x = (*eface)(Pointer(gocpp::recv(unsafe), & i));
        x->_type = pdType;
        x->data = Pointer(gocpp::recv(unsafe), & pd->self);
        return i;
    }

    go_any pdEface = (*pollDesc)(nullptr);
    _type* pdType = efaceOf(& pdEface)->_type;
}
