cmake_minimum_required(VERSION 4.2)
project(l-engine LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

file(GLOB_RECURSE SOURCES CONFIGURE_DEPENDS "${CMAKE_SOURCE_DIR}/*.cpp")
list(FILTER SOURCES EXCLUDE REGEX "/(build|cmake-build[^/]*)/")

add_executable(l-engine ${SOURCES})
target_include_directories(l-engine PRIVATE ${CMAKE_SOURCE_DIR})