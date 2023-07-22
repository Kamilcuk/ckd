MAKEFLAGS = -rR --no-print-directories --warn-undefined-variables
.NOTPARALLEL:

CONF_ARGS = $(shell hash ninja 2>/dev/null && echo -GNinja)
TIME = $(shell hash time 2>/dev/null && echo time)
RUN = $(shell \
          hash systemd-notify 2>/dev/null && \
          hash systemd-run 2>/dev/null && \
          systemd-notify --booted && \
          echo systemd-run -p MemoryMax=10G --user -td)


# Path to build directory
BSUF ?= $(if $(value CC),$(CC),default)
B ?= ./_build/$(BSUF)
ARGS ?=

all: test

config:
	cmake -S. -B$(B) -DCKD_DEV=1 $(CONF_ARGS) $(ARGS)
build: config
	$(RUN) $(TIME) cmake --build $(B) -j $(if $(value VERBOSE),1 --verbose)
gen: config
	cmake --build $(B) --target ckdint_gen
F ?=
R ?=
test: build
	( cd $(B) && ctest $(if $(value R),-R "$R") $(if $F,--rerun-failed -j1) --output-on-failure )
	wc $(B)/include/*.h $(B)/include/*/*.h
clean:
	rm -rf $(B)
distclean:
	rm -rf ./_build

lint: gen
	cd _build/include && cpplint \
		--filter=-whitespace/tab,-runtime/int,-readability/casting,-readability/todo,-build/header_guard,-whitespace/comma,-whitespace/parens,-whitespace/braces \
		--linelength=150 \
		*.h */*.h

coverage:
	$(MAKE) BSUF=coverage ARGS=-DCKD_COVERAGE=1
	gcovr -r $(PWD) -e test -f _build/coverage/include -j $$(nproc)

measure:
	./scripts/measure.sh output

###############################################################################

see: gen
	cat $(B)/include/ckdint.h
	grep -C5 AA $(B)/include/*.h $(B)/include/*/*.h || true

shorttest: gen
	gcc -xc -o $(B)/shorttest.out $(B)/include/ckdint.h
	$(B)/shorttest.out

