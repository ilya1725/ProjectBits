cmake_minimum_required(VERSION 3.16)

project (ProjectBits)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

enable_testing()

add_subdirectory(cmake EXCLUDE_FROM_ALL)

add_subdirectory(tlgr)
add_subdirectory(gtest)
