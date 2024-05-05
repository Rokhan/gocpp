#include <complex>
#include <functional>
#include <iostream>
#include <iomanip>
#include <map>
#include <string>
#include <tuple>
#include <vector>

#include "tests/TourOfGo/concurrency/exercise-equivalent-binary-trees.h"
#include "gocpp/support.h"


namespace golang
{
    // convertSpecs[ImportSpec] Not implemented => "fmt";
    // convertSpecs[ImportSpec] Not implemented => "golang.org/x/tour/tree";
    void Walk(tree::Tree* t, gocpp::channel<int> ch)
    {
        gocpp::Defer defer;
        gocpp::panic("Not implemented");
    }

    bool Same(tree::Tree* t1, tree::Tree* t2)
    {
        gocpp::Defer defer;
        gocpp::panic("Not implemented");
    }

    void main()
    {
        gocpp::Defer defer;
        tree::Tree tree = {};
        mocklib::Printf("%T", tree);
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
