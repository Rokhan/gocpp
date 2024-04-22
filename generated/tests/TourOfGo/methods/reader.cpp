#include <complex>
#include <functional>
#include <iostream>
#include <iomanip>
#include <map>
#include <string>
#include <tuple>
#include <vector>

#include "tests/TourOfGo/methods/reader.h"
#include "gocpp/support.h"


namespace golang
{
    // convertSpecs[ImportSpec] Not implemented => "fmt";
    // convertSpecs[ImportSpec] Not implemented => "io";
    // convertSpecs[ImportSpec] Not implemented => "strings";
    void main()
    {
        gocpp::Defer defer;
        auto r = strings::NewReader("Hello, Reader!");
        auto b = gocpp::make(gocpp::Tag<gocpp::slice<unsigned char>>(), 8);
        for(; ; )
        {
            auto [n, err] = Read(gocpp::recv(r), b);
            mocklib::Printf("n = %v err = %v b = %v\n", n, err, b);
            mocklib::Printf("b[:n] = %q\n", b.make_slice(0, n));
            if(err == io.EOF)
            {
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
