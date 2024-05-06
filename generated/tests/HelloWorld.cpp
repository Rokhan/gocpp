#include <complex>
#include <functional>
#include <iostream>
#include <iomanip>
#include <map>
#include <string>
#include <tuple>
#include <vector>

#include "tests/HelloWorld.h"
#include "gocpp/support.h"


namespace golang
{
    // convertSpecs[ImportSpec] Not implemented => "fmt";
    void main()
    {
        mocklib::Printf("Hello, world.\n");
        auto hello = "Hello";
        auto world = "World";
        helloFunc(hello, world, "!");
        auto a = 5;
        auto b = 8 + 7;
        mocklib::Printf("result = %d\n", a * b + 4);
        mocklib::Printf("\n");
        printN("zzz1", square(3));
        auto n = square(2);
        printN("zzz2", n);
    }

    int square(int num)
    {
        return num * num;
    }

    void helloFunc(std::string str1, std::string str2, std::string str3)
    {
        mocklib::Printf(str1 + ", " + str2 + str3);
    }

    void printN(std::string str1, int n)
    {
        mocklib::Printf(str1 + "%d\n", n);
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
