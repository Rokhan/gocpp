#pragma once

#include <functional>
#include <string>
#include <tuple>
#include <vector>

#include "tests/TourOfGo/methods/interface-values-with-unitialized.fwd.h"
#include "gocpp/support.h"

namespace golang
{
    struct I
    {
        I(){}
        I(I& i) = default;
        I(const I& i) = default;
        I& operator=(I& i) = default;
        I& operator=(const I& i) = default;

        template<typename T>
        I(T& ref);

        template<typename T>
        I(const T& ref);

        template<typename T>
        I(T* ptr);

        using isGoStruct = void;

        std::ostream& PrintTo(std::ostream& os) const;

        struct II
        {
            virtual void vM() = 0;
        };

        template<typename T, typename StoreT>
        struct IImpl : II
        {
            explicit IImpl(T* ptr)
            {
                value.reset(ptr);
            }

            void vM() override;

            StoreT value;
        };

        std::shared_ptr<II> value;
    };

    void M(const gocpp::PtrRecv<I, false>& self);
    void M(const gocpp::ObjRecv<I>& self);

    std::ostream& operator<<(std::ostream& os, const I& value);
    struct T
    {
        std::string S;

        using isGoStruct = void;

        static T Init(void (init)(T&));

        std::ostream& PrintTo(std::ostream& os) const;
    };

    std::ostream& operator<<(std::ostream& os, const T& value);
    void M(T* t);
    void main();
    void describe(I i);
}

