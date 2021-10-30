MAKEFLAGS = -rR --no-print-directories
.NOTPARALLEL:

CONFARGS ?=
ifeq ($(shell hash ninja 2>&1),)
CONFARGS = -GNinja
endif
TIME ?=
ifeq ($(shell hash time 2>&1),)
TIME = time
endif

# Path to build directory
BSUF ?= $(CC)
B ?= _build/$(BSUF)
F ?=

all: test

config:
	cmake -S. -B$(B) -DCKD_DEV=1 $(CONFARGS) $(ARGS)
build: config
	$(TIME) cmake --build $(B) -j
build_gen: config
	cmake --build $(B) --target ckdint_gen
test: build
	( cd $(B) && ctest $(if $(value R),-R "$R") $(if $F,--rerun-failed -j1) --output-on-failure )
	wc $(B)/include/*.h $(B)/include/*/*.h
clean:
	rm -rf $(B)
distclean:
	rm -rf _build

lint: build_gen
	cd _build/include && cpplint \
		--filter=-whitespace/tab,-runtime/int,-readability/casting,-readability/todo,-build/header_guard \
		--linelength=150 \
		*.h */*.h

coverage:
	$(MAKE) BSUF=coverage ARGS=-DCKD_COVERAGE=1
	gcovr -r $(PWD) -e test -f _build/coverage/include -j $$(nproc)

###############################################################################

see: build_gen
	cat $(B)/include/ckdint.h
	grep -C5 AA $(B)/include/*.h $(B)/include/*/*.h || true

shorttest: build_gen
	gcc -xc -o $(B)/shorttest.out $(B)/include/ckdint.h
	$(B)/shorttest.out

