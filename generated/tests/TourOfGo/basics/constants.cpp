#include <complex>
#include <functional>
#include <iostream>
#include <iomanip>
#include <map>
#include <string>
#include <tuple>
#include <vector>

#include "tests/TourOfGo/basics/constants.h"
#include "gocpp/support.h"


namespace golang
{
    // convertSpecs[ImportSpec] Not implemented => "fmt";
    auto Pi = 3.14;
    void main()
    {
        gocpp::Defer defer;
        auto World = "世界";
        mocklib::Println("Hello", World);
        mocklib::Println("Happy", Pi, "Day");
        auto Truth = true;
        mocklib::Println("Go rules?", Truth);
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
