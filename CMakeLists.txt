cmake_minimum_required(VERSION 3.11)
project(ckd LANGUAGES C)

include(CheckTypeSize)
include(CTest)

if(CKD_DEV)
	set(CMAKE_EXPORT_COMPILE_COMMANDS 1)
  set(BUILD_TESTING 1)
	execute_process(
		COMMAND ${CMAKE_COMMAND} -E create_symlink
      ${CMAKE_CURRENT_BINARY_DIR}/compile_commands.json
      ${CMAKE_SOURCE_DIR}/compile_commands.json
	)
  if(CMAKE_C_COMPILER_ID MATCHES "GNU")
    add_compile_options(
      -Wall -Wextra
    )
  endif()
endif()

###############################################################################

check_type_size("__int128" UINT128 BUILTIN_TYPES_ONLY LANGUAGE C)
if (HAVE_UINT128)
	set(HAVE_UINT128 1)
else()
	set(HAVE_UINT128 0)
endif()

find_program(Python_EXECUTABLE NAMES python3 python2 python REQUIRED)

###############################################################################

file(MAKE_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/include)
file(MAKE_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/include/ckdint)
set(generated)
foreach(ii IN ITEMS ckdint.h ckdint/ckdint_nognu.h ckdint/ckdint_gnu.h)
  add_custom_command(
    OUTPUT
      ${CMAKE_CURRENT_BINARY_DIR}/include/${ii}
    DEPENDS
      ${CMAKE_CURRENT_SOURCE_DIR}/src/script.py
      ${CMAKE_CURRENT_SOURCE_DIR}/src/library.jinja
      ${CMAKE_CURRENT_SOURCE_DIR}/src/${ii}
    COMMAND
      ${Python_EXECUTABLE}
      ${CMAKE_CURRENT_SOURCE_DIR}/src/script.py
      ${ii}
      "${HAVE_UINT128}"
      ${CMAKE_CURRENT_BINARY_DIR}/include/${ii}
    COMMENT "Generate ${ii}"
  )
  list(APPEND generated
    ${CMAKE_CURRENT_BINARY_DIR}/include/${ii}
  )
endforeach()

add_custom_target(ckdint_gen
  DEPENDS ${generated}
  COMMENT "Generated ${PROJECT_NAME} header file"
)
add_library(${PROJECT_NAME} INTERFACE)
add_dependencies(${PROJECT_NAME} ckdint_gen)
target_sources(${PROJECT_NAME} INTERFACE ${generated})
target_include_directories(${PROJECT_NAME} INTERFACE
  $<BUILD_INTERFACE:${CMAKE_CURRENT_BINARY_DIR}/include>
)
set_target_properties(${PROJECT_NAME} PROPERTIES
  LINKER_LANGUAGE C
  C_EXTENSIONS NO
  C_STANDARD 11
  C_STANDARD_REQUIRED NO
)
target_compile_features(${PROJECT_NAME} INTERFACE
  c_std_11
  c_function_prototypes
  c_static_assert
  c_variadic_macros
)

###############################################################################

install(FILES
		${CMAKE_CURRENT_BINARY_DIR}/include/ckdint.h
	DESTINATION include
)

###############################################################################

if(BUILD_TESTING)
	file(GLOB tests RELATIVE ${CMAKE_CURRENT_SOURCE_DIR}/tests tests/*.c)
	foreach(tt IN LISTS tests)
    string(REGEX REPLACE "\.c" "" _nn ${tt})
    set(_nn ${PROJECT_NAME}_${_nn})
    add_executable(${_nn} tests/${tt})
    target_link_libraries(${_nn} PUBLIC ${PROJECT_NAME})
    add_test(NAME ${_nn} COMMAND ${_nn})
    set_tests_properties(${_nn} PROPERTIES
      LABEL ${PROJECT_NAME}
    )

    set(_nn ${PROJECT_NAME}_${_nn}_nognu)
    add_executable(${_nn} tests/${tt})
    target_link_libraries(${_nn} PUBLIC ${PROJECT_NAME})
    target_compile_definitions(${_nn} PUBLIC CKD_USE_NOGNU)
    add_test(NAME ${_nn} COMMAND ${_nn})
    set_tests_properties(${_nn} PROPERTIES
      LABEL ${PROJECT_NAME}
    )
	endforeach()
endif()

