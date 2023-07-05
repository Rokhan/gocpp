
GO_TEST_FILES=$(wildcard tests/*.go tests/*/*/*.go)
OUTDIR=generated
LOGDIR=log
SUPPORT_FILES=includes/gocpp/support.h

CPP_TEST_FILES=$(GO_TEST_FILES:.go=.cpp)
OUT_CPP_TEST_FILES=$(addprefix $(OUTDIR)/,$(CPP_TEST_FILES))

HPP_TEST_FILES=$(GO_TEST_FILES:.go=.h)
OUT_HPP_TEST_FILES=$(addprefix $(OUTDIR)/,$(HPP_TEST_FILES))

EXE_TEST_FILES=$(GO_TEST_FILES:.go=.exe)
OUT_EXE_TEST_FILES=$(addprefix $(LOGDIR)/,$(EXE_TEST_FILES))

MD_TEST_FILES=$(GO_TEST_FILES:.go=.md)
OUT_MD_TEST_FILES=$(addprefix $(LOGDIR)/,$(MD_TEST_FILES))

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
	cat $(OUT_MD_TEST_FILES) >> results.md
	dos2unix results.md

allcpp: $(OUT_CPP_TEST_FILES)
	echo $(OUT_CPP_TEST_FILES)

allexe: $(OUT_EXE_TEST_FILES)
	echo $(OUT_EXE_TEST_FILES)

flow: $(filter $(LOGDIR)/tests/TourOfGo/flowcontrol/%, $(OUT_EXE_TEST_FILES))
basics: $(filter $(LOGDIR)/tests/TourOfGo/basics/%, $(OUT_EXE_TEST_FILES))
moretypes: $(filter $(LOGDIR)/tests/TourOfGo/moretypes/%, $(OUT_EXE_TEST_FILES))
methods-all: $(filter $(LOGDIR)/tests/TourOfGo/methods/%, $(OUT_EXE_TEST_FILES))
methods: $(filter $(LOGDIR)/tests/TourOfGo/methods/methods%, $(OUT_EXE_TEST_FILES))

$(OUT_CPP_TEST_FILES): $(OUTDIR)/%.cpp : %.go $(SUPPORT_FILES)
	@echo "    $<"
	@echo "    $@"

	go run ./cmd/main.go -parseFmt=false -binOutDir=$(LOGDIR) -cppOutDir=$(OUTDIR) -input $< > $@".log"
	(cd $(OUTDIR) && make) 
	$(LOGDIR)/$*.go.exe

$(OUT_EXE_TEST_FILES): $(LOGDIR)/%.exe : %.go $(SUPPORT_FILES)
	@echo "    $< "
	@echo "    $@ "
	
	mkdir -p $$(dirname $(LOGDIR)/$*) || true

	echo -n "| $(<:tests/%=%) " > $(LOGDIR)/$*.md

	go run ./cmd/main.go -parseFmt=false -binOutDir=$(LOGDIR) -cppOutDir=$(OUTDIR) -input $< > $(LOGDIR)/$*".log" \
		&&  echo -n "| ✔️ " >> $(LOGDIR)/$*.md \
		|| (echo    "| ❌ | ❌ | ❌ | ❌ |" >> $(LOGDIR)/$*.md && false)

	(cd $(OUTDIR) && g++ -I. -I../includes $*.cpp -o ../$(LOGDIR)/$*.exe) \
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
	@rm -f $(OUT_CPP_TEST_FILES) $(OUT_HPP_TEST_FILES) $(OUT_EXE_TEST_FILES)
	rm -f results.md
