// generated by GoCpp from file '$(ImportDir)/internal/abi/symtab.go'
#include <complex>
#include <functional>
#include <iostream>
#include <iomanip>
#include <map>
#include <string>
#include <tuple>
#include <vector>

#include "golang/internal/abi/symtab.h"
#include "gocpp/support.h"

namespace golang::abi
{
    // using FuncFlag = uint8_t;
    FuncFlag FuncFlagTopFrame = 1 << 0;
    abi.FuncFlag FuncFlagSPWrite = 1 << 1;
    abi.FuncFlag FuncFlagAsm = 1 << 2;
    // using FuncID = uint8_t;
    FuncID FuncIDNormal = 0;
    abi.FuncID FuncID_abort = 1;
    abi.FuncID FuncID_asmcgocall = 2;
    abi.FuncID FuncID_asyncPreempt = 3;
    abi.FuncID FuncID_cgocallback = 4;
    abi.FuncID FuncID_corostart = 5;
    abi.FuncID FuncID_debugCallV2 = 6;
    abi.FuncID FuncID_gcBgMarkWorker = 7;
    abi.FuncID FuncID_goexit = 8;
    abi.FuncID FuncID_gogo = 9;
    abi.FuncID FuncID_gopanic = 10;
    abi.FuncID FuncID_handleAsyncEvent = 11;
    abi.FuncID FuncID_mcall = 12;
    abi.FuncID FuncID_morestack = 13;
    abi.FuncID FuncID_mstart = 14;
    abi.FuncID FuncID_panicwrap = 15;
    abi.FuncID FuncID_rt0_go = 16;
    abi.FuncID FuncID_runfinq = 17;
    abi.FuncID FuncID_runtime_main = 18;
    abi.FuncID FuncID_sigpanic = 19;
    abi.FuncID FuncID_systemstack = 20;
    abi.FuncID FuncID_systemstack_switch = 21;
    abi.FuncID FuncIDWrapper = 22;
    int ArgsSizeUnknown = - 0x80000000;
    int PCDATA_UnsafePoint = 0;
    int PCDATA_StackMapIndex = 1;
    int PCDATA_InlTreeIndex = 2;
    int PCDATA_ArgLiveIndex = 3;
    int FUNCDATA_ArgsPointerMaps = 0;
    int FUNCDATA_LocalsPointerMaps = 1;
    int FUNCDATA_StackObjects = 2;
    int FUNCDATA_InlTree = 3;
    int FUNCDATA_OpenCodedDeferInfo = 4;
    int FUNCDATA_ArgInfo = 5;
    int FUNCDATA_ArgLiveInfo = 6;
    int FUNCDATA_WrapInfo = 7;
    int UnsafePointSafe = - 1;
    int UnsafePointUnsafe = - 2;
    int UnsafePointRestart1 = - 3;
    int UnsafePointRestart2 = - 4;
    int UnsafePointRestartAtEntry = - 5;
}
