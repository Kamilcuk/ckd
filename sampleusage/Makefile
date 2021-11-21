MAKEFLAGS = -rR

all: _build/CPM.cmake
	$(MAKE) build B=CPM
	$(MAKE) build B=fetchcontent

_build/CPM.cmake:
	@mkdir -p $(@D)
	wget -O _build/CPM.cmake https://raw.githubusercontent.com/cpm-cmake/CPM.cmake/master/cmake/CPM.cmake

build: B=
build:
	cmake -S. -B_build/$(B) -DMODE=$(B)
	cmake --build _build/$(B)
	cd _build/$(B) && ctest -V

clean:
	rm -rf _build
