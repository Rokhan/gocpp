#include <complex>
#include <functional>
#include <iostream>
#include <string>
#include <tuple>
#include <vector>

#include "tests/TourOfGo/concurrency/exercise-web-crawler.h"
#include "gocpp/support.h"


namespace golang
{
    // convertSpecs[ImportSpec] Not implemented => "fmt";
    !!TYPE_EXPR_ERROR!! [*ast.TypeSpec];
    void Crawl(std::string url, int depth, Fetcher fetcher)
    {
        gocpp::Defer defer;
        if(; depth [[TOKEN_ERROR: '<=' ]] 0)
        {
            return;
        }
        auto [body, urls, err] = fetcher.Fetch(url);
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

    !!TYPE_EXPR_ERROR!! [*ast.TypeSpec];
    struct fakeResult
    {
        std::string body;
        gocpp::slice<std::string> urls;

        const bool isGoStruct = true;

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
    std::tuple<std::string, gocpp::slice<std::string>, error> Fetch(std::string url)
    {
        gocpp::Defer defer;
        if(auto [res, ok] = f[url]; ok)
        {
            return {res.body, res.urls, nullptr};
        }
        return {"", nullptr, fmt::Errorf("not found: %s", url)};
    }

    auto fetcher = fakeFetcher {!!EXPR_ERROR!! [*ast.KeyValueExpr], !!EXPR_ERROR!! [*ast.KeyValueExpr], !!EXPR_ERROR!! [*ast.KeyValueExpr], !!EXPR_ERROR!! [*ast.KeyValueExpr]};
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
