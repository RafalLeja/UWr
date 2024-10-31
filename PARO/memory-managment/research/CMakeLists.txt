cmake_minimum_required(VERSION 3.18)
project(memory-management-research LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED YES)

find_package(GTest)
if(NOT GTest_FOUND)
    message("Cannot find Google Test Framework!")
endif()

enable_testing()

add_subdirectory(buddy_logger)
add_subdirectory(buddy_allocation)

add_executable(buddy main.cpp)
target_link_libraries(buddy PRIVATE buddy-allocation)
