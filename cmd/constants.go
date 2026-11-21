package main

import (
	"go/constant"
	"math"
)

var baseIndent string = "    "

// global namespace for all generated code
var goNs = "golang"

// receiver namespace
var recNs = "rec"

var int32Min = constant.MakeInt64(math.MinInt32)
var int32Max = constant.MakeInt64(math.MaxInt32)
var int64Min = constant.MakeInt64(math.MinInt64)
var int64Max = constant.MakeInt64(math.MaxInt64)
var uint64Max = constant.MakeUint64(math.MaxUint64)

type recvKey struct {
	pkgPath string // import path of the package declaring the method, "" for the universe (error)
	method  string
}

// Receivers implemented by hand in mocklib.
var mockedReceivers = map[recvKey]string{
	{"", "Error"}:       "mocklib::rec::Error",
	{"time", "Weekday"}: "mocklib::rec::Weekday",
	{"time", "Hour"}:    "mocklib::rec::Hour",
	{"sync", "Lock"}:    "mocklib::rec::Lock",
	{"sync", "Unlock"}:  "mocklib::rec::Unlock",
}

const cpp_str_lit = "_s"
const cpp_string_type = "gocpp::string"
const cpp_cplx64_type = "gocpp::complex64"
const cpp_cplx128_type = "gocpp::complex128"

// cf following files to add missing types:
//
//	=> "go\types\basic.go"
//	=> "go\types\universe.go"
var stdTypeMapping = map[string]string{
	"byte":       "unsigned char",
	"complex":    cpp_cplx128_type,
	"complex64":  cpp_cplx64_type,
	"complex128": cpp_cplx128_type,
	"float":      "double",
	"float32":    "float",
	"float64":    "double",
	"int":        "int64_t",
	"int8":       "int8_t",
	"int16":      "int16_t",
	"int32":      "int32_t",
	"int64":      "int64_t",
	"rune":       "gocpp::rune",
	"string":     cpp_string_type,
	"uint":       "uint64_t",
	"uint8":      "uint8_t",
	"uint16":     "uint16_t",
	"uint32":     "uint32_t",
	"uint64":     "uint64_t",
	"uintptr":    "uintptr_t",
	// untyped types !!!
	"untyped bool":    "bool",
	"untyped complex": cpp_cplx128_type,
	"untyped float":   "double",
	"untyped int":     "int64_t",
	"untyped rune":    "gocpp::rune",
	"untyped string":  cpp_string_type,

	// Type that are keywords in c++, we want to change them always but restore the original name
	// when we know that this is really a type and not an identifier.
	"go_bool": "bool",
}

var stdNsTypeMapping = map[string]nsType{
	// predefined types. To do: need a way to map them to type defined in "golang/runtime"
	"error": {"gocpp", "error"},
}

type fullName struct {
	namespace string
	name      string
}

var knownForwardableFunctions = map[fullName]bool{
	{"", "len"}:          true,
	{"unsafe", "Sizeof"}: true,
}

// Go builtins that are constant expressions in Go but have no constexpr
// implementation in the support library. Constants using them stay `inline const`.
var nonConstexprFuncs = map[fullName]bool{
	{"unsafe", "Offsetof"}: true, // gocpp::Offsetof uses reinterpret_cast
}

// TODO, make a dynamic mapping
var cppKeyWordsMapping = map[string]string{
	// map go keywords to C++ keywords
	"nil": "nullptr",

	// Avoid C++ keywords conflicts, some of them are not really a problem
	// as they are also go keyword and won't appears anywhere.
	"any":       "go_any",       // just to avoid confusion with std::any used in support lib
	"auto":      "go_auto",      // keyword
	"break":     "go_break",     // keyword
	"case":      "go_case",      // keyword
	"catch":     "go_catch",     // keyword
	"class":     "go_class",     // keyword
	"const":     "go_const",     // keyword
	"concept":   "go_concept",   // C++20 keyword
	"consteval": "go_consteval", // C++20 keyword
	"constexpr": "go_constexpr", // keyword
	"constinit": "go_constinit", // C++20 keyword
	"do":        "go_do",        // keyword
	"delete":    "go_delete",    // keyword
	"enum":      "go_enum",      // keyword
	"extern":    "go_extern",    // keyword
	"friend":    "go_friend",    // keyword
	"inline":    "go_inline",    // keyword
	"mutable":   "go_mutable",   // keyword
	"new":       "go_new",       // keyword
	"private":   "go_private",   // keyword
	"protected": "go_protected", // keyword
	"public":    "go_public",    // keyword
	"register":  "go_register",  // keyword
	"sizeof":    "go_sizeof",    // keyword
	"static":    "go_static",    // keyword
	"template":  "go_template",  // keyword
	"this":      "go_this",      // keyword
	"throw":     "go_throw",     // keyword
	"try":       "go_try",       // keyword
	"typeid":    "go_typeid",    // keyword
	"union":     "go_union",     // keyword
	"virtual":   "go_virtual",   // keyword
	"while":     "go_while",     // keyword

	// types that are keywords in C++ but not in Go
	"bool":     "go_bool",     // cpp_base_type
	"char":     "go_char",     // cpp_base_type
	"char8_t":  "go_char8_t",  // cpp_base_type
	"char16_t": "go_char16_t", // cpp_base_type
	"char32_t": "go_char32_t", // cpp_base_type
	"long":     "go_long",     // cpp_base_type
	"short":    "go_short",    // cpp_base_type
	"signed":   "go_signed",   // cpp_base_type
	"unsigned": "go_unsigned", // cpp_base_type
	"void":     "go_void",     // cpp_base_type
	"wchar_t":  "go_wchar_t",  // cpp_base_type

	// More keywords
	"asm":              "go_asm",
	"alignas":          "go_alignas",
	"co_await":         "go_co_await",
	"co_return":        "go_co_return",
	"co_yield":         "go_co_yield",
	"const_cast":       "go_const_cast",
	"decltype":         "go_decltype",
	"dynamic_cast":     "go_dynamic_cast",
	"explicit":         "go_explicit",
	"export":           "go_export",
	"namespace":        "go_namespace",
	"noexcept":         "go_noexcept",
	"nullptr":          "go_nullptr",
	"operator":         "go_operator",
	"reinterpret_cast": "go_reinterpret_cast",
	"requires":         "go_requires",
	"static_assert":    "go_static_assert",
	"static_cast":      "go_static_cast",
	"thread_local":     "go_thread_local",
	"typedef":          "go_typedef",
	"typename":         "go_typename",
	"using":            "go_using",
	"volatile":         "go_volatile",

	// C++ alternative operator tokens (and, or, not, xor are likely Go names)
	"and":    "go_and",
	"and_eq": "go_and_eq",
	"bitand": "go_bitand",
	"bitor":  "go_bitor",
	"compl":  "go_compl",
	"not":    "go_not",
	"not_eq": "go_not_eq",
	"or":     "go_or",
	"or_eq":  "go_or_eq",
	"xor":    "go_xor",
	"xor_eq": "go_xor_eq",

	"alignof":  "go_alignof",  // Macro of <cstddef>
	"offsetof": "go_offsetof", // Macro of <cstddef>
	"EOF":      "go_EOF",      // Macro of <cstdio>
	"stdin":    "go_stdin",    // Macro of <cstdio>
	"stdout":   "go_stdout",   // Macro of <cstdio>
	"stderr":   "go_stderr",   // Macro of <cstdio>

	"SEEK_SET": "go_SEEK_SET", // Macro of <stdio.h>
	"SEEK_CUR": "go_SEEK_CUR", // Macro of <stdio.h>
	"SEEK_END": "go_SEEK_END", // Macro of <stdio.h>

	"_NSIG":     "go__NSIG",     // Misc Macro
	"_MAX_PATH": "go__MAX_PATH", // Misc Macro

	"_C": "go_C", // Misc
	"_L": "go_L", // Misc
	"_N": "go_N", // Misc
	"_P": "go_P", // Misc
	"_S": "go_S", // Misc

	// <csignal>
	"SIGHUP":  "go_SIGHUP",  // Unix Macro
	"SIGINT":  "go_SIGINT",  // Unix Macro
	"SIGQUIT": "go_SIGQUIT", // Unix Macro
	"SIGILL":  "go_SIGILL",  // Unix Macro
	"SIGTRAP": "go_SIGTRAP", // Unix Macro
	"SIGABRT": "go_SIGABRT", // Unix Macro
	"SIGBUS":  "go_SIGBUS",  // Unix Macro
	"SIGFPE":  "go_SIGFPE",  // Unix Macro
	"SIGKILL": "go_SIGKILL", // Unix Macro
	"SIGSEGV": "go_SIGSEGV", // Unix Macro
	"SIGPIPE": "go_SIGPIPE", // Unix Macro
	"SIGALRM": "go_SIGALRM", // Unix Macro
	"SIGTERM": "go_SIGTERM", // Unix Macro

	// More signals
	"SIG_DFL":   "go_SIG_DFL",
	"SIG_IGN":   "go_SIG_IGN",
	"SIG_ERR":   "go_SIG_ERR",
	"SIGUSR1":   "go_SIGUSR1",
	"SIGUSR2":   "go_SIGUSR2",
	"SIGCHLD":   "go_SIGCHLD",
	"SIGCONT":   "go_SIGCONT",
	"SIGSTOP":   "go_SIGSTOP",
	"SIGTSTP":   "go_SIGTSTP",
	"SIGTTIN":   "go_SIGTTIN",
	"SIGTTOU":   "go_SIGTTOU",
	"SIGURG":    "go_SIGURG",
	"SIGXCPU":   "go_SIGXCPU",
	"SIGXFSZ":   "go_SIGXFSZ",
	"SIGVTALRM": "go_SIGVTALRM",
	"SIGPROF":   "go_SIGPROF",
	"SIGWINCH":  "go_SIGWINCH",
	"SIGIO":     "go_SIGIO",
	"SIGPWR":    "go_SIGPWR",
	"SIGSYS":    "go_SIGSYS",
	"SIGSTKFLT": "go_SIGSTKFLT",
	"SIGPOLL":   "go_SIGPOLL",
	"SIGRTMIN":  "go_SIGRTMIN",
	"SIGRTMAX":  "go_SIGRTMAX",

	// <cstdio>, <cstdlib>
	"NULL":         "go_NULL",
	"BUFSIZ":       "go_BUFSIZ",
	"EXIT_SUCCESS": "go_EXIT_SUCCESS",
	"EXIT_FAILURE": "go_EXIT_FAILURE",
	"RAND_MAX":     "go_RAND_MAX",
	"FILENAME_MAX": "go_FILENAME_MAX",
	"FOPEN_MAX":    "go_FOPEN_MAX",
	"TMP_MAX":      "go_TMP_MAX",
	"L_tmpnam":     "go_L_tmpnam",

	// <climits>, <cfloat>
	"CHAR_BIT":    "go_CHAR_BIT",
	"INT_MAX":     "go_INT_MAX",
	"INT_MIN":     "go_INT_MIN",
	"UINT_MAX":    "go_UINT_MAX",
	"LONG_MAX":    "go_LONG_MAX",
	"LONG_MIN":    "go_LONG_MIN",
	"FLT_MAX":     "go_FLT_MAX",
	"FLT_MIN":     "go_FLT_MIN",
	"FLT_EPSILON": "go_FLT_EPSILON",
	"DBL_MAX":     "go_DBL_MAX",
	"DBL_MIN":     "go_DBL_MIN",
	"DBL_EPSILON": "go_DBL_EPSILON",

	// <cmath>, <cerrno>
	"HUGE_VAL": "go_HUGE_VAL",
	"INFINITY": "go_INFINITY",
	"NAN":      "go_NAN",
	"M_PI":     "go_M_PI",
	"M_E":      "go_M_E",
	"errno":    "go_errno",

	// Windows & Unix header Macros
	"E2BIG":           "go_E2BIG",
	"EACCES":          "go_EACCES",
	"EADDRINUSE":      "go_EADDRINUSE",
	"EADDRNOTAVAIL":   "go_EADDRNOTAVAIL",
	"EADV":            "go_EADV",
	"EAFNOSUPPORT":    "go_EAFNOSUPPORT",
	"EAGAIN":          "go_EAGAIN",
	"EALREADY":        "go_EALREADY",
	"EBADE":           "go_EBADE",
	"EBADF":           "go_EBADF",
	"EBADFD":          "go_EBADFD",
	"EBADMSG":         "go_EBADMSG",
	"EBADR":           "go_EBADR",
	"EBADRQC":         "go_EBADRQC",
	"EBADSLT":         "go_EBADSLT",
	"EBFONT":          "go_EBFONT",
	"EBUSY":           "go_EBUSY",
	"ECANCELED":       "go_ECANCELED",
	"ECHILD":          "go_ECHILD",
	"ECHRNG":          "go_ECHRNG",
	"ECOMM":           "go_ECOMM",
	"ECONNABORTED":    "go_ECONNABORTED",
	"ECONNREFUSED":    "go_ECONNREFUSED",
	"ECONNRESET":      "go_ECONNRESET",
	"EDEADLK":         "go_EDEADLK",
	"EDEADLOCK":       "go_EDEADLOCK",
	"EDESTADDRREQ":    "go_EDESTADDRREQ",
	"EDOM":            "go_EDOM",
	"EDOTDOT":         "go_EDOTDOT",
	"EDQUOT":          "go_EDQUOT",
	"EEXIST":          "go_EEXIST",
	"EFAULT":          "go_EFAULT",
	"EFBIG":           "go_EFBIG",
	"EHOSTDOWN":       "go_EHOSTDOWN",
	"EHOSTUNREACH":    "go_EHOSTUNREACH",
	"EIDRM":           "go_EIDRM",
	"EILSEQ":          "go_EILSEQ",
	"EINPROGRESS":     "go_EINPROGRESS",
	"EINTR":           "go_EINTR",
	"EINVAL":          "go_EINVAL",
	"EIO":             "go_EIO",
	"EISCONN":         "go_EISCONN",
	"EISDIR":          "go_EISDIR",
	"EISNAM":          "go_EISNAM",
	"EKEYEXPIRED":     "go_EKEYEXPIRED",
	"EKEYREJECTED":    "go_EKEYREJECTED",
	"EKEYREVOKED":     "go_EKEYREVOKED",
	"EL2HLT":          "go_EL2HLT",
	"EL2NSYNC":        "go_EL2NSYNC",
	"EL3HLT":          "go_EL3HLT",
	"EL3RST":          "go_EL3RST",
	"ELIBACC":         "go_ELIBACC",
	"ELIBBAD":         "go_ELIBBAD",
	"ELIBEXEC":        "go_ELIBEXEC",
	"ELIBMAX":         "go_ELIBMAX",
	"ELIBSCN":         "go_ELIBSCN",
	"ELNRNG":          "go_ELNRNG",
	"ELOOP":           "go_ELOOP",
	"EMEDIUMTYPE":     "go_EMEDIUMTYPE",
	"EMFILE":          "go_EMFILE",
	"EMLINK":          "go_EMLINK",
	"EMSGSIZE":        "go_EMSGSIZE",
	"EMULTIHOP":       "go_EMULTIHOP",
	"ENAMETOOLONG":    "go_ENAMETOOLONG",
	"ENAVAIL":         "go_ENAVAIL",
	"ENETDOWN":        "go_ENETDOWN",
	"ENETRESET":       "go_ENETRESET",
	"ENETUNREACH":     "go_ENETUNREACH",
	"ENFILE":          "go_ENFILE",
	"ENOANO":          "go_ENOANO",
	"ENOBUFS":         "go_ENOBUFS",
	"ENOCSI":          "go_ENOCSI",
	"ENODATA":         "go_ENODATA",
	"ENODEV":          "go_ENODEV",
	"ENOEXEC":         "go_ENOEXEC",
	"ENOKEY":          "go_ENOKEY",
	"ENOLCK":          "go_ENOLCK",
	"ENOLINK":         "go_ENOLINK",
	"ENOMEDIUM":       "go_ENOMEDIUM",
	"ENOMEM":          "go_ENOMEM",
	"ENOMSG":          "go_ENOMSG",
	"ENONET":          "go_ENONET",
	"ENOPKG":          "go_ENOPKG",
	"ENOPROTOOPT":     "go_ENOPROTOOPT",
	"ENOSPC":          "go_ENOSPC",
	"ENOSR":           "go_ENOSR",
	"ENOSTR":          "go_ENOSTR",
	"ENOSYS":          "go_ENOSYS",
	"ENOTBLK":         "go_ENOTBLK",
	"ENOTCONN":        "go_ENOTCONN",
	"ENOTEMPTY":       "go_ENOTEMPTY",
	"ENOTNAM":         "go_ENOTNAM",
	"ENOTRECOVERABLE": "go_ENOTRECOVERABLE",
	"ENOTSOCK":        "go_ENOTSOCK",
	"ENOTSUP":         "go_ENOTSUP",
	"ENOTTY":          "go_ENOTTY",
	"ENOTUNIQ":        "go_ENOTUNIQ",
	"ENXIO":           "go_ENXIO",
	"EOPNOTSUPP":      "go_EOPNOTSUPP",
	"EOVERFLOW":       "go_EOVERFLOW",
	"EOWNERDEAD":      "go_EOWNERDEAD",
	"EPERM":           "go_EPERM",
	"EPFNOSUPPORT":    "go_EPFNOSUPPORT",
	"EPIPE":           "go_EPIPE",
	"EPROTO":          "go_EPROTO",
	"EPROTONOSUPPORT": "go_EPROTONOSUPPORT",
	"EPROTOTYPE":      "go_EPROTOTYPE",
	"ERANGE":          "go_ERANGE",
	"EREMCHG":         "go_EREMCHG",
	"EREMOTE":         "go_EREMOTE",
	"EREMOTEIO":       "go_EREMOTEIO",
	"ERESTART":        "go_ERESTART",
	"EROFS":           "go_EROFS",
	"ESHUTDOWN":       "go_ESHUTDOWN",
	"ESOCKTNOSUPPORT": "go_ESOCKTNOSUPPORT",
	"ESPIPE":          "go_ESPIPE",
	"ESRCH":           "go_ESRCH",
	"ESRMNT":          "go_ESRMNT",
	"ESTALE":          "go_ESTALE",
	"ESTRPIPE":        "go_ESTRPIPE",
	"ETIME":           "go_ETIME",
	"ETIMEDOUT":       "go_ETIMEDOUT",
	"ETOOMANYREFS":    "go_ETOOMANYREFS",
	"ETXTBSY":         "go_ETXTBSY",
	"EUCLEAN":         "go_EUCLEAN",
	"EUNATCH":         "go_EUNATCH",
	"EUSERS":          "go_EUSERS",
	"EWOULDBLOCK":     "go_EWOULDBLOCK",
	"EXDEV":           "go_EXDEV",
	"EXFULL":          "go_EXFULL",
	"EWINDOWS":        "go_EWINDOWS",

	"ENOENT":  "go_ENOENT",
	"ENOTDIR": "go_ENOTDIR",

	// <windows.h> (even with WIN32_LEAN_AND_MEAN)
	"TRUE":                 "go_TRUE",
	"FALSE":                "go_FALSE",
	"IN":                   "go_IN",
	"OUT":                  "go_OUT",
	"OPTIONAL":             "go_OPTIONAL",
	"CONST":                "go_CONST",
	"VOID":                 "go_VOID",
	"FAR":                  "go_FAR",
	"NEAR":                 "go_NEAR",
	"far":                  "go_far",
	"near":                 "go_near",
	"PASCAL":               "go_PASCAL",
	"CALLBACK":             "go_CALLBACK",
	"WINAPI":               "go_WINAPI",
	"APIENTRY":             "go_APIENTRY",
	"MAX_PATH":             "go_MAX_PATH",
	"ERROR":                "go_ERROR",
	"DELETE":               "go_DELETE",
	"NO_ERROR":             "go_NO_ERROR",
	"INFINITE":             "go_INFINITE",
	"INVALID_HANDLE_VALUE": "go_INVALID_HANDLE_VALUE",
	"STILL_ACTIVE":         "go_STILL_ACTIVE",
}

const unsafe_sizeof = "gocpp::unsafe_sizeof"
const unsafe_offsetof = "gocpp::unsafe_offsetof"

var stdFuncMapping = map[string]string{
	// Temporary mappings while 'import' isn't implemented
	// fmt
	"fmt::Print":   "mocklib::Print",
	"fmt::Printf":  "mocklib::Printf",
	"fmt::Println": "mocklib::Println",
	"fmt::Sprint":  "mocklib::Sprint",
	"fmt::Sprintf": "mocklib::Sprintf",
	"fmt::Errorf":  "mocklib::Errorf",
	// rand
	"rand::Intn": "mocklib::Intn",
	// runtime
	"runtime::GOOS": "mocklib::GOOS",
	// cmplx
	"cmplx::Sqrt": "std::sqrt",
	// math
	"math::Pow":   "mocklib::Pow",
	"math::Sqrt":  "std::sqrt",
	"math::Sqrt2": "mocklib::Sqrt2",
	"math::Pi":    "mocklib::Pi",
	// pic
	"pic::Show":      "mocklib::picShow",
	"pic::ShowImage": "mocklib::picShowImage",
	// time
	"time::Time":        "mocklib::Date",
	"time::After":       "mocklib::After",
	"time::Tick":        "mocklib::Tick",
	"time::Now":         "mocklib::Date::Now",
	"time::Saturday":    "mocklib::Date::Saturday",
	"time::Sleep":       "mocklib::Sleep",
	"time::Second":      "mocklib::Second",
	"time::Millisecond": "mocklib::Millisecond",

	// strings
	"strings::Join":   "mocklib::StringsJoin",
	"strings::Fields": "mocklib::StringsFields",

	// sync
	"sync::Mutex": "mocklib::Mutex",

	// wc
	"wc::Test": "mocklib::wcTest",

	// new/delete keywords
	"new":       "new",
	"delete":    "remove",
	"go_new":    "new",    // if already renamed by keyword mapping
	"go_delete": "remove", // if already renamed by keyword mapping

	// Predefined functions
	"make":              "gocpp::make",
	"max":               "gocpp::max",
	"min":               "gocpp::min",
	"panic":             "gocpp::panic",
	"recover":           "gocpp::recover",
	"unsafe::Offsetof":  unsafe_offsetof,
	"unsafe::Sizeof":    unsafe_sizeof,
	"unsafe::String":    "gocpp::unsafe_string",
	"unsafe::SliceData": "gocpp::unsafe_slice_data",

	// type conversions
	"byte":       "(unsigned char)",
	"complex":    cpp_cplx128_type,
	"complex64":  cpp_cplx64_type,
	"complex128": cpp_cplx128_type,
	"float":      "double",
	"float32":    "float",
	"float64":    "double",
	"int":        "int64_t",
	"int8":       "int8_t",
	"int16":      "int16_t",
	"int32":      "int32_t",
	"int64":      "int64_t",
	"rune":       "gocpp::rune",
	"string":     cpp_string_type,
	"uint":       "(uint64_t)",
	"uint8":      "uint8_t",
	"uint16":     "uint16_t",
	"uint32":     "uint32_t",
	"uint64":     "uint64_t",
	"uintptr":    "uintptr_t",

	"unsafe::Pointer": "gocpp::unsafe_pointer",
}

var knownCompilationErrors = []*errorFilter{}
var knownNameConflicts = []*errorFilter{}
var knownMissingDeps = []*errorFilter{}
var knownIncomplete = []*errorFilter{}
