// generated by GoCpp from file 'tests/TourOfGo/concurrency/exercise-web-crawler.go'
#pragma once

#include <functional>
#include <string>
#include <tuple>
#include <vector>

#include "tests/TourOfGo/concurrency/exercise-web-crawler.fwd.h"
#include "gocpp/support.h"


namespace golang::main
{
    struct Fetcher : gocpp::Interface
    {
        using gocpp::Interface::operator==;
        using gocpp::Interface::operator!=;

        Fetcher(){}
        Fetcher(Fetcher& i) = default;
        Fetcher(const Fetcher& i) = default;
        Fetcher& operator=(Fetcher& i) = default;
        Fetcher& operator=(const Fetcher& i) = default;

        template<typename T>
        Fetcher(T& ref);

        template<typename T>
        Fetcher(const T& ref);

        template<typename T>
        Fetcher(T* ptr);

        using isGoInterface = void;

        std::ostream& PrintTo(std::ostream& os) const;

        struct IFetcher
        {
            virtual std::tuple<std::string, gocpp::slice<std::string>, struct gocpp::error> vFetch(std::string url) = 0;
        };

        template<typename T, typename StoreT>
        struct FetcherImpl : IFetcher
        {
            explicit FetcherImpl(T* ptr)
            {
                value.reset(ptr);
            }

            std::tuple<std::string, gocpp::slice<std::string>, struct gocpp::error> vFetch(std::string url) override;

            StoreT value;
        };

        std::shared_ptr<IFetcher> value;
    };

    namespace rec
    {
        std::tuple<std::string, gocpp::slice<std::string>, struct gocpp::error> Fetch(const gocpp::PtrRecv<struct Fetcher, false>& self, std::string url);
        std::tuple<std::string, gocpp::slice<std::string>, struct gocpp::error> Fetch(const gocpp::ObjRecv<struct Fetcher>& self, std::string url);
    }

    std::ostream& operator<<(std::ostream& os, const struct Fetcher& value);
    void Crawl(std::string url, int depth, struct Fetcher fetcher);
    void main();
    struct fakeResult
    {
        std::string body;
        gocpp::slice<std::string> urls;

        using isGoStruct = void;

        template<typename T> requires gocpp::GoStruct<T>
        operator T();

        template<typename T> requires gocpp::GoStruct<T>
        bool operator==(const T& ref) const;

        std::ostream& PrintTo(std::ostream& os) const;
    };

    std::ostream& operator<<(std::ostream& os, const struct fakeResult& value);
    extern main::fakeFetcher fetcher;

    namespace rec
    {
        std::tuple<std::string, gocpp::slice<std::string>, struct gocpp::error> Fetch(golang::main::fakeFetcher f, std::string url);
    }
}

