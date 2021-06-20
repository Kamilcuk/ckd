cmake_minimum_required(VERSION 3.11)

if(CKD_DEV)
	set(CMAKE_EXPORT_COMPILE_COMMANDS 1)
	execute_process(
		COMMAND ${CMAKE_COMMAND} -E create_symlink ${CMAKE_CURRENT_BINARY_DIR}/compile_commands.json ${CMAKE_SOURCE_DIR}/compile_commands.json
	)
endif()

project(ckd LANGUAGES C)

add_custom_command(
	OUTPUT ${CMAKE_CURRENT_BINARY_DIR}/include/ckdint.h
	DEPENDS ${CMAKE_CURRENT_SOURCE_DIR}/src/ckdint.h.py
	COMMAND ${CMAKE_COMMAND} -E make_directory ${CMAKE_CURRENT_BINARY_DIR}/include
	COMMAND
		${CMAKE_CURRENT_SOURCE_DIR}/src/ckdint.h.py 
		${CMAKE_CURRENT_BINARY_DIR}/include/ckdint.h
)
add_custom_target(ckdint.h DEPENDS ${CMAKE_CURRENT_BINARY_DIR}/include/ckdint.h)
add_library(${PROJECT_NAME} INTERFACE
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
	endforeach()
endif()

