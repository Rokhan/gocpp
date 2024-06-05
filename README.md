# gocpp
Quick and dirty experimentations to parse go code and generate equivalent c++ code.

Nothing really useful practically at the moment as a lots of things are still mocked.

The compiler code is in [cmd\main.go](cmd/main.go)
The compiler is tested with go files in [tests/](./tests/) directory and the output is in [generated/](./generated/) directory.

The file [results.md](./results.md) show the status of each test and links to generated code.

Use command "make clean && make -j8 -k; make doc" to build [results.md](./results.md)
