// generated by GoCpp from file '$(ImportDir)/io/io.go'
#pragma once

#include <functional>
#include <string>
#include <tuple>
#include <vector>

#include "golang/io/io.fwd.h"
#include "gocpp/support.h"

// #include "golang/sync/cond.h"  [Ignored, known errors]
#include "golang/sync/pool.h"

namespace golang::io
{
    extern std::string ErrShortWrite;
    extern std::string errInvalidWrite;
    extern std::string ErrShortBuffer;
    extern std::string go_EOF;
    extern std::string ErrUnexpectedEOF;
    extern std::string ErrNoProgress;
    struct Reader : gocpp::Interface
    {
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
            virtual std::tuple<int, std::string> vRead(gocpp::slice<unsigned char> p) = 0;
        };

        template<typename T, typename StoreT>
        struct ReaderImpl : IReader
        {
            explicit ReaderImpl(T* ptr)
            {
                value.reset(ptr);
            }

            std::tuple<int, std::string> vRead(gocpp::slice<unsigned char> p) override;

            StoreT value;
        };

        std::shared_ptr<IReader> value;
    };

    std::tuple<int, std::string> Read(const gocpp::PtrRecv<Reader, false>& self, gocpp::slice<unsigned char> p);
    std::tuple<int, std::string> Read(const gocpp::ObjRecv<Reader>& self, gocpp::slice<unsigned char> p);

    std::ostream& operator<<(std::ostream& os, const struct Reader& value);
    struct Writer : gocpp::Interface
    {
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
            virtual std::tuple<int, std::string> vWrite(gocpp::slice<unsigned char> p) = 0;
        };

        template<typename T, typename StoreT>
        struct WriterImpl : IWriter
        {
            explicit WriterImpl(T* ptr)
            {
                value.reset(ptr);
            }

            std::tuple<int, std::string> vWrite(gocpp::slice<unsigned char> p) override;

            StoreT value;
        };

        std::shared_ptr<IWriter> value;
    };

    std::tuple<int, std::string> Write(const gocpp::PtrRecv<Writer, false>& self, gocpp::slice<unsigned char> p);
    std::tuple<int, std::string> Write(const gocpp::ObjRecv<Writer>& self, gocpp::slice<unsigned char> p);

    std::ostream& operator<<(std::ostream& os, const struct Writer& value);
    struct Closer : gocpp::Interface
    {
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
            virtual std::string vClose() = 0;
        };

        template<typename T, typename StoreT>
        struct CloserImpl : ICloser
        {
            explicit CloserImpl(T* ptr)
            {
                value.reset(ptr);
            }

            std::string vClose() override;

            StoreT value;
        };

        std::shared_ptr<ICloser> value;
    };

    std::string Close(const gocpp::PtrRecv<Closer, false>& self);
    std::string Close(const gocpp::ObjRecv<Closer>& self);

    std::ostream& operator<<(std::ostream& os, const struct Closer& value);
    struct Seeker : gocpp::Interface
    {
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
            virtual std::tuple<int64_t, std::string> vSeek(int64_t offset, int whence) = 0;
        };

        template<typename T, typename StoreT>
        struct SeekerImpl : ISeeker
        {
            explicit SeekerImpl(T* ptr)
            {
                value.reset(ptr);
            }

            std::tuple<int64_t, std::string> vSeek(int64_t offset, int whence) override;

            StoreT value;
        };

        std::shared_ptr<ISeeker> value;
    };

    std::tuple<int64_t, std::string> Seek(const gocpp::PtrRecv<Seeker, false>& self, int64_t offset, int whence);
    std::tuple<int64_t, std::string> Seek(const gocpp::ObjRecv<Seeker>& self, int64_t offset, int whence);

    std::ostream& operator<<(std::ostream& os, const struct Seeker& value);
    struct ReadWriter : gocpp::Interface
    {
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

    std::ostream& operator<<(std::ostream& os, const struct ReadWriter& value);
    struct ReadCloser : gocpp::Interface
    {
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

    std::ostream& operator<<(std::ostream& os, const struct ReadCloser& value);
    struct WriteCloser : gocpp::Interface
    {
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

    std::ostream& operator<<(std::ostream& os, const struct WriteCloser& value);
    struct ReadWriteCloser : gocpp::Interface
    {
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

    std::ostream& operator<<(std::ostream& os, const struct ReadWriteCloser& value);
    struct ReadSeeker : gocpp::Interface
    {
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

    std::ostream& operator<<(std::ostream& os, const struct ReadSeeker& value);
    struct ReadSeekCloser : gocpp::Interface
    {
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

    std::ostream& operator<<(std::ostream& os, const struct ReadSeekCloser& value);
    struct WriteSeeker : gocpp::Interface
    {
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

    std::ostream& operator<<(std::ostream& os, const struct WriteSeeker& value);
    struct ReadWriteSeeker : gocpp::Interface
    {
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

    std::ostream& operator<<(std::ostream& os, const struct ReadWriteSeeker& value);
    struct ReaderFrom : gocpp::Interface
    {
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
            virtual std::tuple<int64_t, std::string> vReadFrom(Reader r) = 0;
        };

        template<typename T, typename StoreT>
        struct ReaderFromImpl : IReaderFrom
        {
            explicit ReaderFromImpl(T* ptr)
            {
                value.reset(ptr);
            }

            std::tuple<int64_t, std::string> vReadFrom(Reader r) override;

            StoreT value;
        };

        std::shared_ptr<IReaderFrom> value;
    };

    std::tuple<int64_t, std::string> ReadFrom(const gocpp::PtrRecv<ReaderFrom, false>& self, Reader r);
    std::tuple<int64_t, std::string> ReadFrom(const gocpp::ObjRecv<ReaderFrom>& self, Reader r);

    std::ostream& operator<<(std::ostream& os, const struct ReaderFrom& value);
    struct WriterTo : gocpp::Interface
    {
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
            virtual std::tuple<int64_t, std::string> vWriteTo(Writer w) = 0;
        };

        template<typename T, typename StoreT>
        struct WriterToImpl : IWriterTo
        {
            explicit WriterToImpl(T* ptr)
            {
                value.reset(ptr);
            }

            std::tuple<int64_t, std::string> vWriteTo(Writer w) override;

            StoreT value;
        };

        std::shared_ptr<IWriterTo> value;
    };

    std::tuple<int64_t, std::string> WriteTo(const gocpp::PtrRecv<WriterTo, false>& self, Writer w);
    std::tuple<int64_t, std::string> WriteTo(const gocpp::ObjRecv<WriterTo>& self, Writer w);

    std::ostream& operator<<(std::ostream& os, const struct WriterTo& value);
    struct ReaderAt : gocpp::Interface
    {
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
            virtual std::tuple<int, std::string> vReadAt(gocpp::slice<unsigned char> p, int64_t off) = 0;
        };

        template<typename T, typename StoreT>
        struct ReaderAtImpl : IReaderAt
        {
            explicit ReaderAtImpl(T* ptr)
            {
                value.reset(ptr);
            }

            std::tuple<int, std::string> vReadAt(gocpp::slice<unsigned char> p, int64_t off) override;

            StoreT value;
        };

        std::shared_ptr<IReaderAt> value;
    };

    std::tuple<int, std::string> ReadAt(const gocpp::PtrRecv<ReaderAt, false>& self, gocpp::slice<unsigned char> p, int64_t off);
    std::tuple<int, std::string> ReadAt(const gocpp::ObjRecv<ReaderAt>& self, gocpp::slice<unsigned char> p, int64_t off);

    std::ostream& operator<<(std::ostream& os, const struct ReaderAt& value);
    struct WriterAt : gocpp::Interface
    {
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
            virtual std::tuple<int, std::string> vWriteAt(gocpp::slice<unsigned char> p, int64_t off) = 0;
        };

        template<typename T, typename StoreT>
        struct WriterAtImpl : IWriterAt
        {
            explicit WriterAtImpl(T* ptr)
            {
                value.reset(ptr);
            }

            std::tuple<int, std::string> vWriteAt(gocpp::slice<unsigned char> p, int64_t off) override;

            StoreT value;
        };

        std::shared_ptr<IWriterAt> value;
    };

    std::tuple<int, std::string> WriteAt(const gocpp::PtrRecv<WriterAt, false>& self, gocpp::slice<unsigned char> p, int64_t off);
    std::tuple<int, std::string> WriteAt(const gocpp::ObjRecv<WriterAt>& self, gocpp::slice<unsigned char> p, int64_t off);

    std::ostream& operator<<(std::ostream& os, const struct WriterAt& value);
    struct ByteReader : gocpp::Interface
    {
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
            virtual std::tuple<unsigned char, std::string> vReadByte() = 0;
        };

        template<typename T, typename StoreT>
        struct ByteReaderImpl : IByteReader
        {
            explicit ByteReaderImpl(T* ptr)
            {
                value.reset(ptr);
            }

            std::tuple<unsigned char, std::string> vReadByte() override;

            StoreT value;
        };

        std::shared_ptr<IByteReader> value;
    };

    std::tuple<unsigned char, std::string> ReadByte(const gocpp::PtrRecv<ByteReader, false>& self);
    std::tuple<unsigned char, std::string> ReadByte(const gocpp::ObjRecv<ByteReader>& self);

    std::ostream& operator<<(std::ostream& os, const struct ByteReader& value);
    struct ByteScanner : gocpp::Interface
    {
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
            virtual std::string vUnreadByte() = 0;
        };

        template<typename T, typename StoreT>
        struct ByteScannerImpl : IByteScanner
        {
            explicit ByteScannerImpl(T* ptr)
            {
                value.reset(ptr);
            }

            std::string vUnreadByte() override;

            StoreT value;
        };

        std::shared_ptr<IByteScanner> value;
    };

    std::string UnreadByte(const gocpp::PtrRecv<ByteScanner, false>& self);
    std::string UnreadByte(const gocpp::ObjRecv<ByteScanner>& self);

    std::ostream& operator<<(std::ostream& os, const struct ByteScanner& value);
    struct ByteWriter : gocpp::Interface
    {
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
            virtual std::string vWriteByte(unsigned char c) = 0;
        };

        template<typename T, typename StoreT>
        struct ByteWriterImpl : IByteWriter
        {
            explicit ByteWriterImpl(T* ptr)
            {
                value.reset(ptr);
            }

            std::string vWriteByte(unsigned char c) override;

            StoreT value;
        };

        std::shared_ptr<IByteWriter> value;
    };

    std::string WriteByte(const gocpp::PtrRecv<ByteWriter, false>& self, unsigned char c);
    std::string WriteByte(const gocpp::ObjRecv<ByteWriter>& self, unsigned char c);

    std::ostream& operator<<(std::ostream& os, const struct ByteWriter& value);
    struct RuneReader : gocpp::Interface
    {
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
            virtual std::tuple<gocpp::rune, int, std::string> vReadRune() = 0;
        };

        template<typename T, typename StoreT>
        struct RuneReaderImpl : IRuneReader
        {
            explicit RuneReaderImpl(T* ptr)
            {
                value.reset(ptr);
            }

            std::tuple<gocpp::rune, int, std::string> vReadRune() override;

            StoreT value;
        };

        std::shared_ptr<IRuneReader> value;
    };

    std::tuple<gocpp::rune, int, std::string> ReadRune(const gocpp::PtrRecv<RuneReader, false>& self);
    std::tuple<gocpp::rune, int, std::string> ReadRune(const gocpp::ObjRecv<RuneReader>& self);

    std::ostream& operator<<(std::ostream& os, const struct RuneReader& value);
    struct RuneScanner : gocpp::Interface
    {
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
            virtual std::string vUnreadRune() = 0;
        };

        template<typename T, typename StoreT>
        struct RuneScannerImpl : IRuneScanner
        {
            explicit RuneScannerImpl(T* ptr)
            {
                value.reset(ptr);
            }

            std::string vUnreadRune() override;

            StoreT value;
        };

        std::shared_ptr<IRuneScanner> value;
    };

    std::string UnreadRune(const gocpp::PtrRecv<RuneScanner, false>& self);
    std::string UnreadRune(const gocpp::ObjRecv<RuneScanner>& self);

    std::ostream& operator<<(std::ostream& os, const struct RuneScanner& value);
    struct StringWriter : gocpp::Interface
    {
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
            virtual std::tuple<int, std::string> vWriteString(std::string s) = 0;
        };

        template<typename T, typename StoreT>
        struct StringWriterImpl : IStringWriter
        {
            explicit StringWriterImpl(T* ptr)
            {
                value.reset(ptr);
            }

            std::tuple<int, std::string> vWriteString(std::string s) override;

            StoreT value;
        };

        std::shared_ptr<IStringWriter> value;
    };

    std::tuple<int, std::string> WriteString(const gocpp::PtrRecv<StringWriter, false>& self, std::string s);
    std::tuple<int, std::string> WriteString(const gocpp::ObjRecv<StringWriter>& self, std::string s);

    std::ostream& operator<<(std::ostream& os, const struct StringWriter& value);
    std::tuple<int, std::string> WriteString(Writer w, std::string s);
    std::tuple<int, std::string> ReadAtLeast(Reader r, gocpp::slice<unsigned char> buf, int min);
    std::tuple<int, std::string> ReadFull(Reader r, gocpp::slice<unsigned char> buf);
    std::tuple<int64_t, std::string> CopyN(Writer dst, Reader src, int64_t n);
    std::tuple<int64_t, std::string> Copy(Writer dst, Reader src);
    std::tuple<int64_t, std::string> CopyBuffer(Writer dst, Reader src, gocpp::slice<unsigned char> buf);
    std::tuple<int64_t, std::string> copyBuffer(Writer dst, Reader src, gocpp::slice<unsigned char> buf);
    Reader LimitReader(Reader r, int64_t n);
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
    std::tuple<int, std::string> Read(struct LimitedReader* l, gocpp::slice<unsigned char> p);
    SectionReader* NewSectionReader(ReaderAt r, int64_t off, int64_t n);
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
    std::tuple<int, std::string> Read(struct SectionReader* s, gocpp::slice<unsigned char> p);
    extern std::string errWhence;
    extern std::string errOffset;
    std::tuple<int64_t, std::string> Seek(struct SectionReader* s, int64_t offset, int whence);
    std::tuple<int, std::string> ReadAt(struct SectionReader* s, gocpp::slice<unsigned char> p, int64_t off);
    int64_t Size(struct SectionReader* s);
    std::tuple<ReaderAt, int64_t, int64_t> Outer(struct SectionReader* s);
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
    OffsetWriter* NewOffsetWriter(WriterAt w, int64_t off);
    std::tuple<int, std::string> Write(struct OffsetWriter* o, gocpp::slice<unsigned char> p);
    std::tuple<int, std::string> WriteAt(struct OffsetWriter* o, gocpp::slice<unsigned char> p, int64_t off);
    std::tuple<int64_t, std::string> Seek(struct OffsetWriter* o, int64_t offset, int whence);
    Reader TeeReader(Reader r, Writer w);
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
    std::tuple<int, std::string> Read(struct teeReader* t, gocpp::slice<unsigned char> p);
    extern Writer Discard;
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
    extern ReaderFrom _;
    std::tuple<int, std::string> Write(discard, gocpp::slice<unsigned char> p);
    std::tuple<int, std::string> WriteString(discard, std::string s);
    extern sync::Pool blackHolePool;
    std::tuple<int64_t, std::string> ReadFrom(discard, Reader r);
    ReadCloser NopCloser(Reader r);
    struct nopCloser
    {

        using isGoStruct = void;

        template<typename T> requires gocpp::GoStruct<T>
        operator T();

        template<typename T> requires gocpp::GoStruct<T>
        bool operator==(const T& ref) const;

        std::ostream& PrintTo(std::ostream& os) const;
    };

    std::ostream& operator<<(std::ostream& os, const struct nopCloser& value);
    std::string Close(nopCloser);
    struct nopCloserWriterTo
    {

        using isGoStruct = void;

        template<typename T> requires gocpp::GoStruct<T>
        operator T();

        template<typename T> requires gocpp::GoStruct<T>
        bool operator==(const T& ref) const;

        std::ostream& PrintTo(std::ostream& os) const;
    };

    std::ostream& operator<<(std::ostream& os, const struct nopCloserWriterTo& value);
    std::string Close(nopCloserWriterTo);
    std::tuple<int64_t, std::string> WriteTo(struct nopCloserWriterTo c, Writer w);
    std::tuple<gocpp::slice<unsigned char>, std::string> ReadAll(Reader r);
}

