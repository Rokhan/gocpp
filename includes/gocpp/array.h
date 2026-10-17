#pragma once

#include "gocpp/support.fwd.h"

#include "gocpp/common.h"
#include "gocpp/mocklib.h"

#include <concepts>
#include <initializer_list>
#include <memory>
#include <type_traits>
#include <vector>

namespace gocpp
{
    // TODO: we should add a parameter to indicate if we own or rent the target pointer
    template <typename TArray>
    struct array_ptr
    {
        array_ptr() { }
        array_ptr(TArray* target) { ptr = target; }

        array_ptr& operator=(TArray* target) { ptr = target; owner.reset(); return *this; }

        // Go: (*[N]T)(s). The result aliases the slice storage (no copy), and panics if len(s) < N.
        template <typename E> requires std::same_as<typename array_base<E>::element_type, typename TArray::element_type>
        array_ptr(const slice<E>& s)
        {
            if(len(s) < TArray::length)
            {
                panic("runtime error: cannot convert slice with length too short to array or pointer to array");
            }
            owner = std::make_shared<TArray>(s.mArray, s.mStart);
            ptr = owner.get();
        }

        // Pointers created from slices own distinct view objects: compare targets only.
        bool operator==(const array_ptr<TArray>& rhs) const { return ptr == rhs.ptr; }
        bool operator!=(const array_ptr<TArray>& rhs) const { return ptr != rhs.ptr; }

        TArray& operator*() { check_not_null(); return *ptr; }
        const TArray& operator*() const { check_not_null(); return *ptr; }

        bool operator==(std::nullptr_t) const { return ptr == nullptr; }
        bool operator!=(std::nullptr_t) const { return ptr != nullptr; }

        TArray::element_type& operator[](size_t index) { return (*ptr)[index]; }
        const TArray::element_type& operator[](size_t index) const { return (*ptr)[index]; }

        inline slice<typename TArray::element_type> make_slice(size_t low) const
        {
            check_not_null();
            return ptr->make_slice(low);
        }

        inline slice<typename TArray::element_type> make_slice(size_t low, size_t high) const
        {
            check_not_null();
            return ptr->make_slice(low, high);
        }

        void check_not_null() const
        {
            if(ptr == nullptr)
            {
                panic("runtime error: slice of nil array pointer");
            }
        }

        TArray::range_iterator begin()
        {
            return ptr->begin();
        }

        TArray::range_iterator end()
        {
            return ptr->end();
        }

        // Keeps the array view alive when built from a slice, empty otherwise.
        std::shared_ptr<TArray> owner;
        TArray* ptr = nullptr;
    };

    template <typename TArray>
    array_ptr<TArray> make_array_ptr(TArray& target)
    {
        return array_ptr<TArray>(&target);
    }

    // Go: (*[N]T)(s), the result aliases the slice storage. Panics if len(s) < N.
    // TArray is the array type (possibly a named one), or just N for a plain [N]E.
    template <typename TArray, typename E>
    array_ptr<TArray> slice_to_array_ptr(const slice<E>& s)
    {
        return array_ptr<TArray>(s);
    }

    template <int N, typename E>
    array_ptr<array<E, N>> slice_to_array_ptr(const slice<E>& s)
    {
        return slice_to_array_ptr<array<E, N>>(s);
    }

    // Go: [N]T(s), the result is a copy of the first N elements. Panics if len(s) < N.
    template <typename TArray, typename E>
    TArray slice_to_array(const slice<E>& s)
    {
        return *array_ptr<TArray>(s);
    }

    template <int N, typename E>
    array<E, N> slice_to_array(const slice<E>& s)
    {
        return slice_to_array<array<E, N>>(s);
    }

    template<typename TArray>
    inline std::ostream& operator<<(std::ostream& os, const array_ptr<TArray>& value)
    {
        if(value.ptr == nullptr)
        {
            os << "nil";
        }
        else
        {
            os << *(value.ptr);
        }
        return os;
    }

    namespace details
    {
        struct bool_wrapper
        {
            bool value = false;
            bool_wrapper() = default;
            constexpr bool_wrapper(bool b) : value(b) { }
            constexpr operator bool() const { return value; }
        };
    }

    template <typename T>
    using safe_vector = std::vector<std::conditional_t<std::is_same_v<T, bool>, details::bool_wrapper, T>>;

    template<typename T>
    struct array_base
    {
        using store_type = safe_vector<T>;
        using element_type = store_type::value_type;
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

        template <typename, int> friend struct array;
        template <typename> friend struct slice;
        template <typename> friend struct array_ptr;

        size_t size() const
        {
            if(mLen >= 0)
            {
                return mLen;
            }

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
                check_view_index(i);
                return mArray->at(i + mBase);
            }

            panic("Cannot access item of an empty array");
        }

        typename store_type::reference operator[](size_t i)
        {
            if(mArray)
            {
                check_view_index(i);
                return mArray->at(i + mBase);
            }

            panic("Cannot access item of an empty array");
        }

        range_iterator begin()
        {
            if(mArray)
            {
                return { 0, mArray->begin() + mBase };
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
                return { size(), mArray->begin() + mBase + (std::ptrdiff_t)size() };
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

        void check_view_index(size_t i) const
        {
            if(mLen >= 0 && i >= (size_t)mLen)
            {
                panic("runtime error: index out of range");
            }
        }

        std::shared_ptr<store_type> mArray;

        // Window on *mArray: [mBase, mBase + mLen). mLen < 0 means "the whole vector".
        // Only used by arrays built as views over slice storage (see array_ptr).
        int mBase = 0;
        int mLen = -1;
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

        static constexpr int length = N;

        // View over [base, base + N) of an existing store, used by array_ptr(slice).
        array(std::shared_ptr<store_type> store, int base)
        {
            this->mArray = std::move(store);
            this->mBase = base;
            this->mLen = N;
        }

        // Go arrays are values: copies are deep.
        array(const array& other)
        {
            this->mArray = std::make_shared<store_type>(N);
            for(int i = 0; i < N; ++i) (*this)[i] = other[i];
        }

        array(array&& other)
        {
            if(other.mLen < 0)
            {
                this->mArray = std::move(other.mArray);
            }
            else
            {
                this->mArray = std::make_shared<store_type>(N);
                for(int i = 0; i < N; ++i) (*this)[i] = other[i];
            }
        }

        // Assignment copies elements, so it writes through views: `*p = x`.
        array& operator=(const array& rhs)
        {
            if(this == &rhs) return *this;
            if(!this->mArray) this->mArray = std::make_shared<store_type>(N);
            for(int i = 0; i < N; ++i) (*this)[i] = rhs[i];
            return *this;
        }

        array& operator=(array&& rhs)
        {
            return *this = static_cast<const array&>(rhs);
        }

        // TODO : other constructors

        bool operator==(const array<T, N>& rhs) const {
            for(int i = 0; i < N; ++i)
            {
                if(!((*this)[i] == rhs[i])) return false;
            }
            return true;
        }

        friend constexpr long len(const array<T, N>& input)
        {
            return N;
        }

        // maybe not needed as we use array_ptr now
        friend constexpr long len(const array<T, N>* input)
        {
            return N;
        }

        friend constexpr long len(const array_ptr<array<T, N>> input)
        {
            return N;
        }
    };

    template<typename T, int N>
    inline std::ostream& operator<<(std::ostream& os, const array<T, N>& arr)
    {
        return mocklib::operator<<(os, arr);
    }
}