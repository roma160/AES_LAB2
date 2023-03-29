cmake_minimum_required(VERSION 3.15)
project(LAB2_AES VERSION 1.0 LANGUAGES CXX)
set(CMAKE_CXX_STANDARD 14)

file("GLOB_RECURSE" "SOURCE_FILES" "src/*.cpp")
add_executable(main LAB2.cpp "include/bitmem.h" ${SOURCE_FILES})
target_include_directories(main PUBLIC "./include")

if(UNIX)
	target_link_libraries(main ncurses)
endif(UNIX)



# https://stackoverflow.com/questions/14474659/cmake-how-to-have-a-target-for-copying-files
# https://stackoverflow.com/questions/42476765/copying-assets-directory-from-source-to-build-directory-in-cmake\
# https://cmake.org/cmake/help/latest/manual/cmake.1.html#cmdoption-cmake-E-arg-copy_if_different
add_custom_target(
	copy
	COMMAND ${CMAKE_COMMAND} -E copy_if_different "${CMAKE_SOURCE_DIR}/program.txt" "${CMAKE_BINARY_DIR}"
	COMMENT "Copying program.txt to a build directory: ${CMAKE_BINARY_DIR}"
)
add_dependencies(main copy)