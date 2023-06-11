
GO_TEST_FILES=$(wildcard tests/*.go tests/*/*/*.go)
OUTDIR=generated
LOGDIR=log

CPP_TEST_FILES=$(GO_TEST_FILES:.go=.cpp)
OUT_CPP_TEST_FILES=$(addprefix $(OUTDIR)/,$(CPP_TEST_FILES))

HPP_TEST_FILES=$(GO_TEST_FILES:.go=.h)
OUT_HPP_TEST_FILES=$(addprefix $(OUTDIR)/,$(HPP_TEST_FILES))

EXE_TEST_FILES=$(GO_TEST_FILES:.go=.exe)
OUT_EXE_TEST_FILES=$(addprefix $(LOGDIR)/,$(EXE_TEST_FILES))

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

flow: $(filter $(LOGDIR)/tests/TourOfGo/flowcontrol/%,$(OUT_EXE_TEST_FILES))

basics: $(filter $(LOGDIR)/tests/TourOfGo/basics/%,$(OUT_EXE_TEST_FILES))

moretypes: $(filter $(LOGDIR)/tests/TourOfGo/moretypes/%,$(OUT_EXE_TEST_FILES))

$(OUT_CPP_TEST_FILES): $(OUTDIR)/%.cpp : %.go
	@echo "    $$$<" $<
	@echo "    $$$@" $@
	go run ./cmd/main.go -parseFmt=false -binOutDir=$(LOGDIR) -cppOutDir=$(OUTDIR) -input $< > $@".log"
	(cd $(OUTDIR) && make) 
	$(LOGDIR)/$*.go.exe

$(OUT_EXE_TEST_FILES): $(LOGDIR)/%.exe : %.go
	@echo "    $$$<"
	@echo "    $$$@"
	echo -n "| $$$< " >> results.md	
	mkdir -p $$(dirname $(LOGDIR)/$*)
	go run ./cmd/main.go -parseFmt=false -binOutDir=$(LOGDIR) -cppOutDir=$(OUTDIR) -input $< > $(LOGDIR)/$*".log" \
		&&  echo -n "| ✔️ " >> results.md \
		|| (echo    "| ❌ | ❌ | ❌ | ❌ |" >> results.md && false)

	(cd $(OUTDIR) && make) \
		&&  echo -n "| ✔️ " >> results.md \
		|| (echo    "| ❌ | ❌ | ❌ |" >> results.md && false)

	if head -1 $< | grep -q "no-run"; then \
		echo -n "| ➖ " >> results.md; \
	else \
		go run $< > $(LOGDIR)/$*.go.out.txt; \
		tput setaf 2; \
		(set -o pipefail; $(LOGDIR)/$*.exe | tee $(LOGDIR)/$*.cpp.out.txt) \
			&&  echo -n "| ✔️ " >> results.md \
			|| (echo    "| ❌ | ❌ |" >> results.md && false); \
		tput sgr0 ;\
	fi	

	if head -1 $< | grep -q -E "no-run|no-diff"; then \
		echo    "| ➖ | " >> results.md; \
	else \
		(diff -q $(LOGDIR)/$*.cpp.out.txt $(LOGDIR)/$*.go.out.txt) \
			&&  echo    "| ✔️ |" >> results.md \
			|| (echo    "| ❌ |" >> results.md && false); \
	fi

clean:
	rm -rf $(LOGDIR)
	@rm -f $(OUT_CPP_TEST_FILES) $(OUT_HPP_TEST_FILES) $(OUT_EXE_TEST_FILES)
	rm -f results.md
