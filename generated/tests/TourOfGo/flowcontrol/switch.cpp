#include <complex>
#include <functional>
#include <iostream>
#include <iomanip>
#include <map>
#include <string>
#include <tuple>
#include <vector>

#include "tests/TourOfGo/flowcontrol/switch.h"
#include "gocpp/support.h"


namespace golang
{
    // convertSpecs[ImportSpec] Not implemented => "fmt";
    // convertSpecs[ImportSpec] Not implemented => "runtime";
    void main()
    {
        gocpp::Defer defer;
        mocklib::Print("Go runs on ");
        //Go switch emulation
        {
            auto os = mocklib::GOOS;
            auto condition = os;
            int conditionId = -1;
            if(condition == "darwin") { conditionId = 0; }
            else if(condition == "linux") { conditionId = 1; }
            switch(conditionId)
            {
                case 0:
                    mocklib::Println("OS X.");
                    break;
                case 1:
                    mocklib::Println("Linux.");
                    break;
                default:
                    mocklib::Printf("%s.\n", os);
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
