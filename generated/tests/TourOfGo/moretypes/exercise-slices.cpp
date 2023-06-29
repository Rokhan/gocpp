#include <complex>
#include <functional>
#include <iostream>
#include <iomanip>
#include <map>
#include <string>
#include <tuple>
#include <vector>

#include "tests/TourOfGo/moretypes/exercise-slices.h"
#include "gocpp/support.h"


namespace golang
{
    // convertSpecs[ImportSpec] Not implemented => "golang.org/x/tour/pic";
    gocpp::slice<gocpp::slice<uint8>> Pic(int dx, int dy)
    {
        gocpp::Defer defer;
        auto result = gocpp::make(gocpp::Tag<gocpp::slice<gocpp::slice<uint8>>>(), dx);
        for(auto i = 0; i < dx; i++)
        {
            result[i] = gocpp::make(gocpp::Tag<gocpp::slice<uint8>>(), dy);
            for(auto j = 0; j < dy; j++)
            {
                result[i][j] = uint8((i / 2 + j / 2) * (i / 2 - j / 2));
            }
        }
        return result;
    }

    void main()
    {
        gocpp::Defer defer;
        pic.Show(Pic);
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
