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

include_directories(utils)

file(GLOB_RECURSE UTILS_SRC_LIST
    utils/*.h
    utils/*.cpp
    )

include_directories(gfx)

file(GLOB_RECURSE GFX_SRC_LIST
    gfx/*.h
    gfx/*.cpp
    )

add_subdirectory(lab2)
add_subdirectory(lab3)
add_subdirectory(lab4)
add_subdirectory(lab5)
add_subdirectory(lab6)
