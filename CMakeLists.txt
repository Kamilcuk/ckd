cmake_minimum_required(VERSION 3.11)

if(CKD_DEV)
	set(CMAKE_EXPORT_COMPILE_COMMANDS 1)
	execute_process(
		COMMAND ${CMAKE_COMMAND} -E create_symlink ${CMAKE_CURRENT_BINARY_DIR}/compile_commands.json ${CMAKE_SOURCE_DIR}/compile_commands.json
	)
endif()

project(ckd LANGUAGES C)

include(CheckTypeSize)
check_type_size("__int128" UINT128 BUILTIN_TYPES_ONLY LANGUAGE C)
if (HAVE_UINT128)
	set(HAVE_UINT128 1)
else()
	set(HAVE_UINT128 0)
endif()

find_program(Python_EXECUTABLE NAMES python3 python2 python REQUIRED)

add_custom_command(
  OUTPUT ${CMAKE_CURRENT_BINARY_DIR}/include/ckdint${suff}.h
  DEPENDS ${CMAKE_CURRENT_SOURCE_DIR}/src/ckdint.h.py
  COMMAND
    ${Python_EXECUTABLE}
    ${CMAKE_CURRENT_SOURCE_DIR}/src/ckdint.h.py
    "${HAVE_UINT128}"
    ${CMAKE_CURRENT_BINARY_DIR}/include/ckdint${suff}.h
)
add_library(${PROJECT_NAME} INTERFACE)
target_sources(${PROJECT_NAME} INTERFACE
	${CMAKE_CURRENT_BINARY_DIR}/include/ckdint.h
)
target_include_directories(${PROJECT_NAME} INTERFACE
	${CMAKE_CURRENT_BINARY_DIR}/include
)

include(CTest)
if(BUILD_TESTING)
	file(GLOB tests RELATIVE ${CMAKE_CURRENT_SOURCE_DIR}/tests tests/*.c)
	foreach(t IN LISTS tests)
    set(n ${PROJECT_NAME}_${t})
    add_executable(${n} tests/${t})
    target_link_libraries(${n} PUBLIC ${PROJECT_NAME})
    add_test(NAME ${n} COMMAND ${n})

    set(n ${PROJECT_NAME}_nongnu_${t})
    add_executable(${n} tests/${t})
    target_link_libraries(${n} PUBLIC ${PROJECT_NAME})
    target_compile_definitions(${n} PUBLIC CKD_DO_NOT_USE_BUILTINS=1)
    add_test(NAME ${n} COMMAND ${n})
	endforeach()
endif()

install(FILES
		${CMAKE_CURRENT_BINARY_DIR}/include/ckdint.h
	DESTINATION include
)

