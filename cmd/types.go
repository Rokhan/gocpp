package main

import (
	"fmt"
	"go/ast"
	"go/constant"
	"go/token"
	"go/types"
	"reflect"
	"strings"
)

func convertGoToCppTypes(goType []types.Type, namespace string, position token.Position) []string {
	results := []string{}
	for _, subType := range goType {
		result, _ := convertGoToCppType(subType, typeConvCtx{namespace: namespace, position: position})
		results = append(results, result)
	}
	return results
}

// constFitsOnlyUint64 reports whether obj is an untyped integer constant whose value
// is above int64 but still fits uint64, so uint64_t can hold it and bigint is not needed
func constFitsOnlyUint64(obj types.Object) bool {
	c, ok := obj.(*types.Const)
	if !ok {
		return false
	}
	b, ok := c.Type().(*types.Basic)
	if !ok || b.Kind() != types.UntypedInt {
		return false
	}
	v := c.Val()
	return v.Kind() == constant.Int &&
		constant.Compare(v, token.GTR, int64Max) &&
		constant.Compare(v, token.LEQ, uint64Max)
}

type constWidth int

const (
	fitsInt32 constWidth = iota // plain C++ int is enough: emit as today
	fitsInt64                   // widen the leaves
	needsBig                    // use the big integer type
)

// Reports whether integer constant v is representable in basic type b (64-bit platform).
func fitsOwnType(v constant.Value, b *types.Basic) bool {
	bits := uint(types.SizesFor("gc", "amd64").Sizeof(b) * 8)
	if b.Info()&types.IsUnsigned != 0 {
		return constant.Sign(v) >= 0 && constant.BitLen(v) <= int(bits)
	}
	min := constant.Shift(constant.MakeInt64(-1), token.SHL, bits-1)
	max := constant.BinaryOp(constant.Shift(constant.MakeInt64(1), token.SHL, bits-1), token.SUB, constant.MakeInt64(1))
	return constant.Compare(v, token.GEQ, min) && constant.Compare(v, token.LEQ, max)
}

func convertCommentLines(comment *ast.CommentGroup) []string {
	if comment == nil {
		return nil
	}
	lines := []string{}
	for _, c := range strings.Split(comment.Text(), "\n") {
		line := strings.TrimSpace(c)
		if line != "" {
			lines = append(lines, line)
		}
	}
	return lines
}

func convertComment(comment *ast.CommentGroup, indent string) string {
	lines := convertCommentLines(comment)
	sep := "\n" + indent + "// "
	return fmt.Sprintf("// %s", strings.Join(lines, sep))
}

func convertInlinedComment(comment *ast.CommentGroup, indent string) string {
	lines := convertCommentLines(comment)
	sep := "\n" + indent
	return fmt.Sprintf("/* %s */", strings.Join(lines, sep))
}

func getArrayLen(goType types.Type, position token.Position) int64 {
	if goType == nil {
		panic("getArrayLen. Cannot convert nil type.")
	}

	switch subType := goType.(type) {
	case *types.Array:
		return subType.Len()
	}

	Panicf("getArrayLen. Unmanaged type, type [%v], position[%v]", reflect.TypeOf(goType), position)
	return 0
}

func underlying(tv types.Type) types.Type {
	var underlying types.Type
	if tv != nil {
		underlying = tv.Underlying()
	}
	return underlying
}

// Get the return type of a function node
func getFunctionSignature(typeInfo *types.Info, funcNode ast.Node) (sig *types.Signature) {

	switch n := funcNode.(type) {
	case *ast.FuncDecl:
		// Try the ast.FuncType entry first
		if n.Type != nil {
			if tv, ok := typeInfo.Types[n.Type]; ok {
				if sig, ok = tv.Type.(*types.Signature); ok {
					break
				}
			}
		}
		// Fall back to function object (named func)
		if n.Name != nil {
			if def := typeInfo.Defs[n.Name]; def != nil {
				var ok bool
				if sig, ok = def.Type().(*types.Signature); ok {
					break
				}
			}
		}

	case *ast.FuncLit:
		if n.Type != nil {
			if tv, ok := typeInfo.Types[n.Type]; ok {
				if sig, ok = tv.Type.(*types.Signature); ok {
					break
				}
			}
		}

	case *ast.FuncType:
		if tv, ok := typeInfo.Types[n]; ok {
			if sig, ok = tv.Type.(*types.Signature); ok {
				break
			}
		}
	}
	return sig
}

func getFunctionReturnType(typeInfo *types.Info, funcNode ast.Node) *types.Tuple {
	sig := getFunctionSignature(typeInfo, funcNode)
	return sig.Results()
}

type FuncKind int

const (
	FuncKindAny    FuncKind = 0
	FuncKindPlain  FuncKind = 1
	FuncKindMethod FuncKind = 2
)

func (kind FuncKind) AppliesTo(sig *types.Signature) bool {
	switch kind {
	case FuncKindAny:
		return true
	case FuncKindPlain:
		return sig.Recv() == nil
	case FuncKindMethod:
		return sig.Recv() != nil
	default:
		Panicf("Unexpected FuncKind value: %v", kind)
		return false // unreachable
	}
}

func isTopLevel(obj types.Object) bool {
	return obj != nil && obj.Parent() == obj.Pkg().Scope()
}

func getFuncNames(methods []*types.Func) []string {
	var result []string
	for _, m := range methods {
		result = append(result, m.Name())
	}
	return result
}
