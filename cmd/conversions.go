package main

import (
	"go/ast"
	"go/token"
	"go/types"
)

// Conversion describes one place in the file where a value is converted
// (implicitly or explicitly) to an interface type.
type Conversion struct {
	Pos   token.Pos  // location of the converted expression
	Kind  string     // "return", "assign", "vardecl", "arg", "explicit"
	Expr  ast.Expr   // the expression being converted
	Src   types.Type // static type of Expr
	Dst   types.Type // target type (often a named interface type)
	Iface *types.Interface

	// NewMethods is a best-effort list of methods Dst requires that
	// weren't already guaranteed by what was known about the value
	// before the conversion (e.g. the enclosing function's sole
	// parameter type, for the "return" case). If no useful baseline
	// exists, it's simply every method of Iface.
	NewMethods []string
}

// FindInterfaceConversions walks pi.astFile and reports every place a value
// is converted to an interface type, resolving types via pi.typeInfo.
func FindInterfaceConversions(pi *parsingInfos) []Conversion {
	var out []Conversion
	ast.Walk(&convVisitor{pi: pi, out: &out}, pi.astFile)
	return out
}

type convVisitor struct {
	pi   *parsingInfos
	sigs []*types.Signature // enclosing function signatures, innermost last
	out  *[]Conversion
}

// Visit returns a *new* visitor (with an extended, never-mutated-in-place
// sigs stack) when descending into a function body, so sibling nodes at the
// call site keep seeing the original, unextended stack. That avoids needing
// an explicit push/pop.
func (v *convVisitor) Visit(n ast.Node) ast.Visitor {
	if n == nil {
		return nil
	}
	info := v.pi.typeInfo

	switch node := n.(type) {
	case *ast.FuncDecl:
		sig, _ := info.TypeOf(node.Name).(*types.Signature)
		return &convVisitor{pi: v.pi, sigs: append(v.sigs, sig), out: v.out}

	case *ast.FuncLit:
		sig, _ := info.TypeOf(node).(*types.Signature)
		return &convVisitor{pi: v.pi, sigs: append(v.sigs, sig), out: v.out}

	case *ast.ReturnStmt:
		v.checkReturn(node)

	case *ast.AssignStmt:
		v.checkAssign(node)

	case *ast.ValueSpec:
		v.checkValueSpec(node)

	case *ast.CallExpr:
		v.checkCall(node)
	}
	return v
}

func (v *convVisitor) curSig() *types.Signature {
	if len(v.sigs) == 0 {
		return nil
	}
	return v.sigs[len(v.sigs)-1]
}

// baseline returns the enclosing function's sole parameter's interface type,
// if it has exactly one parameter and that parameter is an interface. This
// is what lets asReader(r io.Reader) reader diff down to just "Peek".
func (v *convVisitor) baseline() *types.Interface {
	sig := v.curSig()
	if sig == nil || sig.Params().Len() != 1 {
		return nil
	}
	iface, _ := sig.Params().At(0).Type().Underlying().(*types.Interface)
	return iface
}

func (v *convVisitor) record(kind string, expr ast.Expr, src, dst types.Type, have *types.Interface) {
	if src == nil || dst == nil {
		return
	}
	iface, ok := dst.Underlying().(*types.Interface)
	if !ok || types.Identical(src, dst) || !types.AssignableTo(src, dst) {
		return
	}
	if have == nil {
		have = types.NewInterfaceType(nil, nil) // empty interface -> everything counts as "new"
	}
	*v.out = append(*v.out, Conversion{
		Pos:        expr.Pos(),
		Kind:       kind,
		Expr:       expr,
		Src:        src,
		Dst:        dst,
		Iface:      iface,
		NewMethods: missingMethods(have, iface),
	})
}

func (v *convVisitor) checkReturn(ret *ast.ReturnStmt) {
	sig := v.curSig()
	if sig == nil {
		return
	}
	results := sig.Results()
	have := v.baseline()
	for i, expr := range ret.Results {
		if i >= results.Len() {
			break
		}
		v.record("return", expr, v.pi.typeInfo.TypeOf(expr), results.At(i).Type(), have)
	}
}

func (v *convVisitor) checkAssign(as *ast.AssignStmt) {
	if as.Tok != token.ASSIGN {
		return // skip `:=`, it declares a new var with an inferred type
	}
	info := v.pi.typeInfo

	if len(as.Lhs) == len(as.Rhs) {
		for i, lhs := range as.Lhs {
			v.record("assign", as.Rhs[i], info.TypeOf(as.Rhs[i]), info.TypeOf(lhs), nil)
		}
		return
	}
	// Multi-value assignment from a single call: a, b = f()
	if len(as.Rhs) == 1 {
		if tuple, ok := info.TypeOf(as.Rhs[0]).(*types.Tuple); ok {
			for i, lhs := range as.Lhs {
				if i >= tuple.Len() {
					break
				}
				v.record("assign", as.Rhs[0], tuple.At(i).Type(), info.TypeOf(lhs), nil)
			}
		}
	}
}

func (v *convVisitor) checkValueSpec(vs *ast.ValueSpec) {
	if vs.Type == nil || len(vs.Values) == 0 {
		return // no explicit type, or no initializer: nothing to check
	}
	info := v.pi.typeInfo
	dst := info.TypeOf(vs.Type)
	for i, val := range vs.Values {
		if i >= len(vs.Names) {
			break
		}
		v.record("vardecl", val, info.TypeOf(val), dst, nil)
	}
}

func (v *convVisitor) checkCall(call *ast.CallExpr) {
	info := v.pi.typeInfo

	// Explicit conversion: T(x)
	if tv, ok := info.Types[call.Fun]; ok && tv.IsType() {
		if len(call.Args) == 1 {
			v.record("explicit", call.Args[0], info.TypeOf(call.Args[0]), tv.Type, nil)
		}
		return
	}

	// Regular call: check each argument against the callee's parameters.
	sig, ok := info.TypeOf(call.Fun).(*types.Signature)
	if !ok {
		return
	}
	params := sig.Params()
	for i, arg := range call.Args {
		pidx := i
		if sig.Variadic() && pidx >= params.Len()-1 {
			pidx = params.Len() - 1
		}
		if pidx >= params.Len() {
			break
		}
		dst := params.At(pidx).Type()
		if sig.Variadic() && pidx == params.Len()-1 && !call.Ellipsis.IsValid() {
			if s, ok := dst.(*types.Slice); ok {
				dst = s.Elem()
			}
		}
		v.record("arg", arg, info.TypeOf(arg), dst, nil)
	}
}

// missingMethods returns methods `want` requires that `have` doesn't
// already provide (matched by name + identical signature).
func missingMethods(have, want *types.Interface) []string {
	var missing []string
	for i := 0; i < want.NumMethods(); i++ {
		m := want.Method(i)
		found := false
		for j := 0; j < have.NumMethods(); j++ {
			hm := have.Method(j)
			if hm.Name() == m.Name() && types.Identical(hm.Type(), m.Type()) {
				found = true
				break
			}
		}
		if !found {
			missing = append(missing, m.Name())
		}
	}
	return missing
}

// ReceiverFullNames returns the set of "<pkgName>::rec::<MethodName>" full
// names referenced by convs, one per (source package, method) pair found
// in each Conversion's NewMethods. Uses the project's existing set[T].
func ReceiverFullNames(convs []Conversion, currentPkg string) set[string] {
	names := make(set[string])
	for _, c := range convs {
		pkg := srcPackageName(c.Src)
		if pkg == "" || pkg == currentPkg {
			continue
		}
		for _, m := range c.NewMethods {
			names[pkg+"::"+recNs+"::"+m] = true
		}
	}
	return names
}

// srcPackageName returns the package name of t's underlying named type,
// unwrapping a single pointer indirection if present. Returns "" for
// unnamed types (basic types, unnamed struct/interface literals, etc.).
func srcPackageName(t types.Type) string {
	if p, ok := t.(*types.Pointer); ok {
		t = p.Elem()
	}
	named, ok := t.(*types.Named)
	if !ok || named.Obj().Pkg() == nil {
		return ""
	}
	return named.Obj().Pkg().Name()
}
