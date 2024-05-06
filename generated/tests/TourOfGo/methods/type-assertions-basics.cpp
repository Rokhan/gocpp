#include <complex>
#include <functional>
#include <iostream>
#include <iomanip>
#include <map>
#include <string>
#include <tuple>
#include <vector>

#include "tests/TourOfGo/methods/type-assertions-basics.h"
#include "gocpp/support.h"


namespace golang
{
    // convertSpecs[ImportSpec] Not implemented => "fmt";
    void main()
    {
        std::any value = "hello";
        auto s = gocpp::getValue<std::string>(value);
        mocklib::Println(s);
        value = 6.54321;
        auto f = gocpp::getValue<double>(value);
        mocklib::Println(f);
        value = 65;
        auto i = gocpp::getValue<int>(value);
        mocklib::Println(i);
        value = true;
        auto b = gocpp::getValue<bool>(value);
        mocklib::Println(b);
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
