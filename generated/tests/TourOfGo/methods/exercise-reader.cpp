#include <complex>
#include <functional>
#include <iostream>
#include <iomanip>
#include <map>
#include <string>
#include <tuple>
#include <vector>

#include "tests/TourOfGo/methods/exercise-reader.h"
#include "gocpp/support.h"


namespace golang
{
    // convertSpecs[ImportSpec] Not implemented => "golang.org/x/tour/reader";
    
    std::ostream& MyReader::PrintTo(std::ostream& os) const
    {
        os << '{';
        os << '}';
        return os;
    }

    std::ostream& operator<<(std::ostream& os, const MyReader& value)
    {
        return value.PrintTo(os);
    }

    void main()
    {
        Validate(gocpp::recv(reader), MyReader {});
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
