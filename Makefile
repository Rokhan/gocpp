SHELL := /bin/bash

GO_TEST_DIRS:=$(wildcard ./tests ./tests/*/*/)
GO_TEST_DIRS:=$(filter-out ./tests/TourOfGo/img/, $(GO_TEST_DIRS))

GO_TEST_FILES=$(wildcard tests/*.go tests/*/*.go tests/*/*/*.go)
OUTDIR=generated
LOGDIR=log
SUPPORT_FILES=includes/gocpp/support.h includes/gocpp/support.fwd.h

_=$(shell mkdir -p $(OUTDIR)/golang)

GENERATED_GOLANG_LIB_CPP_FILES=$(shell find $(OUTDIR)/golang -name '*.cpp')
GENERATED_GOLANG_LIB_OBJ_FILES=$(patsubst  $(OUTDIR)/%, $(LOGDIR)/%, $(GENERATED_GOLANG_LIB_CPP_FILES:.cpp=.o))
GENERATED_GOLANG_LIB_LINK_MD_FILES=$(patsubst $(OUTDIR)/%, $(LOGDIR)/%, $(GENERATED_GOLANG_LIB_CPP_FILES:.cpp=.link.md))
GENERATED_GOLANG_LIB_OBJ_FULLMD_FILES=$(GENERATED_GOLANG_LIB_OBJ_FILES:.o=.full.md)

CPP_TEST_FILES=$(GO_TEST_FILES:.go=.cpp)
OUT_CPP_TEST_FILES=$(addprefix $(OUTDIR)/,$(CPP_TEST_FILES))

HPP_TEST_FILES=$(GO_TEST_FILES:.go=.h)
OUT_HPP_TEST_FILES=$(addprefix $(OUTDIR)/,$(HPP_TEST_FILES))

EXE_TEST_FILES=$(GO_TEST_FILES:.go=.exe)
OUT_EXE_TEST_FILES=$(addprefix $(LOGDIR)/,$(EXE_TEST_FILES))

MD_TEST_FILES=$(GO_TEST_FILES:.go=.md)
OUT_MD_TEST_FILES=$(addprefix $(LOGDIR)/,$(MD_TEST_FILES))

CCACHE := $(shell which ccache 2> /dev/null)

GCC_TIMEOUT ?= 30s
LINK_TIMEOUT ?= 60s

GOCPP_ALWAYS_REGENERATE = false
GOCPP_STRICT_MODE = false
GOCPP_DEBUG_MODE = false
GOCPP_VERBOSE = false
GOCPP_IGNORE_DEPENDENCIES = false

GOCPP_PARAMETERS = -strictMode=$(GOCPP_STRICT_MODE)
GOCPP_PARAMETERS += -debugMode=$(GOCPP_DEBUG_MODE)
GOCPP_PARAMETERS += -alwaysRegenerate=$(GOCPP_ALWAYS_REGENERATE)
GOCPP_PARAMETERS += -ignoreDependencies=$(GOCPP_IGNORE_DEPENDENCIES)
GOCPP_PARAMETERS += -verbose=$(GOCPP_VERBOSE)
GOCPP_PARAMETERS += -binOutDir=$(LOGDIR)
GOCPP_PARAMETERS += -cppOutDir=$(OUTDIR)

ON_DIFF_ERROR = false
ON_GCC_ERROR = false

GOCPP_SANITIZE ?=
# usage: make GOCPP_SANITIZE=address ...
CXX_SANITIZE = $(if $(GOCPP_SANITIZE),-fsanitize=$(GOCPP_SANITIZE) -g,)

export SHOW_DEBUG_LOG = false

ifeq ($(SHOW_DEBUG_LOG),true)
  define DEBUG_LOG
    @echo $(1)
  endef
else ifeq ($(SHOW_DEBUG_LOG),false)
  define DEBUG_LOG
  endef
endif

define check-nonempty
	test -s "$(1)" || (echo "Error: $(1) is empty" && false)
endef

define compute-time
	$(call check-nonempty,$(1)) || { echo "$(1) | ERROR: empty input" > $(3); exit 1; }; \
	start=$$(date +%s%N); \
	$(2); \
	status=$$?; \
	end=$$(date +%s%N); \
	elapsed=$$((end - start)); \
	echo -n "$(1) | " > $(3); \
	printf '%8.3f\n' "$$(awk "BEGIN {print $$elapsed / 1000000000}")" >> $(3); \
	exit $$status
endef

## ------------------------------------------------------ ##
##  Building stop at first error (as usual in Makefile)   ##
##  To generate full report just use "make -k"            ##
## ------------------------------------------------------ ##

all: allexe go-stdlib-all

doc:
	echo "# Results on test directory" > results.md
	echo >> results.md
	echo "| file | cpp generate | cpp compilation | run | result diff |" >> results.md
	echo "| ---- | ------------ | --------------- | --- | ----------- |" >> results.md
	cat $(OUT_MD_TEST_FILES) | sort -t. -k 1d,1 >> results.md
	echo "" >> results.md
	echo "" >> results.md
	echo "# Conversion of imported packages" >> results.md
	echo "| file | cpp generate | cpp compile | link |" >> results.md
	echo "| ---- | -------------| ----------- | ---- |" >> results.md
	$(MAKE) -j4 md-stdlib ON_GCC_ERROR=true
	cat $$(find log/golang -type f -name "*.full.md" | sort) >> results.md
	dos2unix results.md

	echo > times.md
	echo "File | compilation time " >> times.md
	echo "---- | ---------------- " >> times.md
	cat $$(find . -type f -name '*.time') >> times.md

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
libs: $(filter $(LOGDIR)/tests/TourOfGo/libs/%, $(OUT_EXE_TEST_FILES))
moretypes: $(filter $(LOGDIR)/tests/TourOfGo/moretypes/%, $(OUT_EXE_TEST_FILES))
methods-all: $(filter $(LOGDIR)/tests/TourOfGo/methods/%, $(OUT_EXE_TEST_FILES))
methods: $(filter $(LOGDIR)/tests/TourOfGo/methods/methods%, $(OUT_EXE_TEST_FILES)) \
		 $(filter $(LOGDIR)/tests/TourOfGo/methods/indirection%, $(OUT_EXE_TEST_FILES))
interface: $(filter $(LOGDIR)/tests/TourOfGo/methods/interface%, $(OUT_EXE_TEST_FILES))

gocpp.exe: cmd/*.go
	go vet cmd/*.go
	go build -o gocpp.exe cmd/*.go


CUSTOM_BUILD_INPUT = tests/HelloWorld.go

# Build the cpp from a go file without compiling it.
# usage example: 'make custom-build GOCPP_IGNORE_DEPENDENCIES=true CUSTOM_BUILD_INPUT="F:/Dev/go1.22.2/src/compress/flate/huffman_code.go"'
custom-build: gocpp.exe
	./gocpp.exe $(GOCPP_PARAMETERS) -input $(CUSTOM_BUILD_INPUT) > $(LOGDIR)/gocpp.log

# Build the cpp from a standard library go file then compile it.
# usage example: 'make custom-stdlib-build GOCPP_IGNORE_DEPENDENCIES=true CUSTOM_BUILD_INPUT="compress/flate/huffman_bit_writer.go"'
custom-stdlib-build: gocpp.exe
	./gocpp.exe $(GOCPP_PARAMETERS) -input $$(go env GOROOT)/src/$(CUSTOM_BUILD_INPUT) > $(LOGDIR)/gocpp-stdlib.log
	$(MAKE) $(LOGDIR)/golang/$(CUSTOM_BUILD_INPUT:.go=.o)
	rm -f $(LOGDIR)/golang/$(CUSTOM_BUILD_INPUT:.go=.link.md)
	$(MAKE) $(LOGDIR)/golang/$(CUSTOM_BUILD_INPUT:.go=.link.md)
	cat $(LOGDIR)/golang/$(CUSTOM_BUILD_INPUT:.go=.link.md); echo
	grep -o "undefined reference to .*" $(LOGDIR)/golang/$(CUSTOM_BUILD_INPUT:.go=.link.log) | sort | uniq -c | sort -rn | head -20 || true
	grep -o "multiple definition of .*;" $(LOGDIR)/golang/$(CUSTOM_BUILD_INPUT:.go=.link.log) | sort | uniq -c | sort -rn | head -20 || true

$(OUT_CPP_TEST_FILES): $(OUTDIR)/%.cpp : %.go $(SUPPORT_FILES) gocpp.exe
	$(call DEBUG_LOG, " => $<")
	$(call DEBUG_LOG, " => $@")
	$(call DEBUG_LOG, " => $*")

	./gocpp.exe $(GOCPP_PARAMETERS) -testFile=true -input $< > $@".log"
	(cd $(OUTDIR) && make) 
	$(LOGDIR)/$*.go.exe

$(OUT_EXE_TEST_FILES): $(LOGDIR)/%.exe : %.go $(SUPPORT_FILES) gocpp.exe
	$(call DEBUG_LOG, " => $<")
	$(call DEBUG_LOG, " => $@")
	$(call DEBUG_LOG, " => $*")
	mkdir -p $$(dirname $(LOGDIR)/$*) || true

	echo -n "| [$(<:tests/%=%)]($<) " > $(LOGDIR)/$*.md

	./gocpp.exe $(GOCPP_PARAMETERS) -testFile=true -input $< > $(LOGDIR)/$*".log" \
		&&  echo -n "| ✔️ " >> $(LOGDIR)/$*.md \
		|| (echo    "| ❌ | ❌ | ❌ | ❌ |" >> $(LOGDIR)/$*.md && false)

	(cd $(OUTDIR) && $(CCACHE) g++ -w -c -std=c++20 $(CXX_SANITIZE) -I. -I../includes -I../$(OUTDIR) -I../thirdparty/includes $*.cpp -o ../$(LOGDIR)/$*.o && g++ $(CXX_SANITIZE) ../$(LOGDIR)/$*.o -o ../$(LOGDIR)/$*.exe) \
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
		echo    "| ➖ |" >> $(LOGDIR)/$*.md; \
	else \
		diff $(LOGDIR)/$*.cpp.out.txt $(LOGDIR)/$*.go.out.txt; \
		(diff -q $(LOGDIR)/$*.cpp.out.txt $(LOGDIR)/$*.go.out.txt) \
			&&  echo    "| ✔️ |" >> $(LOGDIR)/$*.md \
			|| (echo    "| ❌ |" >> $(LOGDIR)/$*.md && $(ON_DIFF_ERROR)); \
	fi

go-stdlib-all: allexe
	-$(MAKE) -k go-stdlib
	$(MAKE) -k go-stdlib-link

go-stdlib: $(GENERATED_GOLANG_LIB_OBJ_FILES)
#	$(call DEBUG_LOG, $(GENERATED_GOLANG_LIB_OBJ_FILES))

GOLANG_LIB_COMPILE = \
	( set -o pipefail; \
	  cd $(OUTDIR) && \
	  LC_ALL=C timeout $(GCC_TIMEOUT) $(CCACHE) g++ -w -c -std=c++20 $(CXX_SANITIZE) \
		-I. -I../includes -I../$(OUTDIR) -I../thirdparty/includes \
		-ffunction-sections -fdata-sections \
		$(1).cpp \
		-o ../$(LOGDIR)/$(1).o 2>&1 | tee ../$(LOGDIR)/$(1).compile.log )

$(GENERATED_GOLANG_LIB_OBJ_FILES): $(LOGDIR)/%.o : $(OUTDIR)/%.cpp $(SUPPORT_FILES)
	$(call DEBUG_LOG, " => $<")
	$(call DEBUG_LOG, " => $@")
	$(call DEBUG_LOG, " => $*")

	mkdir -p $$(dirname $@) || true

	@($(call compute-time,$<,$(call GOLANG_LIB_COMPILE,$*),$(LOGDIR)/$*.time)) \
		&&  echo -n " ✔️ |" > $(LOGDIR)/$*.obj.md \
		|| ( [ -s $(LOGDIR)/$*.compile.log ] \
			|| echo "$*.cpp:0:0: error: compile timeout or killed ($(GCC_TIMEOUT))" > $(LOGDIR)/$*.compile.log; \
		    	 echo " ❌ |" > $(LOGDIR)/$*.obj.md  && rm -f $@ && $(ON_GCC_ERROR))


go-stdlib-link: $(GENERATED_GOLANG_LIB_LINK_MD_FILES)

GOLANG_LIB_ARCHIVE=$(LOGDIR)/golang/libgolang.a

.SECONDEXPANSION:

# Rebuilt in a temp file and replaced only if the member list changed,
# so its mtime (and therefore every link result) is stable when nothing was added or removed.
$(GOLANG_LIB_ARCHIVE): FORCE
	find $(CURDIR)/$(LOGDIR)/golang -name '*.o' | sort > $@.list
	rm -f $@.tmp
	xargs ar qcsT $@.tmp < $@.list
	if cmp -s $@.tmp $@; then rm -f $@.tmp; else mv $@.tmp $@; fi

FORCE:

# Linking test for go std lib files
# * '-nostartfiles': library files have no main, we only want to see missing/duplicate symbols.
# * No prerequisite on the .o file on purpose, compilation failure gives ❌ status
$(GENERATED_GOLANG_LIB_LINK_MD_FILES): $(LOGDIR)/%.link.md : $(OUTDIR)/%.cpp $$(wildcard $(LOGDIR)/$$*.o) $(GOLANG_LIB_ARCHIVE)
	mkdir -p $$(dirname $@) || true
	@if [ ! -f $(LOGDIR)/$*.o ]; then \
		echo -n " ❌ |" > $@; \
	else \
		roots=$$(nm --defined-only $(LOGDIR)/$*.o | awk '$$2 ~ /^[TDBRVWSG]$$/ { print "-Wl,-u," $$3 }'); \
		if timeout $(LINK_TIMEOUT) g++ -nostartfiles -pthread $(CXX_SANITIZE) \
				-Wl,--gc-sections $$roots $(LOGDIR)/$*.o $(GOLANG_LIB_ARCHIVE) \
				-o $(LOGDIR)/$*.link.out > $(LOGDIR)/$*.link.log 2>&1; \
		then echo -n " ✔️ |" > $@; \
		else echo -n " ❌ |" > $@; fi; \
	fi

# Most frequent undefined symbols, to see what to implement next.
link-undefined:
	cat $$(find $(LOGDIR)/golang -name '*.link.log') | grep -o "undefined reference to .*" | sort | uniq -c | sort -rn | head -50

# Most frequent multiple definition symbols, to see what to fix next.
link-multiple-definition:
	cat $$(find $(LOGDIR)/golang -name '*.link.log') | grep -o "multiple definition of .*;" | sort | uniq -c | sort -rn | head -50

md-stdlib: $(GENERATED_GOLANG_LIB_OBJ_FULLMD_FILES)
#	$(call DEBUG_LOG, $(GENERATED_GOLANG_LIB_OBJ_FULLMD_FILES))

# Like "head -N", but reports how many lines were cut.
# Override on the command line: make compile-errors TOP_N=100
TOP_N ?= 10
TOP = awk -v n=$(TOP_N) 'NR <= n { print; next } { skipped++ } END { if (skipped) printf "... (%d more lines skipped)\n", skipped }'

# Non-empty compile logs (only failed files keep an error log).
COMPILE_LOGS = $$(find $(LOGDIR)/golang -name '*.compile.log' -size +0)

# Strip "path:line:col: [fatal ]error: ".
STRIP_LOC = sed -E 's/^.*:[0-9]+:[0-9]+: (fatal )?error: //'
# Replace every 'quoted' name with 'X', so the same cause counts once.
GENERALIZE = sed -E "s/'[^']*'/'X'/g"

# Root-cause view: only the FIRST error of each file (later ones are mostly cascades).
# Messages are generalized (names replaced by 'X') so identical causes group together.
compile-errors:
	@echo "### first error per file, generalized (count = number of files) ###"
	@find $(LOGDIR)/golang -name '*.compile.log' -size +0 | xargs -r -n1 grep -m1 -h 'error:' \
		| $(STRIP_LOC) | $(GENERALIZE) | sort | uniq -c | sort -rn | $(TOP)

# Same, with the exact names kept (to see which identifier/header is missing).
compile-errors-exact:
	@find $(LOGDIR)/golang -name '*.compile.log' -size +0 | xargs -r -n1 grep -m1 -h 'error:' \
		| $(STRIP_LOC) | sort | uniq -c | sort -rn | $(TOP)

# Every error, not only the first one (noisy because of cascades).
compile-errors-all:
	@cat $(COMPILE_LOGS) | grep 'error:' | $(STRIP_LOC) | $(GENERALIZE) | sort | uniq -c | sort -rn | $(TOP)

# Files that have the most errors.
compile-errors-files:
	@for f in $(COMPILE_LOGS); do echo "$$(grep -c 'error:' $$f) $$f"; done | sort -rn | $(TOP)

# Files that fail for a given cause. usage: make compile-errors-all-grep PATTERN="was not declared"
compile-errors-all-grep:
	@grep -l -m1 -- "$(PATTERN)" $(COMPILE_LOGS) | sed 's|$(LOGDIR)/||; s|\.compile\.log||' | $(TOP)

# Same as compile-errors-all-grep, but only the FIRST error of each file is tested
compile-errors-grep:
	@for f in $(COMPILE_LOGS); do \
		if grep -m1 -h 'error:' "$$f" | grep -q -- "$(PATTERN)"; then \
			echo "$$f"; \
		fi; \
	done | sed 's|$(LOGDIR)/||; s|\.compile\.log||' | $(TOP)

# Compile everything and keep going, then report.
compile-report:
	-$(MAKE) -k go-stdlib
	$(MAKE) compile-errors


$(GENERATED_GOLANG_LIB_OBJ_FULLMD_FILES): $(LOGDIR)/%.full.md : $(LOGDIR)/%.obj.md $(LOGDIR)/%.status.md $(LOGDIR)/%.link.md
	$(call DEBUG_LOG, " => $<")
	$(call DEBUG_LOG, " => $@")
	$(call DEBUG_LOG, " => $*")
	cat $(LOGDIR)/$*.{status,obj,link}.md | (tr -d "\n" && echo) > $@

clean-full-md:
	rm $$(find $(LOGDIR) -name '*.full.md')

clean-exe-obj:
	rm $$(find $(LOGDIR) -name '*.exe')
	rm $$(find $(LOGDIR) -name '*.o')

clean:
	rm -rf $(LOGDIR) $(OUTDIR)
	rm -f results.md

relink:
	rm -f $$(find $(LOGDIR)/golang -name '*.link.md')
	$(MAKE) -k go-stdlib-link

soft-clean:
	touch cmd/main.go

keep-generated:
	touch $$(find $(OUTDIR) -type f -name '*.cpp' -o -name '*.h')

unix2dos:
	unix2dos -q $$(find generated -type f -name "*.cpp" -o -name "*.h")

dos2unix:
	dos2unix -q $$(find generated -type f -name "*.cpp" -o -name "*.h")

ccache-stats:
	$(CCACHE) -s
