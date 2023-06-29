#include <complex>
#include <functional>
#include <iostream>
#include <iomanip>
#include <map>
#include <string>
#include <tuple>
#include <vector>

#include "tests/TourOfGo/flowcontrol/switch-evaluation-order.h"
#include "gocpp/support.h"


namespace golang
{
    // convertSpecs[ImportSpec] Not implemented => "fmt";
    // convertSpecs[ImportSpec] Not implemented => "time";
    void main()
    {
        gocpp::Defer defer;
        mocklib::Println("When's Saturday?");
        auto today = mocklib::Date::Now().Weekday();
        //Go switch emulation
        {
            auto condition = mocklib::Date::Saturday;
            int conditionId = -1;
            if(condition == today + 0) { conditionId = 0; }
            else if(condition == today + 1) { conditionId = 1; }
            else if(condition == today + 2) { conditionId = 2; }
            switch(conditionId)
            {
                case 0:
                    mocklib::Println("Today.");
                    break;
                case 1:
                    mocklib::Println("Tomorrow.");
                    break;
                case 2:
                    mocklib::Println("In two days.");
                    break;
                default:
                    mocklib::Println("Too far away.");
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
