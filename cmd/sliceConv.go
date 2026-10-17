package main

import (
	"go/ast"
	"go/types"
)

// sliceToArrayConversion recognises the Go conversions from a slice to an
// array or to an array pointer:
//
//	[4]byte(s)        => fn "slice_to_array",     typeExpr [4]byte
//	(*[4]byte)(s)     => fn "slice_to_array_ptr", typeExpr [4]byte
//	(*Hash)(s)        => fn "slice_to_array_ptr", typeExpr Hash  (type Hash [4]byte)
//
// typeExpr is the array type expression, taken from the source.
func sliceToArrayConversion(info *types.Info, call *ast.CallExpr) (fn string, typeExpr ast.Expr, ok bool) {
	if len(call.Args) != 1 {
		return
	}
	if tv, found := info.Types[call.Fun]; !found || !tv.IsType() {
		return // regular call, not a conversion
	}
	argType := info.TypeOf(call.Args[0])
	if argType == nil {
		return
	}
	if _, isSlice := types.Unalias(argType).Underlying().(*types.Slice); !isSlice {
		return
	}

	switch target := types.Unalias(info.Types[call.Fun].Type).Underlying().(type) {
	case *types.Array:
		return "slice_to_array", ast.Unparen(call.Fun), true

	case *types.Pointer:
		if _, isArray := types.Unalias(target.Elem()).Underlying().(*types.Array); !isArray {
			return
		}
		// Only the `(*T)(s)` spelling is handled. A named pointer type such as
		// `type P *[4]int` keeps going through the generic path.
		if star, isStar := ast.Unparen(call.Fun).(*ast.StarExpr); isStar {
			return "slice_to_array_ptr", ast.Unparen(star.X), true
		}
	}
	return
}

// convertConstArg converts a constant expression used as a C++ template
// argument. Binary expressions are parenthesized, as `>` and `>>` would
// otherwise end the argument list.
func (cv *cppConverter) convertConstArg(expr ast.Expr) cppExpr {
	converted := cv.convertExpr(expr)
	if _, isBinary := expr.(*ast.BinaryExpr); isBinary {
		return ExprPrintf("(%s)", converted)
	}
	return converted
}

// convertConversion generates specialised code for type conversions that
// need more than a C++ cast. ok is false when the default path should be used.
// Currently handled: slice -> array and slice -> array pointer, emitted as
//
//	gocpp::slice_to_array[_ptr]<N>(slice)       unnamed array type, N is the length
//	gocpp::slice_to_array[_ptr]<TArray>(slice)  named array type
//
// The length comes from the source expression, not from go/types, which only
// keeps the value: `[maxLen]byte(s)` must stay symbolic.
func (cv *cppConverter) convertConversion(call *ast.CallExpr) (expr cppExpr, ok bool) {
	fn, typeExpr, ok := sliceToArrayConversion(cv.typeInfo, call)
	if !ok {
		return cppExpr{}, false
	}
	arg := cv.convertExpr(call.Args[0])
	if arr, isArray := typeExpr.(*ast.ArrayType); isArray && arr.Len != nil {
		if _, isEllipsis := arr.Len.(*ast.Ellipsis); !isEllipsis {
			return ExprPrintf("gocpp::%s<%s>(%s)", fn, cv.convertConstArg(arr.Len), arg), true
		}
	}
	return ExprPrintf("gocpp::%s<%s>(%s)", fn, cv.convertTypeExpr(typeExpr, ctContext{}), arg), true
}
