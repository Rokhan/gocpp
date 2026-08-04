package main

import (
	"fmt"
	"io"
	"slices"
	"strings"
	"time"

	"github.com/Rokhan/gocpp/utils/hclock"
)

type overlaps struct{ in, out int }

type perfScope struct {
	file     io.Writer
	tag      string
	start    hclock.Time
	adjust   time.Duration
	depth    int
	overlaps overlaps
}

var activePerfScopes = map[*perfScope]bool{}
var aggregatedByTag = map[string]time.Duration{}
var adjustedByTag = map[string]time.Duration{}
var countByTag = map[string]int{}
var overlapsByTag = map[string]map[string]int{}

func createPerfScope(file io.Writer, tag string, depth int) *perfScope {
	newScope := perfScope{file: file, tag: tag, start: hclock.Now(), depth: depth}
	activePerfScopes[&newScope] = true
	return &newScope
}

func (scope *perfScope) Logf(msgFormat string, a ...any) {
	formatedMessage := fmt.Sprintf(msgFormat, a...)
	shiftStr := strings.Repeat("=", scope.depth)
	elapsed := hclock.Since(scope.start)
	delete(activePerfScopes, scope)

	adjusted := elapsed + scope.adjust
	for activeScope := range activePerfScopes {
		activeScope.adjust -= adjusted
		scope.overlaps.out++
		activeScope.overlaps.in++
		if overlapsByTag[activeScope.tag] == nil {
			overlapsByTag[activeScope.tag] = map[string]int{}
		}
		overlapsByTag[activeScope.tag][scope.tag]++
	}

	countByTag[scope.tag]++
	aggregatedByTag[scope.tag] = aggregatedByTag[scope.tag] + elapsed
	adjustedByTag[scope.tag] = adjustedByTag[scope.tag] + adjusted
	fmt.Fprintf(scope.file, "%s, elapsed: %8.3f ms, adjusted: %8.3f, overlaps: %2v, %s=> %s, %s\n", perfLogPrefix(), milliSecs(elapsed), milliSecs(adjusted), scope.overlaps, shiftStr, scope.tag, formatedMessage)
}

func LogAggregatedPerfs(perfFile io.Writer) {
	sortedTags := make([]string, 0, len(aggregatedByTag))
	for tag := range aggregatedByTag {
		sortedTags = append(sortedTags, tag)
	}
	slices.Sort(sortedTags)

	maxTagLen := MaxLen(sortedTags)
	maxCountLen := 0
	for _, count := range countByTag {
		countLen := len(fmt.Sprintf("%d", count))
		if countLen > maxCountLen {
			maxCountLen = countLen
		}
	}
	fmt.Fprintf(perfFile, "### Scope overlaps ###\n")
	for tag, overlaps := range overlapsByTag {
		for otherTag, count := range overlaps {
			fmt.Fprintf(perfFile, "%-*s => %-*s %*d\n", maxTagLen, tag, maxTagLen, otherTag, maxCountLen, count)
		}
	}
	fmt.Fprintf(perfFile, "### Total elapsed time by tag (adjusted and total): ###\n")
	fmt.Fprintf(perfFile, "%-*s %*s  =>  Adjusted //  Total\n", maxTagLen, "Tag", maxCountLen+2, "Count")
	for _, tag := range sortedTags {
		fmt.Fprintf(perfFile, "%-*s [x%*d] => %8.3fs // %8.3fs \n", maxTagLen, tag, maxCountLen, countByTag[tag], adjustedByTag[tag].Seconds(), aggregatedByTag[tag].Seconds())
	}
}
