cmake_minimum_required(VERSION 3.11)
project(ckdtest LANGUAGES C)
add_executable(ckdtest main.c)
include(FetchContent)
include(./example-${MODE}.cmake)
include(CTest)
add_test(NAME ckdtest COMMAND ckdtest)

