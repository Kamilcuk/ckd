all: build
	( cd _build && ctest -V )
see: config
	cmake --build _build --target ckdint.h
	tail -n 160 _build/include/ckdint.h
	grep -C20 AA _build/include/ckdint.h || true 
seesmall: config
	cmake --build _build --target ckdint_small.h
	cat _build/include/ckdint_small.h
	grep -C20 AA _build/include/ckdint_small.h || true 
config:
	cmake -S. -B_build -DCKD_DEV=1 -DBUILD_TESTING=1
build: config
	cmake --build _build -j
clean:
	rm -rf _build

