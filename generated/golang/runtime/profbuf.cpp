// generated by GoCpp from file '$(ImportDir)/runtime/profbuf.go'
#include <complex>
#include <functional>
#include <iostream>
#include <iomanip>
#include <map>
#include <string>
#include <tuple>
#include <vector>

#include "golang/runtime/profbuf.h"
#include "gocpp/support.h"

#include "golang/runtime/internal/atomic/atomic_amd64.h"
#include "golang/runtime/internal/atomic/types.h"
// #include "golang/runtime/lock_sema.h"  [Ignored, known errors]
#include "golang/runtime/panic.h"
#include "golang/runtime/race0.h"
#include "golang/runtime/runtime2.h"
#include "golang/unsafe/unsafe.h"

namespace golang::runtime
{
    
    template<typename T> requires gocpp::GoStruct<T>
    profBuf::operator T()
    {
        T result;
        result.r = this->r;
        result.w = this->w;
        result.overflow = this->overflow;
        result.overflowTime = this->overflowTime;
        result.eof = this->eof;
        result.hdrsize = this->hdrsize;
        result.data = this->data;
        result.tags = this->tags;
        result.rNext = this->rNext;
        result.overflowBuf = this->overflowBuf;
        result.wait = this->wait;
        return result;
    }

    template<typename T> requires gocpp::GoStruct<T>
    bool profBuf::operator==(const T& ref) const
    {
        if (r != ref.r) return false;
        if (w != ref.w) return false;
        if (overflow != ref.overflow) return false;
        if (overflowTime != ref.overflowTime) return false;
        if (eof != ref.eof) return false;
        if (hdrsize != ref.hdrsize) return false;
        if (data != ref.data) return false;
        if (tags != ref.tags) return false;
        if (rNext != ref.rNext) return false;
        if (overflowBuf != ref.overflowBuf) return false;
        if (wait != ref.wait) return false;
        return true;
    }

    std::ostream& profBuf::PrintTo(std::ostream& os) const
    {
        os << '{';
        os << "" << r;
        os << " " << w;
        os << " " << overflow;
        os << " " << overflowTime;
        os << " " << eof;
        os << " " << hdrsize;
        os << " " << data;
        os << " " << tags;
        os << " " << rNext;
        os << " " << overflowBuf;
        os << " " << wait;
        os << '}';
        return os;
    }

    std::ostream& operator<<(std::ostream& os, const struct profBuf& value)
    {
        return value.PrintTo(os);
    }

    profIndex load(profAtomic* x)
    {
        return profIndex(atomic::Load64((uint64_t*)(x)));
    }

    void store(profAtomic* x, profIndex go_new)
    {
        atomic::Store64((uint64_t*)(x), uint64_t(go_new));
    }

    bool cas(profAtomic* x, profIndex old, profIndex go_new)
    {
        return atomic::Cas64((uint64_t*)(x), uint64_t(old), uint64_t(go_new));
    }

    uint32_t dataCount(profIndex x)
    {
        return uint32_t(x);
    }

    uint32_t tagCount(profIndex x)
    {
        return uint32_t(x >> 34);
    }

    int countSub(uint32_t x, uint32_t y)
    {
        return int((int32_t(x - y) << 2) >> 2);
    }

    profIndex addCountsAndClearFlags(profIndex x, int data, int tag)
    {
        return profIndex((((uint64_t(x) >> 34) + uint64_t((uint32_t(tag) << 2) >> 2)) << 34) | uint64_t(uint32_t(x) + uint32_t(data)));
    }

    bool hasOverflow(struct profBuf* b)
    {
        return uint32_t(Load(gocpp::recv(b->overflow))) > 0;
    }

    std::tuple<uint32_t, uint64_t> takeOverflow(struct profBuf* b)
    {
        uint32_t count;
        uint64_t time;
        auto overflow = Load(gocpp::recv(b->overflow));
        time = Load(gocpp::recv(b->overflowTime));
        for(; ; )
        {
            uint32_t count;
            uint64_t time;
            count = uint32_t(overflow);
            if(count == 0)
            {
                uint32_t count;
                uint64_t time;
                time = 0;
                break;
            }
            if(CompareAndSwap(gocpp::recv(b->overflow), overflow, ((overflow >> 32) + 1) << 32))
            {
                uint32_t count;
                uint64_t time;
                break;
            }
            overflow = Load(gocpp::recv(b->overflow));
            time = Load(gocpp::recv(b->overflowTime));
        }
        return {uint32_t(overflow), time};
    }

    void incrementOverflow(struct profBuf* b, int64_t now)
    {
        for(; ; )
        {
            auto overflow = Load(gocpp::recv(b->overflow));
            if(uint32_t(overflow) == 0)
            {
                Store(gocpp::recv(b->overflowTime), uint64_t(now));
                Store(gocpp::recv(b->overflow), (((overflow >> 32) + 1) << 32) + 1);
                break;
            }
            if(int32_t(overflow) == - 1)
            {
                break;
            }
            if(CompareAndSwap(gocpp::recv(b->overflow), overflow, overflow + 1))
            {
                break;
            }
        }
    }

    profBuf* newProfBuf(int hdrsize, int bufwords, int tags)
    {
        if(auto min = 2 + hdrsize + 1; bufwords < min)
        {
            bufwords = min;
        }
        if(bufwords >= (1 << 28) || tags >= (1 << 28))
        {
            go_throw("newProfBuf: buffer too large");
        }
        int i = {};
        for(i = 1; i < bufwords; i <<= 1)
        {
        }
        bufwords = i;
        for(i = 1; i < tags; i <<= 1)
        {
        }
        tags = i;
        auto b = go_new(profBuf);
        b->hdrsize = uintptr_t(hdrsize);
        b->data = gocpp::make(gocpp::Tag<gocpp::slice<uint64_t>>(), bufwords);
        b->tags = gocpp::make(gocpp::Tag<gocpp::slice<unsafe::Pointer>>(), tags);
        b->overflowBuf = gocpp::make(gocpp::Tag<gocpp::slice<uint64_t>>(), 2 + b->hdrsize + 1);
        return b;
    }

    bool canWriteRecord(struct profBuf* b, int nstk)
    {
        auto br = load(gocpp::recv(b->r));
        auto bw = load(gocpp::recv(b->w));
        if(countSub(tagCount(gocpp::recv(br)), tagCount(gocpp::recv(bw))) + len(b->tags) < 1)
        {
            return false;
        }
        auto nd = countSub(dataCount(gocpp::recv(br)), dataCount(gocpp::recv(bw))) + len(b->data);
        auto want = 2 + int(b->hdrsize) + nstk;
        auto i = int(dataCount(gocpp::recv(bw)) % uint32_t(len(b->data)));
        if(i + want > len(b->data))
        {
            nd -= len(b->data) - i;
        }
        return nd >= want;
    }

    bool canWriteTwoRecords(struct profBuf* b, int nstk1, int nstk2)
    {
        auto br = load(gocpp::recv(b->r));
        auto bw = load(gocpp::recv(b->w));
        if(countSub(tagCount(gocpp::recv(br)), tagCount(gocpp::recv(bw))) + len(b->tags) < 2)
        {
            return false;
        }
        auto nd = countSub(dataCount(gocpp::recv(br)), dataCount(gocpp::recv(bw))) + len(b->data);
        auto want = 2 + int(b->hdrsize) + nstk1;
        auto i = int(dataCount(gocpp::recv(bw)) % uint32_t(len(b->data)));
        if(i + want > len(b->data))
        {
            nd -= len(b->data) - i;
            i = 0;
        }
        i += want;
        nd -= want;
        want = 2 + int(b->hdrsize) + nstk2;
        if(i + want > len(b->data))
        {
            nd -= len(b->data) - i;
            i = 0;
        }
        return nd >= want;
    }

    void write(struct profBuf* b, unsafe::Pointer* tagPtr, int64_t now, gocpp::slice<uint64_t> hdr, gocpp::slice<uintptr_t> stk)
    {
        if(b == nullptr)
        {
            return;
        }
        if(len(hdr) > int(b->hdrsize))
        {
            go_throw("misuse of profBuf.write");
        }
        if(auto hasOverflow = hasOverflow(gocpp::recv(b)); hasOverflow && canWriteTwoRecords(gocpp::recv(b), 1, len(stk)))
        {
            auto [count, time] = takeOverflow(gocpp::recv(b));
            if(count > 0)
            {
                gocpp::array<uintptr_t, 1> stk = {};
                stk[0] = uintptr_t(count);
                write(gocpp::recv(b), nullptr, int64_t(time), nullptr, stk.make_slice(0, ));
            }
        }
        else
        if(hasOverflow || ! canWriteRecord(gocpp::recv(b), len(stk)))
        {
            incrementOverflow(gocpp::recv(b), now);
            wakeupExtra(gocpp::recv(b));
            return;
        }
        auto br = load(gocpp::recv(b->r));
        auto bw = load(gocpp::recv(b->w));
        auto wt = int(tagCount(gocpp::recv(bw)) % uint32_t(len(b->tags)));
        if(tagPtr != nullptr)
        {
            *(uintptr_t*)(unsafe::Pointer(& b->tags[wt])) = uintptr_t(*tagPtr);
        }
        auto wd = int(dataCount(gocpp::recv(bw)) % uint32_t(len(b->data)));
        auto nd = countSub(dataCount(gocpp::recv(br)), dataCount(gocpp::recv(bw))) + len(b->data);
        auto skip = 0;
        if(wd + 2 + int(b->hdrsize) + len(stk) > len(b->data))
        {
            b->data[wd] = 0;
            skip = len(b->data) - wd;
            nd -= skip;
            wd = 0;
        }
        auto data = b->data.make_slice(wd);
        data[0] = uint64_t(2 + b->hdrsize + uintptr_t(len(stk)));
        data[1] = uint64_t(now);
        auto i = uintptr_t(copy(data.make_slice(2, 2 + b->hdrsize), hdr));
        for(; i < b->hdrsize; i++)
        {
            data[2 + i] = 0;
        }
        for(auto [i, pc] : stk)
        {
            data[2 + b->hdrsize + uintptr_t(i)] = uint64_t(pc);
        }
        for(; ; )
        {
            auto old = load(gocpp::recv(b->w));
            auto go_new = addCountsAndClearFlags(gocpp::recv(old), skip + 2 + len(stk) + int(b->hdrsize), 1);
            if(! cas(gocpp::recv(b->w), old, go_new))
            {
                continue;
            }
            if(old & profReaderSleeping != 0)
            {
                notewakeup(& b->wait);
            }
            break;
        }
    }

    void close(struct profBuf* b)
    {
        if(Load(gocpp::recv(b->eof)) > 0)
        {
            go_throw("runtime: profBuf already closed");
        }
        Store(gocpp::recv(b->eof), 1);
        wakeupExtra(gocpp::recv(b));
    }

    void wakeupExtra(struct profBuf* b)
    {
        for(; ; )
        {
            auto old = load(gocpp::recv(b->w));
            auto go_new = old | profWriteExtra;
            if(! cas(gocpp::recv(b->w), old, go_new))
            {
                continue;
            }
            if(old & profReaderSleeping != 0)
            {
                notewakeup(& b->wait);
            }
            break;
        }
    }

    gocpp::array<unsafe::Pointer, 1> overflowTag;
    std::tuple<gocpp::slice<uint64_t>, gocpp::slice<unsafe::Pointer>, bool> read(struct profBuf* b, profBufReadMode mode)
    {
        gocpp::slice<uint64_t> data;
        gocpp::slice<unsafe::Pointer> tags;
        bool eof;
        if(b == nullptr)
        {
            gocpp::slice<uint64_t> data;
            gocpp::slice<unsafe::Pointer> tags;
            bool eof;
            return {nullptr, nullptr, true};
        }
        auto br = b->rNext;
        auto rPrev = load(gocpp::recv(b->r));
        if(rPrev != br)
        {
            gocpp::slice<uint64_t> data;
            gocpp::slice<unsafe::Pointer> tags;
            bool eof;
            auto ntag = countSub(tagCount(gocpp::recv(br)), tagCount(gocpp::recv(rPrev)));
            auto ti = int(tagCount(gocpp::recv(rPrev)) % uint32_t(len(b->tags)));
            for(auto i = 0; i < ntag; i++)
            {
                gocpp::slice<uint64_t> data;
                gocpp::slice<unsafe::Pointer> tags;
                bool eof;
                b->tags[ti] = nullptr;
                if(ti++; ti == len(b->tags))
                {
                    gocpp::slice<uint64_t> data;
                    gocpp::slice<unsafe::Pointer> tags;
                    bool eof;
                    ti = 0;
                }
            }
            store(gocpp::recv(b->r), br);
        }
        Read:
        auto bw = load(gocpp::recv(b->w));
        auto numData = countSub(dataCount(gocpp::recv(bw)), dataCount(gocpp::recv(br)));
        if(numData == 0)
        {
            gocpp::slice<uint64_t> data;
            gocpp::slice<unsafe::Pointer> tags;
            bool eof;
            if(hasOverflow(gocpp::recv(b)))
            {
                gocpp::slice<uint64_t> data;
                gocpp::slice<unsafe::Pointer> tags;
                bool eof;
                auto [count, time] = takeOverflow(gocpp::recv(b));
                if(count == 0)
                {
                    gocpp::slice<uint64_t> data;
                    gocpp::slice<unsafe::Pointer> tags;
                    bool eof;
                    goto Read;
                }
                auto dst = b->overflowBuf;
                dst[0] = uint64_t(2 + b->hdrsize + 1);
                dst[1] = time;
                for(auto i = uintptr_t(0); i < b->hdrsize; i++)
                {
                    gocpp::slice<uint64_t> data;
                    gocpp::slice<unsafe::Pointer> tags;
                    bool eof;
                    dst[2 + i] = 0;
                }
                dst[2 + b->hdrsize] = uint64_t(count);
                return {dst.make_slice(0, 2 + b->hdrsize + 1), overflowTag.make_slice(0, 1), false};
            }
            if(Load(gocpp::recv(b->eof)) > 0)
            {
                gocpp::slice<uint64_t> data;
                gocpp::slice<unsafe::Pointer> tags;
                bool eof;
                return {nullptr, nullptr, true};
            }
            if(bw & profWriteExtra != 0)
            {
                gocpp::slice<uint64_t> data;
                gocpp::slice<unsafe::Pointer> tags;
                bool eof;
                cas(gocpp::recv(b->w), bw, bw &^ profWriteExtra);
                goto Read;
            }
            if(mode == profBufNonBlocking)
            {
                gocpp::slice<uint64_t> data;
                gocpp::slice<unsafe::Pointer> tags;
                bool eof;
                return {nullptr, nullptr, false};
            }
            if(! cas(gocpp::recv(b->w), bw, bw | profReaderSleeping))
            {
                gocpp::slice<uint64_t> data;
                gocpp::slice<unsafe::Pointer> tags;
                bool eof;
                goto Read;
            }
            notetsleepg(& b->wait, - 1);
            noteclear(& b->wait);
            goto Read;
        }
        data = b->data.make_slice(dataCount(gocpp::recv(br)) % uint32_t(len(b->data)));
        if(len(data) > numData)
        {
            gocpp::slice<uint64_t> data;
            gocpp::slice<unsafe::Pointer> tags;
            bool eof;
            data = data.make_slice(0, numData);
        }
        else
        {
            gocpp::slice<uint64_t> data;
            gocpp::slice<unsafe::Pointer> tags;
            bool eof;
            numData -= len(data);
        }
        auto skip = 0;
        if(data[0] == 0)
        {
            gocpp::slice<uint64_t> data;
            gocpp::slice<unsafe::Pointer> tags;
            bool eof;
            skip = len(data);
            data = b->data;
            if(len(data) > numData)
            {
                gocpp::slice<uint64_t> data;
                gocpp::slice<unsafe::Pointer> tags;
                bool eof;
                data = data.make_slice(0, numData);
            }
        }
        auto ntag = countSub(tagCount(gocpp::recv(bw)), tagCount(gocpp::recv(br)));
        if(ntag == 0)
        {
            gocpp::slice<uint64_t> data;
            gocpp::slice<unsafe::Pointer> tags;
            bool eof;
            go_throw("runtime: malformed profBuf buffer - tag and data out of sync");
        }
        tags = b->tags.make_slice(tagCount(gocpp::recv(br)) % uint32_t(len(b->tags)));
        if(len(tags) > ntag)
        {
            gocpp::slice<uint64_t> data;
            gocpp::slice<unsafe::Pointer> tags;
            bool eof;
            tags = tags.make_slice(0, ntag);
        }
        auto di = 0;
        auto ti = 0;
        for(; di < len(data) && data[di] != 0 && ti < len(tags); )
        {
            gocpp::slice<uint64_t> data;
            gocpp::slice<unsafe::Pointer> tags;
            bool eof;
            if(uintptr_t(di) + uintptr_t(data[di]) > uintptr_t(len(data)))
            {
                gocpp::slice<uint64_t> data;
                gocpp::slice<unsafe::Pointer> tags;
                bool eof;
                go_throw("runtime: malformed profBuf buffer - invalid size");
            }
            di += int(data[di]);
            ti++;
        }
        b->rNext = addCountsAndClearFlags(gocpp::recv(br), skip + di, ti);
        if(raceenabled)
        {
            gocpp::slice<uint64_t> data;
            gocpp::slice<unsafe::Pointer> tags;
            bool eof;
            raceacquire(unsafe::Pointer(& labelSync));
        }
        return {data.make_slice(0, di), tags.make_slice(0, ti), false};
    }

}

