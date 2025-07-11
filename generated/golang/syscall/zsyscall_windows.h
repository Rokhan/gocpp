// generated by GoCpp from file '$(ImportDir)/syscall/zsyscall_windows.go'
#pragma once

#include <functional>
#include <string>
#include <tuple>
#include <vector>

#include "golang/syscall/zsyscall_windows.fwd.h"
#include "gocpp/support.h"

#include "golang/sync/mutex.h"
#include "golang/syscall/dll_windows.h"
#include "golang/syscall/security_windows.h"
#include "golang/syscall/syscall_windows.h"
#include "golang/syscall/types_windows.h"
#include "golang/syscall/types_windows_amd64.h"

namespace golang::syscall
{
    extern unsafe::Pointer _;
    extern gocpp::error errERROR_IO_PENDING;
    extern gocpp::error errERROR_EINVAL;
    struct gocpp::error errnoErr(golang::syscall::Errno e);
    extern LazyDLL* modadvapi32;
    extern LazyDLL* modcrypt32;
    extern LazyDLL* moddnsapi;
    extern LazyDLL* modiphlpapi;
    extern LazyDLL* modkernel32;
    extern LazyDLL* modmswsock;
    extern LazyDLL* modnetapi32;
    extern LazyDLL* modntdll;
    extern LazyDLL* modsecur32;
    extern LazyDLL* modshell32;
    extern LazyDLL* moduserenv;
    extern LazyDLL* modws2_32;
    struct gocpp::error ConvertSidToStringSid(struct SID* sid, uint16_t** stringSid);
    struct gocpp::error ConvertStringSidToSid(uint16_t* stringSid, struct SID** sid);
    struct gocpp::error CopySid(uint32_t destSidLen, struct SID* destSid, struct SID* srcSid);
    struct gocpp::error CreateProcessAsUser(golang::syscall::Token token, uint16_t* appName, uint16_t* commandLine, struct SecurityAttributes* procSecurity, struct SecurityAttributes* threadSecurity, bool inheritHandles, uint32_t creationFlags, uint16_t* env, uint16_t* currentDir, struct StartupInfo* startupInfo, struct ProcessInformation* outProcInfo);
    struct gocpp::error CryptAcquireContext(golang::syscall::Handle* provhandle, uint16_t* container, uint16_t* provider, uint32_t provtype, uint32_t flags);
    struct gocpp::error CryptGenRandom(golang::syscall::Handle provhandle, uint32_t buflen, unsigned char* buf);
    struct gocpp::error CryptReleaseContext(golang::syscall::Handle provhandle, uint32_t flags);
    uint32_t GetLengthSid(struct SID* sid);
    struct gocpp::error GetTokenInformation(golang::syscall::Token t, uint32_t infoClass, unsigned char* info, uint32_t infoLen, uint32_t* returnedLen);
    struct gocpp::error LookupAccountName(uint16_t* systemName, uint16_t* accountName, struct SID* sid, uint32_t* sidLen, uint16_t* refdDomainName, uint32_t* refdDomainNameLen, uint32_t* use);
    struct gocpp::error LookupAccountSid(uint16_t* systemName, struct SID* sid, uint16_t* name, uint32_t* nameLen, uint16_t* refdDomainName, uint32_t* refdDomainNameLen, uint32_t* use);
    struct gocpp::error OpenProcessToken(golang::syscall::Handle h, uint32_t access, golang::syscall::Token* token);
    struct gocpp::error RegCloseKey(golang::syscall::Handle key);
    struct gocpp::error regEnumKeyEx(golang::syscall::Handle key, uint32_t index, uint16_t* name, uint32_t* nameLen, uint32_t* reserved, uint16_t* go_class, uint32_t* classLen, struct Filetime* lastWriteTime);
    struct gocpp::error RegOpenKeyEx(golang::syscall::Handle key, uint16_t* subkey, uint32_t options, uint32_t desiredAccess, golang::syscall::Handle* result);
    struct gocpp::error RegQueryInfoKey(golang::syscall::Handle key, uint16_t* go_class, uint32_t* classLen, uint32_t* reserved, uint32_t* subkeysLen, uint32_t* maxSubkeyLen, uint32_t* maxClassLen, uint32_t* valuesLen, uint32_t* maxValueNameLen, uint32_t* maxValueLen, uint32_t* saLen, struct Filetime* lastWriteTime);
    struct gocpp::error RegQueryValueEx(golang::syscall::Handle key, uint16_t* name, uint32_t* reserved, uint32_t* valtype, unsigned char* buf, uint32_t* buflen);
    struct gocpp::error CertAddCertificateContextToStore(golang::syscall::Handle store, struct CertContext* certContext, uint32_t addDisposition, struct CertContext** storeContext);
    struct gocpp::error CertCloseStore(golang::syscall::Handle store, uint32_t flags);
    std::tuple<struct CertContext*, struct gocpp::error> CertCreateCertificateContext(uint32_t certEncodingType, unsigned char* certEncoded, uint32_t encodedLen);
    std::tuple<struct CertContext*, struct gocpp::error> CertEnumCertificatesInStore(golang::syscall::Handle store, struct CertContext* prevContext);
    void CertFreeCertificateChain(struct CertChainContext* ctx);
    struct gocpp::error CertFreeCertificateContext(struct CertContext* ctx);
    struct gocpp::error CertGetCertificateChain(golang::syscall::Handle engine, struct CertContext* leaf, struct Filetime* time, golang::syscall::Handle additionalStore, struct CertChainPara* para, uint32_t flags, uintptr_t reserved, struct CertChainContext** chainCtx);
    std::tuple<syscall::Handle, struct gocpp::error> CertOpenStore(uintptr_t storeProvider, uint32_t msgAndCertEncodingType, uintptr_t cryptProv, uint32_t flags, uintptr_t para);
    std::tuple<syscall::Handle, struct gocpp::error> CertOpenSystemStore(golang::syscall::Handle hprov, uint16_t* name);
    struct gocpp::error CertVerifyCertificateChainPolicy(uintptr_t policyOID, struct CertChainContext* chain, struct CertChainPolicyPara* para, struct CertChainPolicyStatus* status);
    bool DnsNameCompare(uint16_t* name1, uint16_t* name2);
    struct gocpp::error DnsQuery(std::string name, uint16_t qtype, uint32_t options, unsigned char* extra, struct DNSRecord** qrs, unsigned char* pr);
    struct gocpp::error _DnsQuery(uint16_t* name, uint16_t qtype, uint32_t options, unsigned char* extra, struct DNSRecord** qrs, unsigned char* pr);
    void DnsRecordListFree(struct DNSRecord* rl, uint32_t freetype);
    struct gocpp::error GetAdaptersInfo(struct IpAdapterInfo* ai, uint32_t* ol);
    struct gocpp::error GetIfEntry(struct MibIfRow* pIfRow);
    struct gocpp::error CancelIo(golang::syscall::Handle s);
    struct gocpp::error CancelIoEx(golang::syscall::Handle s, struct Overlapped* o);
    struct gocpp::error CloseHandle(golang::syscall::Handle handle);
    struct gocpp::error CreateDirectory(uint16_t* path, struct SecurityAttributes* sa);
    std::tuple<syscall::Handle, struct gocpp::error> CreateFileMapping(golang::syscall::Handle fhandle, struct SecurityAttributes* sa, uint32_t prot, uint32_t maxSizeHigh, uint32_t maxSizeLow, uint16_t* name);
    std::tuple<syscall::Handle, struct gocpp::error> CreateFile(uint16_t* name, uint32_t access, uint32_t mode, struct SecurityAttributes* sa, uint32_t createmode, uint32_t attrs, int32_t templatefile);
    struct gocpp::error CreateHardLink(uint16_t* filename, uint16_t* existingfilename, uintptr_t reserved);
    std::tuple<syscall::Handle, struct gocpp::error> createIoCompletionPort(golang::syscall::Handle filehandle, golang::syscall::Handle cphandle, uintptr_t key, uint32_t threadcnt);
    struct gocpp::error CreatePipe(golang::syscall::Handle* readhandle, golang::syscall::Handle* writehandle, struct SecurityAttributes* sa, uint32_t size);
    struct gocpp::error CreateProcess(uint16_t* appName, uint16_t* commandLine, struct SecurityAttributes* procSecurity, struct SecurityAttributes* threadSecurity, bool inheritHandles, uint32_t creationFlags, uint16_t* env, uint16_t* currentDir, struct StartupInfo* startupInfo, struct ProcessInformation* outProcInfo);
    struct gocpp::error CreateSymbolicLink(uint16_t* symlinkfilename, uint16_t* targetfilename, uint32_t flags);
    std::tuple<syscall::Handle, struct gocpp::error> CreateToolhelp32Snapshot(uint32_t flags, uint32_t processId);
    struct gocpp::error DeleteFile(uint16_t* path);
    void deleteProcThreadAttributeList(struct _PROC_THREAD_ATTRIBUTE_LIST* attrlist);
    struct gocpp::error DeviceIoControl(golang::syscall::Handle handle, uint32_t ioControlCode, unsigned char* inBuffer, uint32_t inBufferSize, unsigned char* outBuffer, uint32_t outBufferSize, uint32_t* bytesReturned, struct Overlapped* overlapped);
    struct gocpp::error DuplicateHandle(golang::syscall::Handle hSourceProcessHandle, golang::syscall::Handle hSourceHandle, golang::syscall::Handle hTargetProcessHandle, golang::syscall::Handle* lpTargetHandle, uint32_t dwDesiredAccess, bool bInheritHandle, uint32_t dwOptions);
    void ExitProcess(uint32_t exitcode);
    struct gocpp::error FindClose(golang::syscall::Handle handle);
    std::tuple<syscall::Handle, struct gocpp::error> findFirstFile1(uint16_t* name, struct win32finddata1* data);
    struct gocpp::error findNextFile1(golang::syscall::Handle handle, struct win32finddata1* data);
    struct gocpp::error FlushFileBuffers(golang::syscall::Handle handle);
    struct gocpp::error FlushViewOfFile(uintptr_t addr, uintptr_t length);
    std::tuple<uint32_t, struct gocpp::error> formatMessage(uint32_t flags, uintptr_t msgsrc, uint32_t msgid, uint32_t langid, gocpp::slice<uint16_t> buf, unsigned char* args);
    struct gocpp::error FreeEnvironmentStrings(uint16_t* envs);
    struct gocpp::error FreeLibrary(golang::syscall::Handle handle);
    uint16_t* GetCommandLine();
    struct gocpp::error GetComputerName(uint16_t* buf, uint32_t* n);
    struct gocpp::error GetConsoleMode(golang::syscall::Handle console, uint32_t* mode);
    std::tuple<uint32_t, struct gocpp::error> GetCurrentDirectory(uint32_t buflen, uint16_t* buf);
    std::tuple<syscall::Handle, struct gocpp::error> GetCurrentProcess();
    uint32_t getCurrentProcessId();
    std::tuple<uint16_t*, struct gocpp::error> GetEnvironmentStrings();
    std::tuple<uint32_t, struct gocpp::error> GetEnvironmentVariable(uint16_t* name, uint16_t* buffer, uint32_t size);
    struct gocpp::error GetExitCodeProcess(golang::syscall::Handle handle, uint32_t* exitcode);
    struct gocpp::error GetFileAttributesEx(uint16_t* name, uint32_t level, unsigned char* info);
    std::tuple<uint32_t, struct gocpp::error> GetFileAttributes(uint16_t* name);
    struct gocpp::error GetFileInformationByHandle(golang::syscall::Handle handle, struct ByHandleFileInformation* data);
    std::tuple<uint32_t, struct gocpp::error> GetFileType(golang::syscall::Handle filehandle);
    std::tuple<uint32_t, struct gocpp::error> getFinalPathNameByHandle(golang::syscall::Handle file, uint16_t* filePath, uint32_t filePathSize, uint32_t flags);
    std::tuple<uint32_t, struct gocpp::error> GetFullPathName(uint16_t* path, uint32_t buflen, uint16_t* buf, uint16_t** fname);
    struct gocpp::error GetLastError();
    std::tuple<uint32_t, struct gocpp::error> GetLongPathName(uint16_t* path, uint16_t* buf, uint32_t buflen);
    std::tuple<uintptr_t, struct gocpp::error> GetProcAddress(golang::syscall::Handle module, std::string procname);
    std::tuple<uintptr_t, struct gocpp::error> _GetProcAddress(golang::syscall::Handle module, unsigned char* procname);
    struct gocpp::error GetProcessTimes(golang::syscall::Handle handle, struct Filetime* creationTime, struct Filetime* exitTime, struct Filetime* kernelTime, struct Filetime* userTime);
    struct gocpp::error getQueuedCompletionStatus(golang::syscall::Handle cphandle, uint32_t* qty, uintptr_t* key, struct Overlapped** overlapped, uint32_t timeout);
    std::tuple<uint32_t, struct gocpp::error> GetShortPathName(uint16_t* longpath, uint16_t* shortpath, uint32_t buflen);
    void getStartupInfo(struct StartupInfo* startupInfo);
    std::tuple<syscall::Handle, struct gocpp::error> GetStdHandle(int stdhandle);
    void GetSystemTimeAsFileTime(struct Filetime* time);
    std::tuple<uint32_t, struct gocpp::error> GetTempPath(uint32_t buflen, uint16_t* buf);
    std::tuple<uint32_t, struct gocpp::error> GetTimeZoneInformation(struct Timezoneinformation* tzi);
    std::tuple<uint32_t, struct gocpp::error> GetVersion();
    struct gocpp::error initializeProcThreadAttributeList(struct _PROC_THREAD_ATTRIBUTE_LIST* attrlist, uint32_t attrcount, uint32_t flags, uintptr_t* size);
    std::tuple<syscall::Handle, struct gocpp::error> LoadLibrary(std::string libname);
    std::tuple<syscall::Handle, struct gocpp::error> _LoadLibrary(uint16_t* libname);
    std::tuple<syscall::Handle, struct gocpp::error> LocalFree(golang::syscall::Handle hmem);
    std::tuple<uintptr_t, struct gocpp::error> MapViewOfFile(golang::syscall::Handle handle, uint32_t access, uint32_t offsetHigh, uint32_t offsetLow, uintptr_t length);
    struct gocpp::error MoveFile(uint16_t* from, uint16_t* to);
    std::tuple<syscall::Handle, struct gocpp::error> OpenProcess(uint32_t da, bool inheritHandle, uint32_t pid);
    struct gocpp::error postQueuedCompletionStatus(golang::syscall::Handle cphandle, uint32_t qty, uintptr_t key, struct Overlapped* overlapped);
    struct gocpp::error Process32First(golang::syscall::Handle snapshot, struct ProcessEntry32* procEntry);
    struct gocpp::error Process32Next(golang::syscall::Handle snapshot, struct ProcessEntry32* procEntry);
    struct gocpp::error ReadConsole(golang::syscall::Handle console, uint16_t* buf, uint32_t toread, uint32_t* read, unsigned char* inputControl);
    struct gocpp::error ReadDirectoryChanges(golang::syscall::Handle handle, unsigned char* buf, uint32_t buflen, bool watchSubTree, uint32_t mask, uint32_t* retlen, struct Overlapped* overlapped, uintptr_t completionRoutine);
    struct gocpp::error readFile(golang::syscall::Handle handle, gocpp::slice<unsigned char> buf, uint32_t* done, struct Overlapped* overlapped);
    struct gocpp::error RemoveDirectory(uint16_t* path);
    struct gocpp::error SetCurrentDirectory(uint16_t* path);
    struct gocpp::error SetEndOfFile(golang::syscall::Handle handle);
    struct gocpp::error SetEnvironmentVariable(uint16_t* name, uint16_t* value);
    struct gocpp::error SetFileAttributes(uint16_t* name, uint32_t attrs);
    struct gocpp::error SetFileCompletionNotificationModes(golang::syscall::Handle handle, uint8_t flags);
    std::tuple<uint32_t, struct gocpp::error> SetFilePointer(golang::syscall::Handle handle, int32_t lowoffset, int32_t* highoffsetptr, uint32_t whence);
    struct gocpp::error SetFileTime(golang::syscall::Handle handle, struct Filetime* ctime, struct Filetime* atime, struct Filetime* wtime);
    struct gocpp::error SetHandleInformation(golang::syscall::Handle handle, uint32_t mask, uint32_t flags);
    struct gocpp::error TerminateProcess(golang::syscall::Handle handle, uint32_t exitcode);
    struct gocpp::error UnmapViewOfFile(uintptr_t addr);
    struct gocpp::error updateProcThreadAttribute(struct _PROC_THREAD_ATTRIBUTE_LIST* attrlist, uint32_t flags, uintptr_t attr, unsafe::Pointer value, uintptr_t size, unsafe::Pointer prevvalue, uintptr_t* returnedsize);
    struct gocpp::error VirtualLock(uintptr_t addr, uintptr_t length);
    struct gocpp::error VirtualUnlock(uintptr_t addr, uintptr_t length);
    std::tuple<uint32_t, struct gocpp::error> WaitForSingleObject(golang::syscall::Handle handle, uint32_t waitMilliseconds);
    struct gocpp::error WriteConsole(golang::syscall::Handle console, uint16_t* buf, uint32_t towrite, uint32_t* written, unsigned char* reserved);
    struct gocpp::error writeFile(golang::syscall::Handle handle, gocpp::slice<unsigned char> buf, uint32_t* done, struct Overlapped* overlapped);
    struct gocpp::error AcceptEx(golang::syscall::Handle ls, golang::syscall::Handle as, unsigned char* buf, uint32_t rxdatalen, uint32_t laddrlen, uint32_t raddrlen, uint32_t* recvd, struct Overlapped* overlapped);
    void GetAcceptExSockaddrs(unsigned char* buf, uint32_t rxdatalen, uint32_t laddrlen, uint32_t raddrlen, struct RawSockaddrAny** lrsa, int32_t* lrsalen, struct RawSockaddrAny** rrsa, int32_t* rrsalen);
    struct gocpp::error TransmitFile(golang::syscall::Handle s, golang::syscall::Handle handle, uint32_t bytesToWrite, uint32_t bytsPerSend, struct Overlapped* overlapped, struct TransmitFileBuffers* transmitFileBuf, uint32_t flags);
    struct gocpp::error NetApiBufferFree(unsigned char* buf);
    struct gocpp::error NetGetJoinInformation(uint16_t* server, uint16_t** name, uint32_t* bufType);
    struct gocpp::error NetUserGetInfo(uint16_t* serverName, uint16_t* userName, uint32_t level, unsigned char** buf);
    void rtlGetNtVersionNumbers(uint32_t* majorVersion, uint32_t* minorVersion, uint32_t* buildNumber);
    struct gocpp::error GetUserNameEx(uint32_t nameFormat, uint16_t* nameBuffre, uint32_t* nSize);
    struct gocpp::error TranslateName(uint16_t* accName, uint32_t accNameFormat, uint32_t desiredNameFormat, uint16_t* translatedName, uint32_t* nSize);
    std::tuple<gocpp::array<gocpp::array<uint16_t, 8192>*, 8192>*, struct gocpp::error> CommandLineToArgv(uint16_t* cmd, int32_t* argc);
    struct gocpp::error GetUserProfileDirectory(golang::syscall::Token t, uint16_t* dir, uint32_t* dirLen);
    void FreeAddrInfoW(struct AddrinfoW* addrinfo);
    struct gocpp::error GetAddrInfoW(uint16_t* nodename, uint16_t* servicename, struct AddrinfoW* hints, struct AddrinfoW** result);
    struct gocpp::error WSACleanup();
    std::tuple<int32_t, struct gocpp::error> WSAEnumProtocols(int32_t* protocols, struct WSAProtocolInfo* protocolBuffer, uint32_t* bufferLength);
    struct gocpp::error WSAIoctl(golang::syscall::Handle s, uint32_t iocc, unsigned char* inbuf, uint32_t cbif, unsigned char* outbuf, uint32_t cbob, uint32_t* cbbr, struct Overlapped* overlapped, uintptr_t completionRoutine);
    struct gocpp::error WSARecv(golang::syscall::Handle s, struct WSABuf* bufs, uint32_t bufcnt, uint32_t* recvd, uint32_t* flags, struct Overlapped* overlapped, unsigned char* croutine);
    struct gocpp::error WSARecvFrom(golang::syscall::Handle s, struct WSABuf* bufs, uint32_t bufcnt, uint32_t* recvd, uint32_t* flags, struct RawSockaddrAny* from, int32_t* fromlen, struct Overlapped* overlapped, unsigned char* croutine);
    struct gocpp::error WSASend(golang::syscall::Handle s, struct WSABuf* bufs, uint32_t bufcnt, uint32_t* sent, uint32_t flags, struct Overlapped* overlapped, unsigned char* croutine);
    struct gocpp::error WSASendTo(golang::syscall::Handle s, struct WSABuf* bufs, uint32_t bufcnt, uint32_t* sent, uint32_t flags, struct RawSockaddrAny* to, int32_t tolen, struct Overlapped* overlapped, unsigned char* croutine);
    struct gocpp::error WSAStartup(uint32_t verreq, struct WSAData* data);
    struct gocpp::error bind(golang::syscall::Handle s, unsafe::Pointer name, int32_t namelen);
    struct gocpp::error Closesocket(golang::syscall::Handle s);
    struct gocpp::error connect(golang::syscall::Handle s, unsafe::Pointer name, int32_t namelen);
    std::tuple<struct Hostent*, struct gocpp::error> GetHostByName(std::string name);
    std::tuple<struct Hostent*, struct gocpp::error> _GetHostByName(unsigned char* name);
    struct gocpp::error getpeername(golang::syscall::Handle s, struct RawSockaddrAny* rsa, int32_t* addrlen);
    std::tuple<struct Protoent*, struct gocpp::error> GetProtoByName(std::string name);
    std::tuple<struct Protoent*, struct gocpp::error> _GetProtoByName(unsigned char* name);
    std::tuple<struct Servent*, struct gocpp::error> GetServByName(std::string name, std::string proto);
    std::tuple<struct Servent*, struct gocpp::error> _GetServByName(unsigned char* name, unsigned char* proto);
    struct gocpp::error getsockname(golang::syscall::Handle s, struct RawSockaddrAny* rsa, int32_t* addrlen);
    struct gocpp::error Getsockopt(golang::syscall::Handle s, int32_t level, int32_t optname, unsigned char* optval, int32_t* optlen);
    struct gocpp::error listen(golang::syscall::Handle s, int32_t backlog);
    uint16_t Ntohs(uint16_t netshort);
    struct gocpp::error Setsockopt(golang::syscall::Handle s, int32_t level, int32_t optname, unsigned char* optval, int32_t optlen);
    struct gocpp::error shutdown(golang::syscall::Handle s, int32_t how);
    std::tuple<syscall::Handle, struct gocpp::error> socket(int32_t af, int32_t typ, int32_t protocol);
    extern LazyProc* procConvertSidToStringSidW;
    extern LazyProc* procConvertStringSidToSidW;
    extern LazyProc* procCopySid;
    extern LazyProc* procCreateProcessAsUserW;
    extern LazyProc* procCryptAcquireContextW;
    extern LazyProc* procCryptGenRandom;
    extern LazyProc* procCryptReleaseContext;
    extern LazyProc* procGetLengthSid;
    extern LazyProc* procGetTokenInformation;
    extern LazyProc* procLookupAccountNameW;
    extern LazyProc* procLookupAccountSidW;
    extern LazyProc* procOpenProcessToken;
    extern LazyProc* procRegCloseKey;
    extern LazyProc* procRegEnumKeyExW;
    extern LazyProc* procRegOpenKeyExW;
    extern LazyProc* procRegQueryInfoKeyW;
    extern LazyProc* procRegQueryValueExW;
    extern LazyProc* procCertAddCertificateContextToStore;
    extern LazyProc* procCertCloseStore;
    extern LazyProc* procCertCreateCertificateContext;
    extern LazyProc* procCertEnumCertificatesInStore;
    extern LazyProc* procCertFreeCertificateChain;
    extern LazyProc* procCertFreeCertificateContext;
    extern LazyProc* procCertGetCertificateChain;
    extern LazyProc* procCertOpenStore;
    extern LazyProc* procCertOpenSystemStoreW;
    extern LazyProc* procCertVerifyCertificateChainPolicy;
    extern LazyProc* procDnsNameCompare_W;
    extern LazyProc* procDnsQuery_W;
    extern LazyProc* procDnsRecordListFree;
    extern LazyProc* procGetAdaptersInfo;
    extern LazyProc* procGetIfEntry;
    extern LazyProc* procCancelIo;
    extern LazyProc* procCancelIoEx;
    extern LazyProc* procCloseHandle;
    extern LazyProc* procCreateDirectoryW;
    extern LazyProc* procCreateFileMappingW;
    extern LazyProc* procCreateFileW;
    extern LazyProc* procCreateHardLinkW;
    extern LazyProc* procCreateIoCompletionPort;
    extern LazyProc* procCreatePipe;
    extern LazyProc* procCreateProcessW;
    extern LazyProc* procCreateSymbolicLinkW;
    extern LazyProc* procCreateToolhelp32Snapshot;
    extern LazyProc* procDeleteFileW;
    extern LazyProc* procDeleteProcThreadAttributeList;
    extern LazyProc* procDeviceIoControl;
    extern LazyProc* procDuplicateHandle;
    extern LazyProc* procExitProcess;
    extern LazyProc* procFindClose;
    extern LazyProc* procFindFirstFileW;
    extern LazyProc* procFindNextFileW;
    extern LazyProc* procFlushFileBuffers;
    extern LazyProc* procFlushViewOfFile;
    extern LazyProc* procFormatMessageW;
    extern LazyProc* procFreeEnvironmentStringsW;
    extern LazyProc* procFreeLibrary;
    extern LazyProc* procGetCommandLineW;
    extern LazyProc* procGetComputerNameW;
    extern LazyProc* procGetConsoleMode;
    extern LazyProc* procGetCurrentDirectoryW;
    extern LazyProc* procGetCurrentProcess;
    extern LazyProc* procGetCurrentProcessId;
    extern LazyProc* procGetEnvironmentStringsW;
    extern LazyProc* procGetEnvironmentVariableW;
    extern LazyProc* procGetExitCodeProcess;
    extern LazyProc* procGetFileAttributesExW;
    extern LazyProc* procGetFileAttributesW;
    extern LazyProc* procGetFileInformationByHandle;
    extern LazyProc* procGetFileType;
    extern LazyProc* procGetFinalPathNameByHandleW;
    extern LazyProc* procGetFullPathNameW;
    extern LazyProc* procGetLastError;
    extern LazyProc* procGetLongPathNameW;
    extern LazyProc* procGetProcAddress;
    extern LazyProc* procGetProcessTimes;
    extern LazyProc* procGetQueuedCompletionStatus;
    extern LazyProc* procGetShortPathNameW;
    extern LazyProc* procGetStartupInfoW;
    extern LazyProc* procGetStdHandle;
    extern LazyProc* procGetSystemTimeAsFileTime;
    extern LazyProc* procGetTempPathW;
    extern LazyProc* procGetTimeZoneInformation;
    extern LazyProc* procGetVersion;
    extern LazyProc* procInitializeProcThreadAttributeList;
    extern LazyProc* procLoadLibraryW;
    extern LazyProc* procLocalFree;
    extern LazyProc* procMapViewOfFile;
    extern LazyProc* procMoveFileW;
    extern LazyProc* procOpenProcess;
    extern LazyProc* procPostQueuedCompletionStatus;
    extern LazyProc* procProcess32FirstW;
    extern LazyProc* procProcess32NextW;
    extern LazyProc* procReadConsoleW;
    extern LazyProc* procReadDirectoryChangesW;
    extern LazyProc* procReadFile;
    extern LazyProc* procRemoveDirectoryW;
    extern LazyProc* procSetCurrentDirectoryW;
    extern LazyProc* procSetEndOfFile;
    extern LazyProc* procSetEnvironmentVariableW;
    extern LazyProc* procSetFileAttributesW;
    extern LazyProc* procSetFileCompletionNotificationModes;
    extern LazyProc* procSetFilePointer;
    extern LazyProc* procSetFileTime;
    extern LazyProc* procSetHandleInformation;
    extern LazyProc* procTerminateProcess;
    extern LazyProc* procUnmapViewOfFile;
    extern LazyProc* procUpdateProcThreadAttribute;
    extern LazyProc* procVirtualLock;
    extern LazyProc* procVirtualUnlock;
    extern LazyProc* procWaitForSingleObject;
    extern LazyProc* procWriteConsoleW;
    extern LazyProc* procWriteFile;
    extern LazyProc* procAcceptEx;
    extern LazyProc* procGetAcceptExSockaddrs;
    extern LazyProc* procTransmitFile;
    extern LazyProc* procNetApiBufferFree;
    extern LazyProc* procNetGetJoinInformation;
    extern LazyProc* procNetUserGetInfo;
    extern LazyProc* procRtlGetNtVersionNumbers;
    extern LazyProc* procGetUserNameExW;
    extern LazyProc* procTranslateNameW;
    extern LazyProc* procCommandLineToArgvW;
    extern LazyProc* procGetUserProfileDirectoryW;
    extern LazyProc* procFreeAddrInfoW;
    extern LazyProc* procGetAddrInfoW;
    extern LazyProc* procWSACleanup;
    extern LazyProc* procWSAEnumProtocolsW;
    extern LazyProc* procWSAIoctl;
    extern LazyProc* procWSARecv;
    extern LazyProc* procWSARecvFrom;
    extern LazyProc* procWSASend;
    extern LazyProc* procWSASendTo;
    extern LazyProc* procWSAStartup;
    extern LazyProc* procbind;
    extern LazyProc* procclosesocket;
    extern LazyProc* procconnect;
    extern LazyProc* procgethostbyname;
    extern LazyProc* procgetpeername;
    extern LazyProc* procgetprotobyname;
    extern LazyProc* procgetservbyname;
    extern LazyProc* procgetsockname;
    extern LazyProc* procgetsockopt;
    extern LazyProc* proclisten;
    extern LazyProc* procntohs;
    extern LazyProc* procsetsockopt;
    extern LazyProc* procshutdown;
    extern LazyProc* procsocket;

    namespace rec
    {
    }
}

