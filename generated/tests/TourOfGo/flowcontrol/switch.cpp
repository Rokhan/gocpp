// generated by GoCpp from file 'tests/TourOfGo/flowcontrol/switch.go'
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

#include "golang/fmt/print.h"
#include "golang/runtime/extern.h"

namespace golang::main
{
    namespace rec
    {
        using namespace mocklib::rec;
    }

    void testFallThrough(int n)
    {
        //Go switch emulation
        {
            auto condition = n;
            int conditionId = -1;
            if(condition == 1) { conditionId = 0; }
            else if(condition == 2) { conditionId = 1; }
            else if(condition == 3) { conditionId = 2; }
            switch(conditionId)
            {
                case 0:
                    mocklib::Print("1 "s);
                case 1:
                    mocklib::Print("2 "s);
                case 2:
                    mocklib::Print("3 "s);
                default:
                    mocklib::Printf("Soleil !\n"s);
                    break;
            }
        }
    }

    void main()
    {
        mocklib::Print("Go runs on "s);
        //Go switch emulation
        {
            auto os = mocklib::GOOS;
            auto condition = os;
            int conditionId = -1;
            if(condition == "darwin"s) { conditionId = 0; }
            else if(condition == "linux"s) { conditionId = 1; }
            switch(conditionId)
            {
                case 0:
                    mocklib::Println("OS X."s);
                    break;
                case 1:
                    mocklib::Println("Linux."s);
                    break;
                default:
                    mocklib::Println(os);
                    break;
            }
        }
        mocklib::Print("\nGo runs on "s);
        //Go switch emulation
        {
            auto os = mocklib::GOOS;
            auto condition = os;
            int conditionId = -1;
            if(condition == "darwin"s) { conditionId = 0; }
            else if(condition == "linux"s) { conditionId = 1; }
            else if(condition == "gnu/linux"s) { conditionId = 2; }
            else if(condition == "debian"s) { conditionId = 3; }
            switch(conditionId)
            {
                default:
                    mocklib::Println(os);
                    break;
                case 0:
                    mocklib::Println("OS X."s);
                    break;
                case 1:
                case 2:
                case 3:
                    mocklib::Println("Linux."s);
                    break;
            }
        }
        mocklib::Print("\nGo runs on "s);
        //Go switch emulation
        {
            auto os = mocklib::GOOS;
            auto condition = os;
            int conditionId = -1;
            if(condition == "linux"s) { conditionId = 0; }
            else if(condition == "gnu/linux"s) { conditionId = 1; }
            else if(condition == "debian"s) { conditionId = 2; }
            else if(condition == "darwin"s) { conditionId = 3; }
            switch(conditionId)
            {
                case 0:
                case 1:
                case 2:
                    mocklib::Println("Linux."s);
                    break;
                default:
                    mocklib::Println(os);
                    break;
                case 3:
                    mocklib::Println("OS X."s);
                    break;
            }
        }
        testFallThrough(0);
        testFallThrough(1);
        testFallThrough(2);
        testFallThrough(3);
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
