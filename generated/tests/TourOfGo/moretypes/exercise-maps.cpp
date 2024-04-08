#include <complex>
#include <functional>
#include <iostream>
#include <iomanip>
#include <map>
#include <string>
#include <tuple>
#include <vector>

#include "tests/TourOfGo/moretypes/exercise-maps.h"
#include "gocpp/support.h"


namespace golang
{
    // convertSpecs[ImportSpec] Not implemented => "strings";
    // convertSpecs[ImportSpec] Not implemented => "golang.org/x/tour/wc";
    gocpp::map<std::string, int> WordCount(std::string s)
    {
        gocpp::Defer defer;
        auto fields = mocklib::StringsFields(s);
        auto wc = gocpp::make(gocpp::Tag<gocpp::map<std::string, int>>());
        for(auto [_, f] : fields)
        {
            wc[f]++;
        }
        return wc;
    }

    void main()
    {
        gocpp::Defer defer;
        mocklib::wcTest(WordCount);
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
