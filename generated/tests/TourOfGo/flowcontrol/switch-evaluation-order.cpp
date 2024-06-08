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

// TODO: package import not implemented
// #include "fmt/doc.h"
// #include "fmt/errors.h"
// #include "fmt/format.h"
// #include "fmt/print.h"
// #include "fmt/scan.h"
// #include "time/format.h"
// #include "time/format_rfc3339.h"
// #include "time/sleep.h"
// #include "time/sys_windows.h"
// #include "time/tick.h"
// #include "time/time.h"
// #include "time/zoneinfo.h"
// #include "time/zoneinfo_abbrs_windows.h"
// #include "time/zoneinfo_goroot.h"
// #include "time/zoneinfo_read.h"
// #include "time/zoneinfo_windows.h"

namespace golang::main
{
    void main()
    {
        mocklib::Println("When's Saturday?");
        auto today = Weekday(gocpp::recv(mocklib::Date::Now()));
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
        golang::main::main();
        return 0;
    }
    catch(const gocpp::GoPanic& ex)
    {
        std::cout << "Panic: " << ex.what() << std::endl;
        return -1;
    }
}
