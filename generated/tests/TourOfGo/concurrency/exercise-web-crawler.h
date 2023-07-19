#pragma once

#include <functional>
#include <string>
#include <tuple>
#include <vector>

#include "tests/TourOfGo/concurrency/exercise-web-crawler.fwd.h"
#include "gocpp/support.h"

namespace golang
{
    struct Fetcher;
    void Crawl(std::string url, int depth, Fetcher fetcher);
    void main();
    struct fakeResult
    {
        std::string body;
        gocpp::slice<std::string> urls;

        using isGoStruct = void;

        static fakeResult Init(void (init)(fakeResult&));

        std::ostream& PrintTo(std::ostream& os) const;
    };

    std::ostream& operator<<(std::ostream& os, const fakeResult& value);
    std::tuple<std::string, gocpp::slice<std::string>, error> Fetch(fakeFetcher f, std::string url);
}

