# Main CMakeLists.txt for C++ Algorithms Project
cmake_minimum_required(VERSION 3.16)
project(CPP_Algorithms)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Compiler flags
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fcolor-diagnostics -fansi-escape-codes -g")

# Find packages
find_package(PkgConfig QUIET)

# Try to find Google Test
find_package(GTest QUIET)
if(NOT GTest_FOUND)
    # If not found, try to fetch it
    include(FetchContent)
    FetchContent_Declare(
        googletest
        URL https://github.com/google/googletest/archive/03597a01ee50ed33e9fd7188aa9dc84d7ec74ee6.zip
    )
    FetchContent_MakeAvailable(googletest)
    set(GTEST_LIBRARIES gtest gtest_main)
else()
    set(GTEST_LIBRARIES GTest::gtest GTest::gtest_main)
endif()

# Try to find Google Benchmark
find_package(benchmark QUIET)
if(NOT benchmark_FOUND)
    FetchContent_Declare(
        googlebenchmark
        URL https://github.com/google/benchmark/archive/v1.8.3.zip
    )
    FetchContent_MakeAvailable(googlebenchmark)
    set(BENCHMARK_LIBRARIES benchmark::benchmark)
else()
    set(BENCHMARK_LIBRARIES benchmark::benchmark)
endif()

# Include common headers
include_directories(${CMAKE_SOURCE_DIR}/common)

# Function to create executable from single cpp file
function(create_simple_executable target_name source_file)
    get_filename_component(target_dir ${source_file} DIRECTORY)
    get_filename_component(target_name_base ${source_file} NAME_WE)

    add_executable(${target_name} ${source_file})

    # Set output directory and add .out extension
    set_target_properties(${target_name} PROPERTIES
        RUNTIME_OUTPUT_DIRECTORY ${target_dir}
        OUTPUT_NAME "${target_name_base}.out"
    )

    # Link common utilities if they exist
    if(EXISTS ${CMAKE_SOURCE_DIR}/common/utilities.cpp)
        target_sources(${target_name} PRIVATE ${CMAKE_SOURCE_DIR}/common/utilities.cpp)
    endif()
endfunction()

# Function to create executable with Google Test
function(create_gtest_executable target_name source_file)
    get_filename_component(target_dir ${source_file} DIRECTORY)
    get_filename_component(target_name_base ${source_file} NAME_WE)

    add_executable(${target_name} ${source_file})
    target_link_libraries(${target_name} ${GTEST_LIBRARIES})

    set_target_properties(${target_name} PROPERTIES
        RUNTIME_OUTPUT_DIRECTORY ${target_dir}
        OUTPUT_NAME "${target_name_base}.out"
    )

    if(EXISTS ${CMAKE_SOURCE_DIR}/common/utilities.cpp)
        target_sources(${target_name} PRIVATE ${CMAKE_SOURCE_DIR}/common/utilities.cpp)
    endif()
endfunction()

# Function to create executable with Google Benchmark
function(create_benchmark_executable target_name source_file)
    get_filename_component(target_dir ${source_file} DIRECTORY)
    get_filename_component(target_name_base ${source_file} NAME_WE)

    add_executable(${target_name} ${source_file})
    target_link_libraries(${target_name} ${BENCHMARK_LIBRARIES})

    set_target_properties(${target_name} PROPERTIES
        RUNTIME_OUTPUT_DIRECTORY ${target_dir}
        OUTPUT_NAME "${target_name_base}.out"
    )

    if(EXISTS ${CMAKE_SOURCE_DIR}/common/utilities.cpp)
        target_sources(${target_name} PRIVATE ${CMAKE_SOURCE_DIR}/common/utilities.cpp)
    endif()
endfunction()# Auto-discover and create targets for all cpp files
file(GLOB_RECURSE ALL_CPP_FILES "*.cpp")

foreach(cpp_file ${ALL_CPP_FILES})
    # Skip files in build directories
    string(FIND ${cpp_file} "/build/" build_pos)
    if(build_pos GREATER -1)
        continue()
    endif()

    get_filename_component(file_name ${cpp_file} NAME_WE)
    get_filename_component(file_dir ${cpp_file} DIRECTORY)

    # Create relative path for target name
    file(RELATIVE_PATH rel_path ${CMAKE_SOURCE_DIR} ${cpp_file})
    string(REPLACE "/" "_" target_name ${rel_path})
    string(REPLACE ".cpp" "" target_name ${target_name})

    # Read first few lines to detect dependencies
    file(READ ${cpp_file} file_content)

    # Check for Google Test usage
    string(FIND "${file_content}" "gtest" gtest_pos)
    string(FIND "${file_content}" "TEST(" test_pos)
    string(FIND "${file_content}" "testing::" testing_pos)

    # Check for Google Benchmark usage
    string(FIND "${file_content}" "benchmark" benchmark_pos)
    string(FIND "${file_content}" "BENCHMARK(" benchmark_macro_pos)

    if(gtest_pos GREATER -1 OR test_pos GREATER -1 OR testing_pos GREATER -1)
        create_gtest_executable(${target_name} ${cpp_file})
        message(STATUS "Created GTest target: ${target_name}")
    elseif(benchmark_pos GREATER -1 OR benchmark_macro_pos GREATER -1)
        create_benchmark_executable(${target_name} ${cpp_file})
        message(STATUS "Created Benchmark target: ${target_name}")
    else()
        create_simple_executable(${target_name} ${cpp_file})
        message(STATUS "Created simple target: ${target_name}")
    endif()
endforeach()
