#include <complex>
#include <exception>
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
    
    struct GoPanic : std::runtime_error 
    {
        GoPanic(const std::string& message) : runtime_error(message)
        {
        }
    };

    void panic(const std::string& message)
    {
        throw new GoPanic(message);
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

        int lastPos = 0;
        int i = 0;
        for(int pos = format.find("%v"); pos != std::string::npos; pos = format.find("%v", lastPos+1), ++i)
        {
            Print(format.substr(lastPos, pos));
            Print(arguments[i]);
            lastPos = pos;
        }

        // Printing end of format string
        Print(format.substr(lastPos, std::string::npos));

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
}
