# ckd library

Implementation of [Towards Integer Safety](http://www.open-std.org/jtc1/sc22/wg14/www/docs/n2792.pdf).

The library is header only.
Generated headers are available from Gitlab CI artefacts: [browse](https://gitlab.com/Kamcuk/ckd/-/jobs/artifacts/master/browse?job=gcc) [download](https://gitlab.com/Kamcuk/ckd/-/jobs/artifacts/master/download?job=gcc).

# Building

Prerequisites:
- cmake
- python3
- python3-jinja2

Build with cmake.

# Using from CMake

See ./sampleusage/example-*. Do `add_subdirectory()` this directory.

# Written

Very big thanks for [tstanisl](https://stackoverflow.com/users/4989451/tstanisl) for [this answer](https://stackoverflow.com/a/70096454/9072753).

# License

Copyright (c) 2022 Kamil Cukrowski <kamilcukrowski@gmail.com>

Licensed under MIT License.

For more details, see [`LICENSE.md`](LICENSE.md).

