MAKEFLAGS = -rR --no-print-directories
.NOTPARALLEL:

# Path to build directory
B ?= _build/$(CC)

all: test

config:
	cmake -S. -B$(B) -DCKD_DEV=1 $(ARGS)
build: config
	cmake --build $(B) -j
test: build
	( cd $(B) && ctest -V )
	wc $(B)/include/*.h $(B)/include/*/*.h
clean:
	rm -rf _build
gen:
	@mkdir -p ./generated
	cp -va $(B)/include/* ./generated

###############################################################################

ckdint_gen: config
	cmake --build $(B) --target ckdint_gen
see: ckdint_gen
	cat $(B)/include/ckdint.h
	grep -C5 AA $(B)/include/*.h $(B)/include/*/*.h || true

shorttest: ckdint_gen
	gcc -xc -o $(B)/shorttest.out $(B)/include/ckdint.h
	$(B)/shorttest.out

