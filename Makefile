
GO_TEST_FILES=$(wildcard tests/*.go tests/*/*/*.go)

CPP_TEST_FILES=$(GO_TEST_FILES:.go=.go.cpp)
OUT_CPP_TEST_FILES=$(addprefix out/,$(CPP_TEST_FILES))

HPP_TEST_FILES=$(GO_TEST_FILES:.go=.go.h)
OUT_HPP_TEST_FILES=$(addprefix out/,$(HPP_TEST_FILES))


all: $(OUT_CPP_TEST_FILES)
	echo $(OUT_CPP_TEST_FILES)

$(OUT_CPP_TEST_FILES): out/%.go.cpp : %.go
	@echo "    $$$<" $<
	@echo "    $$$@" $@
	go run ./cmd/main.go -parseFmt=false -input $< > $@".log"
	(cd out && make) 
	true

clean:
	rm -f $(OUT_CPP_TEST_FILES) $(OUT_HPP_TEST_FILES)
