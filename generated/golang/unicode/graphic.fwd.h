// generated by GoCpp from file '$(ImportDir)/unicode/graphic.go'
#pragma once

#include "gocpp/support.fwd.h"


namespace golang::unicode
{
    const int pC = 1 << 0;
    const int pP = 1 << 1;
    const int pN = 1 << 2;
    const int pS = 1 << 3;
    const int pZ = 1 << 4;
    const int pLu = 1 << 5;
    const int pLl = 1 << 6;
    const int pp = 1 << 7;
    const int pg = pp | pZ;
    const int pLo = pLl | pLu;
    const int pLmask = pLo;
}
