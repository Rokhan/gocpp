#include <complex>
#include <functional>
#include <iostream>
#include <iomanip>
#include <map>
#include <string>
#include <tuple>
#include <vector>

#include "tests/TourOfGo/flowcontrol/switch.h"
#include "gocpp/support.h"

// TODO: package import not implemented
// #include "fmt/doc.h"
// #include "fmt/errors.h"
// #include "fmt/format.h"
// #include "fmt/print.h"
// #include "fmt/scan.h"
// #include "runtime/alg.h"
// #include "runtime/arena.h"
// #include "runtime/asan0.h"
// #include "runtime/atomic_pointer.h"
// #include "runtime/auxv_none.h"
// #include "runtime/cgo.h"
// #include "runtime/cgocall.h"
// #include "runtime/cgocallback.h"
// #include "runtime/cgocheck.h"
// #include "runtime/chan.h"
// #include "runtime/checkptr.h"
// #include "runtime/compiler.h"
// #include "runtime/complex.h"
// #include "runtime/coro.h"
// #include "runtime/covercounter.h"
// #include "runtime/covermeta.h"
// #include "runtime/cpuflags.h"
// #include "runtime/cpuflags_amd64.h"
// #include "runtime/cpuprof.h"
// #include "runtime/cputicks.h"
// #include "runtime/create_file_nounix.h"
// #include "runtime/debug.h"
// #include "runtime/debugcall.h"
// #include "runtime/debuglog.h"
// #include "runtime/debuglog_off.h"
// #include "runtime/defs_windows.h"
// #include "runtime/defs_windows_amd64.h"
// #include "runtime/env_posix.h"
// #include "runtime/error.h"
// #include "runtime/exithook.h"
// #include "runtime/extern.h"
// #include "runtime/fastlog2.h"
// #include "runtime/fastlog2table.h"
// #include "runtime/fds_nonunix.h"
// #include "runtime/float.h"
// #include "runtime/hash64.h"
// #include "runtime/heapdump.h"
// #include "runtime/histogram.h"
// #include "runtime/iface.h"
// #include "runtime/lfstack.h"
// #include "runtime/lock_sema.h"
// #include "runtime/lockrank.h"
// #include "runtime/lockrank_off.h"
// #include "runtime/malloc.h"
// #include "runtime/map.h"
// #include "runtime/map_fast32.h"
// #include "runtime/map_fast64.h"
// #include "runtime/map_faststr.h"
// #include "runtime/mbarrier.h"
// #include "runtime/mbitmap.h"
// #include "runtime/mbitmap_allocheaders.h"
// #include "runtime/mcache.h"
// #include "runtime/mcentral.h"
// #include "runtime/mcheckmark.h"
// #include "runtime/mem.h"
// #include "runtime/mem_windows.h"
// #include "runtime/metrics.h"
// #include "runtime/mfinal.h"
// #include "runtime/mfixalloc.h"
// #include "runtime/mgc.h"
// #include "runtime/mgclimit.h"
// #include "runtime/mgcmark.h"
// #include "runtime/mgcpacer.h"
// #include "runtime/mgcscavenge.h"
// #include "runtime/mgcstack.h"
// #include "runtime/mgcsweep.h"
// #include "runtime/mgcwork.h"
// #include "runtime/mheap.h"
// #include "runtime/minmax.h"
// #include "runtime/mpagealloc.h"
// #include "runtime/mpagealloc_64bit.h"
// #include "runtime/mpagecache.h"
// #include "runtime/mpallocbits.h"
// #include "runtime/mprof.h"
// #include "runtime/mranges.h"
// #include "runtime/msan0.h"
// #include "runtime/msize_allocheaders.h"
// #include "runtime/mspanset.h"
// #include "runtime/mstats.h"
// #include "runtime/mwbbuf.h"
// #include "runtime/netpoll.h"
// #include "runtime/netpoll_windows.h"
// #include "runtime/os_nonopenbsd.h"
// #include "runtime/os_windows.h"
// #include "runtime/pagetrace_off.h"
// #include "runtime/panic.h"
// #include "runtime/pinner.h"
// #include "runtime/plugin.h"
// #include "runtime/preempt.h"
// #include "runtime/print.h"
// #include "runtime/proc.h"
// #include "runtime/profbuf.h"
// #include "runtime/proflabel.h"
// #include "runtime/race0.h"
// #include "runtime/rand.h"
// #include "runtime/rdebug.h"
// #include "runtime/runtime.h"
// #include "runtime/runtime1.h"
// #include "runtime/runtime2.h"
// #include "runtime/runtime_boring.h"
// #include "runtime/rwmutex.h"
// #include "runtime/security_nonunix.h"
// #include "runtime/select.h"
// #include "runtime/sema.h"
// #include "runtime/signal_windows.h"
// #include "runtime/sigqueue.h"
// #include "runtime/sigqueue_note.h"
// #include "runtime/sizeclasses.h"
// #include "runtime/slice.h"
// #include "runtime/softfloat64.h"
// #include "runtime/stack.h"
// #include "runtime/stkframe.h"
// #include "runtime/string.h"
// #include "runtime/stubs.h"
// #include "runtime/stubs3.h"
// #include "runtime/stubs_amd64.h"
// #include "runtime/stubs_nonlinux.h"
// #include "runtime/symtab.h"
// #include "runtime/symtabinl.h"
// #include "runtime/sys_nonppc64x.h"
// #include "runtime/sys_x86.h"
// #include "runtime/syscall_windows.h"
// #include "runtime/tagptr.h"
// #include "runtime/tagptr_64bit.h"
// #include "runtime/test_amd64.h"
// #include "runtime/time.h"
// #include "runtime/time_nofake.h"
// #include "runtime/timeasm.h"
// #include "runtime/tls_windows_amd64.h"
// #include "runtime/trace2.h"
// #include "runtime/trace2buf.h"
// #include "runtime/trace2cpu.h"
// #include "runtime/trace2event.h"
// #include "runtime/trace2map.h"
// #include "runtime/trace2region.h"
// #include "runtime/trace2runtime.h"
// #include "runtime/trace2stack.h"
// #include "runtime/trace2status.h"
// #include "runtime/trace2string.h"
// #include "runtime/trace2time.h"
// #include "runtime/traceback.h"
// #include "runtime/type.h"
// #include "runtime/typekind.h"
// #include "runtime/unsafe.h"
// #include "runtime/utf8.h"
// #include "runtime/vdso_in_none.h"
// #include "runtime/write_err.h"
// #include "runtime/zcallback_windows.h"
// #include "runtime/asm_amd64.h.h"
// #include "runtime/asm_ppc64x.h.h"
// #include "runtime/funcdata.h.h"
// #include "runtime/go_tls.h.h"
// #include "runtime/textflag.h.h"
// #include "runtime/time_windows.h.h"
// #include "runtime/asm.s.h"
// #include "runtime/asm_amd64.s.h"
// #include "runtime/duff_amd64.s.h"
// #include "runtime/memclr_amd64.s.h"
// #include "runtime/memmove_amd64.s.h"
// #include "runtime/preempt_amd64.s.h"
// #include "runtime/rt0_windows_amd64.s.h"
// #include "runtime/sys_windows_amd64.s.h"
// #include "runtime/test_amd64.s.h"
// #include "runtime/time_windows_amd64.s.h"
// #include "runtime/zcallback_windows.s.h"

namespace golang::main
{
    void main()
    {
        mocklib::Print("Go runs on ");
        //Go switch emulation
        {
            auto os = mocklib::GOOS;
            auto condition = os;
            int conditionId = -1;
            if(condition == "darwin") { conditionId = 0; }
            else if(condition == "linux") { conditionId = 1; }
            switch(conditionId)
            {
                case 0:
                    mocklib::Println("OS X.");
                    break;
                case 1:
                    mocklib::Println("Linux.");
                    break;
                default:
                    mocklib::Printf("%s.\n", os);
                    break;
            }
        }
    }

}

int main()
{
    try
    {
        std::cout << std::boolalpha << std::fixed << std::setprecision(5);
        golang::main::main();
        return 0;
    }
    catch(const gocpp::GoPanic& ex)
    {
        std::cout << "Panic: " << ex.what() << std::endl;
        return -1;
    }
}
