#pragma once

#include "gocpp/support.fwd.h"

#include <any>

namespace mocklib
{
    struct Date;

    std::string Sprint(const std::any& value);
    std::string Sprint(const gocpp::go_any& value);
    inline std::string RuneToString(gocpp::rune r);

    template<typename T>
    std::ostream& PrintSliceTo(std::false_type, std::ostream& os, gocpp::slice<T> const& slice);
        
    template<typename T>
    std::ostream& PrintSliceTo(std::true_type, std::ostream& os, gocpp::slice<T> const& slice);

    template<typename T>
    std::ostream& operator<<(std::ostream& os, const gocpp::array_base<T>& array);

    namespace rec
    {
    }
}
