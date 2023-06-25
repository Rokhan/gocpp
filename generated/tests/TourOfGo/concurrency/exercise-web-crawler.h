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
    std::tuple<std::string, gocpp::slice<std::string>, error> Fetch(std::string url);
}

