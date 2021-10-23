MAKEFLAGS = -rR --no-print-directories
.NOTPARALLEL:

# Path to build directory
B ?= _build/$(CC)
F ?=

all: test

config:
	cmake -S. -B$(B) -DCKD_DEV=1 $(ARGS)
build: config
	cmake --build $(B) -j
build_gen: config
	cmake --build $(B) --target ckdint_gen
test: build
	( cd $(B) && ctest -V $(if $(value R),-R "$R") $(if $F,--rerun-failed --output-on-failure -j1) )
	wc $(B)/include/*.h $(B)/include/*/*.h
clean:
	rm -rf _build
gen: build_gen
	@mkdir -p ./generated
	cp -va $(B)/include/* ./generated

lint: build_gen
	cd _build/include && cpplint \
		--filter=-whitespace/tab,-runtime/int,-readability/casting,-readability/todo,-build/header_guard \
		--linelength=150 \
		*.h */*.h

###############################################################################

see: build_gen
	cat $(B)/include/ckdint.h
	grep -C5 AA $(B)/include/*.h $(B)/include/*/*.h || true

shorttest: build_gen
	gcc -xc -o $(B)/shorttest.out $(B)/include/ckdint.h
	$(B)/shorttest.out

