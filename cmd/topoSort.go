package main

import (
	"slices"
	"strings"
)

func ComparePlace(cv Logger, x *place, y *place, getter func(place) []string, logPrefix string) int {
	xstr := strings.TrimSpace(getter(*x)[0])
	ystr := strings.TrimSpace(getter(*y)[0])

	xstr = strings.SplitN(xstr, "\n", 2)[0]
	ystr = strings.SplitN(ystr, "\n", 2)[0]

	_, ok := x.depInfo.dependencies[y.DepInfoTypeStr()]
	if ok {
		cv.Logf("'%s' sort type: '%v' use type '%v', rank: %v\n", logPrefix, xstr, y.depInfo.decType, y.depInfo.rank)
		return 1
	}
	_, ok = y.depInfo.dependencies[x.DepInfoTypeStr()]
	if ok {
		cv.Logf("'%s' sort type: '%v' use type '%v', rank: %v\n", logPrefix, ystr, x.depInfo.decType, x.depInfo.rank)
		return -1
	}

	_, ok = x.depInfo.depIdents[y.depInfo.decIdent]
	if ok {
		cv.Logf("'%s' sort ident: '%v' use ident '%v', rank: %v\n", logPrefix, xstr, y.depInfo.decIdent, y.depInfo.rank)
		return 1
	}
	_, ok = y.depInfo.depIdents[x.depInfo.decIdent]
	if ok {
		cv.Logf("'%s' sort ident: '%v' use ident '%v', rank: %v\n", logPrefix, ystr, x.depInfo.decIdent, x.depInfo.rank)
		return -1
	}

	var incType includeType
	incType, ok = x.depInfo.depPkgs[y.depInfo.decPkg]
	if ok && incType == y.includeType {
		cv.Logf("'%s' sort pkg: '%v' use pkg '%v', rank: %v\n", logPrefix, xstr, y.depInfo.decPkg, y.depInfo.rank)
		return 1
	}
	incType, ok = y.depInfo.depPkgs[x.depInfo.decPkg]
	if ok && incType == x.includeType {
		cv.Logf("'%s' sort pkg: '%v' use pkg '%v', rank: %v\n", logPrefix, ystr, x.depInfo.decPkg, x.depInfo.rank)
		return -1
	}

	// TODO: find a way to do include/imports as late as possible

	if cv.VerboseLog() {
		cv.Logf("'%s' sort: '%v' and '%v' are independant, ranks: %v, %v\n", logPrefix, xstr, ystr, x.depInfo.rank, y.depInfo.rank)
	}

	return 0
	//return cmp.Compare(x.depInfo.initialOrder, y.depInfo.initialOrder)
}

// Custom toposort with additional constraints
//
//	-> that preserve initial order if possible
//	-> push import as late as possible
//	-> push declaration as soon as possible
//
// nb: - probably not an efficient toposort algorithm
//   - getter is used only for logs
func topoSort(cv Logger, headerElts []*place, getter func(place) []string, logPrfix string) {
	var maxIndex int = 0
	elts := map[int]map[*place]bool{}
	elts[maxIndex] = map[*place]bool{}
	for _, elt := range headerElts {
		elts[0][elt] = true
	}

	for len(elts[maxIndex]) > 0 {
		curentIndex := maxIndex
		maxIndex++
		elts[maxIndex] = map[*place]bool{}

		for elt1 := range elts[curentIndex] {

			for elt2 := range elts[maxIndex] {
				if elt1 == elt2 {
					continue
				}

				switch ComparePlace(cv, elt1, elt2, getter, logPrfix) {
				case 1:
					delete(elts[curentIndex], elt1)
					elts[maxIndex][elt1] = true
					elt1.depInfo.rank = maxIndex
				}
			}

			for elt2 := range elts[curentIndex] {
				if elt1 == elt2 {
					continue
				}

				switch ComparePlace(cv, elt1, elt2, getter, logPrfix) {
				case -1:
					delete(elts[curentIndex], elt2)
					elts[maxIndex][elt2] = true
					elt2.depInfo.rank = maxIndex
				case 1:
					delete(elts[curentIndex], elt1)
					elts[maxIndex][elt1] = true
					elt1.depInfo.rank = maxIndex
				}
			}
		}

		// TODO, find a better way to detect cycles
		if maxIndex > 10000 {
			cv.Panicf("BUG: max index reached in topoSort, maxIndex: %d\n", maxIndex)
		}
	}

	// Add intermedite space netween existing ranks
	splitElts := map[int]map[*place]bool{}
	for i, rankElts := range elts {
		for elt := range rankElts {
			elt.depInfo.rank = 2*i + 0
		}
		splitElts[2*i+0] = rankElts
		splitElts[2*i+1] = map[*place]bool{}
	}
	elts = splitElts
	maxIndex = 2 * maxIndex

	// Push imports as late as possible
	for i := 0; i < maxIndex-1; i++ {
		for elt1 := range elts[i] {
			if elt1.depInfo.decPkg == "" {
				continue
			}
			pushLater := true
			for elt2 := range elts[i+1] {
				if ComparePlace(cv, elt1, elt2, getter, logPrfix) != 0 {
					pushLater = false
					break
				}
			}

			if pushLater {
				delete(elts[i], elt1)
				elts[i+1][elt1] = true
				elt1.depInfo.rank = i + 1
			}
		}
	}

	// Push defintion as soon as possible
	for i := maxIndex; i > 0; i-- {
		for elt1 := range elts[i] {
			if elt1.depInfo.decPkg != "" {
				continue
			}
			pushSooner := true
			for elt2 := range elts[i-1] {
				if ComparePlace(cv, elt1, elt2, getter, logPrfix) != 0 {
					pushSooner = false
					break
				}
			}

			if pushSooner {
				delete(elts[i], elt1)
				elts[i-1][elt1] = true
				elt1.depInfo.rank = i - 1
			}
		}
	}

	slices.SortFunc(headerElts, func(x *place, y *place) int {
		if x.depInfo.rank < y.depInfo.rank {
			return -1
		} else if x.depInfo.rank > y.depInfo.rank {
			return +1
		}

		if x.depInfo.initialOrder < y.depInfo.initialOrder {
			return -1
		} else if x.depInfo.initialOrder > y.depInfo.initialOrder {
			return +1
		}
		return 0
	})
}
