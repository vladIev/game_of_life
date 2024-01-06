cmake_minimum_required(VERSION 3.20)
project(life VERSION 0.1.0)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_PREFIX_PATH build)

add_compile_options("-std=c++20")

include(CTest)
include("${CMAKE_SOURCE_DIR}/cmake/cmake_utils.cmake")
enable_testing()

find_package(fmt REQUIRED)
find_package(spdlog REQUIRED)
find_package(GTest REQUIRED) 
find_package(magic_enum REQUIRED)

include_directories(${fmt_INCLUDE_DIRS})
include_directories(${spdlog_INCLUDE_DIR})
include_directories(${GTest_INCLUDE_DIRS})
include_directories(${magic_enum_INCLUDE_DIR})

add_subdirectory(src)
