cmake_minimum_required(VERSION 3.10)

project(Bench)

add_executable(Bench main.cpp bench-ninja.cpp bench-normal.cpp bench-free.cpp)

find_package(benchmark REQUIRED)

target_link_libraries(Bench Completer benchmark pthread)

target_include_directories(Bench PUBLIC "../include")
