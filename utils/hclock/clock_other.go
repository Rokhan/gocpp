//go:build !windows

package hclock

import "time"

var epoch = time.Now()

func now() int64 {
	return time.Since(epoch).Nanoseconds()
}
