// generated by GoCpp from file '$(ImportDir)/internal/abi/map.go'
#include <complex>
#include <functional>
#include <iostream>
#include <iomanip>
#include <map>
#include <string>
#include <tuple>
#include <vector>

#include "golang/internal/abi/map.h"
#include "gocpp/support.h"

namespace golang::abi
{
    int MapBucketCountBits = 3;
    int MapBucketCount = 1 << MapBucketCountBits;
    int MapMaxKeyBytes = 128;
    int MapMaxElemBytes = 128;
    int ZeroValSize = 1024;
}

