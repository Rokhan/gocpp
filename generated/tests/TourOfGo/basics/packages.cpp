#include <complex>
#include <functional>
#include <iostream>
#include <iomanip>
#include <map>
#include <string>
#include <tuple>
#include <vector>

#include "tests/TourOfGo/basics/packages.h"
#include "gocpp/support.h"

// TODO: package import not implemented
// #include "fmt/doc.h"
// #include "fmt/errors.h"
// #include "fmt/format.h"
// #include "fmt/print.h"
// #include "fmt/scan.h"
// #include "math/rand/exp.h"
// #include "math/rand/normal.h"
// #include "math/rand/rand.h"
// #include "math/rand/rng.h"
// #include "math/rand/zipf.h"

namespace golang::main
{
    void main()
    {
        mocklib::Println("My favorite number is", mocklib::Intn(10));
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
