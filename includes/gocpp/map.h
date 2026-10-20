#pragma once

#include "gocpp/support.fwd.h"

#include <iostream>
#include <map>
#include <string>
#include <tuple>
#include <type_traits>
#include <utility>

namespace gocpp
{
    template<typename V>
    struct map_value : public std::tuple<typename std::add_lvalue_reference<V>::type, bool>
    {
        using std::tuple<typename std::add_lvalue_reference<V>::type, bool>::tuple;
        using val_ref = typename std::add_lvalue_reference<V>::type;

        val_ref operator= (const V& value)
        {
            return std::get<0>(*this) = value;
        }

        operator val_ref(){ return std::get<0>(*this); }

        template <std::size_t Index>
        std::tuple_element_t<Index, map_value> &get()
        {
            return std::get<Index>(*this);
        }
        
        auto operator->() noexcept -> decltype(std::get<0>(*this))
        {
            return std::get<0>(*this);
        }

        auto operator->() const noexcept -> decltype(std::get<0>(*this))
        {
            return std::get<0>(*this);
        }
    };

    template <typename K, typename V>
    struct map : std::map<K, V>
    {
        using std::map<K, V>::map;
        
        map_value<V> operator[](const K& key)
        {
            auto it = this->find(key);
            if( it != this->end())
            {
                return {it->second, true};
            }

            // FIXME: Not equivalent to go maps.
            // Value are inserted only when explicitly assigned in golang
            return {std::map<K, V>::operator[](key), false};
        }

        friend inline long len(const map<K, V>& input)
        {
            return input.size();
        }

        friend inline void remove(map<K, V>& input, const K& key)
        {
            input.erase(key);
        }

        friend inline void clear(map<K, V>& input)
        {
            input.clear();
        }
    };

    template<typename K, typename V>
    std::ostream& operator<<(std::ostream& os, const gocpp::map<K, V>& dic)
    {
        os << '[';
        int i = 0;
        for(auto& kv : dic)
        {
            if(i != 0) { os << ", "; }            
            os << kv.first << ": " << kv.second;
            i++;
        }
        os << ']';
        return os;
    }
}
