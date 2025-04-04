
GO_TEST_DIRS:=$(wildcard ./tests ./tests/*/*/)
GO_TEST_DIRS:=$(filter-out ./tests/TourOfGo/img/, $(GO_TEST_DIRS))

GO_TEST_FILES=$(wildcard tests/*.go tests/*/*/*.go)
OUTDIR=generated
LOGDIR=log
SUPPORT_FILES=includes/gocpp/support.h includes/gocpp/support.fwd.h

CPP_TEST_FILES=$(GO_TEST_FILES:.go=.cpp)
OUT_CPP_TEST_FILES=$(addprefix $(OUTDIR)/,$(CPP_TEST_FILES))

HPP_TEST_FILES=$(GO_TEST_FILES:.go=.h)
OUT_HPP_TEST_FILES=$(addprefix $(OUTDIR)/,$(HPP_TEST_FILES))

EXE_TEST_FILES=$(GO_TEST_FILES:.go=.exe)
OUT_EXE_TEST_FILES=$(addprefix $(LOGDIR)/,$(EXE_TEST_FILES))

MD_TEST_FILES=$(GO_TEST_FILES:.go=.md)
OUT_MD_TEST_FILES=$(addprefix $(LOGDIR)/,$(MD_TEST_FILES))

CCACHE := $(shell which ccache 2> /dev/null)

GOCPP_ALWAYS_REGENERATE = false
GOCPP_STRICT_MODE = false
GOCPP_VERBOSE = false

GOCPP_PARAMETERS = -parseFmt=false -strictMode=$(GOCPP_STRICT_MODE) -alwaysRegenerate=$(GOCPP_ALWAYS_REGENERATE) -verbose=$(GOCPP_VERBOSE) -binOutDir=$(LOGDIR) -cppOutDir=$(OUTDIR)

## ------------------------------------------------------ ##
##  Building stop at first error (as usual in Makefile)   ##
##  To generate full report just use "make -k"            ##
## ------------------------------------------------------ ##

all: allexe

doc:
	echo "# Results on test directory" > results.md
	echo >> results.md
	echo "| file | cpp generate | cpp compilation | run | result diff |" >> results.md
	echo "| ---- | ------------ | --------------- | --- | ----------- |" >> results.md
	cat $(OUT_MD_TEST_FILES) | sort -t. -k 1d,1 >> results.md
	echo "" >> results.md
	echo "" >> results.md
	echo "# Conversion of imported packages" >> results.md
	echo "| file | cpp generate |" >> results.md
	echo "| ---- | -------------| " >> results.md
	cat $$(find log/golang -type f -name "*.status.md" | sort) >> results.md
	dos2unix results.md

format-tests:
	go fmt $(GO_TEST_DIRS)

allcpp: $(OUT_CPP_TEST_FILES)
	echo $(OUT_CPP_TEST_FILES)

allexe: $(OUT_EXE_TEST_FILES)
	echo $(OUT_EXE_TEST_FILES)

flow: $(filter $(LOGDIR)/tests/TourOfGo/flowcontrol/%, $(OUT_EXE_TEST_FILES))
switch: $(filter $(LOGDIR)/tests/TourOfGo/flowcontrol/switch%, $(OUT_EXE_TEST_FILES))
basics: $(filter $(LOGDIR)/tests/TourOfGo/basics/%, $(OUT_EXE_TEST_FILES))
concurrency: $(filter $(LOGDIR)/tests/TourOfGo/concurrency/%, $(OUT_EXE_TEST_FILES))
generics: $(filter $(LOGDIR)/tests/TourOfGo/generics/%, $(OUT_EXE_TEST_FILES))
moretypes: $(filter $(LOGDIR)/tests/TourOfGo/moretypes/%, $(OUT_EXE_TEST_FILES))
methods-all: $(filter $(LOGDIR)/tests/TourOfGo/methods/%, $(OUT_EXE_TEST_FILES))
methods: $(filter $(LOGDIR)/tests/TourOfGo/methods/methods%, $(OUT_EXE_TEST_FILES)) \
		 $(filter $(LOGDIR)/tests/TourOfGo/methods/indirection%, $(OUT_EXE_TEST_FILES))
interface: $(filter $(LOGDIR)/tests/TourOfGo/methods/interface%, $(OUT_EXE_TEST_FILES))

gocpp.exe: cmd/main.go cmd/constants.go
	go build -o gocpp.exe cmd/main.go cmd/constants.go

$(OUT_CPP_TEST_FILES): $(OUTDIR)/%.cpp : %.go $(SUPPORT_FILES) gocpp.exe
	@echo "    $<"
	@echo "    $@"

	./gocpp.exe $(GOCPP_PARAMETERS) -input $< > $@".log"
	(cd $(OUTDIR) && make) 
	$(LOGDIR)/$*.go.exe

$(OUT_EXE_TEST_FILES): $(LOGDIR)/%.exe : %.go $(SUPPORT_FILES) gocpp.exe
	@echo "    $< "
	@echo "    $@ "
	
	mkdir -p $$(dirname $(LOGDIR)/$*) || true

	echo -n "| [$(<:tests/%=%)]($<) " > $(LOGDIR)/$*.md

	./gocpp.exe $(GOCPP_PARAMETERS) -input $< > $(LOGDIR)/$*".log" \
		&&  echo -n "| ✔️ " >> $(LOGDIR)/$*.md \
		|| (echo    "| ❌ | ❌ | ❌ | ❌ |" >> $(LOGDIR)/$*.md && false)

	(cd $(OUTDIR) && $(CCACHE) g++ -c -std=c++20 -I. -I../includes -I../$(OUTDIR) -I../thirdparty/includes $*.cpp -o ../$(LOGDIR)/$*.o && g++ ../$(LOGDIR)/$*.o -o ../$(LOGDIR)/$*.exe) \
		&&  echo -n "| ✔️ " >> $(LOGDIR)/$*.md \
		|| (echo    "| ❌ | ❌ | ❌ |" >> $(LOGDIR)/$*.md && false)

	if head -1 $< | grep -q "no-run"; then \
		echo -n "| ➖ " >> $(LOGDIR)/$*.md; \
	else \
		go run $< > $(LOGDIR)/$*.go.out.txt; \
		tput setaf 2; \
		(set -o pipefail; $(LOGDIR)/$*.exe | tee $(LOGDIR)/$*.cpp.out.txt) \
			&&  echo -n "| ✔️ ([cpp]($(OUTDIR)/$*.cpp)) " >> $(LOGDIR)/$*.md \
			|| (echo    "| ❌ | ❌ |" >> $(LOGDIR)/$*.md && false); status=$$?;\
		tput sgr0 ;\
		(exit $$status);\
	fi	

	if head -1 $< | grep -q -E "no-run|no-diff"; then \
		echo    "| ➖ | " >> $(LOGDIR)/$*.md; \
	else \
		(diff -q $(LOGDIR)/$*.cpp.out.txt $(LOGDIR)/$*.go.out.txt) \
			&&  echo    "| ✔️ |" >> $(LOGDIR)/$*.md \
			|| (echo    "| ❌ |" >> $(LOGDIR)/$*.md && false); \
	fi

clean:
	rm -rf $(LOGDIR) $(OUTDIR)
#	@rm -f $(OUT_CPP_TEST_FILES) $(OUT_HPP_TEST_FILES) $(OUT_EXE_TEST_FILES)
	rm -f results.md

unix2dos:
	unix2dos -q $$(find generated -type f -name "*.cpp" -o -name "*.h")

dos2unix:
	dos2unix -q $$(find generated -type f -name "*.cpp" -o -name "*.h")
