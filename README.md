# gocpp
Quick and dirty experimentations to parse Go code and generate equivalent C++ code.

Nothing really useful practically at the moment as a lot of things are still mocked and/or not implemented:
- Type casting and interfaces only work in some specific cases.
- Imported libraries are generated but not linked to examples.
- The garbage collector is not implemented at all.
- Lots of other things.

The compiler code is in [cmd\main.go](cmd/main.go).  
The compiler is tested with Go files in the [tests/](./tests/) directory, and the output is in the [generated/](./generated/) directory.

The file [results.md](./results.md) shows the status of each test and links to the generated code.

Use the command `make clean && make -j8 -k; make doc` to build [results.md](./results.md).
