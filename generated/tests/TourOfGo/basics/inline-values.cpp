#include <complex>
#include <functional>
#include <iostream>
#include <iomanip>
#include <map>
#include <string>
#include <tuple>
#include <vector>

#include "tests/TourOfGo/basics/inline-values.h"
#include "gocpp/support.h"


namespace golang
{
    // convertSpecs[ImportSpec] Not implemented => "fmt";
    void main()
    {
        gocpp::Defer defer;
        mocklib::Println(fetcher["https://golang.org/"]->body);
        for(auto [_, url] : fetcher["https://golang.org/"]->urls)
        {
            mocklib::Println(" -> ", url);
        }
        mocklib::Print("Small primes:");
        for(auto [_, prime] : smallPrimes)
        {
            mocklib::Printf(" %v", prime);
        }
        mocklib::Println();
    }

    ints smallPrimes = ints {2, 3, 5, 7, 11, 13, 17, 19, 23, 29};
    
    std::ostream& fakeResult::PrintTo(std::ostream& os) const
    {
        os << '{';
        os << "" << body;
        os << " " << urls;
        os << '}';
        return os;
    }

    std::ostream& operator<<(std::ostream& os, const fakeResult& value)
    {
        return value.PrintTo(os);
    }

    fakeFetcher fetcher = fakeFetcher {{ "https://golang.org/", new fakeResult {"The Go Programming Language", gocpp::slice<std::string> {"https://golang.org/pkg/", "https://golang.org/cmd/"}} }, { "https://golang.org/pkg/", new fakeResult {"Packages", gocpp::slice<std::string> {"https://golang.org/", "https://golang.org/cmd/", "https://golang.org/pkg/fmt/", "https://golang.org/pkg/os/"}} }, { "https://golang.org/pkg/fmt/", new fakeResult {"Package fmt", gocpp::slice<std::string> {"https://golang.org/", "https://golang.org/pkg/"}} }, { "https://golang.org/pkg/os/", new fakeResult {"Package os", gocpp::slice<std::string> {"https://golang.org/", "https://golang.org/pkg/"}} }};
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