cmake_minimum_required(VERSION 3.10)
project(try_outs)

# Main executable
add_executable(try_outs_main cpp/main.cpp)
target_link_libraries(try_outs_main PRIVATE common)
target_include_directories(try_outs_main PRIVATE ../common)

add_executable(try_outs_exercise exercises/exercise.cpp)
target_link_libraries(try_outs_exercise PRIVATE common)
target_include_directories(try_outs_exercise PRIVATE ../common)

# Added executable cpp_bfs_path_find
add_executable(try_outs_bfs_path_find cpp/bfs_path_find.cpp)
target_link_libraries(try_outs_bfs_path_find PRIVATE common)  # Assuming linkage to 'common' library
target_include_directories(try_outs_bfs_path_find PRIVATE ../common)
