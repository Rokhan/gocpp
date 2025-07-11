// generated by GoCpp from file 'tests/TourOfGo/flowcontrol/switch-evaluation-order.go'
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

#include "golang/fmt/print.h"
#include "golang/time/time.h"
#include "golang/time/zoneinfo.h"

namespace golang::main
{
    namespace rec
    {
        using namespace mocklib::rec;
        using mocklib::rec::Weekday;
    }

    void main()
    {
        mocklib::Println("When's Saturday?"s);
        auto today = rec::Weekday(gocpp::recv(mocklib::Date::Now()));
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
                    mocklib::Println("Today."s);
                    break;
                case 1:
                    mocklib::Println("Tomorrow."s);
                    break;
                case 2:
                    mocklib::Println("In two days."s);
                    break;
                default:
                    mocklib::Println("Too far away."s);
                    break;
            }
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
