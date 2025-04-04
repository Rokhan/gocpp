// generated by GoCpp from file 'tests/TourOfGo/moretypes/structs.go'
#include <complex>
#include <functional>
#include <iostream>
#include <iomanip>
#include <map>
#include <string>
#include <tuple>
#include <vector>

#include "tests/TourOfGo/moretypes/structs.h"
#include "gocpp/support.h"

#include "golang/fmt/print.h"

namespace golang::main
{
    
    template<typename T> requires gocpp::GoStruct<T>
    Vertex::operator T()
    {
        T result;
        result.X = this->X;
        result.Y = this->Y;
        return result;
    }

    template<typename T> requires gocpp::GoStruct<T>
    bool Vertex::operator==(const T& ref) const
    {
        if (X != ref.X) return false;
        if (Y != ref.Y) return false;
        return true;
    }

    std::ostream& Vertex::PrintTo(std::ostream& os) const
    {
        os << '{';
        os << "" << X;
        os << " " << Y;
        os << '}';
        return os;
    }

    std::ostream& operator<<(std::ostream& os, const struct Vertex& value)
    {
        return value.PrintTo(os);
    }

    
    template<typename T> requires gocpp::GoStruct<T>
    Empty::operator T()
    {
        T result;
        return result;
    }

    template<typename T> requires gocpp::GoStruct<T>
    bool Empty::operator==(const T& ref) const
    {
        return true;
    }

    std::ostream& Empty::PrintTo(std::ostream& os) const
    {
        os << '{';
        os << '}';
        return os;
    }

    std::ostream& operator<<(std::ostream& os, const struct Empty& value)
    {
        return value.PrintTo(os);
    }

    
    template<typename T> requires gocpp::GoStruct<T>
    Dummy::operator T()
    {
        T result;
        result.i = this->i;
        return result;
    }

    template<typename T> requires gocpp::GoStruct<T>
    bool Dummy::operator==(const T& ref) const
    {
        if (i != ref.i) return false;
        return true;
    }

    std::ostream& Dummy::PrintTo(std::ostream& os) const
    {
        os << '{';
        os << "" << i;
        os << '}';
        return os;
    }

    std::ostream& operator<<(std::ostream& os, const struct Dummy& value)
    {
        return value.PrintTo(os);
    }

    struct gocpp_id_0
        {

            using isGoStruct = void;

            template<typename T> requires gocpp::GoStruct<T>
            operator T()
            {
                T result;
                return result;
            }

            template<typename T> requires gocpp::GoStruct<T>
            bool operator==(const T& ref) const
            {
                return true;
            }

            std::ostream& PrintTo(std::ostream& os) const
            {
                os << '{';
                os << '}';
                return os;
            }
        };

        std::ostream& operator<<(std::ostream& os, const struct gocpp_id_0& value)
        {
            return value.PrintTo(os);
        }


    struct gocpp_id_1
        {

            using isGoStruct = void;

            template<typename T> requires gocpp::GoStruct<T>
            operator T()
            {
                T result;
                return result;
            }

            template<typename T> requires gocpp::GoStruct<T>
            bool operator==(const T& ref) const
            {
                return true;
            }

            std::ostream& PrintTo(std::ostream& os) const
            {
                os << '{';
                os << '}';
                return os;
            }
        };

        std::ostream& operator<<(std::ostream& os, const struct gocpp_id_1& value)
        {
            return value.PrintTo(os);
        }


    struct gocpp_id_2
        {
            int i;

            using isGoStruct = void;

            template<typename T> requires gocpp::GoStruct<T>
            operator T()
            {
                T result;
                result.i = this->i;
                return result;
            }

            template<typename T> requires gocpp::GoStruct<T>
            bool operator==(const T& ref) const
            {
                if (i != ref.i) return false;
                return true;
            }

            std::ostream& PrintTo(std::ostream& os) const
            {
                os << '{';
                os << "" << i;
                os << '}';
                return os;
            }
        };

        std::ostream& operator<<(std::ostream& os, const struct gocpp_id_2& value)
        {
            return value.PrintTo(os);
        }


    struct gocpp_id_3
        {
            int i;

            using isGoStruct = void;

            template<typename T> requires gocpp::GoStruct<T>
            operator T()
            {
                T result;
                result.i = this->i;
                return result;
            }

            template<typename T> requires gocpp::GoStruct<T>
            bool operator==(const T& ref) const
            {
                if (i != ref.i) return false;
                return true;
            }

            std::ostream& PrintTo(std::ostream& os) const
            {
                os << '{';
                os << "" << i;
                os << '}';
                return os;
            }
        };

        std::ostream& operator<<(std::ostream& os, const struct gocpp_id_3& value)
        {
            return value.PrintTo(os);
        }


    struct gocpp_id_4
        {
            int i;

            using isGoStruct = void;

            template<typename T> requires gocpp::GoStruct<T>
            operator T()
            {
                T result;
                result.i = this->i;
                return result;
            }

            template<typename T> requires gocpp::GoStruct<T>
            bool operator==(const T& ref) const
            {
                if (i != ref.i) return false;
                return true;
            }

            std::ostream& PrintTo(std::ostream& os) const
            {
                os << '{';
                os << "" << i;
                os << '}';
                return os;
            }
        };

        std::ostream& operator<<(std::ostream& os, const struct gocpp_id_4& value)
        {
            return value.PrintTo(os);
        }


    void main()
    {
        mocklib::Println(Vertex {1, 2});
        gocpp_id_0 i = {};
        gocpp_id_1 j = {};
        mocklib::Println(i == j);
        auto e = Empty {};
        mocklib::Println(e == j);
        auto v1 = gocpp_id_2 {1};
        auto v2 = gocpp_id_3 {1};
        mocklib::Println(v1 == v2);
        auto d = Dummy {1};
        d = gocpp_id_4 {1};
        mocklib::Println(d == v2);
        mocklib::Println(d == v1);
        Dummy* p1 = & d;
        mocklib::Println(p1);
        p1 = nullptr;
        mocklib::Println(p1);
    }

}

int main()
{
    try
    {
        std::cout << std::boolalpha << std::fixed << std::setprecision(5);
        golang::main::main();
        return 0;
    }
    catch(const gocpp::GoPanic& ex)
    {
        std::cout << "Panic: " << ex.what() << std::endl;
        return -1;
    }
}
