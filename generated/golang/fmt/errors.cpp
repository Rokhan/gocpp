// generated by GoCpp from file '$(ImportDir)/fmt/errors.go'
#include <complex>
#include <functional>
#include <iostream>
#include <iomanip>
#include <map>
#include <string>
#include <tuple>
#include <vector>

#include "golang/fmt/errors.h"
#include "gocpp/support.h"

#include "golang/errors/errors.h"
#include "golang/fmt/format.h"
#include "golang/fmt/print.h"
#include "golang/internal/abi/type.h"
#include "golang/reflect/value.h"
#include "golang/sort/sort.h"

namespace golang::fmt
{
    namespace rec
    {
        using namespace mocklib::rec;
    }

    // Errorf formats according to a format specifier and returns the string as a
    // value that satisfies error.
    //
    // If the format specifier includes a %w verb with an error operand,
    // the returned error will implement an Unwrap method returning the operand.
    // If there is more than one %w verb, the returned error will implement an
    // Unwrap method returning a []error containing all the %w operands in the
    // order they appear in the arguments.
    // It is invalid to supply the %w verb with an operand that does not implement
    // the error interface. The %w verb is otherwise a synonym for %v.
    struct gocpp::error Errorf(std::string format, gocpp::slice<go_any> a)
    {
        auto p = newPrinter();
        p->wrapErrs = true;
        rec::doPrintf(gocpp::recv(p), format, a);
        auto s = std::string(p->buf);
        gocpp::error err = {};
        //Go switch emulation
        {
            auto condition = len(p->wrappedErrs);
            int conditionId = -1;
            if(condition == 0) { conditionId = 0; }
            else if(condition == 1) { conditionId = 1; }
            switch(conditionId)
            {
                case 0:
                    err = errors::New(s);
                    break;
                case 1:
                    auto w = gocpp::InitPtr<wrapError>([=](auto& x) {
                        x.msg = s;
                    });
                    std::tie(w->err, gocpp_id_0) = gocpp::getValue<gocpp::error>(a[p->wrappedErrs[0]]);
                    err = w;
                    break;
                default:
                    if(p->reordered)
                    {
                        sort::Ints(p->wrappedErrs);
                    }
                    gocpp::slice<gocpp::error> errs = {};
                    for(auto [i, argNum] : p->wrappedErrs)
                    {
                        if(i > 0 && p->wrappedErrs[i - 1] == argNum)
                        {
                            continue;
                        }
                        if(auto [e, ok] = gocpp::getValue<gocpp::error>(a[argNum]); ok)
                        {
                            errs = append(errs, e);
                        }
                    }
                    err = new wrapErrors {s, errs};
                    break;
            }
        }
        rec::free(gocpp::recv(p));
        return err;
    }

    
    template<typename T> requires gocpp::GoStruct<T>
    wrapError::operator T()
    {
        T result;
        result.msg = this->msg;
        result.err = this->err;
        return result;
    }

    template<typename T> requires gocpp::GoStruct<T>
    bool wrapError::operator==(const T& ref) const
    {
        if (msg != ref.msg) return false;
        if (err != ref.err) return false;
        return true;
    }

    std::ostream& wrapError::PrintTo(std::ostream& os) const
    {
        os << '{';
        os << "" << msg;
        os << " " << err;
        os << '}';
        return os;
    }

    std::ostream& operator<<(std::ostream& os, const struct wrapError& value)
    {
        return value.PrintTo(os);
    }

    std::string rec::Error(struct wrapError* e)
    {
        return e->msg;
    }

    struct gocpp::error rec::Unwrap(struct wrapError* e)
    {
        return e->err;
    }

    
    template<typename T> requires gocpp::GoStruct<T>
    wrapErrors::operator T()
    {
        T result;
        result.msg = this->msg;
        result.errs = this->errs;
        return result;
    }

    template<typename T> requires gocpp::GoStruct<T>
    bool wrapErrors::operator==(const T& ref) const
    {
        if (msg != ref.msg) return false;
        if (errs != ref.errs) return false;
        return true;
    }

    std::ostream& wrapErrors::PrintTo(std::ostream& os) const
    {
        os << '{';
        os << "" << msg;
        os << " " << errs;
        os << '}';
        return os;
    }

    std::ostream& operator<<(std::ostream& os, const struct wrapErrors& value)
    {
        return value.PrintTo(os);
    }

    std::string rec::Error(struct wrapErrors* e)
    {
        return e->msg;
    }

    gocpp::slice<gocpp::error> rec::Unwrap(struct wrapErrors* e)
    {
        return e->errs;
    }

}

