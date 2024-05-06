#include <complex>
#include <functional>
#include <iostream>
#include <iomanip>
#include <map>
#include <string>
#include <tuple>
#include <vector>

#include "tests/TourOfGo/methods/exercise-rot-reader.h"
#include "gocpp/support.h"


namespace golang
{
    // convertSpecs[ImportSpec] Not implemented => "io";
    // convertSpecs[ImportSpec] Not implemented => "os";
    // convertSpecs[ImportSpec] Not implemented => "strings";
    
    std::ostream& rot13Reader::PrintTo(std::ostream& os) const
    {
        os << '{';
        os << "" << r;
        os << '}';
        return os;
    }

    std::ostream& operator<<(std::ostream& os, const rot13Reader& value)
    {
        return value.PrintTo(os);
    }

    void main()
    {
        auto s = strings::NewReader("Lbh penpxrq gur pbqr!");
        auto r = rot13Reader {s};
        Copy(gocpp::recv(io), os.Stdout, & r);
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
