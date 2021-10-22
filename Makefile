MAKEFLAGS = -rR --no-print-directories
.NOTPARALLEL:

# Path to build directory
B ?= _build/$(CC)

all: test

config:
	cmake -S. -B$(B) -DCKD_DEV=1
build: config
	cmake --build $(B) -j
test: build
	( cd $(B) && ctest -V )
	wc $(B)/include/*
clean:
	rm -rf _build

###############################################################################

ckdint.h: config
	cmake --build $(B) --target ckdint.h
see: ckdint.h
	cat $(B)/include/ckdint.h
	grep -C5 AA $(B)/include/ckdint.h || true

shorttest: ckdint.h
	gcc -xc -o $(B)/shorttest.out $(B)/include/ckdint.h
	$(B)/shorttest.out

