#pragma once

#include "gocpp/support.fwd.h"

#include "gocpp/array.h"
#include "gocpp/mocklib.h"

namespace gocpp
{
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
            mStart = low + a.mBase;
            mEnd = high + a.mBase;
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

            this->mArray = std::make_shared<store_type>(a.mArray->begin() + a.mBase + low, a.mArray->begin() + a.mBase + high);
            this->mArray->reserve(capacity);
            mStart = 0;
            mEnd = high - low;
        }

        // TODO : other constructors

        slice& operator=(std::nullptr_t)
        {
            this->mArray->clear();
            mStart = 0;
            mEnd = 0;
            return *this;
        }

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
            return std::string(this->mArray->begin() + mStart, this->mArray->begin() + mEnd);
        }

        // Go: string([]rune). Each rune is encoded as UTF-8.
        operator std::string() const requires std::is_same<T, gocpp::rune>::value
        {
            std::string result;
            if(!this->mArray)
            {
                return result;
            }
            for(int i = mStart; i < mEnd; ++i)
            {
                result += mocklib::RuneToString((*this->mArray)[i]);
            }
            return result;
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

        // put all elements to default value
        friend inline void clear(slice<T> input)
        {
            for(size_t i = input.mStart; i < input.mEnd; i++)
            {
                (*input.mArray)[i] = T();
            }
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
}