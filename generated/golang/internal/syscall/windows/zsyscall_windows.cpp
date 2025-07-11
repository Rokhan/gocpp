// generated by GoCpp from file '$(ImportDir)/internal/syscall/windows/zsyscall_windows.go'
#include <complex>
#include <functional>
#include <iostream>
#include <iomanip>
#include <map>
#include <string>
#include <tuple>
#include <vector>

#include "golang/internal/syscall/windows/zsyscall_windows.h"
#include "gocpp/support.h"

#include "golang/internal/syscall/windows/memory_windows.h"
#include "golang/internal/syscall/windows/psapi_windows.h"
#include "golang/internal/syscall/windows/security_windows.h"
#include "golang/internal/syscall/windows/syscall_windows.h"
#include "golang/internal/syscall/windows/sysdll/sysdll.h"
#include "golang/sync/mutex.h"
#include "golang/syscall/dll_windows.h"
#include "golang/syscall/security_windows.h"
#include "golang/syscall/syscall_windows.h"
#include "golang/syscall/types_windows.h"
#include "golang/syscall/zerrors_windows.h"
#include "golang/unsafe/unsafe.h"

namespace golang::windows
{
    namespace rec
    {
        using namespace mocklib::rec;
        using syscall::rec::Addr;
        using syscall::rec::NewProc;
    }

    unsafe::Pointer _;
    // Do the interface allocations only once for common
    // Errno values.
    gocpp::error errERROR_IO_PENDING = syscall::Errno(errnoERROR_IO_PENDING);
    gocpp::error errERROR_EINVAL = syscall::go_EINVAL;
    // errnoErr returns common boxed Errno values, to prevent
    // allocations at runtime.
    struct gocpp::error errnoErr(syscall::Errno e)
    {
        //Go switch emulation
        {
            auto condition = e;
            int conditionId = -1;
            if(condition == 0) { conditionId = 0; }
            else if(condition == errnoERROR_IO_PENDING) { conditionId = 1; }
            switch(conditionId)
            {
                case 0:
                    return errERROR_EINVAL;
                    break;
                case 1:
                    return errERROR_IO_PENDING;
                    break;
            }
        }
        return e;
    }

    syscall::LazyDLL* modadvapi32 = syscall::NewLazyDLL(sysdll::Add("advapi32.dll"s));
    syscall::LazyDLL* modbcryptprimitives = syscall::NewLazyDLL(sysdll::Add("bcryptprimitives.dll"s));
    syscall::LazyDLL* modiphlpapi = syscall::NewLazyDLL(sysdll::Add("iphlpapi.dll"s));
    syscall::LazyDLL* modkernel32 = syscall::NewLazyDLL(sysdll::Add("kernel32.dll"s));
    syscall::LazyDLL* modnetapi32 = syscall::NewLazyDLL(sysdll::Add("netapi32.dll"s));
    syscall::LazyDLL* modpsapi = syscall::NewLazyDLL(sysdll::Add("psapi.dll"s));
    syscall::LazyDLL* moduserenv = syscall::NewLazyDLL(sysdll::Add("userenv.dll"s));
    syscall::LazyDLL* modws2_32 = syscall::NewLazyDLL(sysdll::Add("ws2_32.dll"s));
    syscall::LazyProc* procAdjustTokenPrivileges = rec::NewProc(gocpp::recv(modadvapi32), "AdjustTokenPrivileges"s);
    syscall::LazyProc* procDuplicateTokenEx = rec::NewProc(gocpp::recv(modadvapi32), "DuplicateTokenEx"s);
    syscall::LazyProc* procImpersonateSelf = rec::NewProc(gocpp::recv(modadvapi32), "ImpersonateSelf"s);
    syscall::LazyProc* procLookupPrivilegeValueW = rec::NewProc(gocpp::recv(modadvapi32), "LookupPrivilegeValueW"s);
    syscall::LazyProc* procOpenSCManagerW = rec::NewProc(gocpp::recv(modadvapi32), "OpenSCManagerW"s);
    syscall::LazyProc* procOpenServiceW = rec::NewProc(gocpp::recv(modadvapi32), "OpenServiceW"s);
    syscall::LazyProc* procOpenThreadToken = rec::NewProc(gocpp::recv(modadvapi32), "OpenThreadToken"s);
    syscall::LazyProc* procQueryServiceStatus = rec::NewProc(gocpp::recv(modadvapi32), "QueryServiceStatus"s);
    syscall::LazyProc* procRevertToSelf = rec::NewProc(gocpp::recv(modadvapi32), "RevertToSelf"s);
    syscall::LazyProc* procSetTokenInformation = rec::NewProc(gocpp::recv(modadvapi32), "SetTokenInformation"s);
    syscall::LazyProc* procProcessPrng = rec::NewProc(gocpp::recv(modbcryptprimitives), "ProcessPrng"s);
    syscall::LazyProc* procGetAdaptersAddresses = rec::NewProc(gocpp::recv(modiphlpapi), "GetAdaptersAddresses"s);
    syscall::LazyProc* procCreateEventW = rec::NewProc(gocpp::recv(modkernel32), "CreateEventW"s);
    syscall::LazyProc* procGetACP = rec::NewProc(gocpp::recv(modkernel32), "GetACP"s);
    syscall::LazyProc* procGetComputerNameExW = rec::NewProc(gocpp::recv(modkernel32), "GetComputerNameExW"s);
    syscall::LazyProc* procGetConsoleCP = rec::NewProc(gocpp::recv(modkernel32), "GetConsoleCP"s);
    syscall::LazyProc* procGetCurrentThread = rec::NewProc(gocpp::recv(modkernel32), "GetCurrentThread"s);
    syscall::LazyProc* procGetFileInformationByHandleEx = rec::NewProc(gocpp::recv(modkernel32), "GetFileInformationByHandleEx"s);
    syscall::LazyProc* procGetFinalPathNameByHandleW = rec::NewProc(gocpp::recv(modkernel32), "GetFinalPathNameByHandleW"s);
    syscall::LazyProc* procGetModuleFileNameW = rec::NewProc(gocpp::recv(modkernel32), "GetModuleFileNameW"s);
    syscall::LazyProc* procGetTempPath2W = rec::NewProc(gocpp::recv(modkernel32), "GetTempPath2W"s);
    syscall::LazyProc* procGetVolumeInformationByHandleW = rec::NewProc(gocpp::recv(modkernel32), "GetVolumeInformationByHandleW"s);
    syscall::LazyProc* procGetVolumeNameForVolumeMountPointW = rec::NewProc(gocpp::recv(modkernel32), "GetVolumeNameForVolumeMountPointW"s);
    syscall::LazyProc* procLockFileEx = rec::NewProc(gocpp::recv(modkernel32), "LockFileEx"s);
    syscall::LazyProc* procModule32FirstW = rec::NewProc(gocpp::recv(modkernel32), "Module32FirstW"s);
    syscall::LazyProc* procModule32NextW = rec::NewProc(gocpp::recv(modkernel32), "Module32NextW"s);
    syscall::LazyProc* procMoveFileExW = rec::NewProc(gocpp::recv(modkernel32), "MoveFileExW"s);
    syscall::LazyProc* procMultiByteToWideChar = rec::NewProc(gocpp::recv(modkernel32), "MultiByteToWideChar"s);
    syscall::LazyProc* procRtlLookupFunctionEntry = rec::NewProc(gocpp::recv(modkernel32), "RtlLookupFunctionEntry"s);
    syscall::LazyProc* procRtlVirtualUnwind = rec::NewProc(gocpp::recv(modkernel32), "RtlVirtualUnwind"s);
    syscall::LazyProc* procSetFileInformationByHandle = rec::NewProc(gocpp::recv(modkernel32), "SetFileInformationByHandle"s);
    syscall::LazyProc* procUnlockFileEx = rec::NewProc(gocpp::recv(modkernel32), "UnlockFileEx"s);
    syscall::LazyProc* procVirtualQuery = rec::NewProc(gocpp::recv(modkernel32), "VirtualQuery"s);
    syscall::LazyProc* procNetShareAdd = rec::NewProc(gocpp::recv(modnetapi32), "NetShareAdd"s);
    syscall::LazyProc* procNetShareDel = rec::NewProc(gocpp::recv(modnetapi32), "NetShareDel"s);
    syscall::LazyProc* procNetUserGetLocalGroups = rec::NewProc(gocpp::recv(modnetapi32), "NetUserGetLocalGroups"s);
    syscall::LazyProc* procGetProcessMemoryInfo = rec::NewProc(gocpp::recv(modpsapi), "GetProcessMemoryInfo"s);
    syscall::LazyProc* procCreateEnvironmentBlock = rec::NewProc(gocpp::recv(moduserenv), "CreateEnvironmentBlock"s);
    syscall::LazyProc* procDestroyEnvironmentBlock = rec::NewProc(gocpp::recv(moduserenv), "DestroyEnvironmentBlock"s);
    syscall::LazyProc* procGetProfilesDirectoryW = rec::NewProc(gocpp::recv(moduserenv), "GetProfilesDirectoryW"s);
    syscall::LazyProc* procWSASocketW = rec::NewProc(gocpp::recv(modws2_32), "WSASocketW"s);
    std::tuple<uint32_t, struct gocpp::error> adjustTokenPrivileges(syscall::Token token, bool disableAllPrivileges, struct TOKEN_PRIVILEGES* newstate, uint32_t buflen, struct TOKEN_PRIVILEGES* prevstate, uint32_t* returnlen)
    {
        uint32_t ret;
        struct gocpp::error err;
        uint32_t _p0 = {};
        if(disableAllPrivileges)
        {
            _p0 = 1;
        }
        auto [r0, gocpp_id_0, e1] = syscall::Syscall6(rec::Addr(gocpp::recv(procAdjustTokenPrivileges)), 6, uintptr_t(token), uintptr_t(_p0), uintptr_t(unsafe::Pointer(newstate)), uintptr_t(buflen), uintptr_t(unsafe::Pointer(prevstate)), uintptr_t(unsafe::Pointer(returnlen)));
        ret = uint32_t(r0);
        if(true)
        {
            err = errnoErr(e1);
        }
        return {ret, err};
    }

    struct gocpp::error DuplicateTokenEx(syscall::Token hExistingToken, uint32_t dwDesiredAccess, syscall::SecurityAttributes* lpTokenAttributes, uint32_t impersonationLevel, golang::windows::TokenType tokenType, syscall::Token* phNewToken)
    {
        struct gocpp::error err;
        auto [r1, gocpp_id_1, e1] = syscall::Syscall6(rec::Addr(gocpp::recv(procDuplicateTokenEx)), 6, uintptr_t(hExistingToken), uintptr_t(dwDesiredAccess), uintptr_t(unsafe::Pointer(lpTokenAttributes)), uintptr_t(impersonationLevel), uintptr_t(tokenType), uintptr_t(unsafe::Pointer(phNewToken)));
        if(r1 == 0)
        {
            err = errnoErr(e1);
        }
        return err;
    }

    struct gocpp::error ImpersonateSelf(uint32_t impersonationlevel)
    {
        struct gocpp::error err;
        auto [r1, gocpp_id_2, e1] = syscall::Syscall(rec::Addr(gocpp::recv(procImpersonateSelf)), 1, uintptr_t(impersonationlevel), 0, 0);
        if(r1 == 0)
        {
            err = errnoErr(e1);
        }
        return err;
    }

    struct gocpp::error LookupPrivilegeValue(uint16_t* systemname, uint16_t* name, struct LUID* luid)
    {
        struct gocpp::error err;
        auto [r1, gocpp_id_3, e1] = syscall::Syscall(rec::Addr(gocpp::recv(procLookupPrivilegeValueW)), 3, uintptr_t(unsafe::Pointer(systemname)), uintptr_t(unsafe::Pointer(name)), uintptr_t(unsafe::Pointer(luid)));
        if(r1 == 0)
        {
            err = errnoErr(e1);
        }
        return err;
    }

    std::tuple<syscall::Handle, struct gocpp::error> OpenSCManager(uint16_t* machineName, uint16_t* databaseName, uint32_t access)
    {
        syscall::Handle handle;
        struct gocpp::error err;
        auto [r0, gocpp_id_4, e1] = syscall::Syscall(rec::Addr(gocpp::recv(procOpenSCManagerW)), 3, uintptr_t(unsafe::Pointer(machineName)), uintptr_t(unsafe::Pointer(databaseName)), uintptr_t(access));
        handle = syscall::Handle(r0);
        if(handle == 0)
        {
            err = errnoErr(e1);
        }
        return {handle, err};
    }

    std::tuple<syscall::Handle, struct gocpp::error> OpenService(syscall::Handle mgr, uint16_t* serviceName, uint32_t access)
    {
        syscall::Handle handle;
        struct gocpp::error err;
        auto [r0, gocpp_id_5, e1] = syscall::Syscall(rec::Addr(gocpp::recv(procOpenServiceW)), 3, uintptr_t(mgr), uintptr_t(unsafe::Pointer(serviceName)), uintptr_t(access));
        handle = syscall::Handle(r0);
        if(handle == 0)
        {
            err = errnoErr(e1);
        }
        return {handle, err};
    }

    struct gocpp::error OpenThreadToken(syscall::Handle h, uint32_t access, bool openasself, syscall::Token* token)
    {
        struct gocpp::error err;
        uint32_t _p0 = {};
        if(openasself)
        {
            _p0 = 1;
        }
        auto [r1, gocpp_id_6, e1] = syscall::Syscall6(rec::Addr(gocpp::recv(procOpenThreadToken)), 4, uintptr_t(h), uintptr_t(access), uintptr_t(_p0), uintptr_t(unsafe::Pointer(token)), 0, 0);
        if(r1 == 0)
        {
            err = errnoErr(e1);
        }
        return err;
    }

    struct gocpp::error QueryServiceStatus(syscall::Handle hService, struct SERVICE_STATUS* lpServiceStatus)
    {
        struct gocpp::error err;
        auto [r1, gocpp_id_7, e1] = syscall::Syscall(rec::Addr(gocpp::recv(procQueryServiceStatus)), 2, uintptr_t(hService), uintptr_t(unsafe::Pointer(lpServiceStatus)), 0);
        if(r1 == 0)
        {
            err = errnoErr(e1);
        }
        return err;
    }

    struct gocpp::error RevertToSelf()
    {
        struct gocpp::error err;
        auto [r1, gocpp_id_8, e1] = syscall::Syscall(rec::Addr(gocpp::recv(procRevertToSelf)), 0, 0, 0, 0);
        if(r1 == 0)
        {
            err = errnoErr(e1);
        }
        return err;
    }

    struct gocpp::error SetTokenInformation(syscall::Token tokenHandle, uint32_t tokenInformationClass, uintptr_t tokenInformation, uint32_t tokenInformationLength)
    {
        struct gocpp::error err;
        auto [r1, gocpp_id_9, e1] = syscall::Syscall6(rec::Addr(gocpp::recv(procSetTokenInformation)), 4, uintptr_t(tokenHandle), uintptr_t(tokenInformationClass), uintptr_t(tokenInformation), uintptr_t(tokenInformationLength), 0, 0);
        if(r1 == 0)
        {
            err = errnoErr(e1);
        }
        return err;
    }

    struct gocpp::error ProcessPrng(gocpp::slice<unsigned char> buf)
    {
        struct gocpp::error err;
        unsigned char* _p0 = {};
        if(len(buf) > 0)
        {
            _p0 = & buf[0];
        }
        auto [r1, gocpp_id_10, e1] = syscall::Syscall(rec::Addr(gocpp::recv(procProcessPrng)), 2, uintptr_t(unsafe::Pointer(_p0)), uintptr_t(len(buf)), 0);
        if(r1 == 0)
        {
            err = errnoErr(e1);
        }
        return err;
    }

    struct gocpp::error GetAdaptersAddresses(uint32_t family, uint32_t flags, uintptr_t reserved, struct IpAdapterAddresses* adapterAddresses, uint32_t* sizePointer)
    {
        struct gocpp::error errcode;
        auto [r0, gocpp_id_11, gocpp_id_12] = syscall::Syscall6(rec::Addr(gocpp::recv(procGetAdaptersAddresses)), 5, uintptr_t(family), uintptr_t(flags), uintptr_t(reserved), uintptr_t(unsafe::Pointer(adapterAddresses)), uintptr_t(unsafe::Pointer(sizePointer)), 0);
        if(r0 != 0)
        {
            errcode = syscall::Errno(r0);
        }
        return errcode;
    }

    std::tuple<syscall::Handle, struct gocpp::error> CreateEvent(struct SecurityAttributes* eventAttrs, uint32_t manualReset, uint32_t initialState, uint16_t* name)
    {
        syscall::Handle handle;
        struct gocpp::error err;
        auto [r0, gocpp_id_13, e1] = syscall::Syscall6(rec::Addr(gocpp::recv(procCreateEventW)), 4, uintptr_t(unsafe::Pointer(eventAttrs)), uintptr_t(manualReset), uintptr_t(initialState), uintptr_t(unsafe::Pointer(name)), 0, 0);
        handle = syscall::Handle(r0);
        if(handle == 0)
        {
            err = errnoErr(e1);
        }
        return {handle, err};
    }

    uint32_t GetACP()
    {
        uint32_t acp;
        auto [r0, gocpp_id_14, gocpp_id_15] = syscall::Syscall(rec::Addr(gocpp::recv(procGetACP)), 0, 0, 0, 0);
        acp = uint32_t(r0);
        return acp;
    }

    struct gocpp::error GetComputerNameEx(uint32_t nameformat, uint16_t* buf, uint32_t* n)
    {
        struct gocpp::error err;
        auto [r1, gocpp_id_16, e1] = syscall::Syscall(rec::Addr(gocpp::recv(procGetComputerNameExW)), 3, uintptr_t(nameformat), uintptr_t(unsafe::Pointer(buf)), uintptr_t(unsafe::Pointer(n)));
        if(r1 == 0)
        {
            err = errnoErr(e1);
        }
        return err;
    }

    uint32_t GetConsoleCP()
    {
        uint32_t ccp;
        auto [r0, gocpp_id_17, gocpp_id_18] = syscall::Syscall(rec::Addr(gocpp::recv(procGetConsoleCP)), 0, 0, 0, 0);
        ccp = uint32_t(r0);
        return ccp;
    }

    std::tuple<syscall::Handle, struct gocpp::error> GetCurrentThread()
    {
        syscall::Handle pseudoHandle;
        struct gocpp::error err;
        auto [r0, gocpp_id_19, e1] = syscall::Syscall(rec::Addr(gocpp::recv(procGetCurrentThread)), 0, 0, 0, 0);
        pseudoHandle = syscall::Handle(r0);
        if(pseudoHandle == 0)
        {
            err = errnoErr(e1);
        }
        return {pseudoHandle, err};
    }

    struct gocpp::error GetFileInformationByHandleEx(syscall::Handle handle, uint32_t go_class, unsigned char* info, uint32_t bufsize)
    {
        struct gocpp::error err;
        auto [r1, gocpp_id_20, e1] = syscall::Syscall6(rec::Addr(gocpp::recv(procGetFileInformationByHandleEx)), 4, uintptr_t(handle), uintptr_t(go_class), uintptr_t(unsafe::Pointer(info)), uintptr_t(bufsize), 0, 0);
        if(r1 == 0)
        {
            err = errnoErr(e1);
        }
        return err;
    }

    std::tuple<uint32_t, struct gocpp::error> GetFinalPathNameByHandle(syscall::Handle file, uint16_t* filePath, uint32_t filePathSize, uint32_t flags)
    {
        uint32_t n;
        struct gocpp::error err;
        auto [r0, gocpp_id_21, e1] = syscall::Syscall6(rec::Addr(gocpp::recv(procGetFinalPathNameByHandleW)), 4, uintptr_t(file), uintptr_t(unsafe::Pointer(filePath)), uintptr_t(filePathSize), uintptr_t(flags), 0, 0);
        n = uint32_t(r0);
        if(n == 0)
        {
            err = errnoErr(e1);
        }
        return {n, err};
    }

    std::tuple<uint32_t, struct gocpp::error> GetModuleFileName(syscall::Handle module, uint16_t* fn, uint32_t len)
    {
        uint32_t n;
        struct gocpp::error err;
        auto [r0, gocpp_id_22, e1] = syscall::Syscall(rec::Addr(gocpp::recv(procGetModuleFileNameW)), 3, uintptr_t(module), uintptr_t(unsafe::Pointer(fn)), uintptr_t(len));
        n = uint32_t(r0);
        if(n == 0)
        {
            err = errnoErr(e1);
        }
        return {n, err};
    }

    std::tuple<uint32_t, struct gocpp::error> GetTempPath2(uint32_t buflen, uint16_t* buf)
    {
        uint32_t n;
        struct gocpp::error err;
        auto [r0, gocpp_id_23, e1] = syscall::Syscall(rec::Addr(gocpp::recv(procGetTempPath2W)), 2, uintptr_t(buflen), uintptr_t(unsafe::Pointer(buf)), 0);
        n = uint32_t(r0);
        if(n == 0)
        {
            err = errnoErr(e1);
        }
        return {n, err};
    }

    struct gocpp::error GetVolumeInformationByHandle(syscall::Handle file, uint16_t* volumeNameBuffer, uint32_t volumeNameSize, uint32_t* volumeNameSerialNumber, uint32_t* maximumComponentLength, uint32_t* fileSystemFlags, uint16_t* fileSystemNameBuffer, uint32_t fileSystemNameSize)
    {
        struct gocpp::error err;
        auto [r1, gocpp_id_24, e1] = syscall::Syscall9(rec::Addr(gocpp::recv(procGetVolumeInformationByHandleW)), 8, uintptr_t(file), uintptr_t(unsafe::Pointer(volumeNameBuffer)), uintptr_t(volumeNameSize), uintptr_t(unsafe::Pointer(volumeNameSerialNumber)), uintptr_t(unsafe::Pointer(maximumComponentLength)), uintptr_t(unsafe::Pointer(fileSystemFlags)), uintptr_t(unsafe::Pointer(fileSystemNameBuffer)), uintptr_t(fileSystemNameSize), 0);
        if(r1 == 0)
        {
            err = errnoErr(e1);
        }
        return err;
    }

    struct gocpp::error GetVolumeNameForVolumeMountPoint(uint16_t* volumeMountPoint, uint16_t* volumeName, uint32_t bufferlength)
    {
        struct gocpp::error err;
        auto [r1, gocpp_id_25, e1] = syscall::Syscall(rec::Addr(gocpp::recv(procGetVolumeNameForVolumeMountPointW)), 3, uintptr_t(unsafe::Pointer(volumeMountPoint)), uintptr_t(unsafe::Pointer(volumeName)), uintptr_t(bufferlength));
        if(r1 == 0)
        {
            err = errnoErr(e1);
        }
        return err;
    }

    struct gocpp::error LockFileEx(syscall::Handle file, uint32_t flags, uint32_t reserved, uint32_t bytesLow, uint32_t bytesHigh, syscall::Overlapped* overlapped)
    {
        struct gocpp::error err;
        auto [r1, gocpp_id_26, e1] = syscall::Syscall6(rec::Addr(gocpp::recv(procLockFileEx)), 6, uintptr_t(file), uintptr_t(flags), uintptr_t(reserved), uintptr_t(bytesLow), uintptr_t(bytesHigh), uintptr_t(unsafe::Pointer(overlapped)));
        if(r1 == 0)
        {
            err = errnoErr(e1);
        }
        return err;
    }

    struct gocpp::error Module32First(syscall::Handle snapshot, struct ModuleEntry32* moduleEntry)
    {
        struct gocpp::error err;
        auto [r1, gocpp_id_27, e1] = syscall::Syscall(rec::Addr(gocpp::recv(procModule32FirstW)), 2, uintptr_t(snapshot), uintptr_t(unsafe::Pointer(moduleEntry)), 0);
        if(r1 == 0)
        {
            err = errnoErr(e1);
        }
        return err;
    }

    struct gocpp::error Module32Next(syscall::Handle snapshot, struct ModuleEntry32* moduleEntry)
    {
        struct gocpp::error err;
        auto [r1, gocpp_id_28, e1] = syscall::Syscall(rec::Addr(gocpp::recv(procModule32NextW)), 2, uintptr_t(snapshot), uintptr_t(unsafe::Pointer(moduleEntry)), 0);
        if(r1 == 0)
        {
            err = errnoErr(e1);
        }
        return err;
    }

    struct gocpp::error MoveFileEx(uint16_t* from, uint16_t* to, uint32_t flags)
    {
        struct gocpp::error err;
        auto [r1, gocpp_id_29, e1] = syscall::Syscall(rec::Addr(gocpp::recv(procMoveFileExW)), 3, uintptr_t(unsafe::Pointer(from)), uintptr_t(unsafe::Pointer(to)), uintptr_t(flags));
        if(r1 == 0)
        {
            err = errnoErr(e1);
        }
        return err;
    }

    std::tuple<int32_t, struct gocpp::error> MultiByteToWideChar(uint32_t codePage, uint32_t dwFlags, unsigned char* str, int32_t nstr, uint16_t* wchar, int32_t nwchar)
    {
        int32_t nwrite;
        struct gocpp::error err;
        auto [r0, gocpp_id_30, e1] = syscall::Syscall6(rec::Addr(gocpp::recv(procMultiByteToWideChar)), 6, uintptr_t(codePage), uintptr_t(dwFlags), uintptr_t(unsafe::Pointer(str)), uintptr_t(nstr), uintptr_t(unsafe::Pointer(wchar)), uintptr_t(nwchar));
        nwrite = int32_t(r0);
        if(nwrite == 0)
        {
            err = errnoErr(e1);
        }
        return {nwrite, err};
    }

    uintptr_t RtlLookupFunctionEntry(uintptr_t pc, uintptr_t* baseAddress, unsigned char* table)
    {
        uintptr_t ret;
        auto [r0, gocpp_id_31, gocpp_id_32] = syscall::Syscall(rec::Addr(gocpp::recv(procRtlLookupFunctionEntry)), 3, uintptr_t(pc), uintptr_t(unsafe::Pointer(baseAddress)), uintptr_t(unsafe::Pointer(table)));
        ret = uintptr_t(r0);
        return ret;
    }

    uintptr_t RtlVirtualUnwind(uint32_t handlerType, uintptr_t baseAddress, uintptr_t pc, uintptr_t entry, uintptr_t ctxt, uintptr_t* data, uintptr_t* frame, unsigned char* ctxptrs)
    {
        uintptr_t ret;
        auto [r0, gocpp_id_33, gocpp_id_34] = syscall::Syscall9(rec::Addr(gocpp::recv(procRtlVirtualUnwind)), 8, uintptr_t(handlerType), uintptr_t(baseAddress), uintptr_t(pc), uintptr_t(entry), uintptr_t(ctxt), uintptr_t(unsafe::Pointer(data)), uintptr_t(unsafe::Pointer(frame)), uintptr_t(unsafe::Pointer(ctxptrs)), 0);
        ret = uintptr_t(r0);
        return ret;
    }

    struct gocpp::error SetFileInformationByHandle(syscall::Handle handle, uint32_t fileInformationClass, unsafe::Pointer buf, uint32_t bufsize)
    {
        struct gocpp::error err;
        auto [r1, gocpp_id_35, e1] = syscall::Syscall6(rec::Addr(gocpp::recv(procSetFileInformationByHandle)), 4, uintptr_t(handle), uintptr_t(fileInformationClass), uintptr_t(buf), uintptr_t(bufsize), 0, 0);
        if(r1 == 0)
        {
            err = errnoErr(e1);
        }
        return err;
    }

    struct gocpp::error UnlockFileEx(syscall::Handle file, uint32_t reserved, uint32_t bytesLow, uint32_t bytesHigh, syscall::Overlapped* overlapped)
    {
        struct gocpp::error err;
        auto [r1, gocpp_id_36, e1] = syscall::Syscall6(rec::Addr(gocpp::recv(procUnlockFileEx)), 5, uintptr_t(file), uintptr_t(reserved), uintptr_t(bytesLow), uintptr_t(bytesHigh), uintptr_t(unsafe::Pointer(overlapped)), 0);
        if(r1 == 0)
        {
            err = errnoErr(e1);
        }
        return err;
    }

    struct gocpp::error VirtualQuery(uintptr_t address, struct MemoryBasicInformation* buffer, uintptr_t length)
    {
        struct gocpp::error err;
        auto [r1, gocpp_id_37, e1] = syscall::Syscall(rec::Addr(gocpp::recv(procVirtualQuery)), 3, uintptr_t(address), uintptr_t(unsafe::Pointer(buffer)), uintptr_t(length));
        if(r1 == 0)
        {
            err = errnoErr(e1);
        }
        return err;
    }

    struct gocpp::error NetShareAdd(uint16_t* serverName, uint32_t level, unsigned char* buf, uint16_t* parmErr)
    {
        struct gocpp::error neterr;
        auto [r0, gocpp_id_38, gocpp_id_39] = syscall::Syscall6(rec::Addr(gocpp::recv(procNetShareAdd)), 4, uintptr_t(unsafe::Pointer(serverName)), uintptr_t(level), uintptr_t(unsafe::Pointer(buf)), uintptr_t(unsafe::Pointer(parmErr)), 0, 0);
        if(r0 != 0)
        {
            neterr = syscall::Errno(r0);
        }
        return neterr;
    }

    struct gocpp::error NetShareDel(uint16_t* serverName, uint16_t* netName, uint32_t reserved)
    {
        struct gocpp::error neterr;
        auto [r0, gocpp_id_40, gocpp_id_41] = syscall::Syscall(rec::Addr(gocpp::recv(procNetShareDel)), 3, uintptr_t(unsafe::Pointer(serverName)), uintptr_t(unsafe::Pointer(netName)), uintptr_t(reserved));
        if(r0 != 0)
        {
            neterr = syscall::Errno(r0);
        }
        return neterr;
    }

    struct gocpp::error NetUserGetLocalGroups(uint16_t* serverName, uint16_t* userName, uint32_t level, uint32_t flags, unsigned char** buf, uint32_t prefMaxLen, uint32_t* entriesRead, uint32_t* totalEntries)
    {
        struct gocpp::error neterr;
        auto [r0, gocpp_id_42, gocpp_id_43] = syscall::Syscall9(rec::Addr(gocpp::recv(procNetUserGetLocalGroups)), 8, uintptr_t(unsafe::Pointer(serverName)), uintptr_t(unsafe::Pointer(userName)), uintptr_t(level), uintptr_t(flags), uintptr_t(unsafe::Pointer(buf)), uintptr_t(prefMaxLen), uintptr_t(unsafe::Pointer(entriesRead)), uintptr_t(unsafe::Pointer(totalEntries)), 0);
        if(r0 != 0)
        {
            neterr = syscall::Errno(r0);
        }
        return neterr;
    }

    struct gocpp::error GetProcessMemoryInfo(syscall::Handle handle, struct PROCESS_MEMORY_COUNTERS* memCounters, uint32_t cb)
    {
        struct gocpp::error err;
        auto [r1, gocpp_id_44, e1] = syscall::Syscall(rec::Addr(gocpp::recv(procGetProcessMemoryInfo)), 3, uintptr_t(handle), uintptr_t(unsafe::Pointer(memCounters)), uintptr_t(cb));
        if(r1 == 0)
        {
            err = errnoErr(e1);
        }
        return err;
    }

    struct gocpp::error CreateEnvironmentBlock(uint16_t** block, syscall::Token token, bool inheritExisting)
    {
        struct gocpp::error err;
        uint32_t _p0 = {};
        if(inheritExisting)
        {
            _p0 = 1;
        }
        auto [r1, gocpp_id_45, e1] = syscall::Syscall(rec::Addr(gocpp::recv(procCreateEnvironmentBlock)), 3, uintptr_t(unsafe::Pointer(block)), uintptr_t(token), uintptr_t(_p0));
        if(r1 == 0)
        {
            err = errnoErr(e1);
        }
        return err;
    }

    struct gocpp::error DestroyEnvironmentBlock(uint16_t* block)
    {
        struct gocpp::error err;
        auto [r1, gocpp_id_46, e1] = syscall::Syscall(rec::Addr(gocpp::recv(procDestroyEnvironmentBlock)), 1, uintptr_t(unsafe::Pointer(block)), 0, 0);
        if(r1 == 0)
        {
            err = errnoErr(e1);
        }
        return err;
    }

    struct gocpp::error GetProfilesDirectory(uint16_t* dir, uint32_t* dirLen)
    {
        struct gocpp::error err;
        auto [r1, gocpp_id_47, e1] = syscall::Syscall(rec::Addr(gocpp::recv(procGetProfilesDirectoryW)), 2, uintptr_t(unsafe::Pointer(dir)), uintptr_t(unsafe::Pointer(dirLen)), 0);
        if(r1 == 0)
        {
            err = errnoErr(e1);
        }
        return err;
    }

    std::tuple<syscall::Handle, struct gocpp::error> WSASocket(int32_t af, int32_t typ, int32_t protocol, syscall::WSAProtocolInfo* protinfo, uint32_t group, uint32_t flags)
    {
        syscall::Handle handle;
        struct gocpp::error err;
        auto [r0, gocpp_id_48, e1] = syscall::Syscall6(rec::Addr(gocpp::recv(procWSASocketW)), 6, uintptr_t(af), uintptr_t(typ), uintptr_t(protocol), uintptr_t(unsafe::Pointer(protinfo)), uintptr_t(group), uintptr_t(flags));
        handle = syscall::Handle(r0);
        if(handle == syscall::InvalidHandle)
        {
            err = errnoErr(e1);
        }
        return {handle, err};
    }

}

