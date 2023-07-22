MAKEFLAGS = -rR

all: _build/CPM.cmake
	$(MAKE) build B=CPM
	$(MAKE) build B=fetchcontent

_build/CPM.cmake:
	@mkdir -p $(@D)
	wget -O $@ https://github.com/cpm-cmake/CPM.cmake/releases/latest/download/get_cpm.cmake

build: B=
build:
	cmake -S. -B_build/$(B) -DMODE=$(B)
	cmake --build _build/$(B)
	cd _build/$(B) && ctest -V

clean:
	rm -rf _build
