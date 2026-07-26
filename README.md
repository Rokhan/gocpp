# gocpp
Experimental project to parse Go code and generate equivalent C++ code.

The goal is to try to generate code that is as simple and readable as possible while preserving the original semantics and structure.

Not much is really useful in practice at the moment, as a lot of things are still mocked and/or not implemented:
- Type casting and interfaces only work in some specific cases.
- Imported libraries are generated but not linked to examples.
- The garbage collector is not implemented at all.
- Lots of other things.

The compiler code is in [cmd/main.go](cmd/main.go).  
The compiler is tested with Go files in the [tests/](./tests/) directory, and the output is in the [generated/](./generated/) directory.

The file [results.md](./results.md) shows the status of each test and links to the generated code.

Use the command `make clean && make -j8 -k; make doc` to build [results.md](./results.md).
The generation can be quite slow the first time, or if the compiler is modified/recompiled, as all the standard library dependencies will be recompiled.
