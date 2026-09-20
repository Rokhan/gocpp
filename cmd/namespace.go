package main

import (
	"go/ast"
	"go/token"
	"go/types"
	"path/filepath"
	"strings"
	"unicode"

	"golang.org/x/tools/go/packages"
)

// PackageInfo, resolved once per package
type PackageInfo struct {
	PkgPath  string // full import path, e.g. "internal/async", "github.com/foo/bar/v2/internal/async"
	IsStdlib bool
}

// NsNamer resolves *ast.File -> canonical, collision-free C++ namespace segments.
type NsNamer struct {
	fset      *token.FileSet // must be the SAME FileSet used to parse every file you register or query
	pathToPkg map[string]*PackageInfo
	cache     map[string][]string // PkgPath -> segments (pure function, safe to cache)
}

// NewNsNamer creates a Namer bound to fset. Every *ast.File later passed
// to Register or NamespaceFor must have been parsed with this exact FileSet.
func NewNsNamer(fset *token.FileSet) *NsNamer {
	return &NsNamer{
		fset:      fset,
		pathToPkg: make(map[string]*PackageInfo),
		cache:     make(map[string][]string),
	}
}

// Register associates every file in a loaded package with its info.
// Safe to call with *ast.File values from any parser, as long as they
// used this Namer's FileSet.
func (n *NsNamer) Register(files []*ast.File, info *PackageInfo) {
	for _, f := range files {
		n.RegisterPath(n.filePath(f), info)
	}
}

// RegisterPath is the same as Register, but for callers that already know the file path
func (n *NsNamer) RegisterPath(path string, info *PackageInfo) {
	n.pathToPkg[CleanPath(path)] = info
}

// filePath resolves f to a canonical path via this Namer's FileSet.
func (n *NsNamer) filePath(f *ast.File) string {
	tf := n.fset.File(f.Pos())
	if tf == nil {
		name := "<unknown>"
		if f.Name != nil {
			name = f.Name.Name
		}
		Panicf("namer: file for package %q not found in this Namer's FileSet - was it parsed with a different *token.FileSet?", name)
	}
	return CleanPath(tf.Name())
}

// NsSegmentsFromAstFile returns the nested namespace segments for the package
// that f belongs to. f must resolve (via this Namer's FileSet) to a
// path that was previously passed to Register/RegisterPath.
func (n *NsNamer) NsSegmentsFromAstFile(f *ast.File) []string {
	path := n.filePath(f)
	info, ok := n.pathToPkg[path]
	if !ok {
		Panicf("namer: file %q was never registered (call Register first)", path)
	}
	return n.nsSegmentsFromPath(info.PkgPath)
}

// NsSegmentsForTypePkg returns the nested namespace segments for pkg, using its import path.
func (n *NsNamer) NsSegmentsForTypePkg(pkg *types.Package) []string {
	if pkg == nil {
		Panicf("namer: NamespaceForType called with nil *types.Package (universe/builtin object?)")
	}
	return n.nsSegmentsFromPath(pkg.Path())
}

// nsSegmentsFromPath is the shared, cached implementation behind both NamespaceFor and NamespaceForType
func (n *NsNamer) nsSegmentsFromPath(pkgPath string) []string {
	if segs, ok := n.cache[pkgPath]; ok {
		return segs
	}

	var raw []string
	for _, part := range strings.Split(pkgPath, "/") {
		if part != "" {
			raw = append(raw, part)
		}
	}

	segs := make([]string, len(raw))
	for i, s := range raw {
		segs[i] = sanitizeIdent(s)
	}

	n.cache[pkgPath] = segs
	return segs
}

// NamespaceFromAstFile is the "::"-joined convenience form of NamespaceFor.
func (n *NsNamer) NamespaceFromAstFile(f *ast.File) string {
	return strings.Join(n.NsSegmentsFromAstFile(f), "::")
}

// NamespaceFromTypePkg is the "::"-joined convenience form of
// NamespaceForType.
func (n *NsNamer) NamespaceFromTypePkg(pkg *types.Package) string {
	return strings.Join(n.NsSegmentsForTypePkg(pkg), "::")
}

// sanitizeIdent turns one import-path segment into a valid C++ identifier:
//   - dots and hyphens become underscores
//   - a leading digit gets an underscore prefix.
func sanitizeIdent(s string) string {
	var b strings.Builder
	for i, r := range s {
		switch {
		case r == '_' || unicode.IsLetter(r):
			b.WriteRune(r)
		case unicode.IsDigit(r):
			if i == 0 {
				b.WriteRune('_')
			}
			b.WriteRune(r)
		default:
			b.WriteRune('_') // '.', '-', '~', etc.
		}
	}
	out := b.String()
	if out == "" {
		out = "_"
	}
	return out
}

// PkgRegister loads the packages matching patterns and registers
// every file with namer in one step
func (namer *NsNamer) PkgRegister(pkgs []*packages.Package) error {
	for _, pkg := range pkgs {

		stdlib, err := isStdlib(pkg)
		if err != nil {
			return err
		}

		info := &PackageInfo{
			PkgPath:  pkg.PkgPath,
			IsStdlib: stdlib,
		}
		for _, path := range pkg.GoFiles {
			namer.RegisterPath(path, info)
		}
	}
	return nil
}

// isStdlib reports whether pkg's files live under GOROOT.
// TODO: check if we can use  packages.Package.Module instead.
func isStdlib(pkg *packages.Package) (bool, error) {
	root, err := getGoRoot()
	if err != nil {
		return false, err
	}
	srcRoot := filepath.Join(root, "src")
	for _, f := range pkg.GoFiles {
		if strings.HasPrefix(f, srcRoot) {
			return true, nil
		}
	}
	return false, nil
}
