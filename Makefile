all: build
	( cd _build && ctest -V )
	wc -l _build/include/* | grep -v total
see: config
	cmake --build _build --target ckdint.h
	cat _build/include/ckdint.h
	grep -C5 AA _build/include/ckdint.h || true
seesmall: config
	cmake --build _build --target ckdint_small.h
	cat _build/include/ckdint_small.h
	grep -C5 AA _build/include/ckdint_small.h || true
config:
	cmake -S. -B_build -DCKD_DEV=1 -DBUILD_TESTING=1
build: config
	cmake --build _build -j
clean:
	rm -rf _build

