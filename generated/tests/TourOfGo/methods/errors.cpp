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


namespace golang
{
    // convertSpecs[ImportSpec] Not implemented => "fmt";
    // convertSpecs[ImportSpec] Not implemented => "time";
    
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
        gocpp::Defer defer;
        return mocklib::Sprintf("at %v, %s", e->When, e->What);
    }

    error run()
    {
        gocpp::Defer defer;
        return new MyError {mocklib::Date::Now(), "it didn't work"};
    }

    void main()
    {
        gocpp::Defer defer;
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
        golang::main();
        return 0;
    }
    catch(const gocpp::GoPanic& ex)
    {
        std::cout << "Panic: " << ex.what() << std::endl;
        return -1;
    }
}
