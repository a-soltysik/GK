cmake_minimum_required(VERSION 3.14)

project(GK VERSION 0.1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)

if (CMAKE_CXX_COMPILER_ID STREQUAL "MSVC")
    set(COMPILER_REL_CXX_FLAGS "/O2 /MD")
elseif (CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -Wpessimizing-move -Wredundant-move -pedantic -Wconversion")
    set(COMPILER_REL_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O3 -static")
endif ()

set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} ${CMAKE_CXX_FLAGS}")
set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} ${COMPILER_REL_CXX_FLAGS}")

set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)

add_subdirectory(ext/glfw)

include_directories(ext/glfw/include utils)
link_directories(ext/glfw/src)
link_libraries(glfw)

find_package(OpenGL REQUIRED)
link_libraries(OpenGL::GL)

file(GLOB_RECURSE UTILS_SRC_LIST
    utils/*.h
    utils/*.cpp
    )

add_subdirectory(lab2)
add_subdirectory(lab3)

