#include <complex>
#include <functional>
#include <iostream>
#include <iomanip>
#include <map>
#include <string>
#include <tuple>
#include <vector>

#include "tests/TourOfGo/flowcontrol/for-break-continue.h"
#include "gocpp/support.h"


namespace golang
{
    // convertSpecs[ImportSpec] Not implemented => "fmt";
    void main()
    {
        gocpp::Defer defer;
        auto sum = 0;
        for(auto i = 0; i < 10; i++)
        {
            if(i % 2 == 0)
            {
                continue;
            }
            sum += i;
        }
        mocklib::Println(sum);
        sum = 0;
        for(auto i = 0; i < 10; i++)
        {
            if(i == 5)
            {
                break;
            }
            sum += i;
        }
        mocklib::Println(sum);
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
