cmake_minimum_required(VERSION 3.10)
project(fintech)

# Main executable
add_executable(fintech_main cpp/main.cpp)
target_link_libraries(fintech_main PRIVATE common)
target_include_directories(fintech_main PRIVATE ../common)

# Exercises executable
add_executable(fintech_exercises cpp/exercises.cpp)
target_link_libraries(fintech_exercises PRIVATE common)
target_include_directories(fintech_exercises PRIVATE ../common)

# Circular trade processor
add_executable(
    fintech_circular_trade_processor cpp/circular_trade_processor.cpp
)
target_link_libraries(fintech_circular_trade_processor PRIVATE common)
target_include_directories(fintech_circular_trade_processor PRIVATE ../common)

# Trade processor
add_executable(
    fintech_circular_bucket_queue_test cpp/circular_bucket_queue_test.cpp
)
target_link_libraries(fintech_circular_bucket_queue_test PRIVATE common)
target_include_directories(fintech_circular_bucket_queue_test PRIVATE ../common)

# Market Making
add_executable(
    fintech_market_making cpp/market_making.cpp
)
target_link_libraries(fintech_market_making PRIVATE common)
target_include_directories(fintech_market_making PRIVATE ../common)
