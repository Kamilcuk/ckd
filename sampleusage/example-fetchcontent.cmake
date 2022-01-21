# SPDX-FileCopyrightText: 2022 Kamil Cukrowski <kamilcukrowski@gmail.com>
# SPDX-License-Identifier: MIT

FetchContent_Declare(
  ckdint
  URL https://gitlab.com/Kamcuk/ckd/-/jobs/artifacts/master/download?job=gcc
)
FetchContent_MakeAvailable(ckdint)
target_include_directories(ckdtest PUBLIC ${ckdint_SOURCE_DIR})

