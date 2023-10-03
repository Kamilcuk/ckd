# SPDX-FileCopyrightText: 2022 Kamil Cukrowski <kamilcukrowski@gmail.com>
# SPDX-License-Identifier: MIT
cmake_minimum_required(VERSION 3.11)
project(ckd LANGUAGES C)

include(CheckTypeSize)

# ##############################################################################

find_package(Git QUIET REQUIRED)

execute_process(
  COMMAND "${GIT_EXECUTABLE}" describe --always --tags HEAD
  WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}"
  OUTPUT_VARIABLE CKD_VERSION_DESCRIBE
  ERROR_VARIABLE GIT_DESCRIBE_ERROR_VARIABLE
  ERROR_QUIET OUTPUT_STRIP_TRAILING_WHITESPACE
  RESULT_VARIABLE GIT_DESCRIBE_RESULT)
if(GIT_DESCRIBE_RESULT)
  message(
    FATAL_ERROR "${GIT_EXECUTABLE} describe --always --tags HEAD failed!\n"
                "${CKD_VERSION_DESCRIBE}${GIT_DESCRIBE_ERROR_VARIABLE}")
endif()
set_property(GLOBAL APPEND PROPERTY CMAKE_CONFIGURE_DEPENDS
                                    "${CMAKE_SOURCE_DIR}/.git/index")
string(REGEX REPLACE "^v([0-9]+)\\.([0-9]+)\\.([0-9]+).*$" "\\1;\\2;\\3" _tmp
                     "${CKD_VERSION_DESCRIBE}")
set(_tmp ${_tmp})
list(GET _tmp 0 _major)
list(GET _tmp 1 _minor)
list(GET _tmp 2 _patch)
math(EXPR CKD_VERSION "${_major}*256*256+${_minor}*256+${_patch}"
     OUTPUT_FORMAT HEXADECIMAL)

# ##############################################################################

if(CKD_DEV)
  include(CTest)
  set(CMAKE_EXPORT_COMPILE_COMMANDS 1)
  set(BUILD_TESTING 1)
  set(CKD_BUILD_TESTING 1)
  find_program(BASH bash)
  if(BASH AND NOT CMAKE_C_COMPILER_LAUNCHER)
    set(CMAKE_C_COMPILER_LAUNCHER
        ${CMAKE_CURRENT_SOURCE_DIR}/scripts/measure.sh)
  endif()
  execute_process(
    COMMAND
      ${CMAKE_COMMAND} -E create_symlink
      ${CMAKE_CURRENT_BINARY_DIR}/compile_commands.json
      ${CMAKE_CURRENT_SOURCE_DIR}/compile_commands.json)
  execute_process(
    COMMAND ${CMAKE_COMMAND} -E create_symlink
            ${CMAKE_CURRENT_BINARY_DIR}/include ${CMAKE_CURRENT_SOURCE_DIR}/gen)
  if(CMAKE_C_COMPILER_ID STREQUAL "GNU")
    add_compile_options(-Wall -Wextra -Wwrite-strings -Werror=all
                        -Wfatal-errors)
    if(NOT CKD_COVERAGE AND NOT CKD_NOSANITIZE)
      set(_sanitize
          -fsanitize=undefined,address,pointer-compare,pointer-subtract)
      add_compile_options(${_sanitize})
      add_link_options(${_sanitize})
    endif()
  endif()
  if(CMAKE_C_COMPILER_ID STREQUAL "Clang")
    add_link_options(
      # compiler-rt provides symbols for __builtin_*_overflow for clang
      -rtlib=compiler-rt)
  endif()
  if(CKD_COVERAGE)
    add_compile_definitions(CKD_COVERAGE=1)
    add_compile_options(-Werror -Werror=overflow -O0 -g -fprofile-arcs
                        -ftest-coverage)
    link_libraries(gcov)
  endif()
  if(CKD_DOXYGEN)
    find_package(Doxygen REQUIRED dot OPTIONAL_COMPONENTS mscgen dia)
    set(_cfg
        GENERATE_HTML=YES
        HTML_OUTPUT=${CMAKE_CURRENT_SOURCE_DIR}/public
        ENABLE_PREPROCESSING=YES
        MACRO_EXPANSION=YES
        "PREDEFINED=\"CKD_DOXYGEN=1\""
        QUIET=YES
        WARN_IF_UNDOCUMENTED=NO
        WARN_AS_ERROR=YES
        PROJECT_NUMBER=${CKD_VERSION_DESCRIBE}
        "PROJECT_BRIEF=Implementation of C23 stdckdint.h"
        USE_MDFILE_AS_MAINPAGE=${CMAKE_CURRENT_SOURCE_DIR}/README.md
        #
    )
    foreach(ii IN LISTS _cfg)
      string(REGEX REPLACE "^([^=]*)=(.*)$" "\\1;\\2" ii "${ii}")
      set(DOXYGEN_${ii})
    endforeach()
    doxygen_add_docs(
      doxygen ${CMAKE_CURRENT_BINARY_DIR}/include
      ${CMAKE_CURRENT_SOURCE_DIR}/README.md
      ${CMAKE_CURRENT_SOURCE_DIR}/LICENSE.md
      WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/include)
    add_dependencies(doxygen ckdint_gen)
  endif()
endif()

# ##############################################################################

check_type_size("__int128" UINT128 BUILTIN_TYPES_ONLY LANGUAGE C)
if(HAVE_UINT128)
  set(HAVE_UINT128 1)
else()
  set(HAVE_UINT128 0)
endif()

find_program(Python_EXECUTABLE NAMES python3 python REQUIRED)

# ##############################################################################

file(MAKE_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/include)
file(MAKE_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/include/ckdint)
set(_generated)
foreach(file IN ITEMS ckdint.h ckdint/ckdint_nognu.h ckdint/ckdint_gnu.h)
  add_custom_command(
    OUTPUT ${CMAKE_CURRENT_BINARY_DIR}/include/${file}
    DEPENDS ${CMAKE_CURRENT_SOURCE_DIR}/src/script.py
            ${CMAKE_CURRENT_SOURCE_DIR}/src/library.jinja
            ${CMAKE_CURRENT_SOURCE_DIR}/src/${file}
    COMMAND
      ${Python_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/src/script.py ${file}
      ${CMAKE_CURRENT_BINARY_DIR}/include/${file} "HAVE_UINT128=${HAVE_UINT128}"
      "CKD_VERSION_DESCRIBE=${CKD_VERSION_DESCRIBE}"
      "CKD_VERSION=${CKD_VERSION}"
    COMMENT "Generate ${file}"
    VERBATIM)
  list(APPEND _generated ${CMAKE_CURRENT_BINARY_DIR}/include/${file})
endforeach()

add_custom_target(
  ckdint_gen
  DEPENDS ${_generated}
  COMMENT "Generated ${PROJECT_NAME} header files")

add_library(${PROJECT_NAME} INTERFACE)
add_dependencies(${PROJECT_NAME} ckdint_gen)
target_include_directories(
  ${PROJECT_NAME}
  INTERFACE $<BUILD_INTERFACE:${CMAKE_CURRENT_BINARY_DIR}/include>)

# ##############################################################################

if(CKD_INSTALL)
  install(
    DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/include
    DESTINATION include
    FILES_MATCHING
    PATTERN *.h)
endif()

# ##############################################################################

if(BUILD_TESTING AND CKD_BUILD_TESTING)
  file(
    GLOB tests
    RELATIVE ${CMAKE_CURRENT_SOURCE_DIR}/tests
    ./tests/*.c)
  foreach(test IN LISTS tests)
    string(REGEX REPLACE "\\.c" "" _filename ${test})
    set(_name ${PROJECT_NAME}_${_filename}_gnu)
    add_executable(${_name} tests/${test})
    target_compile_definitions(${_name} PUBLIC HAVE_UINT128=${HAVE_UINT128})
    target_link_libraries(${_name} PUBLIC ${PROJECT_NAME})
    add_test(NAME ${_name} COMMAND ${_name})
    set_tests_properties(${_name} PROPERTIES LABEL ${PROJECT_NAME})

    set(_name ${PROJECT_NAME}_${_filename}_nognu)
    add_executable(${_name} tests/${test})
    target_compile_definitions(${_name} PUBLIC HAVE_UINT128=${HAVE_UINT128})
    target_link_libraries(${_name} PUBLIC ${PROJECT_NAME})
    target_compile_definitions(${_name} PUBLIC CKD_NOGNU_SOURCE=1)
    add_test(NAME ${_name} COMMAND ${_name})
    set_tests_properties(${_name} PROPERTIES LABEL ${PROJECT_NAME})
  endforeach()
endif()
