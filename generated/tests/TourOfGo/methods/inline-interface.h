#pragma once

#include <functional>
#include <string>
#include <tuple>
#include <vector>

#include "tests/TourOfGo/methods/inline-interface.fwd.h"
#include "gocpp/support.h"

namespace golang
{
    using MyInt = int;
    using MyFloat = double;
    double Abs(MyInt i);
    double Abs(MyFloat f);
    struct Vertex
    {
        double X;
        double Y;

        using isGoStruct = void;

        std::ostream& PrintTo(std::ostream& os) const;
    };

    std::ostream& operator<<(std::ostream& os, const Vertex& value);
    double Abs(Vertex v);
    void main();
    struct gocpp_id_0 : gocpp::Interface
    {
        gocpp_id_0(){}
        gocpp_id_0(gocpp_id_0& i) = default;
        gocpp_id_0(const gocpp_id_0& i) = default;
        gocpp_id_0& operator=(gocpp_id_0& i) = default;
        gocpp_id_0& operator=(const gocpp_id_0& i) = default;

        template<typename T>
        gocpp_id_0(T& ref);

        template<typename T>
        gocpp_id_0(const T& ref);

        template<typename T>
        gocpp_id_0(T* ptr);

        using isGoStruct = void;

        std::ostream& PrintTo(std::ostream& os) const;

        struct Igocpp_id_0
        {
            virtual double vAbs() = 0;
        };

        template<typename T, typename StoreT>
        struct gocpp_id_0Impl : Igocpp_id_0
        {
            explicit gocpp_id_0Impl(T* ptr)
            {
                value.reset(ptr);
            }

            double vAbs() override;

            StoreT value;
        };

        std::shared_ptr<Igocpp_id_0> value;
    };

    double Abs(const gocpp::PtrRecv<gocpp_id_0, false>& self);
    double Abs(const gocpp::ObjRecv<gocpp_id_0>& self);

    std::ostream& operator<<(std::ostream& os, const gocpp_id_0& value);
    struct gocpp_id_1 : gocpp::Interface
    {
        gocpp_id_1(){}
        gocpp_id_1(gocpp_id_1& i) = default;
        gocpp_id_1(const gocpp_id_1& i) = default;
        gocpp_id_1& operator=(gocpp_id_1& i) = default;
        gocpp_id_1& operator=(const gocpp_id_1& i) = default;

        template<typename T>
        gocpp_id_1(T& ref);

        template<typename T>
        gocpp_id_1(const T& ref);

        template<typename T>
        gocpp_id_1(T* ptr);

        using isGoStruct = void;

        std::ostream& PrintTo(std::ostream& os) const;

        struct Igocpp_id_1
        {
            virtual double vAbs() = 0;
        };

        template<typename T, typename StoreT>
        struct gocpp_id_1Impl : Igocpp_id_1
        {
            explicit gocpp_id_1Impl(T* ptr)
            {
                value.reset(ptr);
            }

            double vAbs() override;

            StoreT value;
        };

        std::shared_ptr<Igocpp_id_1> value;
    };

    double Abs(const gocpp::PtrRecv<gocpp_id_1, false>& self);
    double Abs(const gocpp::ObjRecv<gocpp_id_1>& self);

    std::ostream& operator<<(std::ostream& os, const gocpp_id_1& value);
    void describe(gocpp_id_1 i);
}

