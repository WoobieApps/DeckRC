cmake_minimum_required(VERSION 3.24)
project(DeckRC LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Use pkg-config
find_package(PkgConfig REQUIRED)

# SDL2
pkg_check_modules(SDL2 REQUIRED sdl2)
include_directories(${SDL2_INCLUDE_DIRS})
link_directories(${SDL2_LIBRARY_DIRS})

include_directories(${CMAKE_SOURCE_DIR}/inc)
add_subdirectory(${CMAKE_SOURCE_DIR}/src)