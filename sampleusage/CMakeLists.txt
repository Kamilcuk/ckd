cmake_minimum_required(VERSION 3.11)
project(ckdtester LANGUAGES C)

###############################################################################
include(FetchContent)
FetchContent_Declare(
  ckdint
  URL https://gitlab.com/Kamcuk/ckd/-/jobs/artifacts/master/download?job=gcc
)
FetchContent_MakeAvailable(ckdint)
include_directories(${ckdint_SOURCE_DIR})
###############################################################################

add_executable(ckdtester main.c)
