cmake_minimum_required(VERSION 3.10)

project(UnitTests)

add_executable(UnitTests test1.cpp)

target_link_libraries(UnitTests Completer GTest::GTest GTest::Main)

target_include_directories(UnitTests PUBLIC "../include")

gtest_discover_tests(UnitTests)
