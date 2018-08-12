cmake_minimum_required(VERSION 3.10)

project(Completer)

find_package(GTest REQUIRED)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_library(Completer SHARED src/completer.cpp)

target_include_directories(Completer PRIVATE "include")

enable_testing()

add_subdirectory(tests/)
add_subdirectory(bench/)
add_subdirectory(sample/)
