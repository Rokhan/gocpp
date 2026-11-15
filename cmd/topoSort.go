package main

import (
	"fmt"
	"slices"
	"strings"
)

var maxPlaceId = 1
var placeLogIds = map[*place]int{}

func getPlaceLogId(pp *place) int {
	if pp == nil {
		return -1
	}
	if id, ok := placeLogIds[pp]; ok {
		return id
	}
	maxPlaceId++
	placeLogIds[pp] = maxPlaceId
	return maxPlaceId
}

func ComparePlace(cv Logger, x *place, y *place, getter func(place) []string, logPrefix string) int {
	xstr := strings.TrimSpace(getter(*x)[0])
	ystr := strings.TrimSpace(getter(*y)[0])

	xstr = strings.SplitN(xstr, "\n", 2)[0]
	ystr = strings.SplitN(ystr, "\n", 2)[0]

	logPrefix = fmt.Sprintf("%q, (%3d vs %3d)", logPrefix, getPlaceLogId(x), getPlaceLogId(y))

	_, ok := x.depInfo.dependencies[y.DepInfoTypeStr()]
	if ok {
		cv.Logf("%s sort type: '%v' use type '%v', rank: %v\n", logPrefix, xstr, y.depInfo.decType, y.depInfo.rank)
		return 1
	}
	_, ok = y.depInfo.dependencies[x.DepInfoTypeStr()]
	if ok {
		cv.Logf("%s sort type: '%v' use type '%v', rank: %v\n", logPrefix, ystr, x.depInfo.decType, x.depInfo.rank)
		return -1
	}

	_, ok = x.depInfo.depIdents[y.depInfo.decIdent]
	if ok {
		cv.Logf("%s sort ident:'%v' use ident '%v', rank: %v\n", logPrefix, xstr, y.depInfo.decIdent, y.depInfo.rank)
		return 1
	}
	_, ok = y.depInfo.depIdents[x.depInfo.decIdent]
	if ok {
		cv.Logf("%s sort ident:'%v' use ident '%v', rank: %v\n", logPrefix, ystr, x.depInfo.decIdent, x.depInfo.rank)
		return -1
	}

	var incType includeType
	incType, ok = x.depInfo.depPkgs[y.depInfo.decPkg]
	if ok && incType == y.includeType {
		cv.Logf("%s sort pkg:  '%v[%v]' use pkg '%v[%v]', rank: %v\n", logPrefix, xstr, incType, y.depInfo.decPkg, y.includeType, y.depInfo.rank)
		return 1
	}
	incType, ok = y.depInfo.depPkgs[x.depInfo.decPkg]
	if ok && incType == x.includeType {
		cv.Logf("%s sort pkg:  '%v[%v]' use pkg '%v[%v]', rank: %v\n", logPrefix, ystr, incType, x.depInfo.decPkg, x.includeType, x.depInfo.rank)
		return -1
	}

	if y.namespace != nil {
		_, ok = x.depInfo.depNss[y.namespace.ns]
		if ok {
			cv.Logf("%s sort ns:   '%v' use ns '%v', rank: %v\n", logPrefix, xstr, y.namespace, y.depInfo.rank)
			return 1
		}
	}

	if x.namespace != nil {
		_, ok = y.depInfo.depNss[x.namespace.ns]
		if ok {
			cv.Logf("%s sort ns:   '%v' use ns '%v', rank: %v\n", logPrefix, ystr, x.namespace, x.depInfo.rank)
			return -1
		}
	}

	// TODO: find a way to do include/imports as late as possible

	if cv.VerboseLog() {
		cv.Logf("%s sort: '%v' and '%v' are independant, ranks: %v, %v\n", logPrefix, xstr, ystr, x.depInfo.rank, y.depInfo.rank)
	}

	return 0
	//return cmp.Compare(x.depInfo.initialOrder, y.depInfo.initialOrder)
}

// Imports, includes and `using` namespaces: emitted lazily, just before their first consumer.
func isImportLike(p *place) bool {
	return p.depInfo.decPkg != "" || p.namespace != nil
}

// Min-heap of node indices, keyed by the secondary order (index breaks ties => deterministic).
type placeHeap struct {
	elts  []int
	order []int
}

func (h placeHeap) Len() int { return len(h.elts) }
func (h placeHeap) Less(a, b int) bool {
	ia, ib := h.elts[a], h.elts[b]
	if h.order[ia] != h.order[ib] {
		return h.order[ia] < h.order[ib]
	}
	return ia < ib
}
func (h placeHeap) Swap(a, b int) { h.elts[a], h.elts[b] = h.elts[b], h.elts[a] }
func (h *placeHeap) Push(x any)   { h.elts = append(h.elts, x.(int)) }
func (h *placeHeap) Pop() any {
	old := h.elts
	x := old[len(old)-1]
	h.elts = old[:len(old)-1]
	return x
}

// Topological sort with a secondary criterion (initialOrder):
//   - definitions: Kahn's algorithm, ready nodes picked by smallest initialOrder
//     (=> declarations as soon as possible, original order kept whenever allowed)
//   - imports: never queued; emitted (with their import ancestors) right before
//     the first definition that needs them (=> imports as late as possible)
//
// O(n^2) ComparePlace calls to build edges, then O((V+E) log V).
// nb: getter is used only for logs
func topoSort(cv Logger, headerElts []*place, getter func(place) []string, logPrefix string) {
	n := len(headerElts)
	if n == 0 {
		return
	}

	// 1. Edges: deps[i] = nodes that i must come after.
	deps := make([][]int, n)
	for i := 0; i < n; i++ {
		for j := i + 1; j < n; j++ {
			switch ComparePlace(cv, headerElts[i], headerElts[j], getter, logPrefix) {
			case 1:
				deps[i] = append(deps[i], j)
			case -1:
				deps[j] = append(deps[j], i)
			}
		}
	}

	isImp := make([]bool, n)
	order := make([]int, n)
	for i, p := range headerElts {
		isImp[i] = isImportLike(p)
		order[i] = p.depInfo.initialOrder
	}
	byOrder := func(a, b int) int {
		if order[a] != order[b] {
			return order[a] - order[b]
		}
		return a - b
	}

	// 2. For each definition, look through import nodes:
	//    defDeps = definitions it really waits for, imps = imports to emit before it.
	type closure struct{ defDeps, imps []int }
	closures := make([]closure, n)
	for d := 0; d < n; d++ {
		if isImp[d] {
			continue
		}
		seen := map[int]bool{}
		var c closure
		var walk func(i int)
		walk = func(i int) {
			for _, j := range deps[i] {
				if seen[j] {
					continue
				}
				seen[j] = true
				if isImp[j] {
					c.imps = append(c.imps, j)
					walk(j) // an import may itself need imports/definitions
				} else {
					c.defDeps = append(c.defDeps, j)
				}
			}
		}
		walk(d)
		slices.SortFunc(c.imps, byOrder)
		closures[d] = c
	}

	// 3. Emission.
	result := make([]int, 0, n)
	state := make([]int8, n) // 0 = new, 1 = visiting, 2 = emitted

	var emitImport func(i int)
	emitImport = func(i int) {
		switch state[i] {
		case 2:
			return
		case 1:
			cv.Panicf("BUG: dependency cycle between imports in topoSort, pid: %d\n", getPlaceLogId(headerElts[i]))
		}
		state[i] = 1
		var impDeps []int
		for _, j := range deps[i] {
			if isImp[j] {
				impDeps = append(impDeps, j)
			}
		}
		slices.SortFunc(impDeps, byOrder)
		for _, j := range impDeps {
			emitImport(j)
		}
		state[i] = 2
		result = append(result, i)
	}

	pending := make([]int, n)
	users := make([][]int, n)
	var ready []int
	nbDefs := 0
	for d := 0; d < n; d++ {
		if isImp[d] {
			continue
		}
		nbDefs++
		pending[d] = len(closures[d].defDeps)
		for _, e := range closures[d].defDeps {
			users[e] = append(users[e], d)
		}
		if pending[d] == 0 {
			ready = append(ready, d)
		}
	}

	// Full-include nodes grouped by package, to know when a forward include is already covered.
	hdrByPkg := map[string][]int{}
	for i := 0; i < n; i++ {
		if isImp[i] && headerElts[i].includeType == HdrInclude {
			pkg := headerElts[i].depInfo.decPkg
			hdrByPkg[pkg] = append(hdrByPkg[pkg], i)
		}
	}

	// An import is "done" if emitted, or if it is a forward include
	// whose package full header is already emitted (generateSortedHeader skips it then).
	importDone := func(i int) bool {
		if state[i] == 2 {
			return true
		}
		if headerElts[i].includeType == FwdInclude {
			for _, h := range hdrByPkg[headerElts[i].depInfo.decPkg] {
				if state[h] == 2 {
					return true
				}
			}
		}
		return false
	}

	type importCost struct{ full, fwd int }

	// Imports that would have to be emitted before d.
	// Full includes are counted apart; forward includes and `using` namespaces count as "fwd".
	newImportCost := func(d int) importCost {
		var c importCost
		for _, imp := range closures[d].imps {
			if importDone(imp) {
				continue
			}
			if headerElts[imp].includeType == HdrInclude {
				c.full++
			} else {
				c.fwd++
			}
		}
		return c
	}

	// Order: fewest full includes, then fewest forward includes, then initialOrder.
	lessCost := func(a, b importCost) int {
		if a.full != b.full {
			return a.full - b.full
		}
		return a.fwd - b.fwd
	}

	pickReady := func() int {
		best := -1
		var bestCost importCost
		for k, d := range ready {
			c := newImportCost(d)
			if best == -1 {
				best, bestCost = k, c
				continue
			}
			cmp := lessCost(c, bestCost)
			if cmp < 0 || (cmp == 0 && byOrder(d, ready[best]) < 0) {
				best, bestCost = k, c
			}
		}
		d := ready[best]
		ready = slices.Delete(ready, best, best+1)
		return d
	}

	emittedDefs := 0
	for len(ready) > 0 {
		d := pickReady()
		for _, imp := range closures[d].imps {
			emitImport(imp)
		}
		state[d] = 2
		result = append(result, d)
		emittedDefs++
		for _, u := range users[d] {
			if pending[u]--; pending[u] == 0 {
				ready = append(ready, u)
			}
		}
	}

	if emittedDefs != nbDefs {
		var stuck []int
		for d := 0; d < n; d++ {
			if !isImp[d] && state[d] != 2 {
				stuck = append(stuck, getPlaceLogId(headerElts[d]))
			}
		}
		cv.Panicf("BUG: dependency cycle in topoSort, %d definitions stuck, pids: %v\n", nbDefs-emittedDefs, stuck)
	}

	// Imports nobody needs go last (generateSortedHeader skips them after maxDecIndex).
	var rest []int
	for i := 0; i < n; i++ {
		if isImp[i] && state[i] == 0 {
			rest = append(rest, i)
		}
	}
	slices.SortFunc(rest, byOrder)
	for _, i := range rest {
		emitImport(i)
	}

	// 4. Write back (rank is kept for logPlace).
	sorted := make([]*place, n)
	for idx, i := range result {
		headerElts[i].depInfo.rank = idx
		sorted[idx] = headerElts[i]
	}
	copy(headerElts, sorted)
}
