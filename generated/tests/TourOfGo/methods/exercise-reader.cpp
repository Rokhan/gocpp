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

// TODO: package import not implemented
// #include "golang.org/x/tour/reader/validate.h"

namespace golang::main
{
    
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

    std::tuple<int, error> Read(MyReader, gocpp::slice<unsigned char> buffer)
    {
        buffer = gocpp::slice<unsigned char> {'A'};
        return {1, nullptr};
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
        golang::main::main();
        return 0;
    }
    catch(const gocpp::GoPanic& ex)
    {
        std::cout << "Panic: " << ex.what() << std::endl;
        return -1;
    }
}
