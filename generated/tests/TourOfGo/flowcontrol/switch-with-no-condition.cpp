#include <complex>
#include <functional>
#include <iostream>
#include <iomanip>
#include <map>
#include <string>
#include <tuple>
#include <vector>

#include "tests/TourOfGo/flowcontrol/switch-with-no-condition.h"
#include "gocpp/support.h"


namespace golang
{
    // convertSpecs[ImportSpec] Not implemented => "fmt";
    // convertSpecs[ImportSpec] Not implemented => "time";
    void main()
    {
        gocpp::Defer defer;
        auto t = mocklib::Date::Now();
        //Go switch emulation
        {
            int conditionId = -1;
            if(Hour(gocpp::recv(t)) < 12) { conditionId = 0; }
            else if(Hour(gocpp::recv(t)) < 17) { conditionId = 1; }
            switch(conditionId)
            {
                case 0:
                    mocklib::Println("Good morning!");
                    break;
                case 1:
                    mocklib::Println("Good afternoon.");
                    break;
                default:
                    mocklib::Println("Good evening.");
                    break;
            }
        }
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
