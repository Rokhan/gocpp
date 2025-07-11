// generated by GoCpp from file 'tests/TourOfGo/moretypes/slice-literals.go'
#include <complex>
#include <functional>
#include <iostream>
#include <iomanip>
#include <map>
#include <string>
#include <tuple>
#include <vector>

#include "tests/TourOfGo/moretypes/slice-literals.h"
#include "gocpp/support.h"

#include "golang/fmt/print.h"

namespace golang::main
{
    namespace rec
    {
        using namespace mocklib::rec;
    }

    gocpp::array<std::string, 6> errors = gocpp::Init<gocpp::array<std::string, 6>>([](auto& x) {
        x[3] = "argument list too long"s;
        x[5] = "permission denied"s;
        x[1] = "address already in use"s;
    });
    struct gocpp_id_0
        {
            int i;
            bool b;

            using isGoStruct = void;

            template<typename T> requires gocpp::GoStruct<T>
            operator T()
            {
                T result;
                result.i = this->i;
                result.b = this->b;
                return result;
            }

            template<typename T> requires gocpp::GoStruct<T>
            bool operator==(const T& ref) const
            {
                if (i != ref.i) return false;
                if (b != ref.b) return false;
                return true;
            }

            std::ostream& PrintTo(std::ostream& os) const
            {
                os << '{';
                os << "" << i;
                os << " " << b;
                os << '}';
                return os;
            }
        };

        std::ostream& operator<<(std::ostream& os, const struct gocpp_id_0& value)
        {
            return value.PrintTo(os);
        }


    void main()
    {
        auto q = gocpp::slice<int> {2, 3, 5, 7, 11, 13};
        mocklib::Println(q);
        auto r = gocpp::slice<bool> {true, false, true, true, false, true};
        mocklib::Println(r);
        auto s = gocpp::slice<gocpp_id_0> { {2, true},  {3, false},  {5, true},  {7, true},  {11, false},  {13, true}};
        mocklib::Println(s);
        for(auto [i, err] : errors)
        {
            mocklib::Println(i, err);
        }
    }

}

int main()
{
    try
    {
        std::cout << std::boolalpha << std::setprecision(5) << std::fixed;
        golang::main::main();
        return 0;
    }
    catch(const gocpp::GoPanic& ex)
    {
        std::cout << "Panic: " << ex.what() << std::endl;
        return -1;
    }
}
