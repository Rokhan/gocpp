// generated by GoCpp from file '$(ImportDir)/time/format_rfc3339.go'
#pragma once

#include <functional>
#include <string>
#include <tuple>
#include <vector>

#include "golang/time/format_rfc3339.fwd.h"
#include "gocpp/support.h"

#include "golang/time/time.h"
#include "golang/time/zoneinfo.h"

namespace golang::time
{
    gocpp::slice<unsigned char> appendFormatRFC3339(struct Time t, gocpp::slice<unsigned char> b, bool nanos);
    std::tuple<gocpp::slice<unsigned char>, std::string> appendStrictRFC3339(struct Time t, gocpp::slice<unsigned char> b);

    template<typename bytes>
    std::tuple<Time, bool> parseRFC3339(bytes s, Location* local);
    std::tuple<Time, std::string> parseStrictRFC3339(gocpp::slice<unsigned char> b);
}
