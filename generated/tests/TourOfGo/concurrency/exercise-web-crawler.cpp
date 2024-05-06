#include <complex>
#include <functional>
#include <iostream>
#include <iomanip>
#include <map>
#include <string>
#include <tuple>
#include <vector>

#include "tests/TourOfGo/concurrency/exercise-web-crawler.h"
#include "gocpp/support.h"


namespace golang
{
    // convertSpecs[ImportSpec] Not implemented => "fmt";
    
    template<typename T>
    Fetcher::Fetcher(T& ref)
    {
        value.reset(new FetcherImpl<T, std::unique_ptr<T>>(new T(ref)));
    }

    template<typename T>
    Fetcher::Fetcher(const T& ref)
    {
        value.reset(new FetcherImpl<T, std::unique_ptr<T>>(new T(ref)));
    }

    template<typename T>
    Fetcher::Fetcher(T* ptr)
    {
        value.reset(new FetcherImpl<T, gocpp::ptr<T>>(ptr));
    }

    std::ostream& Fetcher::PrintTo(std::ostream& os) const
    {
        return os;
    }

    template<typename T, typename StoreT>
    std::tuple<std::string, gocpp::slice<std::string>, error> Fetcher::FetcherImpl<T, StoreT>::vFetch(std::string url)
    {
        return Fetch(gocpp::PtrRecv<T, false>(value.get()));
    }

    std::tuple<std::string, gocpp::slice<std::string>, error> Fetch(const gocpp::PtrRecv<Fetcher, false>& self, std::string url)
    {
        return self.ptr->value->vFetch(std::string url);
    }

    std::tuple<std::string, gocpp::slice<std::string>, error> Fetch(const gocpp::ObjRecv<Fetcher>& self, std::string url)
    {
        return self.obj.value->vFetch(std::string url);
    }

    std::ostream& operator<<(std::ostream& os, const Fetcher& value)
    {
        return value.PrintTo(os);
    }

    void Crawl(std::string url, int depth, Fetcher fetcher)
    {
        if(depth <= 0)
        {
            return;
        }
        auto [body, urls, err] = Fetch(gocpp::recv(fetcher), url);
        if(err != nullptr)
        {
            mocklib::Println(err);
            return;
        }
        mocklib::Printf("found: %s %q\n", url, body);
        for(auto [_, u] : urls)
        {
            Crawl(u, depth - 1, fetcher);
        }
        return;
    }

    void main()
    {
        Crawl("https://golang.org/", 4, fetcher);
    }

    
    std::ostream& fakeResult::PrintTo(std::ostream& os) const
    {
        os << '{';
        os << "" << body;
        os << " " << urls;
        os << '}';
        return os;
    }

    std::ostream& operator<<(std::ostream& os, const fakeResult& value)
    {
        return value.PrintTo(os);
    }

    std::tuple<std::string, gocpp::slice<std::string>, error> Fetch(fakeFetcher f, std::string url)
    {
        if(auto [res, ok] = f[url]; ok)
        {
            return {res->body, res->urls, nullptr};
        }
        return {"", nullptr, fmt::Errorf("not found: %s", url)};
    }

    fakeFetcher fetcher = fakeFetcher {{ "https://golang.org/", new fakeResult {"The Go Programming Language", gocpp::slice<std::string> {"https://golang.org/pkg/", "https://golang.org/cmd/"}} }, { "https://golang.org/pkg/", new fakeResult {"Packages", gocpp::slice<std::string> {"https://golang.org/", "https://golang.org/cmd/", "https://golang.org/pkg/fmt/", "https://golang.org/pkg/os/"}} }, { "https://golang.org/pkg/fmt/", new fakeResult {"Package fmt", gocpp::slice<std::string> {"https://golang.org/", "https://golang.org/pkg/"}} }, { "https://golang.org/pkg/os/", new fakeResult {"Package os", gocpp::slice<std::string> {"https://golang.org/", "https://golang.org/pkg/"}} }};
}

int main()
{
    try
    {
        std::cout << std::boolalpha << std::fixed << std::setprecision(5);
        golang::main();
        return 0;
    }
    catch(const gocpp::GoPanic& ex)
    {
        std::cout << "Panic: " << ex.what() << std::endl;
        return -1;
    }
}
