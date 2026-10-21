#pragma once

#include "gocpp/support.fwd.h"
#include "gocpp/common.h"

#include <cstddef>
#include <initializer_list>
#include <iostream>
#include <map>
#include <memory>
#include <string>
#include <tuple>
#include <utility>

namespace gocpp
{
    // Tag selecting the non-nil constructor: map[K]V{} in Go is non-nil and empty.
    struct non_nil_t { explicit non_nil_t() = default; };
    inline constexpr non_nil_t non_nil{};

    // A Go map is a reference type: copies share the same store, and
    // nil is the absence of a store.
    //
    // There is no operator[]: the converter picks the access by context.
    //   m[k] (read)         -> m.get(k)     zero value when absent or nil, never inserts
    //   v, ok := m[k]       -> m.lookup(k)  std::tuple<V, bool>
    //   m[k] = v, m[k]++    -> m.ref(k)     inserts, panics on a nil map
    template <typename K, typename V>
    struct map
    {
        using store_type = std::map<K, V>;
        using value_type = typename store_type::value_type;
        using iterator = typename store_type::iterator;
        using const_iterator = typename store_type::const_iterator;

        map() = default;                                  // nil (Go zero value)
        map(std::nullptr_t) { }
        map(non_nil_t) : mStore(std::make_shared<store_type>()) { }
        map(std::initializer_list<value_type> init) : mStore(std::make_shared<store_type>(init)) { }
        explicit map(int /*capacity hint*/) : mStore(std::make_shared<store_type>()) { }

        // Go: m = nil rebinds this variable only. Other aliases keep the data.
        map& operator=(std::nullptr_t) { mStore.reset(); return *this; }

        bool is_nil() const { return !mStore; }

        // C++20 synthesizes the reversed form and operator!=
        friend bool operator==(const map& m, std::nullptr_t) { return m.is_nil(); }

        size_t size() const { return mStore ? mStore->size() : 0; }
        bool empty() const { return size() == 0; }

        V get(const K& key) const
        {
            if(mStore)
            {
                auto it = mStore->find(key);
                if(it != mStore->end()) { return it->second; }
            }
            return V();
        }

        std::tuple<V, bool> lookup(const K& key) const
        {
            if(mStore)
            {
                auto it = mStore->find(key);
                if(it != mStore->end()) { return {it->second, true}; }
            }
            return {V(), false};
        }

        V& ref(const K& key)
        {
            if(!mStore) { panic("assignment to entry in nil map"); }
            return (*mStore)[key];
        }

        // Iterating a nil map is legal: it visits nothing.
        iterator begin() { return mStore ? mStore->begin() : iterator{}; }
        iterator end()   { return mStore ? mStore->end()   : iterator{}; }
        const_iterator begin() const { return mStore ? std::as_const(*mStore).begin() : const_iterator{}; }
        const_iterator end()   const { return mStore ? std::as_const(*mStore).end()   : const_iterator{}; }

        friend inline long len(const map<K, V>& input) { return input.size(); }
        friend inline void remove(map<K, V>& input, const K& key) { if(input.mStore) { input.mStore->erase(key); } }
        friend inline void clear(map<K, V>& input) { if(input.mStore) { input.mStore->clear(); } }

    private:
        std::shared_ptr<store_type> mStore;
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
