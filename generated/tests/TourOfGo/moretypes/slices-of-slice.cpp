#include <complex>
#include <functional>
#include <iostream>
#include <iomanip>
#include <map>
#include <string>
#include <tuple>
#include <vector>

#include "tests/TourOfGo/moretypes/slices-of-slice.h"
#include "gocpp/support.h"

// TODO: package import not implemented
// #include "fmt/doc.h"
// #include "fmt/errors.h"
// #include "fmt/format.h"
// #include "fmt/print.h"
// #include "fmt/scan.h"
// #include "strings/builder.h"
// #include "strings/clone.h"
// #include "strings/compare.h"
// #include "strings/reader.h"
// #include "strings/replace.h"
// #include "strings/search.h"
// #include "strings/strings.h"

namespace golang::main
{
    void main()
    {
        auto board = gocpp::slice<gocpp::slice<std::string>> {gocpp::slice<std::string> {"_", "_", "_"}, gocpp::slice<std::string> {"_", "_", "_"}, gocpp::slice<std::string> {"_", "_", "_"}};
        board[0][0] = "X";
        board[2][2] = "O";
        board[1][2] = "X";
        board[1][0] = "O";
        board[0][2] = "X";
        for(auto i = 0; i < len(board); i++)
        {
            mocklib::Printf("%v\n", mocklib::StringsJoin(board[i], " "));
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
