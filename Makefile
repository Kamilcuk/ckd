# Makefile
MAKEFLAGS = -rR --no-print-directories --warn-undefined-variables
unexport MAKEFLAGS
.NOTPARALLEL:

CONFARGS = $(shell hash ninja 2>/dev/null && echo -GNinja)
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
# Set to 1 to rerun failed only.
F ?=
# Regex filter to run only these tests
R ?=
ifneq ($(R),)
	R_ALL_TARGETS = $(shell \
				cd tests && printf "%s\n" *.c | \
				sed 's/\.c//; s/.*/ckd_&_gnu\nckd_&_nognu/' )
	R_TARGETS = $(shell <<<"$(R_ALL_TARGETS)" tr ' ' '\n' | grep "$(R)" | tr '\n' ' ' )
ifeq ($(R_TARGETS),)
$(error No CMake target found for $(R): $(R_ALL_TARGETS))
endif
endif

# The number of build jobs.
JOBS ?=

all: test

config:
	cmake -S. -B$(B) -DCKD_DEV=1 $(CONFARGS) $(ARGS)
build: config
	$(RUN) $(TIME) cmake --build $(B) -j $(JOBS) $(if $(value VERBOSE),--verbose) $(if $(value R),--target $(R_TARGETS))
gen: config
	cmake --build $(B) --target ckdint_gen
test: build
	cd $(B) && ctest $(if $(value R),-R "$R") $(if $F,--rerun-failed -j1) --output-on-failure $(ARGS)
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

test_gcc: VERSION=11
test_gcc:
	docker build --build-arg VERSION=$(VERSION) -f Dockerfile.gcc  -t ckdint-gcc-$(VERSION) .
	docker run -ti --rm -v $(PWD):/mnt -u $$(id -u):$$(id -g) -w /mnt ckdint-gcc-$(VERSION) \
		make BSUF=docker-gcc-$(VERSION)
