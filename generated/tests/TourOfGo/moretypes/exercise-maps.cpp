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

// TODO: package import not implemented
// #include "strings/builder.h"
// #include "strings/clone.h"
// #include "strings/compare.h"
// #include "strings/reader.h"
// #include "strings/replace.h"
// #include "strings/search.h"
// #include "strings/strings.h"
// #include "golang.org/x/tour/wc/wc.h"

namespace golang::main
{
    gocpp::map<std::string, int> WordCount(std::string s)
    {
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
        mocklib::wcTest(WordCount);
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
