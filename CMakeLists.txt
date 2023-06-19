cmake_minimum_required(VERSION 3.21)
project(maple VERSION 0.1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
if (MSVC)
    set(CMAKE_WINDOWS_EXPORT_ALL_SYMBOLS ON)
endif()
set(MAPLE_VERSION ${PROJECT_VERSION})
set(MAPLE_SUPER_SOURCE_DIR ${CMAKE_SOURCE_DIR})

option(MAPLE_BUILD_EXAMPLES "Build the mapleUI example programs" ON)

add_subdirectory(engine)
add_subdirectory(math)

if (MAPLE_BUILD_EXAMPLES)
    add_subdirectory(examples)
endif()
