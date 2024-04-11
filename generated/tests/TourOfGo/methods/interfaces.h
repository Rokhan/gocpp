#pragma once

#include <functional>
#include <string>
#include <tuple>
#include <vector>

#include "tests/TourOfGo/methods/interfaces.fwd.h"
#include "gocpp/support.h"

namespace golang
{
    struct Abser
    {
        Abser(){}
        Abser(Abser& i) = default;
        Abser(const Abser& i) = default;
        Abser& operator=(Abser& i) = default;
        Abser& operator=(const Abser& i) = default;

        template<typename T>
        Abser(T& ref);

        template<typename T>
        Abser(const T& ref);

        template<typename T>
        Abser(T* ptr);

        using isGoStruct = void;

        std::ostream& PrintTo(std::ostream& os) const;

        struct IAbser
        {
            virtual double vAbs() = 0;
        };

        template<typename T, typename StoreT>
        struct AbserImpl : IAbser
        {
            explicit AbserImpl(T* ptr)
            {
                value.reset(ptr);
            }

            double vAbs() override;

            StoreT value;
        };

        std::shared_ptr<IAbser> value;
    };

    double Abs(const gocpp::PtrRecv<Abser, false>& self);
    double Abs(const gocpp::ObjRecv<Abser>& self);

    std::ostream& operator<<(std::ostream& os, const Abser& value);
    void main();
    using MyFloat = double;
    double Abs(MyFloat f);
    struct Vertex
    {
        double X;
        double Y;

        using isGoStruct = void;

        std::ostream& PrintTo(std::ostream& os) const;
    };

    std::ostream& operator<<(std::ostream& os, const Vertex& value);
    double Abs(Vertex* v);
}

