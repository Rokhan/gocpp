#pragma once

#include <complex>
#include <exception>
#include <functional>
#include <iostream>
#include <map>
#include <memory>
#include <numbers>
#include <string>
#include <tuple>
#include <utility>
#include <vector>

#include "thread_pool/thread_pool.h"

// Support types implementations
namespace gocpp
{
    // TODO : make forward declaration header for types

    template<typename T> struct array_base;
    template<typename T, int N> struct array;
    template<typename T> struct slice;
    struct complex128;
    struct Defer;

    inline dp::thread_pool<>& global_pool()
    {
        static dp::thread_pool pool(std::thread::hardware_concurrency());
        return pool;
    }

    template <typename T>
    struct ptr
    {
        void reset(T* p) { ptr = p; }
        T* get() { return ptr; }
        T* ptr = nullptr;
    };

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

    template<typename T> struct Tag {};

    struct Defer : std::vector<std::function<void()>>
    {
        ~Defer()
        {
            while(!empty())
            {
                back()();
                pop_back();
            }
        }
    };

    template<typename T>
    struct CheckType
    {
        using type = void;
    };

    template <typename T, typename = void>
    class IsGoStruct : public std::false_type { };

    template <typename T>
    class IsGoStruct<T,typename CheckType<typename T::isGoStruct>::type> : public std::true_type { };

    struct GoPanic : std::runtime_error 
    {
        GoPanic(const std::string& message) : runtime_error(message)
        {
        }
    };

    [[noreturn]] void panic(const std::string& message)
    {
        throw GoPanic(message);
    }


    // Receiver adapter for method calls
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


    template<typename T>
    struct array_base
    {
        using store_type = std::vector<T>;
        using vect_iterator = typename store_type::iterator;
        using const_vect_iterator = typename store_type::iterator;

        // (index, value) iterator
        struct range_iterator
        {
            size_t index;
            vect_iterator iter;

            bool operator != (const range_iterator & other) const { return iter != other.iter; }
            void operator ++ () { ++index; ++iter; }
            range_iterator operator + (int n) { return {index + n, iter + n}; }
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
                return {0 , mArray->begin()};
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
                return mArray->end();
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
        }

        // TODO : other constructors
    };

    template<typename T>
    struct slice : array_base<T>
    {
        using typename array_base<T>::store_type;
        using typename array_base<T>::range_iterator;

        slice()
        {
            this->mArray = std::make_shared<store_type>();
            mStart = 0;
            mEnd = this->size();
        }

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

        slice(array_base<T>& a, int low, int high)
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

            this->mArray = a.mArray;
            mStart = low;
            mEnd = high;
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
        
        friend inline size_t len(slice<T> input)
        {
            return input.mEnd - input.mStart;
        }

        friend inline size_t cap(slice<T> input)
        {
            if(input.mArray)
            {
                return input.mArray->capacity();
            }

            return 0;
        }

        gocpp::slice<T> make_slice(size_t low);
        gocpp::slice<T> make_slice(size_t low, size_t high);

    //private:    
        // [mStart, mEnd[
        int mStart = 0;
        int mEnd = 0;
    };
    

    template<typename T>
    bool operator==(slice<T> s, nullptr_t) { return len(s) == 0; }
    
    template<typename T>
    bool operator==(nullptr_t, slice<T> s) { return len(s) == 0; }

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

        return slice(*this, low, this->size());
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

    template<typename T>
    slice<T> make(Tag<slice<T>>, int n)
    {
        return slice<T>(n);
    }

    template<typename T>
    slice<T> make(Tag<slice<T>>, int n, int r)
    {
        return slice<T>(n, r);
    }

    template<typename K, typename V>
    gocpp::map<K, V> make(Tag<gocpp::map<K, V>>)
    {
        return gocpp::map<K, V>();
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
}

// temporary mock implementations
namespace mocklib
{
    // mock "time" types and functions
    struct Date
    {
        static Date Now() { return Date{}; };
        static const int Saturday = 6;
    };

    inline int Weekday(const Date &) { return Date::Saturday; };
    inline int Hour(const Date &) { return 17; };

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

    // internals: operators for tupples/ostream/slices
    template<typename... Ts>
    std::ostream& operator<<(std::ostream& os, std::tuple<Ts...> const& theTuple)
    {
        std::apply
        (
            [&os](Ts const&... tupleArgs)
            {
                os << '[';
                std::size_t n{0};
                ((os << tupleArgs << (++n != sizeof...(Ts) ? ", " : "")), ...);
                os << ']';
            }, theTuple
        );
        return os;
    }

    template<typename T, int N>
    std::ostream& operator<<(std::ostream& os, gocpp::array<T, N> const& array)
    {
        os << '[';
        for(int i=0; i< array.size(); ++i)
        {
            if(i == 0)
                os << array[i];
            else
                os << " " << array[i];
        }
        os << ']';
        return os;
    }

    template<typename T>
    std::ostream& operator<<(std::ostream& os, std::initializer_list<T> const& array)
    {
        os << '[';
        int i = 0;
        for(const T& item : array)
        {
            if(i == 0)
                os << item;
            else
                os << " " << item;

            i++;
        }
        os << ']';
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
                os << slice[i];
            else
                os << " " << slice[i];
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

    template<typename T>
    std::ostream& operator<<(std::ostream& os, gocpp::slice<T> const& slice)
    {
        return PrintSliceTo<T>(gocpp::IsGoStruct<T>(), os, slice);
    }

    void PrintToVect(std::vector<std::string>&);

    template<typename T>
    void PrintToVect(std::vector<std::string>& out, const T& value);

    template<typename T, typename... Args>
    void PrintToVect(std::vector<std::string>& out, const T& value, Args&&... args);

    void Print(const Date& value)
    {
        std::cout << "[DATE]";
    }

    void Print(bool value)
    {
        std::cout << value;
    }

    template<typename K, typename V>
    void Print(const gocpp::map<K, V>& value)
    {
        std::cout << "map[";
        auto sep = "";
        for(auto kv : value)
        {
            std::cout << sep << kv.first << ":" << kv.second;
            sep = " ";
        }
        std::cout << "]";
    }

    template<typename V>
    void Print(const gocpp::map_value<V>& value)
    {
        std::cout << std::get<0>(value);
    }

    template<typename T>
    void Print(const T& value)
    {
        std::cout << value;
    }

    template<typename T, typename... Args>
    void Print(const T& value, Args&&... args)
    {
        Print(value);
        Print(" ");
        Print(std::forward<Args>(args)...);
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
        std::stringstream sstr;
        sstr << value;
        return sstr.str();
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
    void picShow(const T& func){ /* Just a mock */ }
}
