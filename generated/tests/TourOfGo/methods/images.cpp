#include <complex>
#include <functional>
#include <iostream>
#include <iomanip>
#include <map>
#include <string>
#include <tuple>
#include <vector>

#include "tests/TourOfGo/methods/images.h"
#include "gocpp/support.h"


namespace golang
{
    // convertSpecs[ImportSpec] Not implemented => "fmt";
    // convertSpecs[ImportSpec] Not implemented => "image";
    void main()
    {
        auto m = NewRGBA(gocpp::recv(image), Rect(gocpp::recv(image), 0, 0, 100, 100));
        mocklib::Println(Bounds(gocpp::recv(m)));
        mocklib::Println(RGBA(gocpp::recv(At(gocpp::recv(m), 0, 0))));
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
