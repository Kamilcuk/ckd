# Makefile
MAKEFLAGS = -rR --no-print-directories --warn-undefined-variables
unexport MAKEFLAGS
.NOTPARALLEL:

CONFARGS = $(shell hash ninja 2>/dev/null && echo -GNinja)
TIME = $(shell hash time 2>/dev/null && echo time)
NICE = ionice -c 3 nice -n 40
RUN = $(shell \
          hash systemd-notify 2>/dev/null && \
          hash systemd-run 2>/dev/null && \
          systemd-notify --booted && \
          echo systemd-run --user -tdqp MemoryMax=10G)


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
	TARGETS = $(shell <<<"$(R_ALL_TARGETS)" tr ' ' '\n' | grep "$(R)" | tr '\n' ' ' )
ifeq ($(TARGETS),)
$(error No CMake target found for $(R): $(R_ALL_TARGETS))
endif
endif

# The number of build jobs.
JOBS ?=

all: test

config:
	$(NICE) cmake -S. -B$(B) -DCKD_DEV=1 --check-system-vars --log-context -Werror=dev -Wdev $(CONFARGS) $(ARGS)
build: config
	$(RUN) $(NICE) $(TIME) cmake --build $(B) -j $(JOBS) $(if $(value VERBOSE),--verbose) $(if $(value TARGETS),--target $(TARGETS))
gen: config
	$(NICE) cmake --build $(B) --target ckdint_gen
test: build
	cd $(B) && $(NICE) ctest $(if $(value R),-R "$R") $(if $F,--rerun-failed -j1) --output-on-failure $(ARGS)
	wc $(B)/include/*.h $(B)/include/*/*.h
clean:
	rm -rf $(B)
distclean:
	rm -rf ./_build

lint: cpplint clang-tidy
cpplint:
	$(NICE) cpplint \
		--filter=-whitespace/tab,-runtime/int,-readability/casting,-readability/todo,-build/header_guard,-whitespace/comma,-whitespace/parens,-whitespace/braces,-whitespace/semicolon \
		--linelength=150 \
		gen/*.h gen/*/*.h
clang-tidy:
	$(NICE) clang-tidy -p $(B) gen/*.h

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

doxygen: CONFARGS = -DCKD_DOXYGEN=1
doxygen: BSUF = doxygen
doxygen: TARGETS = doxygen
doxygen: build
