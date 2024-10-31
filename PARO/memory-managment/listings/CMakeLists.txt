cmake_minimum_required(VERSION 3.18)
project(memory-management-listings LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED YES)
add_compile_options(-Wall -Wextra -Wpedantic -Wno-unused-parameter)

add_subdirectory(paro)

enable_testing()

# CHAPTER 1: ALLOCATIONS
add_subdirectory(allocations)

# CHAPTER 2: FUNCTIONS AND EXCEPTIONS
add_subdirectory(functions)

# CHAPTER 3: RAII
add_subdirectory(raii)

# CHAPTER 4 - SHARED PTR + WEAK PTR
add_subdirectory(shared_ptr)

# CHAPTER 5 - RULE OF ZERO/THREE/FIVE
add_subdirectory(ruleofzero)

# CHAPTER 6 - BENCHMARKS
add_subdirectory(benchmarks)
