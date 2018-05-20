package main

import (
	"fmt"
	"go/ast"
	"go/parser"
	"go/token"
	"log"
	"os"
	"reflect"
	"strings"
)

type type_name struct {
	name    []string
	typeStr string
}
type type_names []type_name

func (tn type_name) String() string {
	return fmt.Sprintf("%v %v", tn.typeStr, strings.Join(tn.name, "."))
}

func (tns type_names) String() string {
	var strs []string
	for _, tn := range tns {
		strs = append(strs, tn.String())
	}
	return strings.Join(strs, ", ")
}

type cpp_visitor struct {
	outFile *os.File
	indent  int
}

func (v cpp_visitor) Indent() string {
	return strings.Repeat("  ", v.indent)
}

func (v cpp_visitor) Visit(node ast.Node) ast.Visitor {
	if node == nil {
		v.indent -= 1
		return nil
	}

	fmt.Printf("//RAW_AST %s %T -> %v\n", v.Indent(), node, node)

	switch n := node.(type) {
	case *ast.File:
		fmt.Printf("// ## %s %v\n", v.Indent(), reflect.TypeOf(n))
		file, err := os.Create(n.Name.Name + ".go.cpp") // For read access.
		v.outFile = file
		if err != nil {
			log.Fatal(err)
		}
		//fmt.Printf("%s Name: %v\n", v.Indent(), n.Name)
		//fmt.Printf("%s Scope: %v\n", v.Indent(), n.Scope)
	case *ast.BadDecl:
		fmt.Printf("// ## %s %v\n", v.Indent(), reflect.TypeOf(n))
	case *ast.FuncDecl:
		fmt.Printf("// ## %s %v\n", v.Indent(), reflect.TypeOf(n))
		fmt.Printf("// ## %s  -> Name: %v\n", v.Indent(), n.Name)
		fmt.Printf("// ## %s  -> Body: %v\n", v.Indent(), n.Body)
		params := type_names{}
		for _, field := range n.Type.Params.List {
			var param type_name
			for _, name := range field.Names {
				param.name = append(param.name, name.Name)
			}
			param.typeStr = fmt.Sprintf("%v", field.Type)
			params = append(params, param)
		}

		fmt.Printf("void %s(%s)\n", n.Name.Name, params)

	case *ast.GenDecl:
		fmt.Printf("// ## %s %v\n", v.Indent(), reflect.TypeOf(n))
		fmt.Printf("// ## %s  -> Specs: %v\n", v.Indent(), n.Specs)
	default:
	}

	v.indent += 1
	return v
}

func main() {
	fset := token.NewFileSet() // positions are relative to fset

	f, err := parser.ParseFile(fset, "tests/HelloWorld.go", nil, 0)
	if err != nil {
		fmt.Println(err)
		return
	}

	ast.Print(fset, f)

	fmt.Printf("\n=====\n")
	ast.Walk(new(cpp_visitor), f)
}
