cmake_minimum_required(VERSION 3.10)

project(Sample)

add_executable(Sample sample.cpp)

target_link_libraries(Sample Completer)

target_include_directories(Sample PUBLIC "../include")
