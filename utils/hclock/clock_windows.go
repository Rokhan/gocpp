//go:build windows

package hclock

import (
	"syscall"
	"unsafe"
)

var (
	kernel32 = syscall.NewLazyDLL("kernel32.dll")

	queryPerformanceCounter   = kernel32.NewProc("QueryPerformanceCounter")
	queryPerformanceFrequency = kernel32.NewProc("QueryPerformanceFrequency")

	frequency int64
)

func init() {
	var freq int64

	r, _, err := queryPerformanceFrequency.Call(
		uintptr(unsafe.Pointer(&freq)),
	)

	if r == 0 {
		panic(err)
	}

	frequency = freq
}

func now() int64 {
	var counter int64

	r, _, err := queryPerformanceCounter.Call(
		uintptr(unsafe.Pointer(&counter)),
	)

	if r == 0 {
		panic(err)
	}

	seconds := counter / frequency
	remainder := counter % frequency

	// Avoid overflow: counter is usually ~10^16, multiplying by
	// 1e9 is ~10^25, beyond int64.
	//
	// Split the conversion.
	return seconds*1_000_000_000 +
		remainder*1_000_000_000/frequency
}
