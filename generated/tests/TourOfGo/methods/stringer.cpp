#include <complex>
#include <functional>
#include <iostream>
#include <iomanip>
#include <map>
#include <string>
#include <tuple>
#include <vector>

#include "tests/TourOfGo/methods/stringer.h"
#include "gocpp/support.h"


namespace golang
{
    // convertSpecs[ImportSpec] Not implemented => "fmt";
    
    Person Person::Init(void (init)(Person&))
    {
        Person value;
        init(value);
        return value;
    }

    std::ostream& Person::PrintTo(std::ostream& os) const
    {
        os << '{';
        os << "" << Name;
        os << " " << Age;
        os << '}';
        return os;
    }

    std::ostream& operator<<(std::ostream& os, const Person& value)
    {
        return value.PrintTo(os);
    }

    std::string String(Person p)
    {
        gocpp::Defer defer;
        return mocklib::Sprintf("%v (%v years)", p.Name, p.Age);
    }

    void main()
    {
        gocpp::Defer defer;
        auto a = Person {"Arthur Dent", 42};
        auto z = Person {"Zaphod Beeblebrox", 9001};
        mocklib::Println(a, z);
    }

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
