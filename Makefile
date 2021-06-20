all: build
	( cd _build && ctest -V )
see: config
	cmake --build _build --target include/ckdint.h
	tail -n 160 _build/include/ckdint.h
	grep -C20 AA _build/include/ckdint.h || true 
config:
	cmake -S. -B_build -DCKD_DEV=1 -DBUILD_TESTING=1
build: config
	cmake --build _build
clean:
	rm -rf _build

