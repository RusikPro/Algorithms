cmake_minimum_required(VERSION 3.10)
project(leetcode)

# Main executable
add_executable(leetcode_main cpp/main.cpp)
target_link_libraries(leetcode_main PRIVATE common)
target_include_directories(leetcode_main PRIVATE ../common)

# Exercises executable
add_executable(leetcode_exercises cpp/exercises.cpp)
target_link_libraries(leetcode_exercises PRIVATE common)
target_include_directories(leetcode_exercises PRIVATE ../common)

# 3075_maximize_happiness
add_executable(leetcode_3075_maximize_happiness cpp/3075_maximize_happiness.cpp)
target_link_libraries(leetcode_3075_maximize_happiness PRIVATE common gtest gtest_main)
target_include_directories(leetcode_3075_maximize_happiness PRIVATE ../common ${gtest_SOURCE_DIR}/include)

# Add test for 3075_maximize_happiness
add_test(NAME test_maximize_happiness COMMAND leetcode_3075_maximize_happiness)