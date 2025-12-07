#pragma once

#include "gocpp/support.fwd.h"

#include <any>
#include <complex>
#include <exception>
#include <functional>
#include <iostream>
#include <map>
#include <memory>
#include <numbers>
#include <string>
#include <tuple>
#include <typeinfo>
#include <utility>
#include <vector>

#include "thread_pool/thread_pool.h"

namespace golang
{
    constexpr gocpp::string operator""_s(const char* src, std::size_t);

    // Temporary definitions to mock broken include files
    namespace runtime
    {
        struct g {};
        struct p {};
        struct m {};

        struct sudog{};
        struct stack{};
        struct funcInfo{};
        struct gclinkptr{};
        struct lfnode{};
        struct metricValue{};
        struct lockRank{};
        struct traceMap{};
        struct Frame{};
        struct traceBlockReason{};
    }
    
    namespace cpu
    {
        struct CacheLinePad{};
    }

    namespace tree
    {
        struct Tree;
        std::ostream& operator<<(std::ostream& os, Tree const&)
        {
            os << "Tree";
            return os;
        }
    }

    namespace time
    {
        struct Time;
    }

    // temporary hack, while we don't use the native runtime::error object
    namespace errors
    {
        namespace rec
        {
            gocpp::string Error(struct errorString* e);
        }
    }
    namespace poll
    {
        namespace rec
        {
            gocpp::string Error(struct errNetClosing e);
            gocpp::string Error(struct DeadlineExceededError* e);
        }
    }
    namespace main
    {
        namespace rec
        {
            gocpp::string Error(struct MyError* e);
        }
    }
    namespace hex
    {
        using InvalidByteError = unsigned char;
        namespace rec
        {
            gocpp::string Error(const InvalidByteError& e);
        }
    }
}

namespace mocklib
{
    std::string Sprint(const std::any& value);
    std::string Sprint(const gocpp::go_any& value);
    inline std::string RuneToString(gocpp::rune r);

    template<typename T>
    std::ostream& PrintSliceTo(std::false_type, std::ostream& os, gocpp::slice<T> const& slice);
        
    template<typename T>
    std::ostream& PrintSliceTo(std::true_type, std::ostream& os, gocpp::slice<T> const& slice);

    namespace rec
    {
    }
}

// Support types implementations
namespace gocpp
{

    [[noreturn]] void panic(const gocpp::string& message);

    inline dp::thread_pool<>& global_pool()
    {
        static dp::thread_pool pool(std::thread::hardware_concurrency());
        return pool;
    }
    
    template <typename Function, typename... Args>
    inline void go(Function &&func, Args &&...args)
    {
        global_pool().enqueue_detach(func, args...);
    }

    struct GoPanic : std::runtime_error 
    {
        // maybe make it mutable to be able to use the usual
        // "catch(const GoPanic& p)" syntax
        std::shared_ptr<bool> recovered = std::make_shared<bool>(false);

        inline GoPanic(const std::string& message) : runtime_error(message)
        {
        }
    };

    struct go_any : std::any {
        using any::any;
    };

    template<std::same_as<gocpp::go_any> T, typename U>
    bool operator ==(const T& lhs, U const& rhs) {
        if(lhs.type() != typeid(U))
        {
            return false;
        }
        return std::any_cast<U>(lhs) == rhs;
    }

    // template<typename T>
    // bool operator ==(T& lhs, gocpp::go_any const& rhs) {
    //     if(rhs.type() != typeid(T))
    //     {
    //         return false;
    //     }
    //     return lhs == std::any_cast<T>(rhs);
    // }

    inline std::ostream& operator<<(std::ostream& os, gocpp::go_any const& value) {
        return os << mocklib::Sprint(value);
    }

    inline const std::type_info& type_info(const std::any& value)
    {
        const auto& info = value.type();
        if(info == typeid(const char * const))
        {
            return typeid(std::string);
        }

        return info;
    }

    template<typename T>
    T any_cast(const std::any& value)
    {
        return std::any_cast<T>(value);
    }

    template<>
    std::string any_cast<std::string>(const std::any& value)
    {
        if(value.type() == typeid(const char * const))
        {
            return std::any_cast<const char * const>(value);
        }
        
        return std::any_cast<std::string>(value);
    }

    template <typename T>
    struct ptr
    {
        void reset(T* p) { ptr = p; }
        T* get() { return ptr; }
        T* ptr = nullptr;
    };

    struct complex64 : std::complex<float>
    {
        using std::complex<float>::complex;

        inline complex64(const std::complex<float>& c) : complex(c) {}

        inline std::complex<float>& base() { return *this; }
        inline const std::complex<float>& base() const { return *this; }
    };

    inline static complex64 operator+(int i, complex64 c) { return float(i) + c.base(); };
    inline static complex64 operator+(complex64 c, int i) { return c.base() + float(i); };
    inline static complex64 operator-(int i, complex64 c) { return float(i) - c.base(); };
    inline static complex64 operator-(complex64 c, int i) { return c.base() - float(i); };

    struct complex128 : std::complex<double>
    {
        using std::complex<double>::complex;

        inline complex128(const std::complex<double>& c) : complex(c) {}

        inline std::complex<double>& base() { return *this; }
        inline const std::complex<double>& base() const { return *this; }
    };

    inline static complex128 operator+(int i, complex128 c) { return double(i) + c.base(); };
    inline static complex128 operator+(complex128 c, int i) { return c.base() + double(i); };
    inline static complex128 operator-(int i, complex128 c) { return double(i) - c.base(); };
    inline static complex128 operator-(complex128 c, int i) { return c.base() - double(i); };

    template<class It, class TargetType>
    class transform_iterator 
    {
        It it;

    public:
        using iterator_category = typename std::iterator_traits<It>::iterator_category;
        using value_type        = TargetType;
        using difference_type   = typename std::iterator_traits<It>::difference_type;

        transform_iterator() = default;
        transform_iterator(It it) : it(it) {}

        value_type operator*() const { return TargetType(*it); }

        transform_iterator& operator++() { ++it; return *this; }

        transform_iterator operator++(int) { auto t = *this; ++*this; return t; }

        friend bool operator==(const transform_iterator& a, const transform_iterator& b) 
        {
            return a.it == b.it;
        }

        transform_iterator operator+(difference_type n) const
        {
            return transform_iterator(it + n);
        }

        difference_type operator-(const transform_iterator& other) const
        {
            return it - other.it;
        }
    };


    struct string : std::string
    {
        using std::string::string;

        inline string(const string& src) : std::string(src) { }
        inline string(string&& src) : std::string(std::move(src)) { }

        inline string(const std::string& src) : std::string(src) { }
        inline string(std::string&& src) : std::string(std::move(src)) { }

        inline string(const rune& src) : std::string(mocklib::RuneToString(src)) { }

        inline string make_slice(size_t low) const
        {
            return string(this->substr(low));
        }

        // Assignment operators
        inline string& operator=(const string& src)
        {
            std::string::operator=(src);
            return *this;
        }

        inline string& operator=(string&& src) noexcept
        {
            std::string::operator=(std::move(src));
            return *this;
        }

        inline string& operator=(const std::string& src)
        {
            std::string::operator=(src);
            return *this;
        }

        inline string& operator=(std::string&& src) noexcept
        {
            std::string::operator=(std::move(src));
            return *this;
        }

        inline string& operator=(const char* s)
        {
            std::string::operator=(s ? s : "");
            return *this;
        }

        inline string& operator=(const rune& r)
        {
            std::string::operator=(mocklib::RuneToString(r));
            return *this;
        }

        using string_iterator = typename std::string::iterator;

        // (index, value) iterator
        struct range_iterator
        {
            size_t index;
            transform_iterator<string_iterator, int> iter;

            bool operator != (const range_iterator& other) const { return iter != other.iter; }
            range_iterator operator ++ () { ++index; ++iter; return *this; }
            range_iterator operator + (int n) { return { index + n, iter + n }; }
            auto operator * () const { return std::make_tuple(index, *iter); }
        };

        range_iterator begin() { return { 0, std::string::begin() }; }
        range_iterator end() { return { std::string::size(), std::string::end() }; }
    };

    inline long len(const std::string& input)
    {
        return input.length();
    }

    template<typename T>
    inline T max(T a)
    {
        return a;
    }

    template<typename T1, typename T2, typename... Ts>
    inline std::common_type_t<T1, T2, Ts...> max(T1 a, T2 b, Ts... args)
    {
        return max((a > b ? a : b), args...);
    }

    template<typename T>
    inline T min(T a)
    {
        return a;
    }

    template<typename T1, typename T2, typename... Ts>
    inline std::common_type_t<T1, T2, Ts...> min(T1 a, T2 b, Ts... args)
    {
        return min((a < b ? a : b), args...);
    }

    inline complex64 complex(float r, float i)
    {
        return std::complex<float>(r, i);
    }

    inline complex128 complex(double r, double i)
    {
        return std::complex<double>(r, i);
    }

    template<typename T> struct Tag {};

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
        result_or_error(const std::pair<T, bool>& src) : std::pair<T, bool>(src) {}

        operator const T() const 
        {
            if(!this->second)
                panic(Error::error_message());

            return this->first;
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

        // TODO: use capacity
        channel(int capacity) : mImpl(std::make_shared<channelImpl<T>>(capacity)) {}

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

        void send(T val)
        {
            mImpl->send(val);
        }

        bool recv(T& val)
        {
            auto optVal = mImpl->receive();
            val = optVal.value;
            return optVal.hasValue;
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

    struct Defer : std::vector<std::function<void()>>
    {
        void unwind()
        {
            while(!empty())
            {
                back()();
                pop_back();
            }
        }

        void handlePanic(GoPanic& gp)
        {
            unwind();

            if(!(*gp.recovered)) {
                throw gp;
            }            
        }

        ~Defer()
        {
            unwind();
        }
    };

    // temporary hack, while we don't use the native runtime::error object
    using golang::main::rec::Error;
    using golang::errors::rec::Error;
    using golang::poll::rec::Error;

    template <typename T>
    concept IsRefError = requires(const T& t) {
        { Error(t) } -> std::convertible_to<gocpp::string>;
    };
    
    template <typename T>
    concept IsPtrError = requires(const T *t) {
        { Error(t) } -> std::convertible_to<gocpp::string>;
    };
    
    template <typename T>
    concept IsError = IsRefError<T> || IsPtrError<T>;

    // Maybe should be put in mocklib as we probably want use 
    // the translated definition from "runtime/error.go" at target
    struct error : std::optional<std::string> 
    {
        using optional::optional;

        error() : optional(std::nullopt) {}
        error(std::nullptr_t) : optional(std::nullopt) {}
        error(const gocpp::string& msg) : optional(msg) {}
        
        // Temporary mock, we lose the original type
        template<typename T> requires IsRefError<T>
        error(const T& t) : optional(Error(t)) {}
        
        // Temporary mock, we lose the original type
        template<typename T> requires IsPtrError<T>
        error(const T* t) : optional(Error(t)) {}

        // Temporary mock, we lose the original type
        // Why the "requires IsRefError<T>" constraint does not work here ? 
        error(golang::hex::InvalidByteError t) : optional(golang::hex::rec::Error(t)) {}

        error& operator=(const std::string& msg)
        {
            this->optional::operator=(msg);
            return *this;
        }

        error& operator=(std::nullptr_t)
        {
            this->optional::operator=(std::nullopt);
            return *this;
        }

        friend bool operator==(const error& lhs, const error& rhs) = default;

        friend bool operator==(const error& lhs, const gocpp::string& rhs)
        {
            return lhs.has_value() && lhs.value() == rhs;
        }

        friend bool operator==(const error& lhs, std::nullptr_t)
        {
            return !lhs.has_value();
        }

        friend bool operator==(const gocpp::string& lhs, const error& rhs)
        {
            return rhs == lhs;
        }

        friend bool operator==(std::nullptr_t, const error& rhs)
        {
            return rhs == nullptr;
        }
    };

    std::string Error(const error& e)
    {
        if(e.has_value())
        {
            return e.value();
        }
        return "Undefined error";
    }

    template<typename T>
    struct CheckType
    {
        using type = void;
    };

    template <typename T, typename = void>
    class IsGoStruct : public std::false_type { };

    template <typename T>
    class IsGoStruct<T, typename CheckType<typename T::isGoStruct>::type> : public std::true_type { };

    template<typename T>
    concept GoStruct = IsGoStruct<T>::value;


    template <typename T, typename = void>
    class IsGoInterface : public std::false_type { };

    template <typename T>
    class IsGoInterface<T, typename CheckType<typename T::IsGoInterface>::type> : public std::true_type { };

    template<typename T>
    concept GoInterface = IsGoInterface<T>::value;

    template<typename T, typename Func>
    T Init(Func init)
    {
        T value;
        init(value);
        return value;
    }

    template<typename T, typename Func>
    T* InitPtr(Func init)
    {
        auto value = new T;
        init(*value);
        return value;
    }
    
    struct Interface
    {
        bool isNil = true;

        bool operator==(nullptr_t ptr)
        {
            return isNil;
        }
        
        bool operator!=(nullptr_t ptr)
        {
            return !isNil;
        }
    };

    [[noreturn]] void panic(const gocpp::string& message)
    {
        throw GoPanic(message);
    }

    template<typename ErrorType> requires IsError<ErrorType>    
    [[noreturn]] void panic(const ErrorType& error)
    {
        throw GoPanic(Error(error));
    }

    go_any recover()
    {
        try
        {
            if(auto e_ptr = std::current_exception())
            {
                std::rethrow_exception(e_ptr);
            }
        }
        catch(GoPanic& p)
        {
            *(p.recovered) = true;
            return p.what();
        }        
        return nullptr;
    }

    // Receiver adapter for method calls
    // TODO: check if "IgnoreInterface" parameters has still some utility
    template <typename T, bool IgnoreInterface = false>
    struct PtrRecv
    {        
        T* ptr;

        PtrRecv(T* t) : ptr(t) {}

        operator const T&() const { return *ptr; }
        operator T*() { return ptr; }
        operator const T*() const { return ptr; }
    };

    template <typename T>
    struct ObjRecv
    {        
        T obj;

        ObjRecv(const T& t) : obj(t) {}

        operator const T&() const { return obj; }
        operator T*() { return &obj; }
        operator const T*() const { return &obj; }
    };

    template <typename T>
    PtrRecv<T> recv(T* t) { return PtrRecv<T>(t); }
    
    template <typename T>
    ObjRecv<T> recv(const T& t) { return ObjRecv<T>(t); }

    template <typename T, typename E>
    ObjRecv<T> recv(const result_or_error<T, E>& t) { return ObjRecv<T>(t); }

    template <typename T>
    PtrRecv<T> recv(T& t) { return PtrRecv<T>(&t); }

    template<typename T>
    struct array_base
    {
        using store_type = std::vector<T>;
        using vect_iterator = typename store_type::iterator;
        using const_vect_iterator = typename store_type::iterator;

        array_base(std::initializer_list<T> list)
        {
            this->mArray = std::make_shared<store_type>(list.begin(), list.end());
        }

        // (index, value) iterator
        struct range_iterator
        {
            size_t index;
            vect_iterator iter;

            bool operator != (const range_iterator& other) const { return iter != other.iter; }
            range_iterator operator ++ () { ++index; ++iter; return *this; }
            range_iterator operator + (int n) { return { index + n, iter + n }; }
            auto operator * () const { return std::tie(index, *iter); }
        };

        template <typename, int> friend class array;
        template <typename> friend class slice;

        size_t size() const
        {
            if(mArray)
            {
                return mArray->size();
            }

            return 0;
        }

        typename store_type::const_reference operator[](size_t i) const
        {
            if(mArray)
            {
                return mArray->at(i);
            }

            panic("Cannot access item of an empty array");
        }

        typename store_type::reference operator[](size_t i)
        {
            if(mArray)
            {
                return mArray->at(i);
            }

            panic("Cannot access item of an empty array");
        }
        
        range_iterator begin()
        {
            if(mArray)
            {
                return {0, mArray->begin()};
            }

            return range_iterator();
        }

        // const_iterator begin() const
        // {
        //     if(mArray)
        //     {
        //         return mArray->begin();
        //     }

        //     return const_iterator();
        // }

        range_iterator end()
        {
            if(mArray)
            {
                return {mArray->size(), mArray->end()};
            }

            return range_iterator();
        }

        // const_iterator end() const
        // {
        //     if(mArray)
        //     {
        //         return mArray->end();
        //     }

        //     return const_iterator();
        // }


        gocpp::slice<T> make_slice(size_t low);
        gocpp::slice<T> make_slice(size_t low, size_t high);

    protected:
        array_base() { }

        std::shared_ptr<store_type> mArray;
    };

    template<typename T, int N>
    struct array : array_base<T>
    {
        using typename array_base<T>::store_type;

        array()
        {
            this->mArray = std::make_shared<store_type>(N);
        }

        array(std::initializer_list<T> list)
        {
            this->mArray = std::make_shared<store_type>(list.begin(), list.end());
            this->mArray->resize(N);
        }

        // TODO : other constructors

        friend constexpr long len(const array<T, N>& input)
        {
            return N;
        }

        friend constexpr long len(const array<T, N>* input)
        {
            return N;
        }
    };

    template<typename T>
    struct slice : array_base<T>
    {
        using typename array_base<T>::store_type;
        using typename array_base<T>::range_iterator;

        slice() : slice(0) { }
        
        slice(std::nullptr_t) : slice(0) { }

        slice(int n)
        {
            this->mArray = std::make_shared<store_type>(n);
            mStart = 0;
            mEnd = this->size();
        }

        slice(int n, int r)
        {
            this->mArray = std::make_shared<store_type>(n);
            this->mArray->reserve(r);
            mStart = 0;
            mEnd = this->size();
        }

        slice(std::initializer_list<T> list)
        {
            this->mArray = std::make_shared<store_type>(list.begin(), list.end());
            mStart = 0;
            mEnd = this->size();
        }
        
        template<std::ranges::range R>
        slice(R range)
        {
            this->mArray = std::make_shared<store_type>(range.begin(), range.end());
            mStart = 0;
            mEnd = this->size();
        }

        slice(const std::string& str)
        {
            this->mArray = std::make_shared<store_type>(str.begin(), str.end());
            mStart = 0;
            mEnd = this->size();
        }

        slice(array_base<T>& a, int low, int high)
        {
            checkParams(a, low, high);            
            this->mArray = a.mArray;
            mStart = low;
            mEnd = high;
        }
        
        slice(array_base<T>& a, int low, int high, int capacity)
        {
            checkParams(a, low, high);

            if(high > capacity)
            {
                panic("slice: high > capacity");
            }

            if(a.size() < capacity)
            {
                panic("slice: capacity > size");
            }

            this->mArray = std::make_shared<store_type>(a.mArray->begin() + low, a.mArray->begin() + high);
            this->mArray->reserve(capacity);
            mStart = 0;
            mEnd = high - low;
        }        

        // TODO : other constructors

        range_iterator begin()
        {
            return array_base<T>::begin() + mStart;
        }

        // const_iterator begin() const
        // {
        //     return array_base<T>::begin() + mStart;
        // }

        range_iterator end()
        {
            return array_base<T>::begin() + mEnd;
        }

        // const_iterator end() const
        // {
        //     return array_base<T>::begin() + mEnd;
        // }

        operator std::string() const requires std::is_same<T, unsigned char>::value
        {
            if(!this->mArray)
            {
                return std::string();
            }
            return std::string(this->mArray->begin(), this->mArray->end());
        }

        typename store_type::const_reference operator[](size_t i) const
        {
            return array_base<T>::operator[](i + mStart);
        }

        typename store_type::reference operator[](size_t i)
        {
            return array_base<T>::operator[](i + mStart);
        }

        // Fix this, not efficient
        template<typename ...Args>
        friend inline slice<T> append(slice<T> input, T value, Args... moreValues)
        {
            input = append(input, value);
            return append(input, moreValues...);
        }

        friend inline slice<T> append(slice<T> src1, slice<T> src2)
        {
            for (auto&& [index, elt] : src2)
            {
                src1 = append(src1, elt);
            }
            return src1;
        }

        friend inline slice<T> append(slice<T> input, T value)
        {
            if(input.mEnd == input.mArray->size())
            {
                input.mArray->push_back(value);
                ++input.mEnd;
                return input;                
            }
            
            if(input.mEnd < input.mArray->size())
            {
                (*input.mArray)[input.mEnd] = value;
                ++input.mEnd;
                return input;                
            }

            panic("invalid slice");
        }

        friend inline int copy(slice<T> dst, slice<T> src)
        {
            if(!dst.mArray || !src.mArray)
            {
                return 0;
            }

            int  len = min(dst.mArray->size(), src.mArray->size());
            for(size_t i = 0; i < len; i++)
            {
                dst[i] = src[i];
            }
            return len;
        }

        friend inline int copy(slice<T> dst, std::string src)
        {
            if(!dst.mArray)
            {
                return 0;
            }

            int  len = min(dst.mArray->size(), src.size());
            for(size_t i = 0; i < len; i++)
            {
                dst[i] = src[i];
            }
            return len;
        }

        friend inline long len(const slice<T>& input)
        {
            return input.mEnd - input.mStart;
        }

        friend inline long cap(const slice<T>& input)
        {
            if(input.mArray)
            {
                return input.mArray->capacity();
            }

            return 0;
        }

        gocpp::slice<T> make_slice(size_t low);
        gocpp::slice<T> make_slice(size_t low, size_t high);
        gocpp::slice<T> make_slice(size_t low, size_t high, size_t max);

    //private:    
        // [mStart, mEnd[
        int mStart = 0;
        int mEnd = 0;

    private:
        void checkParams(array_base<T>& a, int low, int high)
        {
            if(low > high)
            {
                panic("slice: low > high");
            }

            if(a.size() < low)
            {
                panic("slice: low > size");
            }

            if(a.size() < high)
            {
                panic("slice: high > size");
            }
        }
    };
    

    template<typename T>
    bool operator==(slice<T> s, nullptr_t) { return len(s) == 0; }
    
    template<typename T>
    bool operator==(nullptr_t, slice<T> s) { return len(s) == 0; }

    template<typename T>
    std::ostream& operator<<(std::ostream& os, gocpp::slice<T> const& slice)
    {
        return mocklib::PrintSliceTo<T>(gocpp::IsGoStruct<T>(), os, slice);
    }

    template<typename V>
    struct map_value : public std::tuple<typename std::add_lvalue_reference<V>::type, bool>
    {
        using std::tuple<typename std::add_lvalue_reference<V>::type, bool>::tuple;
        using val_ref = typename std::add_lvalue_reference<V>::type;

        val_ref operator= (const V& value)
        {
            return std::get<0>(*this) = value;
        }

        operator val_ref(){ return std::get<0>(*this); }

        template <std::size_t Index>
        std::tuple_element_t<Index, map_value> &get()
        {
            return std::get<Index>(*this);
        }
        
        auto operator->() noexcept -> decltype(std::get<0>(*this))
        {
            return std::get<0>(*this);
        }

        auto operator->() const noexcept -> decltype(std::get<0>(*this))
        {
            return std::get<0>(*this);
        }
    };

    template <typename K, typename V>
    struct map : std::map<K, V>
    {
        using std::map<K, V>::map;
        
        map_value<V> operator[](const K& key)
        {
            auto it = this->find(key);
            if( it != this->end())
            {
                return {it->second, true};
            }

            // FIXME: Not equivalent to go maps.
            // Value are inserted only when explicitly assigned in golang
            return {std::map<K, V>::operator[](key), false};
        }

        friend inline void remove(map<K, V>& input, const K& key)
        {
            input.erase(key);
        }
    };

    template<typename K, typename V>
    std::ostream& operator<<(std::ostream& os, const gocpp::map<K, V>& dic)
    {
        os << '[';
        int i = 0;
        for(auto& kv : dic)
        {
            if(i != 0) { os << ", "; }            
            os << kv.first << ": " << kv.second;
            i++;
        }
        os << ']';
        return os;
    }

    // FIXME: golang permit to access all element between size and capacity    
    template<typename T>
    gocpp::slice<T> array_base<T>::make_slice(size_t low)
    {
        if(!this->mArray || low > this->size())
        {
            return {};
        }

        return slice(*this, low, this->size());
    }

    // FIXME: golang permit to access all element between size and capacity    
    template<typename T>
    gocpp::slice<T> array_base<T>::make_slice(size_t low, size_t high)
    {
        if(!this->mArray || low > this->size())
        {
            return {};
        }

        high = std::min(high, this->size());
        return slice(*this, low, high);
    }
    
    // FIXME: golang permit to access all element between size and capacity    
    template<typename T>
    gocpp::slice<T> slice<T>::make_slice(size_t low)
    {
        low = low + this->mStart;
        if(!this->mArray || low >= this->size())
        {
            return {};
        }

        return slice(*this, low, std::min<int>(this->size(), this->mEnd));
    }

    // FIXME: golang permit to access all element between size and capacity    
    template<typename T>
    gocpp::slice<T> slice<T>::make_slice(size_t low, size_t high)
    {
        low = low + this->mStart;
        high = high + this->mStart;
        if(!this->mArray || low >= this->size())
        {
            return {};
        }

        high = std::min(high, this->size());
        return slice(*this, low, high);
    }

    // FIXME: golang permit to access all element between size and capacity    
    template<typename T>
    gocpp::slice<T> slice<T>::make_slice(size_t low, size_t high, size_t max)
    {
        low = low + this->mStart;
        high = high + this->mStart;
        max = max + this->mStart;
        if(!this->mArray || low >= this->size())
        {
            return {};
        }

        high = std::min(high, this->size());
        max = std::min(max, this->size());
        return slice(*this, low, high, max);
    }

    template <typename T>
    T make(Tag<T>)
    {
        return T();
    }
    
    template <typename T, typename P>
    T make(Tag<T>, P p)
    {
        return T(p);
    }

    template <typename T, typename P1, typename P2>
    T make(Tag<T>, P1 p1, P2 p2)
    {
        return T(p1, p2);
    }

    template<typename T, typename... Args>
    gocpp::slice<T> ToSlice(T value, Args&&... args)
    {
        return gocpp::slice<T> { value, T(args)... }; 
    }

    template<typename T, typename... Args>
    gocpp::slice<T> ToSlice(Args&&... args)
    {
        return gocpp::slice<T> { T(args)... }; 
    }

    template <typename T>
    struct ErrInvalidValueCast
    {
        static std::string error_message()
        {
            return std::string("invalid value cast to '") + typeid(T).name() + "'"; 
            // TODO, find a way to get value in error message for debugging
            //return std::string("invalid value cast to type '") + typeid(T).name() + "' from type '" + value.type().name() + "'" };
        }
    };

    template <typename T>
    result_or_error<T, ErrInvalidValueCast<T>> getValue(std::any value)
    {
        if(value.type() == typeid(T))
        {
            return std::make_pair(std::any_cast<T>(value), true);
        }

        return std::make_pair(T{}, false);
    }
    
    template<>
    result_or_error<std::string, ErrInvalidValueCast<std::string>> getValue(std::any value)
    {
        if(value.type() == typeid(std::string))
        {
            return std::make_pair(std::any_cast<std::string>(value), true);
        }
        
        if(value.type() == typeid(const char * const))
        {
            return std::make_pair(std::string(std::any_cast<const char * const>(value)), true);
        }

        return std::make_pair(std::string{}, false);
    }
}

namespace std
{
    template <typename V>
    struct tuple_size<gocpp::map_value<V>>
    {
        static constexpr size_t value = 2;
    };

    // TODO: use the base std::tuple ?
    template <typename V>
    struct tuple_element<0, gocpp::map_value<V>>
    {
        using type = typename std::add_lvalue_reference<V>::type;
    };

    template <typename V>
    struct tuple_element<1, gocpp::map_value<V>>
    {
        using type = bool;
    };

    // Temporary mock for std::function printing, maybe we should use a custom
    // gocpp::ostream type to avoid overloading in std namespace.
    template<typename T>
    inline std::ostream& operator<<(std::ostream& os, const std::function<T>& value) {
        return os << "<function>";
    }
}

namespace golang
{
    constexpr gocpp::string operator""_s(const char* src, std::size_t)
    {
        return gocpp::string(src);
    }

    using gocpp::len;
    using go_any = gocpp::go_any;
    using namespace mocklib;
    using namespace mocklib::rec;
}

// temporary mock implementations
namespace mocklib
{
    // mock "time" types and functions

    // NB: real go api return channel<Time>
    gocpp::channel<int64_t> After(int64_t duration_ns)
    {
        gocpp::channel<int64_t> c;
        gocpp::go([=]() mutable {
            std::this_thread::sleep_for(std::chrono::nanoseconds(duration_ns));
            c.send(0);
        });
        return c;
    }

    // NB: real go api return channel<Time>
    gocpp::channel<int64_t> Tick(int64_t duration_ns)
    {
        gocpp::channel<int64_t> c;
        gocpp::go([=]() mutable {
            while(true)
            {
                std::this_thread::sleep_for(std::chrono::nanoseconds(duration_ns));
                if(c.count_copies()>1)
                {
                    c.send(0);                
                }
                else
                {
                    c.close();
                    return;
                }
            }
        });
        return c;
    }

    struct Date
    {
        static Date Now() { return Date{}; };
        static const int Saturday = 6;
    };
    
    std::ostream& operator<<(std::ostream& os, const Date& date)
    {
        os << "[mocklib::DATE]";
        return os;
    }

    namespace rec
    {
        inline int Weekday(const Date&) { return Date::Saturday; };
        inline int Hour(const Date&) { return 17; };
    }

    const long Nanosecond = 1;
    const long Microsecond = 1000 * Nanosecond;
    const long Millisecond = 1000 * Microsecond;
    const long Second = 1000 * Millisecond;
    const long Minute = 60 * Second;
    // const long Hour         = 60 * Minute;

    inline void Sleep(long duration_ns)
    {
        std::this_thread::sleep_for(std::chrono::nanoseconds(duration_ns));
    }

    // mock "rand" types and functions
    inline int Intn(int n)
    {
        return rand() % n;
    }

    // mock "runtime" types and functions
    inline const char *const GOOS = "undefined";

    // mock "math" types and functions
    inline const double Sqrt2 = std::sqrt(2.0);
    inline const double Pi = std::numbers::pi;

    double Pow(double value, double exp)
    {
        return std::pow(value, exp);
    }

    // mock "sync" types and functions
    struct Mutex : std::shared_ptr<std::mutex>
    {
        Mutex() : std::shared_ptr<std::mutex>(new std::mutex()) { }
    };

    namespace rec
    {
        void Lock(const Mutex& mutex)
        {
            mutex->lock();
        }

        void Unlock(const Mutex& mutex)
        {
            mutex->unlock();
        }
    }
        
    // TODO : call the method generated in utf8 translation "EncodeRune"
    inline std::string RuneToString(gocpp::rune r)
    {
        const char RuneError = '\uFFFD';
        const char MaxRune = '\U0010FFFF';
        const long UTFMax = 4;
        const long surrogateMin = 0xD800;
        const long surrogateMax = 0xDFFF;
        const long tx = 0b10000000;
        const long t2 = 0b11000000;
        const long t3 = 0b11100000;
        const long t4 = 0b11110000;
        const long maskx = 0b00111111;
        const int rune1Max = (1 << 7) - 1;
        const int rune2Max = (1 << 11) - 1;
        const int rune3Max = (1 << 16) - 1;

        {
            std::string p;
            auto i = uint32_t(r);
            int conditionId = -1;
            if(i <= rune1Max) { conditionId = 0; }
            else if(i <= rune2Max) { conditionId = 1; }
            else if(i > MaxRune) { conditionId = 2; }
            else if(surrogateMin <= i && i <= surrogateMax) { conditionId = 3; }
            else if(i <= rune3Max) { conditionId = 4; }
            switch(conditionId)
            {
                case 0:
                    p.resize(1);
                    p[0] = (unsigned char)(r);
                    break;
                case 1:
                    p.resize(2);
                    p[0] = t2 | (unsigned char)(r >> 6);
                    p[1] = tx | (unsigned char)(r) & maskx;
                    break;
                case 2:
                case 3:
                    r = RuneError;
                case 4:
                    p.resize(3);
                    p[0] = t3 | (unsigned char)(r >> 12);
                    p[1] = tx | (unsigned char)(r >> 6) & maskx;
                    p[2] = tx | (unsigned char)(r) & maskx;
                    break;
                default:
                    p.resize(4);
                    p[0] = t4 | (unsigned char)(r >> 18);
                    p[1] = tx | (unsigned char)(r >> 12) & maskx;
                    p[2] = tx | (unsigned char)(r >> 6) & maskx;
                    p[3] = tx | (unsigned char)(r) & maskx;
                    break;
            }
        }
        
    }

    std::ostream& PrintTo(std::ostream& os, const Date& value);
    std::ostream& PrintTo(std::ostream& os, bool value);
    std::ostream& PrintTo(std::ostream& os, char value);
    std::ostream& PrintTo(std::ostream& os, unsigned char value);

    template<typename K, typename V>
    std::ostream& PrintTo(std::ostream& os, const gocpp::map<K, V>& value);

    template<typename V>
    std::ostream& PrintTo(std::ostream& os, const gocpp::map_value<V>& value);

    template<typename T>
    std::ostream& PrintTo(std::ostream& os, const T& value);

    template<typename T, typename E>
    std::ostream& PrintTo(std::ostream& os, const gocpp::result_or_error<T, E>& value);

    template<typename T, typename... Args>
    std::ostream& PrintTo(std::ostream& os, const T& value, Args&&... args);

    // internals: operators for tupples/ostream/slices
    template<typename... Ts>
    std::ostream& operator<<(std::ostream& os, const std::tuple<Ts...>& theTuple)
    {
        std::apply
        (
            [&os](Ts const&... tupleArgs)
            {
                os << '[';
                std::size_t n{0};
                ((PrintTo(os, tupleArgs) << (++n != sizeof...(Ts) ? ", " : "")), ...);
                os << ']';
            }, theTuple
        );
        return os;
    }

    template<typename T>
    std::ostream& operator<<(std::ostream& os, const gocpp::array_base<T>& array)
    {
        os << '[';
        for(int i=0; i< array.size(); ++i)
        {
            if(i == 0)
                PrintTo(os, array[i]);
            else
                PrintTo(os << " ", array[i]);
        }
        os << ']';
        return os;
    }

    template<typename T>
    std::ostream& operator<<(std::ostream& os, const std::initializer_list<T>& array)
    {
        os << '[';
        int i = 0;
        for(const T& item : array)
        {
            if(i == 0)
                PrintTo(os, item);
            else
                PrintTo(os << " ", item);

            i++;
        }
        os << ']';
        return os;
    }

    template<typename T> requires gocpp::GoStruct<T>
    std::ostream& operator<<(std::ostream& os, const T* ptr)
    {
        if(ptr)
        {
            os << '&';
            PrintTo(os, *ptr);
        }
        else
        {
            os << "<nil>";
        } 
        return os;
    }

    // /* 
    // ** Should replace the two previous template but this create ambiguous overload because
    // ** the template match basic_string too
    // */
    //
    // template<typename T, template<typename U> class IndexedContainer>
    // std::ostream& operator<<(std::ostream& os, IndexedContainer<T> const& array)
    // {
    //     os << '[';
    //     for(int i=0; i< array.size(); ++i)
    //     {
    //         if(i == 0)
    //             os << array[i];
    //         else
    //             os << " " << array[i];
    //     }
    //     os << ']';
    //     return os;
    // }

    template<typename T>
    std::ostream& PrintSliceTo(std::false_type, std::ostream& os, gocpp::slice<T> const& slice)
    {
        os << '[';
        for(int i=0; i< slice.mEnd - slice.mStart; ++i)
        {
            if(i == 0)
                PrintTo(os, slice[i]);
            else
                PrintTo(os << " ", slice[i]);
        }
        os << ']';
        return os;
    }
        
    template<typename T>
    std::ostream& PrintSliceTo(std::true_type, std::ostream& os, gocpp::slice<T> const& slice)
    {
        os << '[';
        for(int i=0; i< slice.mEnd - slice.mStart; ++i)
        {
            if(i == 0)
                slice[i].PrintTo(os);
            else
                slice[i].PrintTo(os << " ");
        }
        os << ']';
        return os;
    }

    void PrintToVect(std::vector<std::string>&);

    template<typename T>
    void PrintToVect(std::vector<std::string>& out, const T& value);

    template<typename T, typename... Args>
    void PrintToVect(std::vector<std::string>& out, const T& value, Args&&... args);

    std::ostream& PrintTo(std::ostream& os, const Date& value)
    {
        return os << "[DATE]";
    }

    std::ostream& PrintTo(std::ostream& os, bool value)
    {
        return os << value;
    }   

    std::ostream& PrintTo(std::ostream& os, char value)
    {
        return os << int(value);
    }

    std::ostream& PrintTo(std::ostream& os, unsigned char value)
    {
        return os << int(value);
    }

    template<typename K, typename V>
    std::ostream& PrintTo(std::ostream& os, const gocpp::map<K, V>& value)
    {
        os << "map[";
        auto sep = "";
        for(auto kv : value)
        {
            os << sep << kv.first << ":" << kv.second;
            sep = " ";
        }
        return os << "]";
    }

    template<typename V>
    std::ostream& PrintTo(std::ostream& os, const gocpp::map_value<V>& value)
    {
        return os << std::get<0>(value);
    }

    template<typename T>
    std::ostream& PrintTo(std::ostream& os, const T& value)
    {
        return os << value;
    }

    template<typename T, typename E>
    std::ostream& PrintTo(std::ostream& os, const gocpp::result_or_error<T, E>& value)
    {
        return os << value.first;
    }

    template<typename T, typename... Args>
    std::ostream& PrintTo(std::ostream& os, const T& value, Args&&... args)
    {
        PrintTo(os, value);
        PrintTo(os, " ");
        PrintTo(os, std::forward<Args>(args)...);
        return os;
    }

    template<typename... Args>
    void Print(Args&&... args)
    {
        PrintTo(std::cout, std::forward<Args>(args)...);
    }

    template<typename T>
    void Printf(const T& value)
    {
        std::cout << value;
    }

    // No real formatting at the moment, just replace %v
    template<typename... Args>
    void Printf(const std::string& format, Args&&... args)
    {
        std::vector<std::string> arguments;
        PrintToVect(arguments, std::forward<Args>(args)...);

        int lastPos = -2;
        int i = 0;
        for(int pos = format.find("%v"); pos != std::string::npos; pos = format.find("%v", lastPos+1), ++i)
        {
            Print(format.substr(lastPos+2, pos-lastPos-2));
            Print(arguments[i]);
            lastPos = pos;
        }

        // Printing end of format string
        Print(format.substr(lastPos+2, std::string::npos));

        // Printing unused parameters
        for(; i<arguments.size(); ++i )
        {
            Print(arguments[i]);
        }
    }

    template<typename... Args>
    void Println(Args&&... args)
    {
        Print(std::forward<Args>(args)...);
        std::cout << "\n";
    }
    
    void Println()
    {
        std::cout << "\n";
    }    

    std::string Sprint(const std::any& value)
    {
        return "<std::any>";
    }

    std::string Sprint(const gocpp::go_any& value)
    {
        if (value.type() == typeid(int)) {
            std::stringstream sstr;
            sstr << std::any_cast<int>(value);
            return sstr.str();
        }        
        if (value.type() == typeid(nullptr)) {
            return "<nil>";
        }
        if (value.type() == typeid(const char*)) {
            return std::any_cast<const char*>(value);
        }
        return "<gocpp::go_any>[" + std::string(value.type().name()) + "]";
    }

    template<typename T>
    std::string Sprint(const T& value)
    {
        std::stringstream sstr;
        sstr << value;
        return sstr.str();
    }

    template<typename T>
    std::string Sprintf(const T& value)
    {
        return Sprint(value);
    }

    // No real formatting at the moment
    template<typename T, typename... Args>
    std::string Sprintf(const T& value, Args&&... args)
    {
        auto result = Sprintf(value);
        result += Sprintf(" ");
        result += Sprintf(std::forward<Args>(args)...);
        return result;
    }    

    template<typename... Args>
    gocpp::error Errorf(Args&&... args)
    {
        return Sprintf(std::forward<Args>(args)...);
    }

    void PrintToVect(std::vector<std::string>&) { }

    template<typename T>
    void PrintToVect(std::vector<std::string>& out, const T& value)
    {
        out.push_back(Sprint(value));
    }

    template<typename T, typename... Args>
    void PrintToVect(std::vector<std::string>& out, const T& value, Args&&... args)
    {
        out.push_back(Sprint(value));
        PrintToVect(out, std::forward<Args>(args)...);
    }

    template<typename IdxContainerType>
    std::string StringsJoin(IdxContainerType vect, const std::string& sep)
    {
        std::stringstream sstr;
        for(int i=0; i< vect.size(); ++i)
        {
            if(i == 0)
                sstr << vect[i];
            else
                sstr << sep << vect[i];
        }
        return sstr.str();
    }

    gocpp::slice<std::string> StringsFields(const std::string& strList)
    {
        gocpp::slice<std::string> strings;
        std::istringstream iss(strList);
        std::string elt;
        while (getline(iss, elt, ' '))
        {
            strings = append(strings, elt);
        }
        return strings;
    }

    template<typename Func>
    void wcSingleTest(const Func& func, const std::string& input)
    {
        std::cout << "PASS" << std::endl;
        std::cout << " f(\"" << input << "\") = \n";
        std::cout << "  map[string]int{";
        auto sep = "";
        for(auto kv : func(input))
        {
            std::cout << sep << '"' << kv.first << '"' << ":" << kv.second;
            sep = ", ";
        }
        std::cout << "}" << std::endl;
    }

    template<typename Func>
    void wcTest(const Func& func)
    {
        wcSingleTest(func, "I am learning Go!");
        wcSingleTest(func, "The quick brown fox jumped over the lazy dog.");
        wcSingleTest(func, "I ate a donut. Then I ate another donut.");
        wcSingleTest(func, "A man a plan a canal panama.");
    }

    template<typename T>
    void picShow(const T& func) { /* Just a mock */ }

    template<typename T>
    void picShowImage(const T& func) { /* Just a mock */ }
}
