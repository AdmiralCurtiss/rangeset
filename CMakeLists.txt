cmake_minimum_required(VERSION 3.15)

project(rangeset LANGUAGES C CXX)

enable_testing()
find_package(GTest REQUIRED)

add_executable(test_rangeset
 "rangeset.h"
 "test_insert.cpp"
 "test_iterate.cpp"
 "test_erase.cpp"
)

target_link_libraries(
 test_rangeset
 PUBLIC GTest::GTest GTest::Main
)
