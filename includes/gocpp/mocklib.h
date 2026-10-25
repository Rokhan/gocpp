#pragma once

#include "gocpp/support.fwd.h"

#include <any>
#include <iostream>

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

    std::ostream& PrintTo(std::ostream& os, const Date& value);
    std::ostream& PrintTo(std::ostream& os, bool value);
    std::ostream& PrintTo(std::ostream& os, char value);
    std::ostream& PrintTo(std::ostream& os, unsigned char value);

    template<typename K, typename V>
    std::ostream& PrintTo(std::ostream& os, const gocpp::map<K, V>& value);

    template<typename T>
    std::ostream& PrintTo(std::ostream& os, const T& value);

    template<typename T, typename E>
    std::ostream& PrintTo(std::ostream& os, const gocpp::result_or_error<T, E>& value);

    template<typename T, typename... Args>
    std::ostream& PrintTo(std::ostream& os, const T& value, Args&&... args);

    namespace rec
    {
    }
}
