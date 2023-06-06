
GO_TEST_FILES=$(wildcard tests/*.go tests/*/*/*.go)
OUTDIR=out

CPP_TEST_FILES=$(GO_TEST_FILES:.go=.go.cpp)
OUT_CPP_TEST_FILES=$(addprefix $(OUTDIR)/,$(CPP_TEST_FILES))

HPP_TEST_FILES=$(GO_TEST_FILES:.go=.go.h)
OUT_HPP_TEST_FILES=$(addprefix $(OUTDIR)/,$(HPP_TEST_FILES))

EXE_TEST_FILES=$(GO_TEST_FILES:.go=.go.exe)
OUT_EXE_TEST_FILES=$(addprefix $(OUTDIR)/,$(EXE_TEST_FILES))

LOG_TEST_FILES=$(GO_TEST_FILES:.go=.go.exe.log) $(GO_TEST_FILES:.go=.go.cpp.log)
OUT_LOG_TEST_FILES=$(addprefix $(OUTDIR)/,$(LOG_TEST_FILES))

all : result-header allexe
	dos2unix results.md

## ------------------------------------------------------ ##
##  Building stop at first error (as usual in Makefile)   ##
##  To generate full report just use "make -k"            ##
## ------------------------------------------------------ ##
result-header:
	echo "# Results on test directory" > results.md
	echo >> results.md
	echo "| file | cpp generate | cpp compilation | run | result diff |" >> results.md
	echo "| ---- | ------------ | --------------- | --- | ----------- |" >> results.md

allcpp: $(OUT_CPP_TEST_FILES)
	echo $(OUT_CPP_TEST_FILES)

allexe: $(OUT_EXE_TEST_FILES)
	echo $(OUT_EXE_TEST_FILES)

flow: $(filter $(OUTDIR)/tests/TourOfGo/flowcontrol/%,$(OUT_EXE_TEST_FILES))

$(OUT_CPP_TEST_FILES): out/%.go.cpp : %.go
	@echo "    $$$<" $<
	@echo "    $$$@" $@
	go run ./cmd/main.go -parseFmt=false -input $< > $@".log"
	(cd out && make) 
	out/$*.go.exe

$(OUT_EXE_TEST_FILES): out/%.go.exe : %.go
	@echo "    $$$<"
	@echo "    $$$@"
	echo -n "| $$$< " >> results.md
	go run ./cmd/main.go -parseFmt=false -input $< > $@".log" \
		&&  echo -n "| ✔️ " >> results.md \
		|| (echo    "| ❌ | ❌ | ❌ | todo |" >> results.md && false)

	(cd out && make) \
		&&  echo -n "| ✔️ " >> results.md \
		|| (echo    "| ❌ | ❌ | todo |" >> results.md && false)

	if head -1 $< | grep -q "no-run"; then \
		echo -n "| ➖ " >> results.md; \
	else \
		(out/$*.go.exe) \
			&&  echo -n "| ✔️ " >> results.md \
			|| (echo    "| ❌ | todo |" >> results.md && false) \
	fi

	echo "| todo |" >> results.md

clean:
	rm -f $(OUT_CPP_TEST_FILES) $(OUT_HPP_TEST_FILES) $(OUT_EXE_TEST_FILES) $(OUT_LOG_TEST_FILES)
	rm -f results.md
