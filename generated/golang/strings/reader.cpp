// generated by GoCpp from file '$(ImportDir)/strings/reader.go'
#include <complex>
#include <functional>
#include <iostream>
#include <iomanip>
#include <map>
#include <string>
#include <tuple>
#include <vector>

#include "golang/strings/reader.h"
#include "gocpp/support.h"

#include "golang/errors/errors.h"
#include "golang/io/io.h"
#include "golang/unicode/utf8/utf8.h"

namespace golang::strings
{
    
    template<typename T> requires gocpp::GoStruct<T>
    Reader::operator T()
    {
        T result;
        result.s = this->s;
        result.i = this->i;
        result.prevRune = this->prevRune;
        return result;
    }

    template<typename T> requires gocpp::GoStruct<T>
    bool Reader::operator==(const T& ref) const
    {
        if (s != ref.s) return false;
        if (i != ref.i) return false;
        if (prevRune != ref.prevRune) return false;
        return true;
    }

    std::ostream& Reader::PrintTo(std::ostream& os) const
    {
        os << '{';
        os << "" << s;
        os << " " << i;
        os << " " << prevRune;
        os << '}';
        return os;
    }

    std::ostream& operator<<(std::ostream& os, const struct Reader& value)
    {
        return value.PrintTo(os);
    }

    int Len(struct Reader* r)
    {
        if(r->i >= int64_t(len(r->s)))
        {
            return 0;
        }
        return int(int64_t(len(r->s)) - r->i);
    }

    int64_t Size(struct Reader* r)
    {
        return int64_t(len(r->s));
    }

    std::tuple<int, std::string> Read(struct Reader* r, gocpp::slice<unsigned char> b)
    {
        int n;
        std::string err;
        if(r->i >= int64_t(len(r->s)))
        {
            int n;
            std::string err;
            return {0, io::go_EOF};
        }
        r->prevRune = - 1;
        n = copy(b, r->s.make_slice(r->i));
        r->i += int64_t(n);
        return {n, err};
    }

    std::tuple<int, std::string> ReadAt(struct Reader* r, gocpp::slice<unsigned char> b, int64_t off)
    {
        int n;
        std::string err;
        if(off < 0)
        {
            int n;
            std::string err;
            return {0, errors::New("strings.Reader.ReadAt: negative offset")};
        }
        if(off >= int64_t(len(r->s)))
        {
            int n;
            std::string err;
            return {0, io::go_EOF};
        }
        n = copy(b, r->s.make_slice(off));
        if(n < len(b))
        {
            int n;
            std::string err;
            err = io::go_EOF;
        }
        return {n, err};
    }

    std::tuple<unsigned char, std::string> ReadByte(struct Reader* r)
    {
        r->prevRune = - 1;
        if(r->i >= int64_t(len(r->s)))
        {
            return {0, io::go_EOF};
        }
        auto b = r->s[r->i];
        r->i++;
        return {b, nullptr};
    }

    std::string UnreadByte(struct Reader* r)
    {
        if(r->i <= 0)
        {
            return errors::New("strings.Reader.UnreadByte: at beginning of string");
        }
        r->prevRune = - 1;
        r->i--;
        return nullptr;
    }

    std::tuple<gocpp::rune, int, std::string> ReadRune(struct Reader* r)
    {
        gocpp::rune ch;
        int size;
        std::string err;
        if(r->i >= int64_t(len(r->s)))
        {
            gocpp::rune ch;
            int size;
            std::string err;
            r->prevRune = - 1;
            return {0, 0, io::go_EOF};
        }
        r->prevRune = int(r->i);
        if(auto c = r->s[r->i]; c < utf8::RuneSelf)
        {
            gocpp::rune ch;
            int size;
            std::string err;
            r->i++;
            return {rune(c), 1, nullptr};
        }
        std::tie(ch, size) = utf8::DecodeRuneInString(r->s.make_slice(r->i));
        r->i += int64_t(size);
        return {ch, size, err};
    }

    std::string UnreadRune(struct Reader* r)
    {
        if(r->i <= 0)
        {
            return errors::New("strings.Reader.UnreadRune: at beginning of string");
        }
        if(r->prevRune < 0)
        {
            return errors::New("strings.Reader.UnreadRune: previous operation was not ReadRune");
        }
        r->i = int64_t(r->prevRune);
        r->prevRune = - 1;
        return nullptr;
    }

    std::tuple<int64_t, std::string> Seek(struct Reader* r, int64_t offset, int whence)
    {
        r->prevRune = - 1;
        int64_t abs = {};
        //Go switch emulation
        {
            auto condition = whence;
            int conditionId = -1;
            if(condition == io::SeekStart) { conditionId = 0; }
            else if(condition == io::SeekCurrent) { conditionId = 1; }
            else if(condition == io::SeekEnd) { conditionId = 2; }
            switch(conditionId)
            {
                case 0:
                    abs = offset;
                    break;
                case 1:
                    abs = r->i + offset;
                    break;
                case 2:
                    abs = int64_t(len(r->s)) + offset;
                    break;
                default:
                    return {0, errors::New("strings.Reader.Seek: invalid whence")};
                    break;
            }
        }
        if(abs < 0)
        {
            return {0, errors::New("strings.Reader.Seek: negative position")};
        }
        r->i = abs;
        return {abs, nullptr};
    }

    std::tuple<int64_t, std::string> WriteTo(struct Reader* r, io::Writer w)
    {
        int64_t n;
        std::string err;
        r->prevRune = - 1;
        if(r->i >= int64_t(len(r->s)))
        {
            int64_t n;
            std::string err;
            return {0, nullptr};
        }
        auto s = r->s.make_slice(r->i);
        auto [m, err] = io::WriteString(w, s);
        if(m > len(s))
        {
            int64_t n;
            std::string err;
            gocpp::panic("strings.Reader.WriteTo: invalid WriteString count");
        }
        r->i += int64_t(m);
        n = int64_t(m);
        if(m != len(s) && err == nullptr)
        {
            int64_t n;
            std::string err;
            err = io::ErrShortWrite;
        }
        return {n, err};
    }

    void Reset(struct Reader* r, std::string s)
    {
        *r = Reader {s, 0, - 1};
    }

    Reader* NewReader(std::string s)
    {
        return new Reader {s, 0, - 1};
    }

}

