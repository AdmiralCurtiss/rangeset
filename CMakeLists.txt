cmake_minimum_required(VERSION 3.15)

project(rangeset LANGUAGES C CXX)

enable_testing()
find_package(GTest REQUIRED)

add_executable(test_rangeset
 "rangeset.h"
 "test_insert.cpp"
 "test_iterate.cpp"
 "test_erase.cpp"
 "test_contains.cpp"
 "test_insert_size.cpp"
 "test_iterate_size.cpp"
 "test_erase_size.cpp"
 "test_contains_size.cpp"
 "test_types_size.cpp"
 "test_lookup_size.cpp"
 "test_swap.cpp"
 "test_swap_size.cpp"
)

target_link_libraries(
 test_rangeset
 PUBLIC GTest::GTest GTest::Main
)

target_compile_features(
 test_rangeset
 PRIVATE cxx_std_17
)
