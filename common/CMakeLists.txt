cmake_minimum_required(VERSION 3.10)
project(CommonLib)

add_library(common STATIC Utilities.cpp Utilities.h)

target_include_directories(common PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})