cmake_minimum_required(VERSION 3.18.0)
project(uebung_9 VERSION 0.1.0)

cmake_policy(SET CMP0072 NEW)
find_package(OpenGL REQUIRED)

set(dirs											# dirs to compile
	src
	include
)

set(COMPILE_SOURCES)					# files from dirs put into COMPILE_SOURCES

foreach(dir ${dirs})
	file(GLOB_RECURSE sources  "${dir}/*.cpp" "${dir}/*.c")
	list(APPEND COMPILE_SOURCES ${sources})
endforeach()

add_executable(${PROJECT_NAME}
	${COMPILE_SOURCES}
)

target_link_libraries(${PROJECT_NAME}
	glfw
	OpenGL::GL
)
target_include_directories(${PROJECT_NAME} PRIVATE include)