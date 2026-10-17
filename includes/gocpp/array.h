#pragma once

#include "gocpp/support.fwd.h"

#include "gocpp/common.h"
#include "gocpp/mocklib.h"

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

        array_ptr& operator=(TArray* target) { ptr = target; return *this; }

        bool operator==(const array_ptr<TArray>&) const = default;
        bool operator!=(const array_ptr<TArray>&) const = default;

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

        TArray* ptr = nullptr;
    };

    template <typename TArray>
    array_ptr<TArray> make_array_ptr(TArray& target)
    {
        return array_ptr<TArray>(&target);
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
                return { 0, mArray->begin() };
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
                return { mArray->size(), mArray->end() };
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

        bool operator==(const array<T, N>& rhs) const {
            return *this->mArray.get() == *rhs.mArray.get();
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