package main

// cf following files to add missing types:
//
//	=> "go\types\basic.go"
//	=> "go\types\universe.go"
var stdTypeMapping = map[string]string{
	"byte":       "unsigned char",
	"complex128": "gocpp::complex128",
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
	"string":     "std::string",
	// untyped types !!!
	"untyped bool":    "bool",
	"untyped complex": "goccp::complex128",
	"untyped float":   "double",
	"untyped int":     "int",
	"untyped rune":    "gocpp::rune",
	"untyped string":  "std::string",
	// predefined types
	"error": "std::string",
}

// TODO, make a dynamic mapping
var cppKeyWordsMapping = map[string]string{
	"any":       "go_any",       // just to avoid confusion with std::any used in support lib
	"class":     "go_class",     // keyword
	"do":        "go_do",        // keyword
	"delete":    "go_delete",    // keyword
	"enum":      "go_enum",      // keyword
	"EOF":       "go_EOF",       // Macro of <cstdio>
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
}

var stdFuncMapping = map[string]string{
	// Temporary mappings while 'import' isn't implemented
	// fmt
	"fmt::Print":   "mocklib::Print",
	"fmt::Printf":  "mocklib::Printf",
	"fmt::Println": "mocklib::Println",
	"fmt::Sprint":  "mocklib::Sprint",
	"fmt::Sprintf": "mocklib::Sprintf",
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
	"pic::Show": "mocklib::picShow",
	// time
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

	// Predefined functions
	"delete":         "remove",
	"go_delete":      "remove", // if already renamed by keyword mapping
	"make":           "gocpp::make",
	"panic":          "gocpp::panic",
	"recover":        "gocpp::recover",
	"nil":            "nullptr",
	"unsafe::Sizeof": "gocpp::Sizeof",

	// type conversions
	"byte":       "unsigned char",
	"complex128": "gocpp::complex128",
	"float":      "double",
	"float32":    "float",
	"float64":    "double",
	"uint":       "(unsigned int)",
	"uint8":      "uint8_t",
	"uint16":     "uint16_t",
	"uint32":     "uint32_t",
	"uint64":     "uint64_t",
	"uintptr":    "uintptr_t",
	"int8":       "int8_t",
	"int16":      "int16_t",
	"int32":      "int32_t",
	"int64":      "int64_t",
}

var knownCompilationErrors = []*errorFilter{
	{"abi", "internal/abi/symtab.go"},
	{"bytealg", "internal/bytealg/bytealg.go"},
	{"cmp", "cmp/cmp.go"},
	{"cpu", "internal/cpu/cpu.go"},
	{"atomic", "sync/atomic/doc.go"},
	{"fmtsort", "internal/fmtsort/sort.go"},
	{"pic", "golang.org/x/tour@v0.1.0/pic/pic.go"},
	{"wc", "golang.org/x/tour@v0.1.0/wc/wc.go"},
	{"png", "image/png/writer.go"},
	{"race", "internal/race/norace.go"},
	{"reflect", "reflect/value.go"},
	{"runtime", "runtime/alg.go"},
	{"runtime", "runtime/cgocall.go"},
	{"runtime", "runtime/defs_windows.go"},
	{"runtime", "runtime/lockrank.go"},
	{"runtime", "runtime/lockrank_off.go"},
	{"runtime", "runtime/lock_sema.go"},
	{"runtime", "runtime/mbitmap_allocheaders.go"},
	{"runtime", "runtime/metrics.go"},
	{"runtime", "runtime/mgclimit.go"},
	{"runtime", "runtime/mgcscavenge.go"},
	{"runtime", "runtime/mgcpacer.go"},
	{"runtime", "runtime/mgcsweep.go"},
	{"runtime", "runtime/mcache.go"},
	{"runtime", "runtime/netpoll.go"},
	{"runtime", "runtime/netpoll_windows.go"},
	{"runtime", "runtime/os_windows.go"},
	{"runtime", "runtime/pagetrace_off.go"},
	{"runtime", "runtime/preempt.go"},
	{"runtime", "runtime/print.go"},
	{"runtime", "runtime/rand.go"},
	{"runtime", "runtime/runtime1.go"},
	{"runtime", "runtime/sema.go"},
	{"runtime", "runtime/sigqueue_note.go"},
	{"runtime", "runtime/signal_windows.go"},
	{"runtime", "runtime/stubs.go"},
	{"runtime", "runtime/symtab.go"},
	{"runtime", "runtime/symtabinl.go"},
	{"runtime", "runtime/syscall_windows.go"},
	{"runtime", "runtime/traceback.go"},
	{"runtime", "runtime/trace2map.go"},
	{"runtime", "runtime/trace2region.go"},
	{"runtime", "runtime/trace2runtime.go"},
	{"runtime", "runtime/time.go"},
	{"runtime", "runtime/typekind.go"},
	{"slices", "slices/sort.go"},
	{"slices", "slices/zsortanyfunc.go"},
	{"slices", "slices/zsortordered.go"},
	{"sync", "sync/cond.go"},
	{"sync", "sync/runtime.go"},
	{"sync", "sync/runtime2.go"},
	{"time", "time/tick.go"},
}

var knownNameConflicts = []*errorFilter{
	{"ArrayType", "internal/abi/type"},
	{"ChanDir", "internal/abi/type"},
	{"FuncType", "internal/abi/type"},
	{"InterfaceType", "internal/abi/type"},
	{"Kind", "internal/abi/type"},
	{"Name", "internal/abi/type"},
	{"String", "internal/abi/type"},
	{"StructType", "internal/abi/type"},
	{"MapType", "internal/abi/type"},

	{"name", "runtime/type"},
	{"nameOff", "runtime/type"},
	{"typeOff", "runtime/type"},
	{"textOff", "runtime/type"},

	{"slice", "runtime/mbarrier"},
	{"slice", "runtime/arena"},

	// missing included type def
	{"typesEqual", "runtime/type"},
	{"partialUnswept", "runtime/mcentral"},
	{"partialSwept", "runtime/mcentral"},
	{"fullUnswept", "runtime/mcentral"},
	{"fullSwept", "runtime/mcentral"},

	{"queuefinalizer", "runtime/mfinal"},
	{"iterate_finq", "runtime/mfinal"},
	{"finalizercommit", "runtime/mfinal"},
	{"wakefing", "runtime/mfinal"},

	{"recordUnlock", "runtime/mprof"},                // missing type from broken include
	{"recordLock", "runtime/mprof"},                  // missing type from broken include
	{"tryRecordGoroutineProfileWB", "runtime/mprof"}, // missing type from broken include
	{"tryRecordGoroutineProfile", "runtime/mprof"},   // missing type from broken include
	{"doRecordGoroutineProfile", "runtime/mprof"},    // missing type from broken include
	{"saveg", "runtime/mprof"},                       // missing type from broken include

	{"Month", "time/time"},      // func vs type
	{"Weekday", "time/time"},    // func vs type
	{"Location", "time/time"},   // func vs type
	{"Hour", "time/time"},       // func vs constant
	{"Minute", "time/time"},     // func vs constant
	{"Second", "time/time"},     // func vs constant
	{"Nanosecond", "time/time"}, // func vs constant
	{"UTC", "time/time"},        // func vs global var
	{"Local", "time/time"},      // func vs global var
}

var knownMissingDeps = []*errorFilter{
	{"buckhashArray", "runtime/mprof"},
	{"goroutineProfileStateHolder", "runtime/mprof"},
	{"mProfCycleWrap", "runtime/mprof"}, // constant using incomplete type

	{"pallocSumBytes", "runtime/mpagealloc"}, // constant using incomplete type

	{"physPageAlignedStacks", "runtime/mheap"}, // constant using strings (GOOS == "openbsd")
	{"gcBitsHeaderBytes", "runtime/mheap"},     // constant unsafe::Sizeof and incomplete type

	{"pageCachePages", "runtime/mpagecache"}, // constant unsafe::Sizeof and incomplete type

	{"hchanSize", "runtime/chan"}, // constant unsafe::Sizeof and incomplete type
}

var knownIncomplete = []*errorFilter{
	{"InterfaceType::PkgPath", "internal/abi/type"},
	{"StructField::Name", "internal/abi/type"},
	{"StructType::PkgPath", "internal/abi/type"},

	{"dlogger::w", "runtime/debuglog"},           // Declaration order problem
	{"dlogger::owned", "runtime/debuglog"},       // Type not declared because of error in included files
	{"debugLogWriter::data", "runtime/debuglog"}, // Declaration order problem
	{"debugLogWriter::r", "runtime/debuglog"},    // Declaration order problem

	{"memRecord::active", "runtime/mprof"},       // Declaration order problem
	{"mProfCycleHolder::value", "runtime/mprof"}, // Type not declared because of error in included files
	{"lockTimer::lock", "runtime/mprof"},         // Type not declared because of error in included files
	{"mLockProfile::waitTime", "runtime/mprof"},  // Type not declared because of error in included files

	{"mcentral::partial", "runtime/mcentral"}, // Type not declared because of error in included files
	{"mcentral::full", "runtime/mcentral"},    // Type not declared because of error in included files

	{"finblock::_", "runtime/mfinal"},   // ??? !!!
	{"finblock::fin", "runtime/mfinal"}, // Unknwon constants in type
	{"finalizer::fn", "runtime/mfinal"}, // Unknwon constants in type

	{"userArena::defunct", "runtime/arena"}, // Type not declared because of error in included files

	{"hchan::recvq", "runtime/chan"}, // Declaration order problem
	{"hchan::sendq", "runtime/chan"}, // Declaration order problem
	{"hchan::lock", "runtime/chan"},  // Type not declared because of error in included files
	{"waitq::first", "runtime/chan"}, // Type not declared because of error in included files
	{"waitq::last", "runtime/chan"},  // Type not declared because of error in included files

	{"mstats::heapStats", "runtime/mstats"}, // Declaration order problem

	{"addrRange::base", "runtime/mranges"},  // Declaration order problem
	{"addrRange::limit", "runtime/mranges"}, // Declaration order problem

	{"pageAlloc::scav", "runtime/mpagealloc"}, // Missing inlined subtype gocpp_id_0

	{"mheap::_", "runtime/mheap"},              // ??? !!!
	{"mheap::curArena", "runtime/mheap"},       // Missing inlined subtype gocpp_id_0
	{"mheap::userArena", "runtime/mheap"},      // Missing inlined subtype gocpp_id_2
	{"mheap::heapArenaAlloc", "runtime/mheap"}, // Multi header Declaration order problem with runtime/malloc
	{"mheap::arena", "runtime/mheap"},          // Multi header Declaration order problem with runtime/malloc
	{"gcBitsArena::bits", "runtime/mheap"},     // type declaration ignored in header becuase of other error

	{"stackpoolItem::span", "runtime/stack"}, // Multi header Declaration order problem with runtime/mheap

	{"stackWorkBuf::obj", "runtime/mgcstack"},   // Declaration order + Need special case to manage unsafe::Sizeof
	{"stackObjectBuf::obj", "runtime/mgcstack"}, // Multi header Declaration order problem with runtime/malloc

	{"workbuf::obj", "runtime/mgcwork"}, // Need special case to manage unsafe::Sizeof

	{"Int32::noCopy", "runtime/internal/atomic/types"},         // Declaration order problem
	{"Int64::noCopy", "runtime/internal/atomic/types"},         // Declaration order problem
	{"Int64::_", "runtime/internal/atomic/types"},              // Declaration order problem
	{"Uint8::noCopy", "runtime/internal/atomic/types"},         // Declaration order problem
	{"Uint32::noCopy", "runtime/internal/atomic/types"},        // Declaration order problem
	{"Uint64::noCopy", "runtime/internal/atomic/types"},        // Declaration order problem
	{"Uint64::_", "runtime/internal/atomic/types"},             // Declaration order problem
	{"Uintptr::noCopy", "runtime/internal/atomic/types"},       // Declaration order problem
	{"UnsafePointer::noCopy", "runtime/internal/atomic/types"}, // Declaration order problem

	{"spanSet::spineLock", "runtime/mspanset"},       // Multi header Declaration order problem with runtime/malloc
	{"spanSet::spine", "runtime/mspanset"},           // Declaration order problem
	{"spanSet::index", "runtime/mspanset"},           // Declaration order problem
	{"spanSetBlockAlloc::stack", "runtime/mspanset"}, // Type not declared, included files not generated

	{"cpuProfile::lock", "runtime/cpuprof"}, // Multi header Declaration order problem with runtime/malloc

	{"profBuf::wait", "runtime/profbuf"}, // Multi header Declaration order problem with runtime/malloc

	{"traceEventWriter::w", "runtime/trace2event"}, // Multi header Declaration order problem with runtime/malloc

	{"Bool::_", "sync/atomic/type"},    // Declaration order problem
	{"Pointer::_", "sync/atomic/type"}, // Declaration order problem
	{"Int32::_", "sync/atomic/type"},   // Declaration order problem
	{"Int64::_", "sync/atomic/type"},   // Declaration order problem
	{"Uint32::_", "sync/atomic/type"},  // Declaration order problem
	{"Uint64::_", "sync/atomic/type"},  // Declaration order problem
	{"Uintptr::_", "sync/atomic/type"}, // Declaration order problem

	{"Pool::noCopy", "sync/pool"}, // Declaration order problem

	{"Matcher::dedup", "internal/bisect/bisect"}, // Declaration order problem

	{"Location::cacheZone", "time/zoneinfo"}, // Declaration order problem
}
