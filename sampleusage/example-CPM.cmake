# SPDX-FileCopyrightText: 2022 Kamil Cukrowski <kamilcukrowski@gmail.com>
# SPDX-License-Identifier: MIT

execute_process(
  COMMAND git rev-parse HEAD
  OUTPUT_VARIABLE commit
  OUTPUT_STRIP_TRAILING_WHITESPACE
)

include(./_build/CPM.cmake)
CPMAddPackage(
  NAME ckd
  GIT_REPOSITORY https://gitlab.com/Kamcuk/ckd.git
  GIT_TAG ${commit}
)

target_link_libraries(ckdtest PUBLIC ckd)
