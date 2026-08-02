package main

import (
	"fmt"
	"io"
	"slices"
	"strings"
	"time"
)

type perfScope struct {
	file  io.Writer
	tag   string
	start time.Time
	depth int
}

var aggregatedByTag = map[string]time.Duration{}
var countByTag = map[string]int{}

func (cv *perfScope) Logf(msgFormat string, a ...any) {
	formatedMessage := fmt.Sprintf(msgFormat, a...)
	shiftStr := strings.Repeat("=", cv.depth)
	elapsed := time.Since(cv.start)

	countByTag[cv.tag]++
	aggregatedByTag[cv.tag] = aggregatedByTag[cv.tag] + elapsed
	fmt.Fprintf(cv.file, "%s, elapsed: %8.3f ms, %s=> %s, %s\n", perfLogPrefix(), milliSecs(elapsed), shiftStr, cv.tag, formatedMessage)
}

func LogAggregatedPerfs(perfFile io.Writer) {
	fmt.Fprintf(perfFile, "Aggregated elapsed time by tag:\n")
	sortedTags := make([]string, 0, len(aggregatedByTag))
	for tag := range aggregatedByTag {
		sortedTags = append(sortedTags, tag)
	}
	slices.Sort(sortedTags)

	maxLen := MaxLen(sortedTags)
	for _, tag := range sortedTags {
		if tag == "(none)" {
			continue
		}
		fmt.Fprintf(perfFile, "%-*s [x%4d]=> %v\n", maxLen, tag, countByTag[tag], aggregatedByTag[tag])
	}
}
