#pragma once

#include <functional>
#include <string>
#include <tuple>
#include <vector>

#include "gocpp/support.h"

namespace golang
{
    void Crawl(std::string url, int depth, Fetcher fetcher);
    void main();
    struct fakeResult;
    std::tuple<std::string, gocpp::slice<std::string>, error> Fetch(fakeFetcher f, std::string url);
}

