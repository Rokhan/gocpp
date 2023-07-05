#include <complex>
#include <functional>
#include <iostream>
#include <iomanip>
#include <map>
#include <string>
#include <tuple>
#include <vector>

#include "tests/TourOfGo/concurrency/exercise-web-crawler.h"
#include "gocpp/support.h"


namespace golang
{
    // convertSpecs[ImportSpec] Not implemented => "fmt";
    !!TYPE_SPEC_ERROR!! [*ast.TypeSpec];
    void Crawl(std::string url, int depth, Fetcher fetcher)
    {
        gocpp::Defer defer;
        if(; depth [[TOKEN_ERROR: '<=' ]] 0)
        {
            return;
        }
        auto [body, urls, err] = Fetch(fetcher, url);
        if(; err [[TOKEN_ERROR: '!=' ]] nullptr)
        {
            mocklib::Println(err);
            return;
        }
        mocklib::Printf("found: %s %q\n", url, body);
        for(auto [_, u] : urls)
        {
            Crawl(u, depth - 1, fetcher);
        }
        return;
    }

    void main()
    {
        gocpp::Defer defer;
        Crawl("https://golang.org/", 4, fetcher);
    }

    !!TYPE_SPEC_ERROR!! [*ast.TypeSpec];
    struct fakeResult
    {
        std::string body;
        gocpp::slice<std::string> urls;

        using isGoStruct = void;

        static fakeResult Init(void (init)(fakeResult&))
        {
            fakeResult value;
            init(value);
            return value;
        }

        std::ostream& PrintTo(std::ostream& os) const
        {
            os << '{';
            os << "" << body;
            os << " " << urls;
            os << '}';
            return os;
        }
    };

    std::ostream& operator<<(std::ostream& os, const fakeResult& value)
    {
        return value.PrintTo(os);
    }
;
    std::tuple<std::string, gocpp::slice<std::string>, error> Fetch(fakeFetcher f, std::string url)
    {
        gocpp::Defer defer;
        if(auto [res, ok] = f[url]; ok)
        {
            return {res.body, res.urls, nullptr};
        }
        return {"", nullptr, fmt::Errorf("not found: %s", url)};
    }

    auto fetcher = fakeFetcher::Init([](fakeFetcher& x) { x.&{%!s(token.Pos=1169) STRING "https://golang.org/"} = new fakeResult {"The Go Programming Language", gocpp::slice<std::string> {"https://golang.org/pkg/", "https://golang.org/cmd/"}}; x.&{%!s(token.Pos=1320) STRING "https://golang.org/pkg/"} = new fakeResult {"Packages", gocpp::slice<std::string> {"https://golang.org/", "https://golang.org/cmd/", "https://golang.org/pkg/fmt/", "https://golang.org/pkg/os/"}}; x.&{%!s(token.Pos=1519) STRING "https://golang.org/pkg/fmt/"} = new fakeResult {"Package fmt", gocpp::slice<std::string> {"https://golang.org/", "https://golang.org/pkg/"}}; x.&{%!s(token.Pos=1658) STRING "https://golang.org/pkg/os/"} = new fakeResult {"Package os", gocpp::slice<std::string> {"https://golang.org/", "https://golang.org/pkg/"}}; });
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
