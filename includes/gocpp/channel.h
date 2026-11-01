#pragma once


#include "gocpp/support.fwd.h"

#include "gocpp/common.h"

#include <atomic>
#include <iostream>
#include <utility>
#include <string>

#include "thread_pool/thread_pool.h"

namespace gocpp
{
    template <typename T>
    class channelImpl
    {
    private:
        dp::thread_safe_queue<T> mQueue;
        std::atomic_bool mOpen;
        int mCapacity; // No used at the moment
        int sync = 0;

    public:
        channelImpl(int capacity = 0)
        {
            mCapacity = capacity;
            mOpen.store(true);
        }

        ~channelImpl()
        {
            close();
        }

        int capacity() const
        {
            return mCapacity;
        }

        void close()
        {
            mOpen.store(false);
        }

        bool isOpen() const
        {
            return mOpen || !mQueue.empty();
        }

        void send(T val)
        {
            if (!mOpen)
            {
                panic("send attempt while closed");
            }
            mQueue.push_back(std::move(val));
        }

        // TODO: wait when capacity reached
        bool trySend(T val)
        { 
            //hack to not block select statements            
            ++sync;
            if(sync%2 == 0)
            {
                send(val);
                return true;
            }

            return false;
        }

        std::pair<T, bool> receive()
        {
            // TODO use condition variable
            while (isOpen())
            {
                auto optVal = mQueue.pop_front();
                if (optVal.has_value())
                {
                    return {optVal.value(), optVal.has_value()};
                }

                std::this_thread::yield();
            }
            return {};
        }

        std::pair<T, bool> tryReceive()
        {
            if (isOpen())
            {
                auto optVal = mQueue.pop_front();
                if (optVal.has_value())
                {
                    return {optVal.value(), optVal.has_value()};
                }
            }
            return {};
        }
    };

    template <typename T, typename Error>
    struct result_or_error : std::pair<T, bool>
    {
        result_or_error() {}
        result_or_error(const std::pair<T, bool>& src) : std::pair<T, bool>(src) {}

        operator const T() const 
        {
            if(!this->second)
                panic(Error::error_message());

            return this->first;
        }

        auto operator->() noexcept -> decltype(std::get<0>(*this))
        {
            return std::get<0>(*this);
        }
    };

    struct ErrNoValueInChannel
    {
        static std::string error_message() { return "no value in channel"; }
    };

    template <typename T>
    class channel
    {
    private:
        std::shared_ptr<channelImpl<T>> mImpl;

    public:
        channel() : mImpl(std::make_shared<channelImpl<T>>()) {}

        channel(nullptr_t) : mImpl(nullptr) {}

        // TODO: use capacity
        channel(int capacity) : mImpl(std::make_shared<channelImpl<T>>(capacity)) {}

        inline friend bool operator==(const channel<T>& lhs, const channel<T> rhs)
        {
            return lhs.mImpl.get() == rhs.mImpl.get();
        }

        bool is_nil() const
        {
            return mImpl == nullptr;
        }

        const void* address() const
        {
            return mImpl.get();
        }

        struct channel_iterator
        {
            channel<T> chan;
            std::optional<T> value;
            int index = 0;

            channel_iterator(channel<T> c) : chan(c) {}

            std::pair<T, int> operator*()
            {
                if(!value.has_value())
                {
                    value = chan.recv();
                }

                return {value.value(), index};
            }

            channel_iterator& operator++()
            {
                ++index;
                value.reset();
                return *this;
            }
        };

        struct channel_iterator_end { };

        inline friend bool operator==(const channel_iterator& it, channel_iterator_end end)
        {
            return !it.chan.isOpen();
        }

        channel_iterator begin()
        {
            return channel_iterator(*this);
        }

        channel_iterator_end end()
        {
            return {};
        }

        bool trySend(T val)
        {
            return mImpl->trySend(val);
        }

        std::pair<T, bool> tryRecv()
        {
            return mImpl->tryReceive();
        }
        
        bool tryRecv(T& val)
        {
            auto optVal = mImpl->tryReceive();
            val = optVal.first;
            return optVal.second;
        }

        void send(T val)
        {
            mImpl->send(val);
        }

        bool recv(T& val)
        {
            auto optVal = mImpl->receive();
            val = optVal.first;
            return optVal.second;
        }

        result_or_error<T, ErrNoValueInChannel> recv()
        {
            return mImpl->receive();
        }

        bool isOpen() const
        {
            return mImpl->isOpen();
        }

        void close()
        {
            mImpl->close();
        }

        friend inline size_t cap(const channel<T>& input)
        {
            return input.mImpl->capacity();
        }

        friend inline void close(channel<T>& input)
        {
            input.close();
        }

        long count_copies() const
        {
            // TODO: fix this, not safe in theory
            return mImpl.use_count();
        }
    };

    template<typename T>
    std::ostream& operator<<(std::ostream& os, const gocpp::channel<T>& chan)
    {
        if(chan.is_nil())
        {
            return os << "<nil>";
        }
        return os << chan.address();
    }
}