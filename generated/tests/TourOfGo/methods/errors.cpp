#include <complex>
#include <functional>
#include <iostream>
#include <iomanip>
#include <map>
#include <string>
#include <tuple>
#include <vector>

#include "tests/TourOfGo/methods/errors.h"
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
    
    std::ostream& MyError::PrintTo(std::ostream& os) const
    {
        os << '{';
        os << "" << When;
        os << " " << What;
        os << '}';
        return os;
    }

    std::ostream& operator<<(std::ostream& os, const MyError& value)
    {
        return value.PrintTo(os);
    }

    std::string Error(MyError* e)
    {
        return mocklib::Sprintf("at %v, %s", e->When, e->What);
    }

    error run()
    {
        return new MyError {mocklib::Date::Now(), "it didn't work"};
    }

    void main()
    {
        if(auto err = run(); err != nullptr)
        {
            mocklib::Println(err);
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
