
GO_TEST_DIRS:=$(wildcard ./tests ./tests/*/*/)
GO_TEST_DIRS:=$(filter-out ./tests/TourOfGo/img/, $(GO_TEST_DIRS))

GO_TEST_FILES=$(wildcard tests/*.go tests/*/*/*.go)
OUTDIR=generated
LOGDIR=log
SUPPORT_FILES=includes/gocpp/support.h includes/gocpp/support.fwd.h

_=$(shell mkdir -p $(OUTDIR)/golang)

GENERATED_GOLANG_LIB_CPP_FILES=$(shell find $(OUTDIR)/golang -name '*.cpp')
GENERATED_GOLANG_LIB_OBJ_FILES=$(patsubst  $(OUTDIR)/%, $(LOGDIR)/%, $(GENERATED_GOLANG_LIB_CPP_FILES:.cpp=.o))
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

GOCPP_ALWAYS_REGENERATE = false
GOCPP_STRICT_MODE = false
GOCPP_VERBOSE = false
GOCPP_IGNORE_DEPENDENCIES = false

GOCPP_PARAMETERS = -strictMode=$(GOCPP_STRICT_MODE)
GOCPP_PARAMETERS += -alwaysRegenerate=$(GOCPP_ALWAYS_REGENERATE)
GOCPP_PARAMETERS += -ignoreDependencies=$(GOCPP_IGNORE_DEPENDENCIES)
GOCPP_PARAMETERS += -verbose=$(GOCPP_VERBOSE)
GOCPP_PARAMETERS += -binOutDir=$(LOGDIR)
GOCPP_PARAMETERS += -cppOutDir=$(OUTDIR)

ON_DIFF_ERROR = false
ON_GCC_ERROR = false

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
	test -s $(1) || (echo "Error: $(1) is empty" && false)
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
	echo "| file | cpp generate | cpp compile |" >> results.md
	echo "| ---- | -------------| ----------- |" >> results.md
	make md-stdlib
	cat $$(find log/golang -type f -name "*.full.md" | sort) >> results.md
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
libs: $(filter $(LOGDIR)/tests/TourOfGo/libs/%, $(OUT_EXE_TEST_FILES))
moretypes: $(filter $(LOGDIR)/tests/TourOfGo/moretypes/%, $(OUT_EXE_TEST_FILES))
methods-all: $(filter $(LOGDIR)/tests/TourOfGo/methods/%, $(OUT_EXE_TEST_FILES))
methods: $(filter $(LOGDIR)/tests/TourOfGo/methods/methods%, $(OUT_EXE_TEST_FILES)) \
		 $(filter $(LOGDIR)/tests/TourOfGo/methods/indirection%, $(OUT_EXE_TEST_FILES))
interface: $(filter $(LOGDIR)/tests/TourOfGo/methods/interface%, $(OUT_EXE_TEST_FILES))

gocpp.exe: cmd/main.go cmd/constants.go cmd/utils.go
	go build -o gocpp.exe cmd/main.go cmd/constants.go cmd/utils.go


CUSTOM_BUILD_INPUT = tests/HelloWorld.go

custom-build: gocpp.exe
	./gocpp.exe $(GOCPP_PARAMETERS) -input $(CUSTOM_BUILD_INPUT) > $(LOGDIR)/gocpp.log


$(OUT_CPP_TEST_FILES): $(OUTDIR)/%.cpp : %.go $(SUPPORT_FILES) gocpp.exe
	$(call DEBUG_LOG, " => $<")
	$(call DEBUG_LOG, " => $@")
	$(call DEBUG_LOG, " => $*")

	./gocpp.exe $(GOCPP_PARAMETERS) -input $< > $@".log"
	(cd $(OUTDIR) && make) 
	$(LOGDIR)/$*.go.exe

$(OUT_EXE_TEST_FILES): $(LOGDIR)/%.exe : %.go $(SUPPORT_FILES) gocpp.exe
	$(call DEBUG_LOG, " => $<")
	$(call DEBUG_LOG, " => $@")
	$(call DEBUG_LOG, " => $*")
	mkdir -p $$(dirname $(LOGDIR)/$*) || true

	echo -n "| [$(<:tests/%=%)]($<) " > $(LOGDIR)/$*.md

	./gocpp.exe $(GOCPP_PARAMETERS) -input $< > $(LOGDIR)/$*".log" \
		&&  echo -n "| ✔️ " >> $(LOGDIR)/$*.md \
		|| (echo    "| ❌ | ❌ | ❌ | ❌ |" >> $(LOGDIR)/$*.md && false)

	(cd $(OUTDIR) && $(CCACHE) g++ -w -c -std=c++20 -I. -I../includes -I../$(OUTDIR) -I../thirdparty/includes $*.cpp -o ../$(LOGDIR)/$*.o && g++ ../$(LOGDIR)/$*.o -o ../$(LOGDIR)/$*.exe) \
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
			|| (echo    "| ❌ |" >> $(LOGDIR)/$*.md && $(ON_DIFF_ERROR)); \
	fi

go-stdlib-all: allexe
	make go-stdlib

go-stdlib: $(GENERATED_GOLANG_LIB_OBJ_FILES)
#	$(call DEBUG_LOG, $(GENERATED_GOLANG_LIB_OBJ_FILES))


$(GENERATED_GOLANG_LIB_OBJ_FILES): $(LOGDIR)/%.o : $(OUTDIR)/%.cpp $(SUPPORT_FILES)
	$(call DEBUG_LOG, " => $<")
	$(call DEBUG_LOG, " => $@")
	$(call DEBUG_LOG, " => $*")

	mkdir -p $$(dirname $@) || true

	($(call check-nonempty, $<) && cd $(OUTDIR) && $(CCACHE) g++ -w -c -std=c++20 -I. -I../includes -I../$(OUTDIR) -I../thirdparty/includes $*.cpp -o ../$(LOGDIR)/$*.o) \
		&&  echo -n " ✔️ |" > $(LOGDIR)/$*.obj.md \
		|| (echo    " ❌ |" > $(LOGDIR)/$*.obj.md && $(ON_GCC_ERROR))

md-stdlib: $(GENERATED_GOLANG_LIB_OBJ_FULLMD_FILES)
#	$(call DEBUG_LOG, $(GENERATED_GOLANG_LIB_OBJ_FULLMD_FILES))

$(GENERATED_GOLANG_LIB_OBJ_FULLMD_FILES): $(LOGDIR)/%.full.md : $(LOGDIR)/%.obj.md $(LOGDIR)/%.status.md
	$(call DEBUG_LOG, " => $<")
	$(call DEBUG_LOG, " => $@")
	$(call DEBUG_LOG, " => $*")
	cat $(LOGDIR)/$*.status.md $(LOGDIR)/$*.obj.md | (tr -d "\n" && echo) > $@

clean-full-md:
	rm $$(find $(LOGDIR) -name '*.full.md')

clean-exe-obj:
	rm $$(find $(LOGDIR) -name '*.exe')
	rm $$(find $(LOGDIR) -name '*.o')

clean:
	rm -rf $(LOGDIR) $(OUTDIR)
	rm -f results.md

soft-clean:
	touch cmd/main.go

keep-generated:
	touch $$(find $(OUTDIR) -type f -name '*.cpp' -o -name '*.h')

unix2dos:
	unix2dos -q $$(find generated -type f -name "*.cpp" -o -name "*.h")

dos2unix:
	dos2unix -q $$(find generated -type f -name "*.cpp" -o -name "*.h")
