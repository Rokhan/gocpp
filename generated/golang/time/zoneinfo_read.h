// generated by GoCpp from file '$(ImportDir)/time/zoneinfo_read.go'
#pragma once

#include <functional>
#include <string>
#include <tuple>
#include <vector>

#include "golang/time/zoneinfo_read.fwd.h"
#include "gocpp/support.h"

#include "golang/time/zoneinfo.h"

namespace golang::time
{
    void registerLoadFromEmbeddedTZData(std::function<std::tuple<std::string, std::string> (std::string)> f);
    std::string Error(fileSizeError f);
    struct dataIO
    {
        gocpp::slice<unsigned char> p;
        bool error;

        using isGoStruct = void;

        template<typename T> requires gocpp::GoStruct<T>
        operator T();

        template<typename T> requires gocpp::GoStruct<T>
        bool operator==(const T& ref) const;

        std::ostream& PrintTo(std::ostream& os) const;
    };

    std::ostream& operator<<(std::ostream& os, const struct dataIO& value);
    gocpp::slice<unsigned char> read(struct dataIO* d, int n);
    std::tuple<uint32_t, bool> big4(struct dataIO* d);
    std::tuple<uint64_t, bool> big8(struct dataIO* d);
    std::tuple<unsigned char, bool> byte(struct dataIO* d);
    gocpp::slice<unsigned char> rest(struct dataIO* d);
    std::string byteString(gocpp::slice<unsigned char> p);
    extern std::string errBadData;
    std::tuple<Location*, std::string> LoadLocationFromTZData(std::string name, gocpp::slice<unsigned char> data);
    int findZone(gocpp::slice<zone> zones, std::string name, int offset, bool isDST);
    std::tuple<gocpp::slice<unsigned char>, std::string> loadTzinfoFromDirOrZip(std::string dir, std::string name);
    int get4(gocpp::slice<unsigned char> b);
    int get2(gocpp::slice<unsigned char> b);
    std::tuple<gocpp::slice<unsigned char>, std::string> loadTzinfoFromZip(std::string zipfile, std::string name);
    std::tuple<gocpp::slice<unsigned char>, std::string> loadTzinfo(std::string name, std::string source);
    std::tuple<Location*, std::string> loadLocation(std::string name, gocpp::slice<std::string> sources);
    std::tuple<gocpp::slice<unsigned char>, std::string> readFile(std::string name);
}

