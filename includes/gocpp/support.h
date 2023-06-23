#pragma once

#include <complex>
#include <exception>
#include <functional>
#include <iostream>
#include <memory>
#include <string>
#include <tuple>
#include <vector>

// Support types implementations
namespace gocpp
{
	// TODO : make forward declaration header for types

    template<typename T> struct array_base;
    template<typename T, int N> struct array;
    template<typename T> struct slice;
    struct complex128;
    struct Defer;

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

    template<typename T>
    struct array_base
    {
        using vect_iterator = typename std::vector<T>::iterator;
        using const_vect_iterator = typename std::vector<T>::iterator;

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

        const T& operator[](size_t i) const
        {
            if(mArray)
            {
                return mArray->at(i);
            }

            panic("Cannot access item of an empty array");
        }

        T& operator[](size_t i)
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


        gocpp::slice<T> make_slice(int low);
        gocpp::slice<T> make_slice(int low, int high);

    protected:    
        std::shared_ptr<std::vector<T>> mArray;
    };

    template<typename T, int N>
    struct array : array_base<T>
    {
        array()
        {
            this->mArray = std::make_shared<std::vector<T>>(N);
        }

        array(std::initializer_list<T> list)
        {
            this->mArray = std::make_shared<std::vector<T>>(list.begin(), list.end());
        }

        // TODO : other constructors
    };

    template<typename T>
    struct slice : array_base<T>
    {
        using typename array_base<T>::range_iterator;

        slice()
        {
            this->mArray = std::make_shared<std::vector<T>>();
            mStart = 0;
            mEnd = this->size();
        }

        slice(int n)
        {
            this->mArray = std::make_shared<std::vector<T>>(n);
            mStart = 0;
            mEnd = this->size();
        }

        slice(std::initializer_list<T> list)
        {
            this->mArray = std::make_shared<std::vector<T>>(list.begin(), list.end());
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

        const T& operator[](size_t i) const
        {
            return array_base<T>::operator[](i + mStart);
        }

        T& operator[](size_t i)
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

    //private:    
        // [mStart, mEnd[
        int mStart = 0;
        int mEnd = 0;
    };
    
    template<typename T>
    gocpp::slice<T> array_base<T>::make_slice(int low)
    {
        return slice(*this, low, this->size());
    }

    template<typename T>
    gocpp::slice<T> array_base<T>::make_slice(int low, int high)
    {
        return slice(*this, low, high);
    }
    
    template<typename T>
    slice<T> make(Tag<slice<T>>, int n)
    {
        return slice<T>(n);
    }
}

// temporary mock implementations
namespace mocklib
{
    struct Date
    {        
        static Date Now() { return Date{}; };
        static int  Weekday() { return Saturday; };
        static int Hour() { return 17; };
        static const int Saturday = 6;
    };

    inline int Intn(int n)
    {
        return rand() % n;
    }

    const char* const GOOS = "undefined";

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
    // ** the template match nasic_string too
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
    std::ostream& operator<<(std::ostream& os, gocpp::slice<T> const& slice)
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
        std::cout << std::boolalpha << value;
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
        result += Printf(" ");
        result += Printf(std::forward<Args>(args)...);
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
}
