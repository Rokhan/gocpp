//https://gist.githubusercontent.com/ks888/74f2be67e187aa15f7af2f9f24eda57a/raw/26cb0d84da718c214bf950167486bbfbcd2ca347/findimport.go

// Another logic to find the import path.
// If the package is already imported at the other Go file of the same directory,
// the import path declared at the file will be used as the import path of the target file.
//
// Install:
// cp findimport.go $GOPATH/src/golang.org/x/tools/imports
// go install golang.org/x/tools/cmd/goimports
//
// Uninstall:
// rm $GOPATH/src/golang.org/x/tools/imports/findimport.go
// go install golang.org/x/tools/cmd/goimports

package imports

/*
import (
	"go/ast"
	"go/build"
	"go/parser"
	"go/token"
	"io/ioutil"
	"log"
	"os"
	"path/filepath"
	"strings"
)

func findImportSiblings(pkgName string, symbols map[string]bool, filename string) (string, bool, error) {
	dirname := filepath.Dir(filename)
	fileInfos, err := ioutil.ReadDir(dirname)
	if err != nil {
		return "", false, err
	}

	for _, fileInfo := range fileInfos {
		fileName := fileInfo.Name()
		if fileInfo.IsDir() || fileInfo.Mode() == os.ModeSymlink || !strings.HasSuffix(fileName, ".go") {
			continue
		}
		if x.tools.goimports.Debug {
			log.Printf("check %s\n", fileInfo.Name())
		}

		// TODO: cache imported packages
		importedPkgs, err := loadImports(dirname, fileName)
		if err != nil {
			continue
		}
		importSpec, ok := importedPkgs[pkgName]
		if !ok {
			continue
		}
		importPath := strings.Trim(importSpec.Path.Value, `"`)
		if Debug {
			log.Printf("the file imports %s from %s", pkgName, importPath)
		}

		buildPkg, err := build.Import(importPath, dirname, build.FindOnly)
		if err != nil {
			continue
		}
		actualPkgName := importPathToName(importPath, buildPkg.Dir)
		exports := loadExports(actualPkgName, buildPkg.Dir)
		match := true
		for symbol := range symbols {
			if !exports[symbol] {
				match = false
				break
			}
		}
		if !match {
			continue
		}
		return importPath, actualPkgName != pkgName, nil
	}
	return "", false, nil
}

func loadImports(dirname, basename string) (map[string]*ast.ImportSpec, error) {
	path := filepath.Join(dirname, basename)
	src, err := ioutil.ReadFile(path)
	if err != nil {
		return nil, err
	}

	fset := token.NewFileSet()
	fileAST, err := parser.ParseFile(fset, path, src, parser.ImportsOnly)
	if err != nil {
		return nil, err
	}

	importedPkgs := make(map[string]*ast.ImportSpec)
	var visitor visitFn
	visitor = visitFn(func(node ast.Node) ast.Visitor {
		if node == nil {
			return visitor
		}
		switch v := node.(type) {
		case *ast.ImportSpec:
			if v.Name != nil {
				importedPkgs[v.Name.Name] = v
				break
			}
			ipath := strings.Trim(v.Path.Value, `"`)
			if ipath == "C" {
				break
			}
			local := importPathToName(ipath, dirname)
			importedPkgs[local] = v
		}
		return visitor
	})
	ast.Walk(visitor, fileAST)
	return importedPkgs, nil
}

func init() {
	findImport = func(pkgName string, symbols map[string]bool, filename string) (string, bool, error) {
		if filename != "" {
			foundPkg, rename, err := findImportSiblings(pkgName, symbols, filename)
			if err != nil {
				if Debug {
					log.Printf("error occured on finding the import path from siblings: %s", err.Error())
				}
			} else if foundPkg != "" {
				return foundPkg, rename, nil
			}
		}
		return findImportGoPath(pkgName, symbols, filename)
	}
}
*/
