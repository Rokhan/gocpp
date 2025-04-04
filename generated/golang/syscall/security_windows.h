// generated by GoCpp from file '$(ImportDir)/syscall/security_windows.go'
#pragma once

#include <functional>
#include <string>
#include <tuple>
#include <vector>

#include "golang/syscall/security_windows.fwd.h"
#include "gocpp/support.h"


namespace golang::syscall
{
    std::tuple<std::string, std::string> TranslateAccountName(std::string username, uint32_t from, uint32_t to, int initSize);
    struct UserInfo10
    {
        uint16_t* Name;
        uint16_t* Comment;
        uint16_t* UsrComment;
        uint16_t* FullName;

        using isGoStruct = void;

        template<typename T> requires gocpp::GoStruct<T>
        operator T();

        template<typename T> requires gocpp::GoStruct<T>
        bool operator==(const T& ref) const;

        std::ostream& PrintTo(std::ostream& os) const;
    };

    std::ostream& operator<<(std::ostream& os, const struct UserInfo10& value);
    struct SID
    {

        using isGoStruct = void;

        template<typename T> requires gocpp::GoStruct<T>
        operator T();

        template<typename T> requires gocpp::GoStruct<T>
        bool operator==(const T& ref) const;

        std::ostream& PrintTo(std::ostream& os) const;
    };

    std::ostream& operator<<(std::ostream& os, const struct SID& value);
    std::tuple<SID*, std::string> StringToSid(std::string s);
    std::tuple<SID*, std::string, uint32_t, std::string> LookupSID(std::string system, std::string account);
    std::tuple<std::string, std::string> String(struct SID* sid);
    int Len(struct SID* sid);
    std::tuple<SID*, std::string> Copy(struct SID* sid);
    std::tuple<std::string, std::string, uint32_t, std::string> LookupAccount(struct SID* sid, std::string system);
    struct SIDAndAttributes
    {
        SID* Sid;
        uint32_t Attributes;

        using isGoStruct = void;

        template<typename T> requires gocpp::GoStruct<T>
        operator T();

        template<typename T> requires gocpp::GoStruct<T>
        bool operator==(const T& ref) const;

        std::ostream& PrintTo(std::ostream& os) const;
    };

    std::ostream& operator<<(std::ostream& os, const struct SIDAndAttributes& value);
    struct Tokenuser
    {
        SIDAndAttributes User;

        using isGoStruct = void;

        template<typename T> requires gocpp::GoStruct<T>
        operator T();

        template<typename T> requires gocpp::GoStruct<T>
        bool operator==(const T& ref) const;

        std::ostream& PrintTo(std::ostream& os) const;
    };

    std::ostream& operator<<(std::ostream& os, const struct Tokenuser& value);
    struct Tokenprimarygroup
    {
        SID* PrimaryGroup;

        using isGoStruct = void;

        template<typename T> requires gocpp::GoStruct<T>
        operator T();

        template<typename T> requires gocpp::GoStruct<T>
        bool operator==(const T& ref) const;

        std::ostream& PrintTo(std::ostream& os) const;
    };

    std::ostream& operator<<(std::ostream& os, const struct Tokenprimarygroup& value);
    std::tuple<Token, std::string> OpenCurrentProcessToken();
    std::string Close(Token t);
    std::tuple<unsafe::Pointer, std::string> getInfo(Token t, uint32_t go_class, int initSize);
    std::tuple<Tokenuser*, std::string> GetTokenUser(Token t);
    std::tuple<Tokenprimarygroup*, std::string> GetTokenPrimaryGroup(Token t);
    std::tuple<std::string, std::string> GetUserProfileDirectory(Token t);
}

