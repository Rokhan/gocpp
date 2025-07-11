// generated by GoCpp from file 'tests/TourOfGo/methods/interfaces.go'
#pragma once

#include <functional>
#include <string>
#include <tuple>
#include <vector>

#include "tests/TourOfGo/methods/interfaces.fwd.h"
#include "gocpp/support.h"


namespace golang::main
{
    struct Abser : gocpp::Interface
    {
        using gocpp::Interface::operator==;
        using gocpp::Interface::operator!=;

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

        using isGoInterface = void;

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

    namespace rec
    {
        double Abs(const gocpp::PtrRecv<struct Abser, false>& self);
        double Abs(const gocpp::ObjRecv<struct Abser>& self);
    }

    std::ostream& operator<<(std::ostream& os, const struct Abser& value);
    struct dummy : gocpp::Interface
    {
        using gocpp::Interface::operator==;
        using gocpp::Interface::operator!=;

        dummy(){}
        dummy(dummy& i) = default;
        dummy(const dummy& i) = default;
        dummy& operator=(dummy& i) = default;
        dummy& operator=(const dummy& i) = default;

        template<typename T>
        dummy(T& ref);

        template<typename T>
        dummy(const T& ref);

        template<typename T>
        dummy(T* ptr);

        using isGoInterface = void;

        std::ostream& PrintTo(std::ostream& os) const;

        struct Idummy
        {
            virtual bool vAs(go_any _1) = 0;
        };

        template<typename T, typename StoreT>
        struct dummyImpl : Idummy
        {
            explicit dummyImpl(T* ptr)
            {
                value.reset(ptr);
            }

            bool vAs(go_any _1) override;

            StoreT value;
        };

        std::shared_ptr<Idummy> value;
    };

    namespace rec
    {
        bool As(const gocpp::PtrRecv<struct dummy, false>& self, go_any _1);
        bool As(const gocpp::ObjRecv<struct dummy>& self, go_any _1);
    }

    std::ostream& operator<<(std::ostream& os, const struct dummy& value);
    void main();
    struct Vertex
    {
        double X;
        double Y;

        using isGoStruct = void;

        template<typename T> requires gocpp::GoStruct<T>
        operator T();

        template<typename T> requires gocpp::GoStruct<T>
        bool operator==(const T& ref) const;

        std::ostream& PrintTo(std::ostream& os) const;
    };

    std::ostream& operator<<(std::ostream& os, const struct Vertex& value);

    namespace rec
    {
        double Abs(golang::main::MyFloat f);
        double Abs(struct Vertex* v);
    }
}

