// generated by GoCpp from file '$(ImportDir)/io/io.go'
#pragma once

#include <functional>
#include <string>
#include <tuple>
#include <vector>

#include "golang/io/io.fwd.h"
#include "gocpp/support.h"

#include "golang/sync/cond.h"
#include "golang/sync/pool.h"

namespace golang::io
{
    extern gocpp::error ErrShortWrite;
    extern gocpp::error errInvalidWrite;
    extern gocpp::error ErrShortBuffer;
    extern gocpp::error go_EOF;
    extern gocpp::error ErrUnexpectedEOF;
    extern gocpp::error ErrNoProgress;
    struct Reader : gocpp::Interface
    {
        using gocpp::Interface::operator==;
        using gocpp::Interface::operator!=;

        Reader(){}
        Reader(Reader& i) = default;
        Reader(const Reader& i) = default;
        Reader& operator=(Reader& i) = default;
        Reader& operator=(const Reader& i) = default;

        template<typename T>
        Reader(T& ref);

        template<typename T>
        Reader(const T& ref);

        template<typename T>
        Reader(T* ptr);

        using isGoInterface = void;

        std::ostream& PrintTo(std::ostream& os) const;

        struct IReader
        {
            virtual std::tuple<int, struct gocpp::error> vRead(gocpp::slice<unsigned char> p) = 0;
        };

        template<typename T, typename StoreT>
        struct ReaderImpl : IReader
        {
            explicit ReaderImpl(T* ptr)
            {
                value.reset(ptr);
            }

            std::tuple<int, struct gocpp::error> vRead(gocpp::slice<unsigned char> p) override;

            StoreT value;
        };

        std::shared_ptr<IReader> value;
    };

    namespace rec
    {
        std::tuple<int, struct gocpp::error> Read(const gocpp::PtrRecv<struct Reader, false>& self, gocpp::slice<unsigned char> p);
        std::tuple<int, struct gocpp::error> Read(const gocpp::ObjRecv<struct Reader>& self, gocpp::slice<unsigned char> p);
    }

    std::ostream& operator<<(std::ostream& os, const struct Reader& value);
    struct Writer : gocpp::Interface
    {
        using gocpp::Interface::operator==;
        using gocpp::Interface::operator!=;

        Writer(){}
        Writer(Writer& i) = default;
        Writer(const Writer& i) = default;
        Writer& operator=(Writer& i) = default;
        Writer& operator=(const Writer& i) = default;

        template<typename T>
        Writer(T& ref);

        template<typename T>
        Writer(const T& ref);

        template<typename T>
        Writer(T* ptr);

        using isGoInterface = void;

        std::ostream& PrintTo(std::ostream& os) const;

        struct IWriter
        {
            virtual std::tuple<int, struct gocpp::error> vWrite(gocpp::slice<unsigned char> p) = 0;
        };

        template<typename T, typename StoreT>
        struct WriterImpl : IWriter
        {
            explicit WriterImpl(T* ptr)
            {
                value.reset(ptr);
            }

            std::tuple<int, struct gocpp::error> vWrite(gocpp::slice<unsigned char> p) override;

            StoreT value;
        };

        std::shared_ptr<IWriter> value;
    };

    namespace rec
    {
        std::tuple<int, struct gocpp::error> Write(const gocpp::PtrRecv<struct Writer, false>& self, gocpp::slice<unsigned char> p);
        std::tuple<int, struct gocpp::error> Write(const gocpp::ObjRecv<struct Writer>& self, gocpp::slice<unsigned char> p);
    }

    std::ostream& operator<<(std::ostream& os, const struct Writer& value);
    struct Closer : gocpp::Interface
    {
        using gocpp::Interface::operator==;
        using gocpp::Interface::operator!=;

        Closer(){}
        Closer(Closer& i) = default;
        Closer(const Closer& i) = default;
        Closer& operator=(Closer& i) = default;
        Closer& operator=(const Closer& i) = default;

        template<typename T>
        Closer(T& ref);

        template<typename T>
        Closer(const T& ref);

        template<typename T>
        Closer(T* ptr);

        using isGoInterface = void;

        std::ostream& PrintTo(std::ostream& os) const;

        struct ICloser
        {
            virtual struct gocpp::error vClose() = 0;
        };

        template<typename T, typename StoreT>
        struct CloserImpl : ICloser
        {
            explicit CloserImpl(T* ptr)
            {
                value.reset(ptr);
            }

            struct gocpp::error vClose() override;

            StoreT value;
        };

        std::shared_ptr<ICloser> value;
    };

    namespace rec
    {
        struct gocpp::error Close(const gocpp::PtrRecv<struct Closer, false>& self);
        struct gocpp::error Close(const gocpp::ObjRecv<struct Closer>& self);
    }

    std::ostream& operator<<(std::ostream& os, const struct Closer& value);
    struct Seeker : gocpp::Interface
    {
        using gocpp::Interface::operator==;
        using gocpp::Interface::operator!=;

        Seeker(){}
        Seeker(Seeker& i) = default;
        Seeker(const Seeker& i) = default;
        Seeker& operator=(Seeker& i) = default;
        Seeker& operator=(const Seeker& i) = default;

        template<typename T>
        Seeker(T& ref);

        template<typename T>
        Seeker(const T& ref);

        template<typename T>
        Seeker(T* ptr);

        using isGoInterface = void;

        std::ostream& PrintTo(std::ostream& os) const;

        struct ISeeker
        {
            virtual std::tuple<int64_t, struct gocpp::error> vSeek(int64_t offset, int whence) = 0;
        };

        template<typename T, typename StoreT>
        struct SeekerImpl : ISeeker
        {
            explicit SeekerImpl(T* ptr)
            {
                value.reset(ptr);
            }

            std::tuple<int64_t, struct gocpp::error> vSeek(int64_t offset, int whence) override;

            StoreT value;
        };

        std::shared_ptr<ISeeker> value;
    };

    namespace rec
    {
        std::tuple<int64_t, struct gocpp::error> Seek(const gocpp::PtrRecv<struct Seeker, false>& self, int64_t offset, int whence);
        std::tuple<int64_t, struct gocpp::error> Seek(const gocpp::ObjRecv<struct Seeker>& self, int64_t offset, int whence);
    }

    std::ostream& operator<<(std::ostream& os, const struct Seeker& value);
    struct ReadWriter : gocpp::Interface
    {
        using gocpp::Interface::operator==;
        using gocpp::Interface::operator!=;

        ReadWriter(){}
        ReadWriter(ReadWriter& i) = default;
        ReadWriter(const ReadWriter& i) = default;
        ReadWriter& operator=(ReadWriter& i) = default;
        ReadWriter& operator=(const ReadWriter& i) = default;

        template<typename T>
        ReadWriter(T& ref);

        template<typename T>
        ReadWriter(const T& ref);

        template<typename T>
        ReadWriter(T* ptr);

        using isGoInterface = void;

        std::ostream& PrintTo(std::ostream& os) const;

        struct IReadWriter
        {
        };

        template<typename T, typename StoreT>
        struct ReadWriterImpl : IReadWriter
        {
            explicit ReadWriterImpl(T* ptr)
            {
                value.reset(ptr);
            }

            StoreT value;
        };

        std::shared_ptr<IReadWriter> value;
    };

    namespace rec
    {    }

    std::ostream& operator<<(std::ostream& os, const struct ReadWriter& value);
    struct ReadCloser : gocpp::Interface
    {
        using gocpp::Interface::operator==;
        using gocpp::Interface::operator!=;

        ReadCloser(){}
        ReadCloser(ReadCloser& i) = default;
        ReadCloser(const ReadCloser& i) = default;
        ReadCloser& operator=(ReadCloser& i) = default;
        ReadCloser& operator=(const ReadCloser& i) = default;

        template<typename T>
        ReadCloser(T& ref);

        template<typename T>
        ReadCloser(const T& ref);

        template<typename T>
        ReadCloser(T* ptr);

        using isGoInterface = void;

        std::ostream& PrintTo(std::ostream& os) const;

        struct IReadCloser
        {
        };

        template<typename T, typename StoreT>
        struct ReadCloserImpl : IReadCloser
        {
            explicit ReadCloserImpl(T* ptr)
            {
                value.reset(ptr);
            }

            StoreT value;
        };

        std::shared_ptr<IReadCloser> value;
    };

    namespace rec
    {    }

    std::ostream& operator<<(std::ostream& os, const struct ReadCloser& value);
    struct WriteCloser : gocpp::Interface
    {
        using gocpp::Interface::operator==;
        using gocpp::Interface::operator!=;

        WriteCloser(){}
        WriteCloser(WriteCloser& i) = default;
        WriteCloser(const WriteCloser& i) = default;
        WriteCloser& operator=(WriteCloser& i) = default;
        WriteCloser& operator=(const WriteCloser& i) = default;

        template<typename T>
        WriteCloser(T& ref);

        template<typename T>
        WriteCloser(const T& ref);

        template<typename T>
        WriteCloser(T* ptr);

        using isGoInterface = void;

        std::ostream& PrintTo(std::ostream& os) const;

        struct IWriteCloser
        {
        };

        template<typename T, typename StoreT>
        struct WriteCloserImpl : IWriteCloser
        {
            explicit WriteCloserImpl(T* ptr)
            {
                value.reset(ptr);
            }

            StoreT value;
        };

        std::shared_ptr<IWriteCloser> value;
    };

    namespace rec
    {    }

    std::ostream& operator<<(std::ostream& os, const struct WriteCloser& value);
    struct ReadWriteCloser : gocpp::Interface
    {
        using gocpp::Interface::operator==;
        using gocpp::Interface::operator!=;

        ReadWriteCloser(){}
        ReadWriteCloser(ReadWriteCloser& i) = default;
        ReadWriteCloser(const ReadWriteCloser& i) = default;
        ReadWriteCloser& operator=(ReadWriteCloser& i) = default;
        ReadWriteCloser& operator=(const ReadWriteCloser& i) = default;

        template<typename T>
        ReadWriteCloser(T& ref);

        template<typename T>
        ReadWriteCloser(const T& ref);

        template<typename T>
        ReadWriteCloser(T* ptr);

        using isGoInterface = void;

        std::ostream& PrintTo(std::ostream& os) const;

        struct IReadWriteCloser
        {
        };

        template<typename T, typename StoreT>
        struct ReadWriteCloserImpl : IReadWriteCloser
        {
            explicit ReadWriteCloserImpl(T* ptr)
            {
                value.reset(ptr);
            }

            StoreT value;
        };

        std::shared_ptr<IReadWriteCloser> value;
    };

    namespace rec
    {    }

    std::ostream& operator<<(std::ostream& os, const struct ReadWriteCloser& value);
    struct ReadSeeker : gocpp::Interface
    {
        using gocpp::Interface::operator==;
        using gocpp::Interface::operator!=;

        ReadSeeker(){}
        ReadSeeker(ReadSeeker& i) = default;
        ReadSeeker(const ReadSeeker& i) = default;
        ReadSeeker& operator=(ReadSeeker& i) = default;
        ReadSeeker& operator=(const ReadSeeker& i) = default;

        template<typename T>
        ReadSeeker(T& ref);

        template<typename T>
        ReadSeeker(const T& ref);

        template<typename T>
        ReadSeeker(T* ptr);

        using isGoInterface = void;

        std::ostream& PrintTo(std::ostream& os) const;

        struct IReadSeeker
        {
        };

        template<typename T, typename StoreT>
        struct ReadSeekerImpl : IReadSeeker
        {
            explicit ReadSeekerImpl(T* ptr)
            {
                value.reset(ptr);
            }

            StoreT value;
        };

        std::shared_ptr<IReadSeeker> value;
    };

    namespace rec
    {    }

    std::ostream& operator<<(std::ostream& os, const struct ReadSeeker& value);
    struct ReadSeekCloser : gocpp::Interface
    {
        using gocpp::Interface::operator==;
        using gocpp::Interface::operator!=;

        ReadSeekCloser(){}
        ReadSeekCloser(ReadSeekCloser& i) = default;
        ReadSeekCloser(const ReadSeekCloser& i) = default;
        ReadSeekCloser& operator=(ReadSeekCloser& i) = default;
        ReadSeekCloser& operator=(const ReadSeekCloser& i) = default;

        template<typename T>
        ReadSeekCloser(T& ref);

        template<typename T>
        ReadSeekCloser(const T& ref);

        template<typename T>
        ReadSeekCloser(T* ptr);

        using isGoInterface = void;

        std::ostream& PrintTo(std::ostream& os) const;

        struct IReadSeekCloser
        {
        };

        template<typename T, typename StoreT>
        struct ReadSeekCloserImpl : IReadSeekCloser
        {
            explicit ReadSeekCloserImpl(T* ptr)
            {
                value.reset(ptr);
            }

            StoreT value;
        };

        std::shared_ptr<IReadSeekCloser> value;
    };

    namespace rec
    {    }

    std::ostream& operator<<(std::ostream& os, const struct ReadSeekCloser& value);
    struct WriteSeeker : gocpp::Interface
    {
        using gocpp::Interface::operator==;
        using gocpp::Interface::operator!=;

        WriteSeeker(){}
        WriteSeeker(WriteSeeker& i) = default;
        WriteSeeker(const WriteSeeker& i) = default;
        WriteSeeker& operator=(WriteSeeker& i) = default;
        WriteSeeker& operator=(const WriteSeeker& i) = default;

        template<typename T>
        WriteSeeker(T& ref);

        template<typename T>
        WriteSeeker(const T& ref);

        template<typename T>
        WriteSeeker(T* ptr);

        using isGoInterface = void;

        std::ostream& PrintTo(std::ostream& os) const;

        struct IWriteSeeker
        {
        };

        template<typename T, typename StoreT>
        struct WriteSeekerImpl : IWriteSeeker
        {
            explicit WriteSeekerImpl(T* ptr)
            {
                value.reset(ptr);
            }

            StoreT value;
        };

        std::shared_ptr<IWriteSeeker> value;
    };

    namespace rec
    {    }

    std::ostream& operator<<(std::ostream& os, const struct WriteSeeker& value);
    struct ReadWriteSeeker : gocpp::Interface
    {
        using gocpp::Interface::operator==;
        using gocpp::Interface::operator!=;

        ReadWriteSeeker(){}
        ReadWriteSeeker(ReadWriteSeeker& i) = default;
        ReadWriteSeeker(const ReadWriteSeeker& i) = default;
        ReadWriteSeeker& operator=(ReadWriteSeeker& i) = default;
        ReadWriteSeeker& operator=(const ReadWriteSeeker& i) = default;

        template<typename T>
        ReadWriteSeeker(T& ref);

        template<typename T>
        ReadWriteSeeker(const T& ref);

        template<typename T>
        ReadWriteSeeker(T* ptr);

        using isGoInterface = void;

        std::ostream& PrintTo(std::ostream& os) const;

        struct IReadWriteSeeker
        {
        };

        template<typename T, typename StoreT>
        struct ReadWriteSeekerImpl : IReadWriteSeeker
        {
            explicit ReadWriteSeekerImpl(T* ptr)
            {
                value.reset(ptr);
            }

            StoreT value;
        };

        std::shared_ptr<IReadWriteSeeker> value;
    };

    namespace rec
    {    }

    std::ostream& operator<<(std::ostream& os, const struct ReadWriteSeeker& value);
    struct ReaderFrom : gocpp::Interface
    {
        using gocpp::Interface::operator==;
        using gocpp::Interface::operator!=;

        ReaderFrom(){}
        ReaderFrom(ReaderFrom& i) = default;
        ReaderFrom(const ReaderFrom& i) = default;
        ReaderFrom& operator=(ReaderFrom& i) = default;
        ReaderFrom& operator=(const ReaderFrom& i) = default;

        template<typename T>
        ReaderFrom(T& ref);

        template<typename T>
        ReaderFrom(const T& ref);

        template<typename T>
        ReaderFrom(T* ptr);

        using isGoInterface = void;

        std::ostream& PrintTo(std::ostream& os) const;

        struct IReaderFrom
        {
            virtual std::tuple<int64_t, struct gocpp::error> vReadFrom(struct Reader r) = 0;
        };

        template<typename T, typename StoreT>
        struct ReaderFromImpl : IReaderFrom
        {
            explicit ReaderFromImpl(T* ptr)
            {
                value.reset(ptr);
            }

            std::tuple<int64_t, struct gocpp::error> vReadFrom(struct Reader r) override;

            StoreT value;
        };

        std::shared_ptr<IReaderFrom> value;
    };

    namespace rec
    {
        std::tuple<int64_t, struct gocpp::error> ReadFrom(const gocpp::PtrRecv<struct ReaderFrom, false>& self, struct Reader r);
        std::tuple<int64_t, struct gocpp::error> ReadFrom(const gocpp::ObjRecv<struct ReaderFrom>& self, struct Reader r);
    }

    std::ostream& operator<<(std::ostream& os, const struct ReaderFrom& value);
    struct WriterTo : gocpp::Interface
    {
        using gocpp::Interface::operator==;
        using gocpp::Interface::operator!=;

        WriterTo(){}
        WriterTo(WriterTo& i) = default;
        WriterTo(const WriterTo& i) = default;
        WriterTo& operator=(WriterTo& i) = default;
        WriterTo& operator=(const WriterTo& i) = default;

        template<typename T>
        WriterTo(T& ref);

        template<typename T>
        WriterTo(const T& ref);

        template<typename T>
        WriterTo(T* ptr);

        using isGoInterface = void;

        std::ostream& PrintTo(std::ostream& os) const;

        struct IWriterTo
        {
            virtual std::tuple<int64_t, struct gocpp::error> vWriteTo(struct Writer w) = 0;
        };

        template<typename T, typename StoreT>
        struct WriterToImpl : IWriterTo
        {
            explicit WriterToImpl(T* ptr)
            {
                value.reset(ptr);
            }

            std::tuple<int64_t, struct gocpp::error> vWriteTo(struct Writer w) override;

            StoreT value;
        };

        std::shared_ptr<IWriterTo> value;
    };

    namespace rec
    {
        std::tuple<int64_t, struct gocpp::error> WriteTo(const gocpp::PtrRecv<struct WriterTo, false>& self, struct Writer w);
        std::tuple<int64_t, struct gocpp::error> WriteTo(const gocpp::ObjRecv<struct WriterTo>& self, struct Writer w);
    }

    std::ostream& operator<<(std::ostream& os, const struct WriterTo& value);
    struct ReaderAt : gocpp::Interface
    {
        using gocpp::Interface::operator==;
        using gocpp::Interface::operator!=;

        ReaderAt(){}
        ReaderAt(ReaderAt& i) = default;
        ReaderAt(const ReaderAt& i) = default;
        ReaderAt& operator=(ReaderAt& i) = default;
        ReaderAt& operator=(const ReaderAt& i) = default;

        template<typename T>
        ReaderAt(T& ref);

        template<typename T>
        ReaderAt(const T& ref);

        template<typename T>
        ReaderAt(T* ptr);

        using isGoInterface = void;

        std::ostream& PrintTo(std::ostream& os) const;

        struct IReaderAt
        {
            virtual std::tuple<int, struct gocpp::error> vReadAt(gocpp::slice<unsigned char> p, int64_t off) = 0;
        };

        template<typename T, typename StoreT>
        struct ReaderAtImpl : IReaderAt
        {
            explicit ReaderAtImpl(T* ptr)
            {
                value.reset(ptr);
            }

            std::tuple<int, struct gocpp::error> vReadAt(gocpp::slice<unsigned char> p, int64_t off) override;

            StoreT value;
        };

        std::shared_ptr<IReaderAt> value;
    };

    namespace rec
    {
        std::tuple<int, struct gocpp::error> ReadAt(const gocpp::PtrRecv<struct ReaderAt, false>& self, gocpp::slice<unsigned char> p, int64_t off);
        std::tuple<int, struct gocpp::error> ReadAt(const gocpp::ObjRecv<struct ReaderAt>& self, gocpp::slice<unsigned char> p, int64_t off);
    }

    std::ostream& operator<<(std::ostream& os, const struct ReaderAt& value);
    struct WriterAt : gocpp::Interface
    {
        using gocpp::Interface::operator==;
        using gocpp::Interface::operator!=;

        WriterAt(){}
        WriterAt(WriterAt& i) = default;
        WriterAt(const WriterAt& i) = default;
        WriterAt& operator=(WriterAt& i) = default;
        WriterAt& operator=(const WriterAt& i) = default;

        template<typename T>
        WriterAt(T& ref);

        template<typename T>
        WriterAt(const T& ref);

        template<typename T>
        WriterAt(T* ptr);

        using isGoInterface = void;

        std::ostream& PrintTo(std::ostream& os) const;

        struct IWriterAt
        {
            virtual std::tuple<int, struct gocpp::error> vWriteAt(gocpp::slice<unsigned char> p, int64_t off) = 0;
        };

        template<typename T, typename StoreT>
        struct WriterAtImpl : IWriterAt
        {
            explicit WriterAtImpl(T* ptr)
            {
                value.reset(ptr);
            }

            std::tuple<int, struct gocpp::error> vWriteAt(gocpp::slice<unsigned char> p, int64_t off) override;

            StoreT value;
        };

        std::shared_ptr<IWriterAt> value;
    };

    namespace rec
    {
        std::tuple<int, struct gocpp::error> WriteAt(const gocpp::PtrRecv<struct WriterAt, false>& self, gocpp::slice<unsigned char> p, int64_t off);
        std::tuple<int, struct gocpp::error> WriteAt(const gocpp::ObjRecv<struct WriterAt>& self, gocpp::slice<unsigned char> p, int64_t off);
    }

    std::ostream& operator<<(std::ostream& os, const struct WriterAt& value);
    struct ByteReader : gocpp::Interface
    {
        using gocpp::Interface::operator==;
        using gocpp::Interface::operator!=;

        ByteReader(){}
        ByteReader(ByteReader& i) = default;
        ByteReader(const ByteReader& i) = default;
        ByteReader& operator=(ByteReader& i) = default;
        ByteReader& operator=(const ByteReader& i) = default;

        template<typename T>
        ByteReader(T& ref);

        template<typename T>
        ByteReader(const T& ref);

        template<typename T>
        ByteReader(T* ptr);

        using isGoInterface = void;

        std::ostream& PrintTo(std::ostream& os) const;

        struct IByteReader
        {
            virtual std::tuple<unsigned char, struct gocpp::error> vReadByte() = 0;
        };

        template<typename T, typename StoreT>
        struct ByteReaderImpl : IByteReader
        {
            explicit ByteReaderImpl(T* ptr)
            {
                value.reset(ptr);
            }

            std::tuple<unsigned char, struct gocpp::error> vReadByte() override;

            StoreT value;
        };

        std::shared_ptr<IByteReader> value;
    };

    namespace rec
    {
        std::tuple<unsigned char, struct gocpp::error> ReadByte(const gocpp::PtrRecv<struct ByteReader, false>& self);
        std::tuple<unsigned char, struct gocpp::error> ReadByte(const gocpp::ObjRecv<struct ByteReader>& self);
    }

    std::ostream& operator<<(std::ostream& os, const struct ByteReader& value);
    struct ByteScanner : gocpp::Interface
    {
        using gocpp::Interface::operator==;
        using gocpp::Interface::operator!=;

        ByteScanner(){}
        ByteScanner(ByteScanner& i) = default;
        ByteScanner(const ByteScanner& i) = default;
        ByteScanner& operator=(ByteScanner& i) = default;
        ByteScanner& operator=(const ByteScanner& i) = default;

        template<typename T>
        ByteScanner(T& ref);

        template<typename T>
        ByteScanner(const T& ref);

        template<typename T>
        ByteScanner(T* ptr);

        using isGoInterface = void;

        std::ostream& PrintTo(std::ostream& os) const;

        struct IByteScanner
        {
            virtual struct gocpp::error vUnreadByte() = 0;
        };

        template<typename T, typename StoreT>
        struct ByteScannerImpl : IByteScanner
        {
            explicit ByteScannerImpl(T* ptr)
            {
                value.reset(ptr);
            }

            struct gocpp::error vUnreadByte() override;

            StoreT value;
        };

        std::shared_ptr<IByteScanner> value;
    };

    namespace rec
    {
        struct gocpp::error UnreadByte(const gocpp::PtrRecv<struct ByteScanner, false>& self);
        struct gocpp::error UnreadByte(const gocpp::ObjRecv<struct ByteScanner>& self);
    }

    std::ostream& operator<<(std::ostream& os, const struct ByteScanner& value);
    struct ByteWriter : gocpp::Interface
    {
        using gocpp::Interface::operator==;
        using gocpp::Interface::operator!=;

        ByteWriter(){}
        ByteWriter(ByteWriter& i) = default;
        ByteWriter(const ByteWriter& i) = default;
        ByteWriter& operator=(ByteWriter& i) = default;
        ByteWriter& operator=(const ByteWriter& i) = default;

        template<typename T>
        ByteWriter(T& ref);

        template<typename T>
        ByteWriter(const T& ref);

        template<typename T>
        ByteWriter(T* ptr);

        using isGoInterface = void;

        std::ostream& PrintTo(std::ostream& os) const;

        struct IByteWriter
        {
            virtual struct gocpp::error vWriteByte(unsigned char c) = 0;
        };

        template<typename T, typename StoreT>
        struct ByteWriterImpl : IByteWriter
        {
            explicit ByteWriterImpl(T* ptr)
            {
                value.reset(ptr);
            }

            struct gocpp::error vWriteByte(unsigned char c) override;

            StoreT value;
        };

        std::shared_ptr<IByteWriter> value;
    };

    namespace rec
    {
        struct gocpp::error WriteByte(const gocpp::PtrRecv<struct ByteWriter, false>& self, unsigned char c);
        struct gocpp::error WriteByte(const gocpp::ObjRecv<struct ByteWriter>& self, unsigned char c);
    }

    std::ostream& operator<<(std::ostream& os, const struct ByteWriter& value);
    struct RuneReader : gocpp::Interface
    {
        using gocpp::Interface::operator==;
        using gocpp::Interface::operator!=;

        RuneReader(){}
        RuneReader(RuneReader& i) = default;
        RuneReader(const RuneReader& i) = default;
        RuneReader& operator=(RuneReader& i) = default;
        RuneReader& operator=(const RuneReader& i) = default;

        template<typename T>
        RuneReader(T& ref);

        template<typename T>
        RuneReader(const T& ref);

        template<typename T>
        RuneReader(T* ptr);

        using isGoInterface = void;

        std::ostream& PrintTo(std::ostream& os) const;

        struct IRuneReader
        {
            virtual std::tuple<gocpp::rune, int, struct gocpp::error> vReadRune() = 0;
        };

        template<typename T, typename StoreT>
        struct RuneReaderImpl : IRuneReader
        {
            explicit RuneReaderImpl(T* ptr)
            {
                value.reset(ptr);
            }

            std::tuple<gocpp::rune, int, struct gocpp::error> vReadRune() override;

            StoreT value;
        };

        std::shared_ptr<IRuneReader> value;
    };

    namespace rec
    {
        std::tuple<gocpp::rune, int, struct gocpp::error> ReadRune(const gocpp::PtrRecv<struct RuneReader, false>& self);
        std::tuple<gocpp::rune, int, struct gocpp::error> ReadRune(const gocpp::ObjRecv<struct RuneReader>& self);
    }

    std::ostream& operator<<(std::ostream& os, const struct RuneReader& value);
    struct RuneScanner : gocpp::Interface
    {
        using gocpp::Interface::operator==;
        using gocpp::Interface::operator!=;

        RuneScanner(){}
        RuneScanner(RuneScanner& i) = default;
        RuneScanner(const RuneScanner& i) = default;
        RuneScanner& operator=(RuneScanner& i) = default;
        RuneScanner& operator=(const RuneScanner& i) = default;

        template<typename T>
        RuneScanner(T& ref);

        template<typename T>
        RuneScanner(const T& ref);

        template<typename T>
        RuneScanner(T* ptr);

        using isGoInterface = void;

        std::ostream& PrintTo(std::ostream& os) const;

        struct IRuneScanner
        {
            virtual struct gocpp::error vUnreadRune() = 0;
        };

        template<typename T, typename StoreT>
        struct RuneScannerImpl : IRuneScanner
        {
            explicit RuneScannerImpl(T* ptr)
            {
                value.reset(ptr);
            }

            struct gocpp::error vUnreadRune() override;

            StoreT value;
        };

        std::shared_ptr<IRuneScanner> value;
    };

    namespace rec
    {
        struct gocpp::error UnreadRune(const gocpp::PtrRecv<struct RuneScanner, false>& self);
        struct gocpp::error UnreadRune(const gocpp::ObjRecv<struct RuneScanner>& self);
    }

    std::ostream& operator<<(std::ostream& os, const struct RuneScanner& value);
    struct StringWriter : gocpp::Interface
    {
        using gocpp::Interface::operator==;
        using gocpp::Interface::operator!=;

        StringWriter(){}
        StringWriter(StringWriter& i) = default;
        StringWriter(const StringWriter& i) = default;
        StringWriter& operator=(StringWriter& i) = default;
        StringWriter& operator=(const StringWriter& i) = default;

        template<typename T>
        StringWriter(T& ref);

        template<typename T>
        StringWriter(const T& ref);

        template<typename T>
        StringWriter(T* ptr);

        using isGoInterface = void;

        std::ostream& PrintTo(std::ostream& os) const;

        struct IStringWriter
        {
            virtual std::tuple<int, struct gocpp::error> vWriteString(std::string s) = 0;
        };

        template<typename T, typename StoreT>
        struct StringWriterImpl : IStringWriter
        {
            explicit StringWriterImpl(T* ptr)
            {
                value.reset(ptr);
            }

            std::tuple<int, struct gocpp::error> vWriteString(std::string s) override;

            StoreT value;
        };

        std::shared_ptr<IStringWriter> value;
    };

    namespace rec
    {
        std::tuple<int, struct gocpp::error> WriteString(const gocpp::PtrRecv<struct StringWriter, false>& self, std::string s);
        std::tuple<int, struct gocpp::error> WriteString(const gocpp::ObjRecv<struct StringWriter>& self, std::string s);
    }

    std::ostream& operator<<(std::ostream& os, const struct StringWriter& value);
    std::tuple<int, struct gocpp::error> WriteString(struct Writer w, std::string s);
    std::tuple<int, struct gocpp::error> ReadAtLeast(struct Reader r, gocpp::slice<unsigned char> buf, int min);
    std::tuple<int, struct gocpp::error> ReadFull(struct Reader r, gocpp::slice<unsigned char> buf);
    std::tuple<int64_t, struct gocpp::error> CopyN(struct Writer dst, struct Reader src, int64_t n);
    std::tuple<int64_t, struct gocpp::error> Copy(struct Writer dst, struct Reader src);
    std::tuple<int64_t, struct gocpp::error> CopyBuffer(struct Writer dst, struct Reader src, gocpp::slice<unsigned char> buf);
    std::tuple<int64_t, struct gocpp::error> copyBuffer(struct Writer dst, struct Reader src, gocpp::slice<unsigned char> buf);
    struct Reader LimitReader(struct Reader r, int64_t n);
    struct SectionReader* NewSectionReader(struct ReaderAt r, int64_t off, int64_t n);
    extern gocpp::error errWhence;
    extern gocpp::error errOffset;
    struct OffsetWriter* NewOffsetWriter(struct WriterAt w, int64_t off);
    struct Reader TeeReader(struct Reader r, struct Writer w);
    struct discard
    {

        using isGoStruct = void;

        template<typename T> requires gocpp::GoStruct<T>
        operator T();

        template<typename T> requires gocpp::GoStruct<T>
        bool operator==(const T& ref) const;

        std::ostream& PrintTo(std::ostream& os) const;
    };

    std::ostream& operator<<(std::ostream& os, const struct discard& value);
    extern sync::Pool blackHolePool;
    struct ReadCloser NopCloser(struct Reader r);
    std::tuple<gocpp::slice<unsigned char>, struct gocpp::error> ReadAll(struct Reader r);
    struct LimitedReader
    {
        Reader R;
        int64_t N;

        using isGoStruct = void;

        template<typename T> requires gocpp::GoStruct<T>
        operator T();

        template<typename T> requires gocpp::GoStruct<T>
        bool operator==(const T& ref) const;

        std::ostream& PrintTo(std::ostream& os) const;
    };

    std::ostream& operator<<(std::ostream& os, const struct LimitedReader& value);
    struct SectionReader
    {
        ReaderAt r;
        int64_t base;
        int64_t off;
        int64_t limit;
        int64_t n;

        using isGoStruct = void;

        template<typename T> requires gocpp::GoStruct<T>
        operator T();

        template<typename T> requires gocpp::GoStruct<T>
        bool operator==(const T& ref) const;

        std::ostream& PrintTo(std::ostream& os) const;
    };

    std::ostream& operator<<(std::ostream& os, const struct SectionReader& value);
    struct OffsetWriter
    {
        WriterAt w;
        int64_t base;
        int64_t off;

        using isGoStruct = void;

        template<typename T> requires gocpp::GoStruct<T>
        operator T();

        template<typename T> requires gocpp::GoStruct<T>
        bool operator==(const T& ref) const;

        std::ostream& PrintTo(std::ostream& os) const;
    };

    std::ostream& operator<<(std::ostream& os, const struct OffsetWriter& value);
    struct teeReader
    {
        Reader r;
        Writer w;

        using isGoStruct = void;

        template<typename T> requires gocpp::GoStruct<T>
        operator T();

        template<typename T> requires gocpp::GoStruct<T>
        bool operator==(const T& ref) const;

        std::ostream& PrintTo(std::ostream& os) const;
    };

    std::ostream& operator<<(std::ostream& os, const struct teeReader& value);
    extern Writer Discard;
    extern ReaderFrom _;
    struct nopCloser
    {
        Reader Reader;

        using isGoStruct = void;

        template<typename T> requires gocpp::GoStruct<T>
        operator T();

        template<typename T> requires gocpp::GoStruct<T>
        bool operator==(const T& ref) const;

        std::ostream& PrintTo(std::ostream& os) const;
    };

    std::ostream& operator<<(std::ostream& os, const struct nopCloser& value);
    struct nopCloserWriterTo
    {
        Reader Reader;

        using isGoStruct = void;

        template<typename T> requires gocpp::GoStruct<T>
        operator T();

        template<typename T> requires gocpp::GoStruct<T>
        bool operator==(const T& ref) const;

        std::ostream& PrintTo(std::ostream& os) const;
    };

    std::ostream& operator<<(std::ostream& os, const struct nopCloserWriterTo& value);

    namespace rec
    {
        std::tuple<int, struct gocpp::error> Read(struct LimitedReader* l, gocpp::slice<unsigned char> p);
        std::tuple<int, struct gocpp::error> Read(struct SectionReader* s, gocpp::slice<unsigned char> p);
        std::tuple<int64_t, struct gocpp::error> Seek(struct SectionReader* s, int64_t offset, int whence);
        std::tuple<int, struct gocpp::error> ReadAt(struct SectionReader* s, gocpp::slice<unsigned char> p, int64_t off);
        int64_t Size(struct SectionReader* s);
        std::tuple<struct ReaderAt, int64_t, int64_t> Outer(struct SectionReader* s);
        std::tuple<int, struct gocpp::error> Write(struct OffsetWriter* o, gocpp::slice<unsigned char> p);
        std::tuple<int, struct gocpp::error> WriteAt(struct OffsetWriter* o, gocpp::slice<unsigned char> p, int64_t off);
        std::tuple<int64_t, struct gocpp::error> Seek(struct OffsetWriter* o, int64_t offset, int whence);
        std::tuple<int, struct gocpp::error> Read(struct teeReader* t, gocpp::slice<unsigned char> p);
        std::tuple<int, struct gocpp::error> Write(discard, gocpp::slice<unsigned char> p);
        std::tuple<int, struct gocpp::error> WriteString(discard, std::string s);
        std::tuple<int64_t, struct gocpp::error> ReadFrom(discard, struct Reader r);
        struct gocpp::error Close(nopCloser);
        struct gocpp::error Close(nopCloserWriterTo);
        std::tuple<int64_t, struct gocpp::error> WriteTo(struct nopCloserWriterTo c, struct Writer w);
    }
}

