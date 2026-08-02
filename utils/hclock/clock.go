package hclock

import "time"

// Time is an opaque monotonic timestamp.
// Implement 'Since' and 'Sub' to match time.Time api.
type Time int64

func Now() Time {
	return Time(now())
}

func Since(t Time) time.Duration {
	return time.Duration(now() - int64(t))
}

func (t Time) Sub(other Time) time.Duration {
	return time.Duration(int64(t) - int64(other))
}
