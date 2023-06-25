#include <complex>
#include <functional>
#include <iostream>
#include <string>
#include <tuple>
#include <vector>

#include "tests/TourOfGo/moretypes/slices-of-slice.h"
#include "gocpp/support.h"


namespace golang
{
    // convertSpecs[ImportSpec] Not implemented => "fmt";
    // convertSpecs[ImportSpec] Not implemented => "strings";
    void main()
    {
        gocpp::Defer defer;
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
        std::cout << std::boolalpha;
        golang::main();
        return 0;
    }
    catch(const gocpp::GoPanic& ex)
    {
        std::cout << "Panic: " << ex.what() << std::endl;
        return -1;
    }
}
