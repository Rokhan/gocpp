// generated by GoCpp from file '$(ImportDir)/runtime/internal/atomic/stubs.go'
#include <complex>
#include <functional>
#include <iostream>
#include <iomanip>
#include <map>
#include <string>
#include <tuple>
#include <vector>

#include "golang/runtime/internal/atomic/stubs.h"
#include "gocpp/support.h"

#include "golang/unsafe/unsafe.h"

namespace golang::atomic
{
    namespace rec
    {
        using namespace mocklib::rec;
    }

    //go:noescape
    bool Cas(uint32_t* ptr, uint32_t old, uint32_t go_new)
    /* convertBlockStmt, nil block */;

    // NO go:noescape annotation; see atomic_pointer.go.
    bool Casp1(unsafe::Pointer* ptr, unsafe::Pointer old, unsafe::Pointer go_new)
    /* convertBlockStmt, nil block */;

    //go:noescape
    bool Casint32(int32_t* ptr, int32_t old, int32_t go_new)
    /* convertBlockStmt, nil block */;

    //go:noescape
    bool Casint64(int64_t* ptr, int64_t old, int64_t go_new)
    /* convertBlockStmt, nil block */;

    //go:noescape
    bool Casuintptr(uintptr_t* ptr, uintptr_t old, uintptr_t go_new)
    /* convertBlockStmt, nil block */;

    //go:noescape
    void Storeint32(int32_t* ptr, int32_t go_new)
    /* convertBlockStmt, nil block */;

    //go:noescape
    void Storeint64(int64_t* ptr, int64_t go_new)
    /* convertBlockStmt, nil block */;

    //go:noescape
    void Storeuintptr(uintptr_t* ptr, uintptr_t go_new)
    /* convertBlockStmt, nil block */;

    //go:noescape
    uintptr_t Loaduintptr(uintptr_t* ptr)
    /* convertBlockStmt, nil block */;

    //go:noescape
    unsigned int Loaduint(unsigned int* ptr)
    /* convertBlockStmt, nil block */;

    //go:noescape
    int32_t Loadint32(int32_t* ptr)
    /* convertBlockStmt, nil block */;

    //go:noescape
    int64_t Loadint64(int64_t* ptr)
    /* convertBlockStmt, nil block */;

    //go:noescape
    int32_t Xaddint32(int32_t* ptr, int32_t delta)
    /* convertBlockStmt, nil block */;

    //go:noescape
    int64_t Xaddint64(int64_t* ptr, int64_t delta)
    /* convertBlockStmt, nil block */;

    //go:noescape
    int32_t Xchgint32(int32_t* ptr, int32_t go_new)
    /* convertBlockStmt, nil block */;

    //go:noescape
    int64_t Xchgint64(int64_t* ptr, int64_t go_new)
    /* convertBlockStmt, nil block */;

}

