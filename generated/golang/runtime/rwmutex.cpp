// generated by GoCpp from file '$(ImportDir)/runtime/rwmutex.go'
#include <complex>
#include <functional>
#include <iostream>
#include <iomanip>
#include <map>
#include <string>
#include <tuple>
#include <vector>

#include "golang/runtime/rwmutex.h"
#include "gocpp/support.h"

#include "golang/internal/abi/type.h"
#include "golang/internal/chacha8rand/chacha8.h"
// #include "golang/runtime/cgocall.h"  [Ignored, known errors]
#include "golang/runtime/chan.h"
#include "golang/runtime/coro.h"
#include "golang/runtime/debuglog_off.h"
#include "golang/runtime/internal/atomic/types.h"
#include "golang/runtime/internal/sys/nih.h"
// #include "golang/runtime/lock_sema.h"  [Ignored, known errors]
// #include "golang/runtime/lockrank.h"  [Ignored, known errors]
// #include "golang/runtime/lockrank_off.h"  [Ignored, known errors]
#include "golang/runtime/mprof.h"
// #include "golang/runtime/os_windows.h"  [Ignored, known errors]
#include "golang/runtime/panic.h"
// #include "golang/runtime/runtime1.h"  [Ignored, known errors]
#include "golang/runtime/runtime2.h"
// #include "golang/runtime/signal_windows.h"  [Ignored, known errors]
// #include "golang/runtime/stubs.h"  [Ignored, known errors]
// #include "golang/runtime/symtab.h"  [Ignored, known errors]
// #include "golang/runtime/time.h"  [Ignored, known errors]
#include "golang/runtime/trace2buf.h"
// #include "golang/runtime/trace2runtime.h"  [Ignored, known errors]
#include "golang/runtime/trace2status.h"
#include "golang/runtime/trace2time.h"

namespace golang::runtime
{
    
    template<typename T> requires gocpp::GoStruct<T>
    rwmutex::operator T()
    {
        T result;
        result.rLock = this->rLock;
        result.readers = this->readers;
        result.readerPass = this->readerPass;
        result.wLock = this->wLock;
        result.writer = this->writer;
        result.readerCount = this->readerCount;
        result.readerWait = this->readerWait;
        result.readRank = this->readRank;
        return result;
    }

    template<typename T> requires gocpp::GoStruct<T>
    bool rwmutex::operator==(const T& ref) const
    {
        if (rLock != ref.rLock) return false;
        if (readers != ref.readers) return false;
        if (readerPass != ref.readerPass) return false;
        if (wLock != ref.wLock) return false;
        if (writer != ref.writer) return false;
        if (readerCount != ref.readerCount) return false;
        if (readerWait != ref.readerWait) return false;
        if (readRank != ref.readRank) return false;
        return true;
    }

    std::ostream& rwmutex::PrintTo(std::ostream& os) const
    {
        os << '{';
        os << "" << rLock;
        os << " " << readers;
        os << " " << readerPass;
        os << " " << wLock;
        os << " " << writer;
        os << " " << readerCount;
        os << " " << readerWait;
        os << " " << readRank;
        os << '}';
        return os;
    }

    std::ostream& operator<<(std::ostream& os, const struct rwmutex& value)
    {
        return value.PrintTo(os);
    }

    void init(struct rwmutex* rw, lockRank readRank, lockRank readRankInternal, lockRank writeRank)
    {
        rw->readRank = readRank;
        lockInit(& rw->rLock, readRankInternal);
        lockInit(& rw->wLock, writeRank);
    }

    void rlock(struct rwmutex* rw)
    {
        acquirem();
        acquireLockRank(rw->readRank);
        lockWithRankMayAcquire(& rw->rLock, getLockRank(& rw->rLock));
        if(Add(gocpp::recv(rw->readerCount), 1) < 0)
        {
            systemstack([=]() mutable -> void
            {
                lock(& rw->rLock);
                if(rw->readerPass > 0)
                {
                    rw->readerPass -= 1;
                    unlock(& rw->rLock);
                }
                else
                {
                    auto m = getg()->m;
                    m->schedlink = rw->readers;
                    set(gocpp::recv(rw->readers), m);
                    unlock(& rw->rLock);
                    notesleep(& m->park);
                    noteclear(& m->park);
                }
            });
        }
    }

    void runlock(struct rwmutex* rw)
    {
        if(auto r = Add(gocpp::recv(rw->readerCount), - 1); r < 0)
        {
            if(r + 1 == 0 || r + 1 == - rwmutexMaxReaders)
            {
                go_throw("runlock of unlocked rwmutex");
            }
            if(Add(gocpp::recv(rw->readerWait), - 1) == 0)
            {
                lock(& rw->rLock);
                auto w = ptr(gocpp::recv(rw->writer));
                if(w != nullptr)
                {
                    notewakeup(& w->park);
                }
                unlock(& rw->rLock);
            }
        }
        releaseLockRank(rw->readRank);
        releasem(getg()->m);
    }

    void lock(struct rwmutex* rw)
    {
        lock(& rw->wLock);
        auto m = getg()->m;
        auto r = Add(gocpp::recv(rw->readerCount), - rwmutexMaxReaders) + rwmutexMaxReaders;
        lock(& rw->rLock);
        if(r != 0 && Add(gocpp::recv(rw->readerWait), r) != 0)
        {
            systemstack([=]() mutable -> void
            {
                set(gocpp::recv(rw->writer), m);
                unlock(& rw->rLock);
                notesleep(& m->park);
                noteclear(& m->park);
            });
        }
        else
        {
            unlock(& rw->rLock);
        }
    }

    void unlock(struct rwmutex* rw)
    {
        auto r = Add(gocpp::recv(rw->readerCount), rwmutexMaxReaders);
        if(r >= rwmutexMaxReaders)
        {
            go_throw("unlock of unlocked rwmutex");
        }
        lock(& rw->rLock);
        for(; ptr(gocpp::recv(rw->readers)) != nullptr; )
        {
            auto reader = ptr(gocpp::recv(rw->readers));
            rw->readers = reader->schedlink;
            set(gocpp::recv(reader->schedlink), nullptr);
            notewakeup(& reader->park);
            r -= 1;
        }
        rw->readerPass += uint32_t(r);
        unlock(& rw->rLock);
        unlock(& rw->wLock);
    }

}

