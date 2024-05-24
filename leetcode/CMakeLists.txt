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
add_test(NAME test_maximize_happiness COMMAND leetcode_3075_maximize_happiness)

# 857_min_cost_to_hire
add_executable(leetcode_857_min_cost_to_hire cpp/857_min_cost_to_hire.cpp)
target_link_libraries(leetcode_857_min_cost_to_hire PRIVATE common gtest gtest_main)
target_include_directories(leetcode_857_min_cost_to_hire PRIVATE ../common ${gtest_SOURCE_DIR}/include)
add_test(NAME test_857_min_cost_to_hire COMMAND leetcode_857_min_cost_to_hire)
