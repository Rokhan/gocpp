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


namespace golang
{
    // convertSpecs[ImportSpec] Not implemented => "fmt";
    void main()
    {
        gocpp::Defer defer;
        auto q = gocpp::slice<int> {2, 3, 5, 7, 11, 13};
        mocklib::Println(q);
        auto r = gocpp::slice<bool> {true, false, true, true, false, true};
        mocklib::Println(r);
        struct gocpp_id_0
        {
            int i;
            bool b;

            using isGoStruct = void;

            std::ostream& PrintTo(std::ostream& os) const
            {
                os << '{';
                os << "" << i;
                os << " " << b;
                os << '}';
                return os;
            }
        };

        auto s = gocpp::slice<gocpp_id_0> {{2, true}, {3, false}, {5, true}, {7, true}, {11, false}, {13, true}};
        mocklib::Println(s);
    }

}

int main()
{
    try
    {
        std::cout << std::boolalpha << std::fixed << std::setprecision(5);
        golang::main();
        return 0;
    }
    catch(const gocpp::GoPanic& ex)
    {
        std::cout << "Panic: " << ex.what() << std::endl;
        return -1;
    }
}
