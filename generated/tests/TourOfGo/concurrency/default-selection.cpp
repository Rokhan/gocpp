#include <complex>
#include <functional>
#include <iostream>
#include <iomanip>
#include <map>
#include <string>
#include <tuple>
#include <vector>

#include "tests/TourOfGo/concurrency/default-selection.h"
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
        auto tick = mocklib::Tick(100 * mocklib::Millisecond);
        auto boom = mocklib::After(500 * mocklib::Millisecond);
        mocklib::Sleep(10 * mocklib::Millisecond);
        for(; ; )
        {
            //Go select emulation
            {
                int conditionId = -1;
                if(auto [gocpp_ignored , ok] = tick.tryRecv(); ok) { conditionId = 0; }
                else if(auto [gocpp_ignored , ok] = boom.tryRecv(); ok) { conditionId = 1; }
                switch(conditionId)
                {
                    case 0:
                        mocklib::Println("tick.");
                        break;
                    case 1:
                        mocklib::Println("BOOM!");
                        return;
                        break;
                    default:
                        mocklib::Println("    .");
                        mocklib::Sleep(50 * mocklib::Millisecond);
                        break;
                }
            }
            std::this_thread::yield();
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
