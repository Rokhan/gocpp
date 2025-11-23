package main

var baseIndent string = "    "

// receiver namespace
var recNs = "rec"

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
	"complex64":  cpp_cplx64_type,
	"complex128": cpp_cplx128_type,
	"float":      "double",
	"float32":    "float",
	"float64":    "double",
	"int":        "int",
	"uintptr":    "uintptr_t",
	"uint":       "unsigned int",
	"uint8":      "uint8_t",
	"uint16":     "uint16_t",
	"uint32":     "uint32_t",
	"uint64":     "uint64_t",
	"int8":       "int8_t",
	"int16":      "int16_t",
	"int32":      "int32_t",
	"int64":      "int64_t",
	"rune":       "gocpp::rune",
	"string":     cpp_string_type,
	// untyped types !!!
	"untyped bool":    "bool",
	"untyped complex": cpp_cplx128_type,
	"untyped float":   "double",
	"untyped int":     "int",
	"untyped rune":    "gocpp::rune",
	"untyped string":  cpp_string_type,
	// predefined types. To do: need a way to map them to type defined in "golang/runtime"
	"error": "gocpp::error",
}

// TODO, make a dynamic mapping
var cppKeyWordsMapping = map[string]string{
	// map go keywords to C++ keywords
	"nil": "nullptr",

	// avoid C++ keywords conflicts
	"any":       "go_any",       // just to avoid confusion with std::any used in support lib
	"class":     "go_class",     // keyword
	"do":        "go_do",        // keyword
	"delete":    "go_delete",    // keyword
	"enum":      "go_enum",      // keyword
	"new":       "go_new",       // keyword
	"private":   "go_private",   // keyword
	"protected": "go_protected", // keyword
	"public":    "go_public",    // keyword
	"register":  "go_register",  // keyword
	"signed":    "go_signed",    // keyword
	"template":  "go_template",  // keyword
	"throw":     "go_throw",     // keyword
	"typeid":    "go_typeid",    // keyword
	"unsigned":  "go_unsigned",  // keyword
	"while":     "go_while",     // keyword
	"break":     "go_break",     // keyword
	"case":      "go_case",      // keyword

	"EOF":    "go_EOF",    // Macro of <cstdio>
	"stdin":  "go_stdin",  // Macro of <cstdio>
	"stdout": "go_stdout", // Macro of <cstdio>
	"stderr": "go_stderr", // Macro of <cstdio>

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
}

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
	"time::Time":         "mocklib::Date",
	"time::After":        "mocklib::After",
	"time::Tick":         "mocklib::Tick",
	"time::Now":          "mocklib::Date::Now",
	"time::Saturday":     "mocklib::Date::Saturday",
	"time::Sleep":        "mocklib::Sleep",
	"time::Second":       "mocklib::Second",
	"time::Millisecond":  "mocklib::Millisecond",
	"time::rec::Weekday": "mocklib::rec::Weekday",
	"time::rec::Hour":    "mocklib::rec::Hour",
	// strings
	"strings::Join":   "mocklib::StringsJoin",
	"strings::Fields": "mocklib::StringsFields",

	// sync
	"sync::Mutex":       "mocklib::Mutex",
	"sync::rec::Lock":   "mocklib::rec::Lock",
	"sync::rec::Unlock": "mocklib::rec::Unlock",

	// wc
	"wc::Test": "mocklib::wcTest",

	// new/delete keywords
	"new":       "new",
	"delete":    "remove",
	"go_new":    "new",    // if already renamed by keyword mapping
	"go_delete": "remove", // if already renamed by keyword mapping

	// Predefined functions
	"make":           "gocpp::make",
	"max":            "gocpp::max",
	"min":            "gocpp::min",
	"panic":          "gocpp::panic",
	"recover":        "gocpp::recover",
	"unsafe::Sizeof": "gocpp::Sizeof",

	// type conversions
	"byte":       "(unsigned char)",
	"complex64":  cpp_cplx64_type,
	"complex128": cpp_cplx128_type,
	"float":      "double",
	"float32":    "float",
	"float64":    "double",
	"int8":       "int8_t",
	"int16":      "int16_t",
	"int32":      "int32_t",
	"int64":      "int64_t",
	"rune":       "gocpp::rune",
	"string":     cpp_string_type,
	"uint":       "(unsigned int)",
	"uint8":      "uint8_t",
	"uint16":     "uint16_t",
	"uint32":     "uint32_t",
	"uint64":     "uint64_t",
	"uintptr":    "uintptr_t",
}

var knownCompilationErrors = []*errorFilter{}

var knownNameConflicts = []*errorFilter{}

var knownMissingDeps = []*errorFilter{
	{"mProfCycleWrap", "runtime/mprof"}, // constant using incomplete type

	{"pallocSumBytes", "runtime/mpagealloc"}, // constant using incomplete type

	{"gcBitsHeaderBytes", "runtime/mheap"}, // constant unsafe::Sizeof and incomplete type

	{"pageCachePages", "runtime/mpagecache"}, // constant unsafe::Sizeof and incomplete type

	{"hchanSize", "runtime/chan"}, // constant unsafe::Sizeof and incomplete type
}

var knownIncomplete = []*errorFilter{
	{"gcBitsArena::bits", "runtime/mheap"}, // type declaration ignored in header becuase of other error

	{"stackWorkBuf::obj", "runtime/mgcstack"}, // Declaration order + Need special case to manage unsafe::Sizeof

	{"workbuf::obj", "runtime/mgcwork"}, // Need special case to manage unsafe::Sizeof

	{"Method::Func", "reflect/type"},          // Multi header Declaration order problem
	{"methodValue::rcvr", "reflect/makefunc"}, // Multi header Declaration order problem
}
