#include <complex>
#include <functional>
#include <iostream>
#include <string>
#include <tuple>
#include <vector>

// Support types implementations
namespace gocpp
{
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
}

// temporary mock implementations
namespace mocklib
{
    inline int Intn(int n)
    {
        return rand() % n;
    }

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

    template<typename T>
    void Printf(const T& value)
    {
        std::cout << value << " ";
    }

    // No real formatting at the moment
    template<typename T, typename... Args>
    void Printf(const T& value, Args&&... args)
    {
        Printf(value);
        Printf(std::forward<Args>(args)...);
    }

    template<typename... Args>
    void Println(Args&&... args)
    {
        Printf(std::forward<Args>(args)...);
        std::cout << "\n";
    }    

    template<typename T>
    std::string Sprint(const T& value)
    {
        std::stringstream sstr;
        sstr << value << " ";
        return sstr.str();
    }

    template<typename T>
    std::string Sprintf(const T& value)
    {
        std::stringstream sstr;
        sstr << value << " ";
        return sstr.str();
    }

    // No real formatting at the moment
    template<typename T, typename... Args>
    std::string Sprintf(const T& value, Args&&... args)
    {
        auto result = Sprintf(value);
        result += Printf(std::forward<Args>(args)...);
        return result;
    }
}
